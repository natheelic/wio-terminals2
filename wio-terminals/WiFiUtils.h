#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include "config.h"

struct AppState;

String getSecurityTypeString(int securityType);
void scanWiFiNetworks(AppState* state);
ConnectionStatus connectToWiFi(AppState* state);

#endif