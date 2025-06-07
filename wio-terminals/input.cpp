#include "input.h"
#include "MainMenu.h"
#include "Submenu1.h"
#include "Submenu2.h"
#include "Submenu3.h"
#include "Keyboard.h"
#include "WiFiConfig.h"
#include "WiFiScan.h"
#include "WiFiConnect.h"
#include "WiFiManualSetup.h"
#include "WiFiUtils.h"
#include "drawResetConfirm.h"
#include "drawSystemInfo.h"

// Internal function declarations
void handleUp(AppState *state);
void handleDown(AppState *state);
void handleLeft(AppState *state);
void handleRight(AppState *state);
void handleCenter(AppState *state);
void handleKeyA(AppState *state);
void handleKeyB(AppState *state);
void handleKeyC(AppState *state);
void handleKeyboardInput(AppState *state);
void enterKeyboard(AppState *state); // Helper function to enter keyboard state

static bool upPressed = false, downPressed = false, leftPressed = false, rightPressed = false, centerPressed = false;
static bool keyAPressed = false, keyBPressed = false, keyCPressed = false;

void initButtons()
{
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
}

void handleButtons(AppState *state)
{
  bool upState = !digitalRead(WIO_5S_UP);
  bool downState = !digitalRead(WIO_5S_DOWN);
  bool leftState = !digitalRead(WIO_5S_LEFT);
  bool rightState = !digitalRead(WIO_5S_RIGHT);
  bool centerState = !digitalRead(WIO_5S_PRESS);
  bool keyAState = !digitalRead(WIO_KEY_A);
  bool keyBState = !digitalRead(WIO_KEY_B);
  bool keyCState = !digitalRead(WIO_KEY_C);

  if (upState && !upPressed)
  {
    upPressed = true;
    handleUp(state);
  }
  else if (!upState)
  {
    upPressed = false;
  }
  if (downState && !downPressed)
  {
    downPressed = true;
    handleDown(state);
  }
  else if (!downState)
  {
    downPressed = false;
  }
  if (leftState && !leftPressed)
  {
    leftPressed = true;
    handleLeft(state);
  }
  else if (!leftState)
  {
    leftPressed = false;
  }
  if (rightState && !rightPressed)
  {
    rightPressed = true;
    handleRight(state);
  }
  else if (!rightState)
  {
    rightPressed = false;
  }
  if (centerState && !centerPressed)
  {
    centerPressed = true;
    handleCenter(state);
  }
  else if (!centerState)
  {
    centerPressed = false;
  }
  if (keyAState && !keyAPressed)
  {
    keyAPressed = true;
    handleKeyA(state);
  }
  else if (!keyAState)
  {
    keyAPressed = false;
  }
  if (keyBState && !keyBPressed)
  {
    keyBPressed = true;
    handleKeyB(state);
  }
  else if (!keyBState)
  {
    keyBPressed = false;
  }
  if (keyCState && !keyCPressed)
  {
    keyCPressed = true;
    handleKeyC(state);
  }
  else if (!keyCState)
  {
    keyCPressed = false;
  }
}

void enterKeyboard(AppState *state)
{
  state->previousState = state->currentState; // Remember where we came from
  state->currentState = KEYBOARD_INPUT;
  state->keyboardMode = MODE_ALPHA_LOWER;
  state->keyboardRow = 0;
  state->keyboardCol = 0;
  drawKeyboard(state);
}

void handleKeyA(AppState *state)
{
  if (state->currentState == KEYBOARD_INPUT)
  {
    // Mode Switch: a-z -> A-Z -> 0-9 -> a-z
    if (state->keyboardMode == MODE_ALPHA_LOWER)
      state->keyboardMode = MODE_ALPHA_UPPER;
    else if (state->keyboardMode == MODE_ALPHA_UPPER)
      state->keyboardMode = MODE_NUM_SYM;
    else
      state->keyboardMode = MODE_ALPHA_LOWER;
    drawKeyboard(state);
  }
  else
  {
    handleCenter(state); // If not on keyboard, Key A acts as OK
  }
}

