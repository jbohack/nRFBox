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
   
   extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
   
   bool isBleSpamming = false;
   uint32_t lastFloodTime = 0;
   const uint32_t floodInterval = 20;
   
   static bool useCustomNamesMode = true;
   
   // BLE advertising parameters (non-connectable)
   static esp_ble_adv_params_t adv_params = {
       .adv_int_min        = 0x20,
       .adv_int_max        = 0x40,
       .adv_type           = ADV_TYPE_NONCONN_IND,
       .own_addr_type      = BLE_ADDR_TYPE_RANDOM,
       .channel_map        = ADV_CHNL_ALL,
       .adv_filter_policy  = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY
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
   
   const uint8_t minNameLen = 3;
   const uint8_t maxNameLen = 10;
   
   static void generateRandomName(char* buf, uint8_t length) {
       for(uint8_t i = 0; i < length; i++) {
           buf[i] = 'A' + random(26);
       }
       buf[length] = '\0';
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
       for(int i = 0; i < 6; i++) randAddr[i] = random(0,256);
       randAddr[0] = (randAddr[0] & 0x3F) | 0xC0;
       esp_ble_gap_set_rand_addr(randAddr);
       delay(5);
   
       uint8_t size;
       PacketPtr packet;
       make_packet(chosenName, &size, &packet);
       esp_ble_gap_config_adv_data_raw(packet, size);
       free(packet);
   
       esp_ble_gap_start_advertising(&adv_params);
   
       u8g2.clearBuffer();
       u8g2.setFont(u8g2_font_6x10_tf);
       u8g2.drawStr(0, 12, "BLE Spam Active");
       u8g2.setCursor(0, 24);
       u8g2.print("Mode: "); u8g2.print(useCustomNamesMode ? "Custom" : "Random");
       u8g2.setCursor(0, 48);
       u8g2.print("< to toggle modes");
       u8g2.setCursor(0, 60);
       u8g2.print("Press SEL to exit");
       u8g2.sendBuffer();
   }
   
   static const char* pickName(char* buf) {
       if(useCustomNamesMode && customNamesCount > 0) {
           return customNames[random(customNamesCount)];
       } else {
           uint8_t len = random(minNameLen, maxNameLen + 1);
           generateRandomName(buf, len);
           return buf;
       }
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
       lastFloodTime = millis() - floodInterval;
   }
   
   void bleSpamLoop() {
       if(!isBleSpamming) return;
   
       if(digitalRead(BUTTON_PIN_LEFT) == LOW) {
           useCustomNamesMode = !useCustomNamesMode;
           delay(200);
       }
   
       uint32_t now = millis();
       if(now - lastFloodTime >= floodInterval) {
           lastFloodTime = now;
           char nameBuf[maxNameLen + 1];
           const char* name = pickName(nameBuf);
           advertiseDevice(name);
       }
   
       if (digitalRead(BUTTON_PIN_CENTER) == LOW) {
        isBleSpamming = false;
        esp_ble_gap_stop_advertising();
        BLEDevice::deinit();
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_6x10_tf);
        u8g2.drawStr(0, 12, "BLE Spam Stopped");
        u8g2.drawStr(0, 24, "SEL again to exit");
        u8g2.sendBuffer();
        return; 
       }
   }
   