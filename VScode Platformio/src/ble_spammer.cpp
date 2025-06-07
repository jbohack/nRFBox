/* ____________________________
   This software is licensed under the MIT License:
   https://github.com/jbohack/nyanBOX
   ________________________________________ */
      
#include "../include/pindefs.h"
#include "ble_spammer.h"
#include <U8g2lib.h>
#include <Arduino.h>
#include <BLEDevice.h>
#include <esp_gap_ble_api.h>
#include <string.h>
    
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    
bool isBleSpamming = false;
static uint8_t mode = 3; // 0=Custom, 1=Random ASCII, 2=Random Emoji, 3=All

// BLE advertising parameters (non-connectable)
static esp_ble_adv_params_t adv_params = {
    .adv_int_min = 0x20,
    .adv_int_max = 0x40,
    .adv_type = ADV_TYPE_NONCONN_IND,
    .own_addr_type = BLE_ADDR_TYPE_RANDOM,
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY
};
    
// NyanBOX Custom Names
static const char* customNames[] = {
    "zr_crackin was here",
    "jbohack was here",
    "defcon.lullaby.cafe",
    "Sub2TalkingSasquach",
    "nyanBOX",
    "Crypto Wallet",
    "Toaster",
    "ATM Machine",
    "OnlyFans Portal",
    "FeetFinder Portal",
    "Garbage Can",
    "FBI Surveillance Van",
    "Toilet",
    "Listening Device",
    "Bathroom Camera",
    "Rickroll",
    "Ejection Seat",
    "Dark Web Access Point",
    "Time Machine",
    "👉👌",
    "hi ;)"
};
static const uint8_t customNamesCount = sizeof(customNames) / sizeof(customNames[0]);
    
static const uint32_t emojiRanges[][2] = {
    { 0x1F600, 0x1F64F },
    { 0x1F300, 0x1F5FF },
    { 0x1F680, 0x1F6FF },
    { 0x2600, 0x26FF },
    { 0x2700, 0x27BF },
    { 0x1F1E6, 0x1F1FF }
};
static const uint8_t emojiRangeCount = sizeof(emojiRanges) / sizeof(emojiRanges[0]);
    
static const uint8_t minNameLen = 3;
static const uint8_t maxNameLen = 10;
static const uint16_t nameBufSize = maxNameLen * 4 + 1;
    
static uint8_t utf8_encode(uint32_t cp, char *out) {
    if (cp <= 0x7F) {
        out[0] = cp; return 1;
    } else if (cp <= 0x7FF) {
        out[0] = 0xC0 | ((cp >> 6) & 0x1F);
        out[1] = 0x80 | (cp & 0x3F);
        return 2;
    } else if (cp <= 0xFFFF) {
        out[0] = 0xE0 | ((cp >> 12) & 0x0F);
        out[1] = 0x80 | ((cp >> 6) & 0x3F);
        out[2] = 0x80 | (cp & 0x3F);
        return 3;
    } else if (cp <= 0x10FFFF) {
        out[0] = 0xF0 | ((cp >> 18) & 0x07);
        out[1] = 0x80 | ((cp >> 12) & 0x3F);
        out[2] = 0x80 | ((cp >> 6) & 0x3F);
        out[3] = 0x80 | (cp & 0x3F);
        return 4;
    }
    return 0;
}
    
static void generateRandomAlphaName(char* buf, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        buf[i] = 'A' + random(26);
    }
    buf[length] = '\0';
}

static void generateRandomEmojiName(char* buf) {
    uint8_t count = random(minNameLen, maxNameLen + 1);
    uint16_t pos = 0;
    for (uint8_t i = 0; i < count; i++) {
        uint8_t ri = random(emojiRangeCount);
        uint32_t start = emojiRanges[ri][0];
        uint32_t end = emojiRanges[ri][1];
        uint32_t cp = random(start, end + 1);
        char utf8[4];
        uint8_t len = utf8_encode(cp, utf8);
        if (pos + len < nameBufSize) {
            memcpy(&buf[pos], utf8, len);
            pos += len;
        }
    }
    buf[pos] = '\0';
}

static void generateRandomMixedName(char* buf) {
    uint8_t glyphs = random(minNameLen, maxNameLen + 1);
    uint16_t pos = 0;
    for (uint8_t i = 0; i < glyphs; i++) {
        if (random(2) == 0) {
            if (pos + 1 < nameBufSize) {
                buf[pos++] = 'A' + random(26);
            }
        } else {
            uint8_t ri = random(emojiRangeCount);
            uint32_t start = emojiRanges[ri][0];
            uint32_t end = emojiRanges[ri][1];
            uint32_t cp = random(start, end + 1);
            char utf8[4];
            uint8_t len = utf8_encode(cp, utf8);
            if (pos + len < nameBufSize) {
                memcpy(&buf[pos], utf8, len);
                pos += len;
            }
        }
    }
    buf[pos] = '\0';
}
    
