#include "config.h"
#include "input.h"
#include "MainMenu.h"
#include "AutoConnecting.h"
#include "WiFiUtils.h"
#include "Buzzer.h"

// --- ส่วนที่เปลี่ยนแปลง ---
// สร้าง object สำหรับ FlashStorage **ที่นี่ที่เดียวเท่านั้น**
// struct WifiCredentials ได้ถูกย้ายไปประกาศใน WiFiUtils.h แล้ว
FlashStorage(credentials_storage, WifiCredentials);
// --- จบส่วนที่เปลี่ยนแปลง ---

TFT_eSPI tft = TFT_eSPI();
AppState appState;

void setup() {
  Serial.begin(115200);

  appState.tft = &tft;
  appState.currentState = MAIN_MENU;
  appState.selectedMenuItem = 0;
  appState.selectedWiFiItem = 0;
  appState.keyboardRow = 0;
  appState.keyboardCol = 0;
  appState.keyboardMode = MODE_ALPHA_LOWER;
  appState.isEnteringPassword = false;
  appState.isEnteringSSID = false;
  appState.foundNetworks = 0;
  appState.selectedNetworkIndex = -1;
  appState.wifiConnectionStatus = PENDING;

  tft.init();
  tft.setRotation(3);
  initButtons();
  buzzer_init();

  WifiCredentials savedCreds = credentials_storage.read();
  if (strlen(savedCreds.ssid) > 0) {
    appState.wifiSSID = String(savedCreds.ssid);
    appState.wifiPassword = String(savedCreds.password);

    appState.currentState = AUTO_CONNECTING;
    drawAutoConnecting(&appState);
    
    appState.wifiConnectionStatus = CONNECTING;
    drawAutoConnecting(&appState);
    ConnectionStatus status = connectToWiFi(&appState);
    appState.wifiConnectionStatus = status;
    
    drawAutoConnecting(&appState);
    delay(2500);
  }

  appState.currentState = MAIN_MENU;
  drawMainMenu(&appState);
}

void loop() {
  handleButtons(&appState);
  delay(50);
}