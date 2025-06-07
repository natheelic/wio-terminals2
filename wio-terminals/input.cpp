#include "input.h"

// Include screen headers
#include "MainMenu.h"
#include "Submenu1.h"
#include "Submenu2.h"
#include "Submenu3.h"
#include "Keyboard.h"
#include "WiFiConfig.h"
#include "WiFiScan.h"
#include "WiFiConnect.h"
#include "WiFiManualSetup.h"
// Include utility headers
#include "WiFiUtils.h"

// Internal function declarations
void handleUp(AppState* state);
void handleDown(AppState* state);
void handleLeft(AppState* state);
void handleRight(AppState* state);
void handleCenter(AppState* state);

static bool upPressed = false, downPressed = false, leftPressed = false, rightPressed = false, centerPressed = false;

void initButtons() {
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
}

void handleButtons(AppState* state) {
  bool upState = !digitalRead(WIO_5S_UP);
  bool downState = !digitalRead(WIO_5S_DOWN);
  bool leftState = !digitalRead(WIO_5S_LEFT);
  bool rightState = !digitalRead(WIO_5S_RIGHT);
  bool centerState = !digitalRead(WIO_5S_PRESS);

  if (upState && !upPressed) { upPressed = true; handleUp(state); } else if (!upState) { upPressed = false; }
  if (downState && !downPressed) { downPressed = true; handleDown(state); } else if (!downState) { downPressed = false; }
  if (leftState && !leftPressed) { leftPressed = true; handleLeft(state); } else if (!leftState) { leftPressed = false; }
  if (rightState && !rightPressed) { rightPressed = true; handleRight(state); } else if (!rightState) { rightPressed = false; }
  if (centerState && !centerPressed) { centerPressed = true; handleCenter(state); } else if (!centerState) { centerPressed = false; }
}

void handleUp(AppState* state) {
  switch (state->currentState) {
    case MAIN_MENU: state->selectedMenuItem = (state->selectedMenuItem - 1 + 3) % 3; drawMainMenu(state); break;
    case SUBMENU_1: state->selectedWiFiItem = (state->selectedWiFiItem - 1 + 4) % 4; drawSubmenu1(state); break;
    case WIFI_CONFIG: state->selectedWiFiItem = (state->selectedWiFiItem - 1 + 4) % 4; drawWiFiConfig(state); break;
    case WIFI_MANUAL_SETUP: state->selectedWiFiItem = (state->selectedWiFiItem - 1 + 4) % 4; drawWiFiManualSetup(state); break;
    case WIFI_SCAN: if (state->foundNetworks > 0) { state->selectedWiFiItem = (state->selectedWiFiItem - 1 + state->foundNetworks) % state->foundNetworks; drawWiFiScan(state); } break;
    case KEYBOARD_INPUT: state->keyboardRow = (state->keyboardRow - 1 + 5) % 5; drawKeyboard(state); break;
  }
}

void handleDown(AppState* state) {
  switch (state->currentState) {
    case MAIN_MENU: state->selectedMenuItem = (state->selectedMenuItem + 1) % 3; drawMainMenu(state); break;
    case SUBMENU_1: state->selectedWiFiItem = (state->selectedWiFiItem + 1) % 4; drawSubmenu1(state); break;
    case WIFI_CONFIG: state->selectedWiFiItem = (state->selectedWiFiItem + 1) % 4; drawWiFiConfig(state); break;
    case WIFI_MANUAL_SETUP: state->selectedWiFiItem = (state->selectedWiFiItem + 1) % 4; drawWiFiManualSetup(state); break;
    case WIFI_SCAN: if (state->foundNetworks > 0) { state->selectedWiFiItem = (state->selectedWiFiItem + 1) % state->foundNetworks; drawWiFiScan(state); } break;
    case KEYBOARD_INPUT: state->keyboardRow = (state->keyboardRow + 1) % 5; drawKeyboard(state); break;
  }
}

void handleLeft(AppState* state) {
  switch (state->currentState) {
    case SUBMENU_1: case SUBMENU_2: case SUBMENU_3: state->currentState = MAIN_MENU; drawMainMenu(state); break;
    case WIFI_CONFIG: state->currentState = SUBMENU_1; drawSubmenu1(state); break;
    case WIFI_SCAN: case WIFI_MANUAL_SETUP: state->currentState = WIFI_CONFIG; drawWiFiConfig(state); break;
    case WIFI_CONNECT: state->currentState = WIFI_SCAN; drawWiFiScan(state); break;
    case KEYBOARD_INPUT: state->keyboardCol = (state->keyboardCol - 1 + (state->keyboardRow < 4 ? 10 : 4)) % (state->keyboardRow < 4 ? 10 : 4); drawKeyboard(state); break;
  }
}

void handleRight(AppState* state) {
  switch(state->currentState) {
    case KEYBOARD_INPUT: state->keyboardCol = (state->keyboardCol + 1) % (state->keyboardRow < 4 ? 10 : 4); drawKeyboard(state); break;
  }
}

