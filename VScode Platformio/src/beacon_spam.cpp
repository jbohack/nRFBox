/* ____________________________
   This software is licensed under the MIT License:
   https://github.com/jbohack/nyanBOX
   ________________________________________
*/

#include "../include/beacon_spam.h"
#include "../include/pindefs.h"
#include <stdint.h>
#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

// Disable frame sanity checks
extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3) {
    return 0;
}

// ===== Setting Options ===== //
const uint8_t channels[] = {1, 6, 11};    // Common channels are 1, 6, 11
const bool wpa2 = false;                 // Open networks = better visibility
const uint8_t ssidBatchSize = 10;        // SSIDs per batch
const uint32_t delayBetweenSSIDs = 20;   // Delay between beacons (ms)
const uint8_t beaconRepetitions = 2;     // Beacons per SSID

const char ssids[] PROGMEM = {
  "Mom Use This One\n"
  "Abraham Linksys\n"
  "Benjamin FrankLAN\n"
  "Martin Router King\n"
  "John Wilkes Bluetooth\n"
  "Pretty Fly for a Wi-Fi\n"
  "Bill Wi the Science Fi\n"
  "I Believe Wi Can Fi\n"
  "Tell My Wi-Fi Love Her\n"
  "No More Mister Wi-Fi\n"
  "Subscribe to TalkingSasquach\n"
  "jbohack was here\n"
  "zr_crackiin was here\n"
  "defcon.lullaby.cafe\n"
  "LAN Solo\n"
  "The LAN Before Time\n"
  "Silence of the LANs\n"
  "House LANister\n"
  "Winternet Is Coming\n"
  "Ping's Landing\n"
  "The Ping in the North\n"
  "This LAN Is My LAN\n"
  "Get Off My LAN\n"
  "The Promised LAN\n"
  "The LAN Down Under\n"
  "FBI Surveillance Van 4\n"
  "Area 51 Test Site\n"
  "Drive-By Wi-Fi\n"
  "Planet Express\n"
  "Wu Tang LAN\n"
  "Darude LANstorm\n"
  "Never Gonna Give You Up\n"
  "Hide Yo Kids, Hide Yo Wi-Fi\n"
  "Loading…\n"
  "Searching…\n"
  "VIRUS.EXE\n"
  "Virus-Infected Wi-Fi\n"
  "Starbucks Wi-Fi\n"
  "Text ###-#### for Password\n"
  "Yell ____ for Password\n"
  "The Password Is 1234\n"
  "Free Public Wi-Fi\n"
  "No Free Wi-Fi Here\n"
  "Get Your Own Damn Wi-Fi\n"
  "It Hurts When IP\n"
  "Dora the Internet Explorer\n"
  "404 Wi-Fi Unavailable\n"
  "Porque-Fi\n"
  "Titanic Syncing\n"
  "Test Wi-Fi Please Ignore\n"
  "Drop It Like It's Hotspot\n"
  "Life in the Fast LAN\n"
  "The Creep Next Door\n"
  "Ye Olde Internet\n"
  "Lan Before Time\n"
  "Lan Of The Lost\n"
};

bool isBeaconSpamming = false;
char emptySSID[32];
uint8_t macAddr[6];
uint8_t wifi_channel = 1;
uint32_t currentTime = 0;
uint32_t packetSize = 0;
uint32_t ssidIndex = 0;

uint8_t beaconPacket[100] = {
  0x80, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
  0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x64, 0x00,
  0x21, 0x04,
  0x00, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x0c, 0x18, 0x30, 0x48,
  0x03, 0x01, 0x01
};

void randomMac() {
  for (int i = 0; i < 6; i++) {
    macAddr[i] = random(256);
  }
}

void nextChannel() {
  static uint8_t channelIndex = 0;
  wifi_channel = channels[channelIndex];
  channelIndex = (channelIndex + 1) % (sizeof(channels) / sizeof(channels[0]));
  esp_wifi_set_channel(wifi_channel, WIFI_SECOND_CHAN_NONE);
}

void beaconSpamSetup() {
  for (int i = 0; i < 32; i++) emptySSID[i] = ' ';
  randomSeed(esp_random());

  packetSize = sizeof(beaconPacket);
  if (!wpa2) {
    beaconPacket[34] = 0x21;
    packetSize -= 26;
  }

  WiFi.mode(WIFI_STA);
  esp_wifi_set_mode(WIFI_MODE_STA);
  esp_wifi_start();
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(channels[0], WIFI_SECOND_CHAN_NONE);

  isBeaconSpamming = true;

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "Beacon Spam");
  u8g2.drawStr(0, 25, "Starting...");
  u8g2.sendBuffer();
  delay(1000);
}

void beaconSpamLoop() {
  currentTime = millis();

  static unsigned long lastDisplayUpdate = 0;
  if (currentTime - lastDisplayUpdate >= 250) {
    lastDisplayUpdate = currentTime;
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "Beacon Spam Active");

    char status[32];
    snprintf(status, sizeof(status), "Channel: %d", wifi_channel);
    u8g2.drawStr(0, 25, status);
    snprintf(status, sizeof(status), "SSID Index: %d", ssidIndex);
    u8g2.drawStr(0, 40, status);
    u8g2.drawStr(0, 55, "Press SEL to stop");
    u8g2.sendBuffer();
  }

  for (int i = 0; i < ssidBatchSize; i++) {
    int currentSSIDIndex = (ssidIndex + i) % strlen_P(ssids);
    int ssidStart = 0;
    for (int j = 0, count = 0; j < currentSSIDIndex; j++) {
      if (pgm_read_byte(ssids + j) == '\n') {
        ssidStart = j + 1;
        count++;
      }
    }

    int j = 0;
    char tmp;
    do {
      tmp = pgm_read_byte(ssids + ssidStart + j);
      j++;
    } while (tmp != '\n' && j <= 32 && (ssidStart + j) < (int)strlen_P(ssids));
    uint8_t ssidLen = j - 1;

    randomMac();
    memcpy(&beaconPacket[10], macAddr, 6);
    memcpy(&beaconPacket[16], macAddr, 6);
    memcpy(&beaconPacket[38], emptySSID, 32);

    for (int k = 0; k < ssidLen; k++) {
      beaconPacket[38 + k] = pgm_read_byte(ssids + ssidStart + k);
    }
    beaconPacket[37] = ssidLen;
    beaconPacket[82] = wifi_channel;

    for (int r = 0; r < beaconRepetitions; r++) {
      uint32_t timestamp = micros();
      memcpy(&beaconPacket[24], &timestamp, 4);
      esp_wifi_80211_tx(WIFI_IF_STA, beaconPacket, packetSize, false);
      delayMicroseconds(delayBetweenSSIDs * 100);
    }
  }

  ssidIndex = (ssidIndex + ssidBatchSize) % strlen_P(ssids);

  static uint8_t batchesSinceSwitch = 0;
  if (++batchesSinceSwitch >= 4) {
    batchesSinceSwitch = 0;
    nextChannel();
  }

  static uint32_t lastButtonCheck = 0;
  if (currentTime - lastButtonCheck > 100) {
    lastButtonCheck = currentTime;
    if (digitalRead(BUTTON_PIN_CENTER) == LOW) {
      isBeaconSpamming = false;
      esp_wifi_set_promiscuous(false);
      esp_wifi_stop();
      WiFi.mode(WIFI_OFF);

      u8g2.clearBuffer();
      return;
    }
  }
}
