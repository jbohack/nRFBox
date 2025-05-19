/* ____________________________
   This software is licensed under the MIT License:
   https://github.com/jbohack/nyanbox
   ________________________________________ */

#ifndef analyzer_H
#define analyzer_H

#include <SPI.h>
#include <U8g2lib.h>
#include "esp_bt.h"
#include "esp_wifi.h"
#include "neopixel.h"

void analyzerSetup();
void analyzerLoop();

#endif
