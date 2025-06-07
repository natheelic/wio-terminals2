#ifndef CONFIG_H
#define CONFIG_H

#include <TFT_eSPI.h>
#include <rpcWiFi.h>
#include <FlashStorage.h>

enum ScreenState {
  AUTO_CONNECTING,
  MAIN_MENU, SUBMENU_1, SUBMENU_2, SUBMENU_3,
  KEYBOARD_INPUT, WIFI_CONFIG, WIFI_SCAN,
  WIFI_CONNECT, WIFI_MANUAL_SETUP, RESET_CONFIRM, SYSTEM_INFO
};
enum ConnectionStatus { PENDING, CONNECTING, SUCCESS, FAILED };

// NEW: Keyboard mode enum
enum KeyboardMode { MODE_ALPHA_LOWER, MODE_ALPHA_UPPER, MODE_NUM_SYM };

struct AppState {
  TFT_eSPI* tft;
  ScreenState currentState;
  ScreenState previousState; // NEW: To remember where we came from
  int selectedMenuItem, selectedWiFiItem;
  String inputText, wifiSSID, wifiPassword;
  int keyboardRow, keyboardCol;
  // bool keyboardUpperCase is now replaced by keyboardMode
  KeyboardMode keyboardMode; // NEW: To manage keyboard layout
  bool isEnteringPassword, isEnteringSSID;
  int foundNetworks;
  String networkNames[10];
  int networkRSSI[10];
  int networkSecurity[10];
  int selectedNetworkIndex;
  ConnectionStatus wifiConnectionStatus;
  int wifiScanScrollOffset;
};

// Extern declarations for keyboard layouts
extern const char keyboard[4][10];
extern const char keyboardUpper[4][10];
extern const char keyboardNumSym[4][10]; // NEW: For numbers and symbols

#endif