void handleKeyB(AppState *state)
{
  if (state->currentState == KEYBOARD_INPUT)
  {
    // Backspace
    if (state->inputText.length() > 0)
    {
      state->inputText.remove(state->inputText.length() - 1);
      drawKeyboard(state);
    }
  }
  else
  {
    // Go Back to previous screen
    switch (state->currentState)
    {
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
      if (state->wifiConnectionStatus == SUCCESS || state->wifiConnectionStatus == FAILED)
      {
        state->currentState = WIFI_CONFIG;
        drawWiFiConfig(state);
      }
      else if (state->selectedNetworkIndex != -1)
      {
        state->currentState = WIFI_SCAN;
        drawWiFiScan(state);
      }
      else
      {
        state->currentState = WIFI_MANUAL_SETUP;
        drawWiFiManualSetup(state);
      }
      break;
    case RESET_CONFIRM:
      state->currentState = SUBMENU_1;
      drawSubmenu1(state);
      break;

    case SYSTEM_INFO: // <--- เพิ่ม case นี้
      state->currentState = SUBMENU_1;
      drawSubmenu1(state);
      break;
    }
  }
}

void handleKeyC(AppState *state)
{
  if (state->currentState == KEYBOARD_INPUT)
  {
    // Space
    if (state->inputText.length() < 32)
      state->inputText += ' ';
    drawKeyboard(state);
  }
  else
  {
    // Go Home
    if (state->currentState != MAIN_MENU)
    {
      state->currentState = MAIN_MENU;
      state->selectedMenuItem = 0;
      drawMainMenu(state);
    }
  }
}

// --- MODIFIED Original Handlers ---

// --- COPY AND REPLACE THESE TWO FUNCTIONS IN input.cpp ---

void handleUp(AppState *state)
{
  const int MAX_VISIBLE_NETWORKS = 6; // Make sure this matches the value in WiFiScan.cpp
  switch (state->currentState)
  {
  case MAIN_MENU:
    state->selectedMenuItem = (state->selectedMenuItem - 1 + 3) % 3;
    drawMainMenu(state);
    break;
  case SUBMENU_1:
    state->selectedWiFiItem = (state->selectedWiFiItem - 1 + 4) % 4;
    drawSubmenu1(state);
    break;
  case WIFI_CONFIG:
    state->selectedWiFiItem = (state->selectedWiFiItem - 1 + 4) % 4;
    drawWiFiConfig(state);
    break;
  case WIFI_MANUAL_SETUP:
    state->selectedWiFiItem = (state->selectedWiFiItem - 1 + 4) % 4;
    drawWiFiManualSetup(state);
    break;
  case WIFI_SCAN:
    if (state->foundNetworks > 0)
    {
      int oldSelection = state->selectedWiFiItem;
      state->selectedWiFiItem = (state->selectedWiFiItem - 1 + state->foundNetworks) % state->foundNetworks;

      // NEW LOGIC: Check for wrap-around from first to last item
      if (state->selectedWiFiItem > oldSelection)
      {
        // This means we wrapped around from 0 to the last item.
        // Scroll the view to the bottom.
        state->wifiScanScrollOffset = state->foundNetworks - MAX_VISIBLE_NETWORKS;
        if (state->wifiScanScrollOffset < 0)
          state->wifiScanScrollOffset = 0;
      }
      // Logic to scroll view up when selection goes above the visible area
      else if (state->selectedWiFiItem < state->wifiScanScrollOffset)
      {
        state->wifiScanScrollOffset = state->selectedWiFiItem;
      }
      drawWiFiScan(state);
    }
    break;
  case KEYBOARD_INPUT:
    state->keyboardRow = (state->keyboardRow - 1 + 5) % 5;
    drawKeyboard(state);
    break;
  }
}

void handleDown(AppState *state)
{
  const int MAX_VISIBLE_NETWORKS = 6; // Make sure this matches the value in WiFiScan.cpp
  switch (state->currentState)
  {
  case MAIN_MENU:
    state->selectedMenuItem = (state->selectedMenuItem + 1) % 3;
    drawMainMenu(state);
    break;
  case SUBMENU_1:
    state->selectedWiFiItem = (state->selectedWiFiItem + 1) % 4;
    drawSubmenu1(state);
    break;
  case WIFI_CONFIG:
    state->selectedWiFiItem = (state->selectedWiFiItem + 1) % 4;
    drawWiFiConfig(state);
    break;
  case WIFI_MANUAL_SETUP:
    state->selectedWiFiItem = (state->selectedWiFiItem + 1) % 4;
    drawWiFiManualSetup(state);
    break;
  case WIFI_SCAN:
    if (state->foundNetworks > 0)
    {
      int oldSelection = state->selectedWiFiItem;
      state->selectedWiFiItem = (state->selectedWiFiItem + 1) % state->foundNetworks;

      // NEW LOGIC: Check for wrap-around from last to first item
      if (state->selectedWiFiItem < oldSelection)
      {
        // This means we wrapped around from the last item back to 0.
        // Reset scroll to the top.
        state->wifiScanScrollOffset = 0;
      }
      // Logic to scroll view down when selection goes below the visible area
      else if (state->selectedWiFiItem >= state->wifiScanScrollOffset + MAX_VISIBLE_NETWORKS)
      {
        state->wifiScanScrollOffset = state->selectedWiFiItem - MAX_VISIBLE_NETWORKS + 1;
      }
      drawWiFiScan(state);
    }
    break;
  case KEYBOARD_INPUT:
    state->keyboardRow = (state->keyboardRow + 1) % 5;
    drawKeyboard(state);
    break;
  }
}
void handleLeft(AppState *state)
{
  if (state->currentState == KEYBOARD_INPUT)
  {
    int cols = (state->keyboardRow < 4) ? 10 : 3;
    state->keyboardCol = (state->keyboardCol - 1 + cols) % cols;
    drawKeyboard(state);
  }
  else if (state->currentState == RESET_CONFIRM)
  {
    state->selectedMenuItem = (state->selectedMenuItem - 1 + 2) % 2;
    drawResetConfirm(state);
  }
}

