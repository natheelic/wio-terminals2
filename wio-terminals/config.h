#ifndef CONFIG_H
#define CONFIG_H

#include <TFT_eSPI.h>
#include <rpcWiFi.h>

// สถานะของหน้าจอ
enum ScreenState {
  MAIN_MENU,
  SUBMENU_1,
  SUBMENU_2,
  SUBMENU_3,
  KEYBOARD_INPUT,
  WIFI_CONFIG,
  WIFI_SCAN,
  WIFI_CONNECT,
  WIFI_MANUAL_SETUP
};

// สถานะการเชื่อมต่อ WiFi
enum ConnectionStatus {
  PENDING,
  CONNECTING,
  SUCCESS,
  FAILED
};

// Struct ที่รวบรวมสถานะทั้งหมดของแอปพลิเคชัน
struct AppState {
  TFT_eSPI* tft;
  ScreenState currentState;
  int selectedMenuItem;
  int selectedWiFiItem;
  String inputText;
  String wifiSSID;
  String wifiPassword;
  int keyboardRow;
  int keyboardCol;
  bool keyboardUpperCase;
  bool isEnteringPassword;
  bool isEnteringSSID;
  int foundNetworks;
  String networkNames[10];
  int networkRSSI[10];
  int networkSecurity[10];
  int selectedNetworkIndex;
  ConnectionStatus wifiConnectionStatus;
};

// Keyboard layout (เป็นข้อมูลคงที่)
extern const char keyboard[4][10];
extern const char keyboardUpper[4][10];

#endif