void handleCenter(AppState* state) {
  switch (state->currentState) {
    case MAIN_MENU:
      if (state->selectedMenuItem == 0) { state->currentState = SUBMENU_1; state->selectedWiFiItem = 0; drawSubmenu1(state); }
      else if (state->selectedMenuItem == 1) { state->currentState = SUBMENU_2; drawSubmenu2(state); }
      else if (state->selectedMenuItem == 2) { state->currentState = KEYBOARD_INPUT; state->inputText = ""; state->isEnteringPassword = false; state->isEnteringSSID = false; drawKeyboard(state); }
      break;
    case SUBMENU_1:
      if (state->selectedWiFiItem == 0) { state->currentState = WIFI_CONFIG; state->selectedWiFiItem = 0; drawWiFiConfig(state); }
      break;
    case WIFI_CONFIG:
      if (state->selectedWiFiItem == 0) { state->currentState = WIFI_SCAN; scanWiFiNetworks(state); drawWiFiScan(state); }
      else if (state->selectedWiFiItem == 1) { state->currentState = WIFI_MANUAL_SETUP; state->wifiSSID = ""; state->wifiPassword = ""; drawWiFiManualSetup(state); }
      else if (state->selectedWiFiItem == 2) { WiFi.disconnect(); drawWiFiConfig(state); }
      else if (state->selectedWiFiItem == 3) { state->currentState = SUBMENU_1; drawSubmenu1(state); }
      break;
    case WIFI_SCAN:
      if (state->foundNetworks > 0) {
        state->selectedNetworkIndex = state->selectedWiFiItem; state->wifiSSID = state->networkNames[state->selectedNetworkIndex]; state->wifiPassword = "";
        state->currentState = WIFI_CONNECT; state->wifiConnectionStatus = PENDING; drawWiFiConnect(state);
      } else { scanWiFiNetworks(state); drawWiFiScan(state); }
      break;
    case WIFI_CONNECT:
      if (state->wifiConnectionStatus == PENDING) {
        if (state->networkSecurity[state->selectedNetworkIndex] == WIFI_AUTH_OPEN) {
          state->wifiConnectionStatus = CONNECTING; drawWiFiConnect(state);
          state->wifiConnectionStatus = connectToWiFi(state); drawWiFiConnect(state);
        } else {
          state->currentState = KEYBOARD_INPUT; state->isEnteringPassword = true; state->isEnteringSSID = false; state->inputText = ""; drawKeyboard(state);
        }
      } else { state->currentState = WIFI_CONFIG; drawWiFiConfig(state); }
      break;
    case WIFI_MANUAL_SETUP:
      if (state->selectedWiFiItem == 0) { state->currentState = KEYBOARD_INPUT; state->isEnteringSSID = true; state->isEnteringPassword = false; state->inputText = state->wifiSSID; drawKeyboard(state); }
      else if (state->selectedWiFiItem == 1) { state->currentState = KEYBOARD_INPUT; state->isEnteringPassword = true; state->isEnteringSSID = false; state->inputText = state->wifiPassword; drawKeyboard(state); }
      else if (state->selectedWiFiItem == 2) {
        if(state->wifiSSID.length() > 0) {
          state->selectedNetworkIndex = -1; state->currentState = WIFI_CONNECT; state->wifiConnectionStatus = CONNECTING;
          drawWiFiConnect(state); state->wifiConnectionStatus = connectToWiFi(state); drawWiFiConnect(state);
        }
      } else if (state->selectedWiFiItem == 3) { state->currentState = WIFI_CONFIG; drawWiFiConfig(state); }
      break;
    case KEYBOARD_INPUT:
      if (state->keyboardRow < 4) { state->inputText += state->keyboardUpperCase ? keyboardUpper[state->keyboardRow][state->keyboardCol] : keyboard[state->keyboardRow][state->keyboardCol]; }
      else {
        if (state->keyboardCol == 0) { state->keyboardUpperCase = !state->keyboardUpperCase; }
        else if (state->keyboardCol == 1) { state->inputText += ' '; }
        else if (state->keyboardCol == 2) { if (state->inputText.length() > 0) state->inputText.remove(state->inputText.length() - 1); }
        else if (state->keyboardCol == 3) { // OK
          if (state->isEnteringPassword) {
            state->wifiPassword = state->inputText; bool fromManual = (state->selectedNetworkIndex == -1);
            if(fromManual) { state->currentState = WIFI_MANUAL_SETUP; drawWiFiManualSetup(state); }
            else { state->currentState = WIFI_CONNECT; state->wifiConnectionStatus = CONNECTING; drawWiFiConnect(state); state->wifiConnectionStatus = connectToWiFi(state); drawWiFiConnect(state); }
          } else if (state->isEnteringSSID) { state->wifiSSID = state->inputText; state->currentState = WIFI_MANUAL_SETUP; drawWiFiManualSetup(state); }
          else { state->currentState = SUBMENU_3; drawSubmenu3(state); }
          return;
        }
      }
      drawKeyboard(state);
      break;
    case SUBMENU_2: case SUBMENU_3: state->currentState = MAIN_MENU; drawMainMenu(state); break;
  }
}