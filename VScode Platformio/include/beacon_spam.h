/* ____________________________
   This software is licensed under the MIT License:
   https://github.com/jbohack/nyanBOX
   ________________________________________
*/

#ifndef BEACON_SPAM_H
#define BEACON_SPAM_H

#include <WiFi.h>
#include "esp_wifi.h"

extern bool isBeaconSpamming;

void beaconSpamSetup();
void beaconSpamLoop();

#endif
