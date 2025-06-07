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
void handleKeyA(AppState* state); // NEW: Handler for Key A
void handleKeyB(AppState* state); // NEW: Handler for Key B
void handleKeyC(AppState* state); // NEW: Handler for Key C
void handleKeyboardInput(AppState* state);

// Button press state flags
static bool upPressed = false, downPressed = false, leftPressed = false, rightPressed = false, centerPressed = false;
static bool keyAPressed = false, keyBPressed = false, keyCPressed = false; // NEW: Flags for side keys

void initButtons() {
  // 5-way switch
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);

  // NEW: Initialize side keys
  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
}

void handleButtons(AppState* state) {
  // Read 5-way switch states
  bool upState = !digitalRead(WIO_5S_UP);
  bool downState = !digitalRead(WIO_5S_DOWN);
  bool leftState = !digitalRead(WIO_5S_LEFT);
  bool rightState = !digitalRead(WIO_5S_RIGHT);
  bool centerState = !digitalRead(WIO_5S_PRESS);

  // NEW: Read side key states
  bool keyAState = !digitalRead(WIO_KEY_A);
  bool keyBState = !digitalRead(WIO_KEY_B);
  bool keyCState = !digitalRead(WIO_KEY_C);

  // Handle presses
  if (upState && !upPressed) { upPressed = true; handleUp(state); } else if (!upState) { upPressed = false; }
  if (downState && !downPressed) { downPressed = true; handleDown(state); } else if (!downState) { downPressed = false; }
  if (leftState && !leftPressed) { leftPressed = true; handleLeft(state); } else if (!leftState) { leftPressed = false; }
  if (rightState && !rightPressed) { rightPressed = true; handleRight(state); } else if (!rightState) { rightPressed = false; }
  
  // Combine Center press and Key A press to trigger the same action
  if ((centerState && !centerPressed) || (keyAState && !keyAPressed)) { 
    centerPressed = centerState;
    keyAPressed = keyAState;
    handleCenter(state); // Key A will act as "Confirm/OK"
  } else {
    if (!centerState) { centerPressed = false; }
    if (!keyAState) { keyAPressed = false; }
  }

  // Handle Key B and Key C
  if (keyBState && !keyBPressed) { keyBPressed = true; handleKeyB(state); } else if (!keyBState) { keyBPressed = false; }
  if (keyCState && !keyCPressed) { keyCPressed = true; handleKeyC(state); } else if (!keyCState) { keyCPressed = false; }
}

// NEW: Handler for Key A (acts as Center/OK)
// We merge its logic into handleCenter, so this function is not needed.

// NEW: Handler for Key B (acts as Back)
void handleKeyB(AppState* state) {
  switch (state->currentState) {
    case SUBMENU_1:
    case SUBMENU_2:
    case SUBMENU_3:
      state->currentState = MAIN_MENU;
      drawMainMenu(state);
      break;
    case WIFI_CONFIG:
      state->currentState = SUBMENU_1;
      drawSubmenu1(state);
      break;
    case WIFI_SCAN:
    case WIFI_MANUAL_SETUP:
      state->currentState = WIFI_CONFIG;
      drawWiFiConfig(state);
      break;
    case WIFI_CONNECT:
       // If connected or failed, go back to config. If pending, go back to scan/manual.
      if (state->wifiConnectionStatus == SUCCESS || state->wifiConnectionStatus == FAILED) {
        state->currentState = WIFI_CONFIG;
        drawWiFiConfig(state);
      } else if (state->selectedNetworkIndex != -1) { // From scan
        state->currentState = WIFI_SCAN;
        drawWiFiScan(state);
      } else { // From manual
        state->currentState = WIFI_MANUAL_SETUP;
        drawWiFiManualSetup(state);
      }
      break;
    // On Keyboard, Key B will act as Backspace
    case KEYBOARD_INPUT:
      if (state->inputText.length() > 0) {
        state->inputText.remove(state->inputText.length() - 1);
        drawKeyboard(state);
      }
      break;
    default:
      // Do nothing on main menu
      break;
  }
}

// NEW: Handler for Key C (acts as Home)
void handleKeyC(AppState* state) {
  // No matter where we are, go back to the main menu
  if (state->currentState != MAIN_MENU) {
    state->currentState = MAIN_MENU;
    state->selectedMenuItem = 0; // Reset selection
    drawMainMenu(state);
  }
}


// --- MODIFIED Original Handlers ---

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
  // Left button is now mainly for keyboard navigation
  switch (state->currentState) {
    case KEYBOARD_INPUT: state->keyboardCol = (state->keyboardCol - 1 + (state->keyboardRow < 4 ? 10 : 4)) % (state->keyboardRow < 4 ? 10 : 4); drawKeyboard(state); break;
    // The "Back" functionality is now handled by Key B for consistency.
  }
}

