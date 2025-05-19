/* ____________________________
   This software is licensed under the MIT License:
   https://github.com/jbohack/nyanBOX
   ________________________________________ */

#ifndef flipper_H
#define flipper_H

#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "neopixel.h"
#include "esp_bt.h"
#include "esp_wifi.h"

void flipperSetup();

#endif