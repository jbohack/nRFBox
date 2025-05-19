/* ____________________________
   This software is licensed under the MIT License:
   https://github.com/jbohack/nyanBOX
   ________________________________________ */

#include <Arduino.h>
#include <U8g2lib.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "blescan.h"
#include "neopixel.h"
#include "../include/pindefs.h"

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

static int selectedIndex = 0;
static int displayStartIndex = 0;
static bool showDetails = false;
static BLEAdvertisedDevice selectedDevice;

void blescanSetup() {
  BLEDevice::init("BLEScanner");
  BLEScan* scan = BLEDevice::getScan();
  scan->setActiveScan(true);

  selectedIndex = 0;
  displayStartIndex = 0;
  showDetails = false;

  u8g2.setFont(u8g2_font_6x10_tr);

  pinMode(BUTTON_PIN_UP, INPUT_PULLUP);
  pinMode(BUTTON_PIN_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_PIN_CENTER, INPUT_PULLUP);
  pinMode(BUTTON_PIN_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_PIN_RIGHT, INPUT_PULLUP);

  for (int cycle = 0; cycle < 3; cycle++) {
    for (int i = 0; i < 3; i++) {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(0, 10, "Scanning BLE");

      String dots = "";
      for (int j = 0; j <= i; j++) dots += " .";
      u8g2.drawStr(75, 10, dots.c_str());

      setNeoPixelColour("white");
      u8g2.sendBuffer();
      delay(300);
    }
  }
  setNeoPixelColour("0");

  BLEScanResults results = scan->start(5, false);
  scan->stop();

  std::vector<BLEAdvertisedDevice> devices;
  for (int i = 0; i < results.getCount(); i++) {
    devices.push_back(results.getDevice(i));
  }

  while (true) {
    if (digitalRead(BUTTON_PIN_CENTER) == LOW) {
      while (digitalRead(BUTTON_PIN_CENTER) == LOW);
      return;
    }

    if (!showDetails) {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_6x10_tr);
      u8g2.drawStr(0, 10, "BLE Devices:");

      for (int i = 0; i < 5 && (i + displayStartIndex) < devices.size(); i++) {
        BLEAdvertisedDevice device = devices[i + displayStartIndex];
        String name = device.getName().c_str();
        if (name.length() == 0) name = "No Name";
        String info = name.substring(0, 7) + " | RSSI " + String(device.getRSSI());

        if ((i + displayStartIndex) == selectedIndex) u8g2.drawStr(0, 20 + i * 10, ">");
        u8g2.drawStr(10, 20 + i * 10, info.c_str());
      }

      u8g2.sendBuffer();

      if (digitalRead(BUTTON_PIN_UP) == LOW) {
        if (selectedIndex > 0) selectedIndex--;
        if (selectedIndex < displayStartIndex) displayStartIndex--;
        delay(200);
      }

      if (digitalRead(BUTTON_PIN_DOWN) == LOW) {
        if (selectedIndex < devices.size() - 1) selectedIndex++;
        if (selectedIndex >= displayStartIndex + 5) displayStartIndex++;
        delay(200);
      }

      if (digitalRead(BUTTON_PIN_RIGHT) == LOW) {
        selectedDevice = devices[selectedIndex];
        showDetails = true;
        delay(200);
      }

    } else {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_6x10_tr);
      u8g2.drawStr(0, 10, "Device Details:");
      u8g2.setFont(u8g2_font_5x8_tr);
      u8g2.drawStr(0, 20, ("Name: " + String(selectedDevice.getName().c_str())).c_str());
      u8g2.drawStr(0, 30, ("Addr: " + String(selectedDevice.getAddress().toString().c_str())).c_str());
      u8g2.drawStr(0, 40, ("RSSI: " + String(selectedDevice.getRSSI())).c_str());
      u8g2.drawStr(0, 50, "Press LEFT to go back");
      u8g2.sendBuffer();

      if (digitalRead(BUTTON_PIN_LEFT) == LOW) {
        while (digitalRead(BUTTON_PIN_LEFT) == LOW);
        showDetails = false;
        delay(200);
      }

      if (digitalRead(BUTTON_PIN_CENTER) == LOW) {
        while (digitalRead(BUTTON_PIN_CENTER) == LOW);
        return;
      }
    }
  }
}