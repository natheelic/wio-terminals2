#ifndef CONFIG_H
#define CONFIG_H

#include <TFT_eSPI.h>
#include <rpcWiFi.h>

enum ScreenState {
  MAIN_MENU, SUBMENU_1, SUBMENU_2, SUBMENU_3,
  KEYBOARD_INPUT, WIFI_CONFIG, WIFI_SCAN,
  WIFI_CONNECT, WIFI_MANUAL_SETUP
};

enum ConnectionStatus { PENDING, CONNECTING, SUCCESS, FAILED };

struct AppState {
  TFT_eSPI* tft;
  ScreenState currentState;
  int selectedMenuItem, selectedWiFiItem;
  String inputText, wifiSSID, wifiPassword;
  int keyboardRow, keyboardCol;
  bool keyboardUpperCase, isEnteringPassword, isEnteringSSID;
  int foundNetworks;
  String networkNames[10];
  int networkRSSI[10];
  int networkSecurity[10];
  int selectedNetworkIndex;
  ConnectionStatus wifiConnectionStatus;
};

extern const char keyboard[4][10];
extern const char keyboardUpper[4][10];

#endif