void handleRight(AppState* state) {
  // Right button is now mainly for keyboard navigation
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
      // Add actions for other submenu items here if needed
      break;
    case SUBMENU_2:
    case SUBMENU_3:
      // These screens now use Key B (Back) or Key C (Home) to exit
      break;
    case WIFI_CONFIG:
      if (state->selectedWiFiItem == 0) { state->currentState = WIFI_SCAN; scanWiFiNetworks(state); drawWiFiScan(state); }
      else if (state->selectedWiFiItem == 1) { state->currentState = WIFI_MANUAL_SETUP; state->wifiSSID = ""; state->wifiPassword = ""; state->selectedWiFiItem = 0; drawWiFiManualSetup(state); }
      else if (state->selectedWiFiItem == 2) { WiFi.disconnect(); clearWiFiCredentials(); drawWiFiConfig(state); }
      else if (state->selectedWiFiItem == 3) { state->currentState = SUBMENU_1; drawSubmenu1(state); } // Back option
      break;
    case WIFI_SCAN:
      if (state->foundNetworks > 0) {
        state->selectedNetworkIndex = state->selectedWiFiItem; state->wifiSSID = state->networkNames[state->selectedNetworkIndex]; state->wifiPassword = "";
        state->currentState = WIFI_CONNECT; state->wifiConnectionStatus = PENDING; drawWiFiConnect(state);
      } else { scanWiFiNetworks(state); drawWiFiScan(state); } // Re-scan if no networks found
      break;
    case WIFI_CONNECT:
      if (state->wifiConnectionStatus == PENDING) {
        if (state->networkSecurity[state->selectedNetworkIndex] == WIFI_AUTH_OPEN) {
          state->wifiConnectionStatus = CONNECTING; drawWiFiConnect(state);
          state->wifiConnectionStatus = connectToWiFi(state); drawWiFiConnect(state);
        } else {
          state->currentState = KEYBOARD_INPUT; state->isEnteringPassword = true; state->isEnteringSSID = false; state->inputText = ""; drawKeyboard(state);
        }
      } else { 
        // If connection succeeded or failed, pressing OK/Center will go to WiFi Config
        state->currentState = WIFI_CONFIG; drawWiFiConfig(state); 
      }
      break;
    case WIFI_MANUAL_SETUP:
      if (state->selectedWiFiItem == 0) { state->currentState = KEYBOARD_INPUT; state->isEnteringSSID = true; state->isEnteringPassword = false; state->inputText = state->wifiSSID; drawKeyboard(state); }
      else if (state->selectedWiFiItem == 1) { state->currentState = KEYBOARD_INPUT; state->isEnteringPassword = true; state->isEnteringSSID = false; state->inputText = state->wifiPassword; drawKeyboard(state); }
      else if (state->selectedWiFiItem == 2) {
        if(state->wifiSSID.length() > 0) {
          state->selectedNetworkIndex = -1; state->currentState = WIFI_CONNECT; state->wifiConnectionStatus = CONNECTING;
          drawWiFiConnect(state); state->wifiConnectionStatus = connectToWiFi(state); drawWiFiConnect(state);
        }
      } else if (state->selectedWiFiItem == 3) { state->currentState = WIFI_CONFIG; drawWiFiConfig(state); } // Back option
      break;
    case KEYBOARD_INPUT:
      handleKeyboardInput(state);
      break;
  }
}

void handleKeyboardInput(AppState* state) {
  if (state->keyboardRow < 4) { // Character keys
    char selectedChar = state->keyboardUpperCase ? keyboardUpper[state->keyboardRow][state->keyboardCol] : keyboard[state->keyboardRow][state->keyboardCol];
    if (state->inputText.length() < 32) {
        state->inputText += selectedChar;
    }
  } else { // Special keys row
    if (state->keyboardCol == 0) { // Shift
      state->keyboardUpperCase = !state->keyboardUpperCase;
    } else if (state->keyboardCol == 1) { // Space
      state->inputText += ' ';
    } else if (state->keyboardCol == 2) { // Backspace
      if (state->inputText.length() > 0) {
        state->inputText.remove(state->inputText.length() - 1);
      }
    } else if (state->keyboardCol == 3) { // Return/OK
      if (state->isEnteringPassword) {
        state->wifiPassword = state->inputText;
        bool fromManual = (state->selectedNetworkIndex == -1);
        if(fromManual) {
             state->currentState = WIFI_MANUAL_SETUP;
             drawWiFiManualSetup(state);
        } else {
            state->currentState = WIFI_CONNECT;
            state->wifiConnectionStatus = CONNECTING;
            drawWiFiConnect(state);
            ConnectionStatus status = connectToWiFi(state);
            state->wifiConnectionStatus = status;
            
            if (status == SUCCESS) {
                saveWiFiCredentials(state);
            }
            drawWiFiConnect(state);
        }
      } else if (state->isEnteringSSID) {
        state->wifiSSID = state->inputText;
        state->currentState = WIFI_MANUAL_SETUP;
        drawWiFiManualSetup(state);
      } else {
        // Exiting keyboard from general text input
        state->currentState = SUBMENU_3;
        drawSubmenu3(state);
      }
      return; // Exit to prevent redrawing keyboard
    }
  }
  drawKeyboard(state); // Redraw keyboard to show changes
}