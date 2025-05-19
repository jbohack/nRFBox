/* ____________________________
   This software is licensed under the MIT License:
   https://github.com/jbohack/nyanBOX
   ________________________________________ */
   
#ifndef spoofer_H
#define spoofer_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <U8g2lib.h>
#include <Adafruit_NeoPixel.h>
#include "neopixel.h"

void spooferSetup();
void spooferLoop();

#endif