static const char* pickName(char* buf) {
    if (mode == 0 && customNamesCount > 0) {
        return customNames[random(customNamesCount)];
    }
    if (mode == 1) {
        uint8_t len = random(minNameLen, maxNameLen + 1);
        generateRandomAlphaName(buf, len);
    } else {
        generateRandomEmojiName(buf);
    }
    return buf;
}
    
// Packet structure for each advertisement
typedef uint8_t* PacketPtr;
static void make_packet(const char* name, uint8_t* size, PacketPtr* packet) {
    uint8_t name_len = strlen(name);
    uint8_t total = 12 + name_len;
    *packet = (uint8_t*)malloc(total);
    uint8_t i = 0;
    // Flags
    (*packet)[i++] = 2;
    (*packet)[i++] = 0x01;
    (*packet)[i++] = 0x06;
    // Complete Local Name
    (*packet)[i++] = name_len + 1;
    (*packet)[i++] = 0x09;
    memcpy(&(*packet)[i], name, name_len);
    i += name_len;
    // Service UUID List (HID)
    (*packet)[i++] = 3;
    (*packet)[i++] = 0x02;
    (*packet)[i++] = 0x12;
    (*packet)[i++] = 0x18;
    // Tx Power Level
    (*packet)[i++] = 2;
    (*packet)[i++] = 0x0A;
    (*packet)[i++] = 0x00;
    *size = total;
}
    
static void advertiseDevice(const char* chosenName) {
    esp_ble_gap_stop_advertising();
    delay(5);
    esp_bd_addr_t randAddr;
    for (int i = 0; i < 6; i++) randAddr[i] = random(0,256);
    randAddr[0] = (randAddr[0] & 0x3F) | 0xC0;
    esp_ble_gap_set_rand_addr(randAddr);
    delay(5);
    uint8_t size; PacketPtr packet;
    make_packet(chosenName, &size, &packet);
    esp_ble_gap_config_adv_data_raw(packet, size);
    free(packet);
    esp_ble_gap_start_advertising(&adv_params);
}
    
void bleSpamSetup() {
    Serial.begin(115200);
    randomSeed(analogRead(0));
    pinMode(BUTTON_PIN_CENTER, INPUT_PULLUP);
    pinMode(BUTTON_PIN_LEFT, INPUT_PULLUP);
    
    BLEDevice::init("");
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9);
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN, ESP_PWR_LVL_P9);
    esp_ble_gap_register_callback([](esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param){});
    
    isBleSpamming = true;
}
    
void bleSpamLoop() {
    if (!isBleSpamming) return;
    
    static uint8_t nextIdx = 0;
    const uint8_t batchSize = 5;
    char nameBuf[nameBufSize];
    
    if (digitalRead(BUTTON_PIN_LEFT) == LOW) {
        mode = (mode + 1) % 4;
        nextIdx = 0;
        delay(200);
    }
    
    for (uint8_t i = 0; i < batchSize; i++) {
        const char* name;
        uint8_t useMode = mode;
        if (mode == 3) useMode = i % 3;

        if (useMode == 0 && customNamesCount > 0) {
            name = customNames[nextIdx++];
            if (nextIdx >= customNamesCount) nextIdx = 0;
        } else {
            uint8_t oldMode = mode;
            mode = useMode;
            name = pickName(nameBuf);
            mode = oldMode;
        }
        advertiseDevice(name);
        delay(2);
    }
    
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(0, 12, "BLE Spam Active");
    u8g2.setCursor(0, 24);
    u8g2.print("Mode: ");
    if (mode == 0) u8g2.print("Custom");
    else if (mode == 1) u8g2.print("Random");
    else if (mode == 2) u8g2.print("Random/Emoji");
    else u8g2.print("All");
    u8g2.setCursor(0, 48);
    u8g2.print("< to toggle modes");
    u8g2.setCursor(0, 60);
    u8g2.print("SEL to exit");
    u8g2.sendBuffer();
    
    if (digitalRead(BUTTON_PIN_CENTER) == LOW) {
        isBleSpamming = false;
        esp_ble_gap_stop_advertising();
        BLEDevice::deinit();
        return;
    }
}