#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"

// Forward declaration to prevent circular dependency
struct AppState;

// Display initialization
void initDisplay(TFT_eSPI* tft);

// Menu drawing functions
void drawMainMenu(AppState* state);
void drawSubmenu1(AppState* state);
void drawSubmenu2(AppState* state);
void drawSubmenu3(AppState* state);
void drawKeyboard(AppState* state);
void drawWiFiConfig(AppState* state);
void drawWiFiScan(AppState* state);
void drawWiFiConnect(AppState* state);
void drawWiFiManualSetup(AppState* state);

// WiFi functions
void scanWiFiNetworks(AppState* state);
ConnectionStatus connectToWiFi(AppState* state);
void showWiFiStatus(AppState* state);

#endif