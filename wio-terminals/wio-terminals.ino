#include "config.h"
#include "input.h"
#include "MainMenu.h"

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
  appState.keyboardUpperCase = false;
  appState.isEnteringPassword = false;
  appState.isEnteringSSID = false;
  appState.foundNetworks = 0;
  appState.selectedNetworkIndex = -1;
  appState.wifiConnectionStatus = PENDING;

  tft.init();
  tft.setRotation(3);
  initButtons();

  drawMainMenu(&appState);
}

void loop() {
  handleButtons(&appState);
  delay(50);
}