void handleRight(AppState *state)
{
  if (state->currentState == KEYBOARD_INPUT)
  {
    int cols = (state->keyboardRow < 4) ? 10 : 3;
    state->keyboardCol = (state->keyboardCol + 1) % cols;
    drawKeyboard(state);
  }
  else if (state->currentState == RESET_CONFIRM)
  {
    state->selectedMenuItem = (state->selectedMenuItem + 1) % 2;
    drawResetConfirm(state);
  }
}

void handleCenter(AppState *state)
{
  switch (state->currentState)
  {
  case MAIN_MENU:
    if (state->selectedMenuItem == 0)
    {
      state->currentState = SUBMENU_1;
      state->selectedWiFiItem = 0;
      drawSubmenu1(state);
    }
    else if (state->selectedMenuItem == 1)
    {
      state->currentState = SUBMENU_2;
      drawSubmenu2(state);
    }
    else if (state->selectedMenuItem == 2)
    {
      state->inputText = "";
      state->isEnteringPassword = false;
      state->isEnteringSSID = false;
      enterKeyboard(state);
    }
    break;
  case SUBMENU_1:
    if (state->selectedWiFiItem == 0)
    {
      state->currentState = WIFI_CONFIG;
      state->selectedWiFiItem = 0;
      drawWiFiConfig(state);
    }
    else if (state->selectedWiFiItem == 2)
    { // <--- เพิ่ม else if นี้
      state->currentState = SYSTEM_INFO;
      drawSystemInfo(state);
    }
    else if (state->selectedWiFiItem == 3)
    { // <-- แก้ไขตรงนี้ จากเดิมไม่มี else if
      state->currentState = RESET_CONFIRM;
      state->selectedMenuItem = 1; // ให้ "No" เป็นค่าเริ่มต้น
      drawResetConfirm(state);
    }
    break;
  case WIFI_CONFIG:
    if (state->selectedWiFiItem == 0)
    {
      state->currentState = WIFI_SCAN;
      state->wifiScanScrollOffset = 0;
      scanWiFiNetworks(state);
      drawWiFiScan(state);
    }
    else if (state->selectedWiFiItem == 1)
    {
      state->currentState = WIFI_MANUAL_SETUP;
      state->wifiSSID = "";
      state->wifiPassword = "";
      state->selectedWiFiItem = 0;
      drawWiFiManualSetup(state);
    }
    else if (state->selectedWiFiItem == 2)
    {
      WiFi.disconnect();
      clearWiFiCredentials();
      drawWiFiConfig(state);
    }
    else if (state->selectedWiFiItem == 3)
    {
      state->currentState = SUBMENU_1;
      drawSubmenu1(state);
    }
    break;
  case WIFI_SCAN:
    if (state->foundNetworks > 0)
    {
      state->selectedNetworkIndex = state->selectedWiFiItem;
      state->wifiSSID = state->networkNames[state->selectedNetworkIndex];
      state->wifiPassword = "";
      state->currentState = WIFI_CONNECT;
      state->wifiConnectionStatus = PENDING;
      drawWiFiConnect(state);
    }
    else
    {
      scanWiFiNetworks(state);
      drawWiFiScan(state);
    }
    break;
  case WIFI_CONNECT:
    if (state->wifiConnectionStatus == PENDING)
    {
      if (state->networkSecurity[state->selectedNetworkIndex] == WIFI_AUTH_OPEN)
      {
        state->wifiConnectionStatus = CONNECTING;
        drawWiFiConnect(state);
        state->wifiConnectionStatus = connectToWiFi(state);
        drawWiFiConnect(state);
      }
      else
      {
        state->isEnteringPassword = true;
        state->isEnteringSSID = false;
        state->inputText = "";
        enterKeyboard(state);
      }
    }
    else
    {
      state->currentState = WIFI_CONFIG;
      drawWiFiConfig(state);
    }
    break;
  case WIFI_MANUAL_SETUP:
    if (state->selectedWiFiItem == 0)
    {
      state->isEnteringSSID = true;
      state->isEnteringPassword = false;
      state->inputText = state->wifiSSID;
      enterKeyboard(state);
    }
    else if (state->selectedWiFiItem == 1)
    {
      state->isEnteringPassword = true;
      state->isEnteringSSID = false;
      state->inputText = state->wifiPassword;
      enterKeyboard(state);
    }
    else if (state->selectedWiFiItem == 2)
    {
      if (state->wifiSSID.length() > 0)
      {
        state->selectedNetworkIndex = -1;
        state->currentState = WIFI_CONNECT;
        state->wifiConnectionStatus = CONNECTING;
        drawWiFiConnect(state);
        state->wifiConnectionStatus = connectToWiFi(state);
        drawWiFiConnect(state);
      }
    }
    else if (state->selectedWiFiItem == 3)
    {
      state->currentState = WIFI_CONFIG;
      drawWiFiConfig(state);
    }
    break;
  case KEYBOARD_INPUT:
    handleKeyboardInput(state);
    break;
  case RESET_CONFIRM: // <--- เพิ่ม case นี้ทั้งหมด
    if (state->selectedMenuItem == 0)
    {                     // Selected "Yes"
      NVIC_SystemReset(); // สั่งให้เครื่องรีสตาร์ท
    }
    else
    { // Selected "No"
      state->currentState = SUBMENU_1;
      drawSubmenu1(state);
    }
    break;
  }
}

void handleKeyboardInput(AppState *state)
{
  if (state->keyboardRow < 4)
  { // Character keys
    char selectedChar;
    if (state->keyboardMode == MODE_ALPHA_LOWER)
      selectedChar = keyboard[state->keyboardRow][state->keyboardCol];
    else if (state->keyboardMode == MODE_ALPHA_UPPER)
      selectedChar = keyboardUpper[state->keyboardRow][state->keyboardCol];
    else
      selectedChar = keyboardNumSym[state->keyboardRow][state->keyboardCol];

    if (state->inputText.length() < 64)
    {
      state->inputText += selectedChar;
    }
  }
  else
  { // Special keys row
    if (state->keyboardCol == 0)
    { // Shift / Mode
      if (state->keyboardMode == MODE_ALPHA_LOWER)
        state->keyboardMode = MODE_ALPHA_UPPER;
      else if (state->keyboardMode == MODE_ALPHA_UPPER)
        state->keyboardMode = MODE_ALPHA_LOWER;
      else
        state->keyboardMode = MODE_ALPHA_LOWER; // From Num/Sym back to Lower
    }
    else if (state->keyboardCol == 1)
    {                                             // Cancel
      state->currentState = state->previousState; // Go back to where we came from
      // Re-draw the previous screen
      switch (state->currentState)
      {
      case WIFI_CONNECT:
        drawWiFiConnect(state);
        break;
      case WIFI_MANUAL_SETUP:
        drawWiFiManualSetup(state);
        break;
      default:
        drawMainMenu(state);
        break; // Default fallback
      }
      return;
    }
    else if (state->keyboardCol == 2)
    { // OK
      if (state->isEnteringPassword)
      {
        state->wifiPassword = state->inputText;
        state->currentState = (state->selectedNetworkIndex == -1) ? WIFI_MANUAL_SETUP : WIFI_CONNECT;
        if (state->currentState == WIFI_MANUAL_SETUP)
        {
          drawWiFiManualSetup(state);
        }
        else
        {
          state->wifiConnectionStatus = CONNECTING;
          drawWiFiConnect(state);
          state->wifiConnectionStatus = connectToWiFi(state);
          drawWiFiConnect(state);
        }
      }
      else if (state->isEnteringSSID)
      {
        state->wifiSSID = state->inputText;
        state->currentState = WIFI_MANUAL_SETUP;
        drawWiFiManualSetup(state);
      }
      else
      {
        state->currentState = SUBMENU_3;
        drawSubmenu3(state);
      }
      return;
    }
  }
  drawKeyboard(state);
}