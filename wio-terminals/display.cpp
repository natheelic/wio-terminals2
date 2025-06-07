#include "display.h"

void initDisplay(TFT_eSPI* tft) {
  tft->init();
  tft->setRotation(3);
  tft->fillScreen(TFT_BLACK);
}

String getSecurityTypeString(int securityType) {
  switch (securityType) {
    case WIFI_AUTH_OPEN: return "Open";
    case WIFI_AUTH_WEP: return "WEP";
    case WIFI_AUTH_WPA_PSK: return "WPA";
    case WIFI_AUTH_WPA2_PSK: return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2-Enterprise";
    default: return "Unknown";
  }
}

void drawMainMenu(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("WIO Terminal Menu", 60, 20);

  String menuItems[] = {"1. Settings", "2. Data View", "3. Text Input"};
  for (int i = 0; i < 3; i++) {
    if (i == state->selectedMenuItem) {
      tft->setTextColor(TFT_BLACK);
      tft->fillRect(20, 60 + i * 40, 280, 30, TFT_CYAN);
    } else {
      tft->setTextColor(TFT_WHITE);
    }
    tft->drawString(menuItems[i], 30, 65 + i * 40);
  }

  tft->setTextColor(TFT_YELLOW);
  tft->setTextSize(1);
  tft->drawString("UP/DOWN: Navigate, CENTER: Select", 20, 200);
}

void drawSubmenu1(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_NAVY);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("Settings Menu", 80, 20);
  tft->setTextSize(1);

  String settingsItems[] = {"WiFi Configuration", "Display Settings", "System Info", "Reset Device"};
  for (int i = 0; i < 4; i++) {
    if (i == state->selectedWiFiItem) {
      tft->setTextColor(TFT_BLACK);
      tft->fillRect(20, 60 + i * 30, 280, 25, TFT_CYAN);
    } else {
      tft->setTextColor(TFT_CYAN);
    }
    tft->drawString("- " + settingsItems[i], 30, 65 + i * 30);
  }

  tft->setTextColor(TFT_YELLOW);
  tft->drawString("UP/DOWN: Navigate, CENTER: Select, LEFT: Back", 10, 200);
}

void drawSubmenu2(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_DARKGREEN);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("Data View", 100, 20);
  
  tft->setTextSize(1);
  tft->setTextColor(TFT_GREEN);
  tft->drawString("Temperature: 25.6 C", 30, 70);
  tft->drawString("Humidity: 65%", 30, 90);
  
  tft->setTextColor(TFT_YELLOW);
  tft->drawString("Press any button to return", 20, 200);
}

void drawSubmenu3(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_MAROON);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("Input Result", 80, 20);
  
  tft->setTextSize(1);
  tft->drawString("You entered:", 30, 70);
  
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString(state->inputText, 30, 100);

  tft->setTextColor(TFT_YELLOW);
  tft->setTextSize(1);
  tft->drawString("Press any button to return", 20, 200);
}

void drawWiFiConfig(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_BLUE);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("WiFi Configuration", 50, 20);
  
  tft->setTextSize(1);
  if (WiFi.status() == WL_CONNECTED) {
    tft->setTextColor(TFT_GREEN);
    tft->drawString("Status: Connected", 30, 60);
    tft->setTextColor(TFT_WHITE);
    tft->drawString("SSID: " + WiFi.SSID(), 30, 80);
    tft->drawString("IP: " + WiFi.localIP().toString(), 30, 100);
  } else {
    tft->setTextColor(TFT_RED);
    tft->drawString("Status: Disconnected", 30, 60);
  }
  
  tft->setTextColor(TFT_CYAN);
  String wifiOptions[] = {"Scan Networks", "Manual Setup", "Disconnect", "Back"};
  for (int i = 0; i < 4; i++) {
    if (i == state->selectedWiFiItem) {
      tft->setTextColor(TFT_BLACK);
      tft->fillRect(20, 140 + i * 20, 280, 18, TFT_CYAN);
    } else {
      tft->setTextColor(TFT_CYAN);
    }
    tft->drawString(String(i + 1) + ". " + wifiOptions[i], 30, 143 + i * 20);
  }
  
  tft->setTextColor(TFT_YELLOW);
  tft->drawString("UP/DOWN: Navigate, CENTER: Select", 20, 220);
}


void drawWiFiScan(AppState* state) {
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(TFT_BLACK);
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->drawString("WiFi Networks", 80, 10);
    tft->setTextSize(1);

    if (state->foundNetworks == 0) {
        tft->setTextColor(TFT_RED);
        tft->drawString("No networks found.", 30, 60);
        tft->drawString("Press CENTER to scan again.", 30, 80);
    } else {
        for (int i = 0; i < state->foundNetworks && i < 8; i++) {
            if (i == state->selectedWiFiItem) {
                tft->setTextColor(TFT_BLACK);
                tft->fillRect(10, 35 + i * 25, 300, 23, TFT_CYAN);
            } else {
                tft->setTextColor(TFT_WHITE);
            }
            
            String networkLine = state->networkNames[i] + " (" + state->networkRSSI[i] + "dBm) " + getSecurityTypeString(state->networkSecurity[i]);
            tft->drawString(networkLine, 15, 38 + i * 25);
        }
    }
    tft->setTextColor(TFT_YELLOW);
    tft->drawString("UP/DOWN: Select, CENTER: Connect, LEFT: Back", 10, 220);
}


void drawWiFiConnect(AppState* state) {
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(TFT_DARKGREEN);
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    
    tft->drawString("WiFi Connect", 70, 20);
    
    tft->setTextSize(1);
    tft->drawString("SSID: " + state->wifiSSID, 30, 60);
    if(state->selectedNetworkIndex >= 0 && state->selectedNetworkIndex < state->foundNetworks) {
       tft->drawString("Security: " + getSecurityTypeString(state->networkSecurity[state->selectedNetworkIndex]), 30, 80);
    }

    switch (state->wifiConnectionStatus) {
        case PENDING:
             tft->setTextColor(TFT_YELLOW);
             if (state->networkSecurity[state->selectedNetworkIndex] == WIFI_AUTH_OPEN) {
                tft->drawString("This is an open network.", 30, 120);
                tft->drawString("Press CENTER to connect.", 30, 140);
             } else {
                tft->drawString("Password required.", 30, 120);
                tft->drawString("Press CENTER to open keyboard.", 30, 140);
             }
            break;
        case CONNECTING:
            tft->setTextColor(TFT_YELLOW);
            tft->drawString("Status: Connecting...", 30, 120);
            break;
        case SUCCESS:
            tft->setTextColor(TFT_GREEN);
            tft->drawString("Status: Connected successfully!", 30, 120);
            tft->drawString("IP: " + WiFi.localIP().toString(), 30, 140);
            tft->setTextColor(TFT_YELLOW);
            tft->drawString("Press any button to continue.", 30, 180);
            break;
        case FAILED:
            tft->setTextColor(TFT_RED);
            tft->drawString("Status: Connection failed!", 30, 120);
            tft->drawString("Wrong password or weak signal.", 30, 140);
            tft->setTextColor(TFT_YELLOW);
            tft->drawString("Press any button to go back.", 30, 180);
            break;
    }
}

void drawWiFiManualSetup(AppState* state) {
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(TFT_NAVY);
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->drawString("Manual WiFi Setup", 60, 20);

    tft->setTextSize(1);
    tft->setTextColor(TFT_LIGHTGREY);
    
    tft->drawString("SSID:", 30, 70);
    tft->drawRect(30, 90, 260, 20, TFT_WHITE);
    tft->setTextColor(TFT_WHITE);
    tft->drawString(state->wifiSSID, 35, 95);

    tft->setTextColor(TFT_LIGHTGREY);
    tft->drawString("Password:", 30, 125);
    tft->drawRect(30, 145, 260, 20, TFT_WHITE);
    String maskedPassword = "";
    for (int i = 0; i < state->wifiPassword.length(); i++) {
        maskedPassword += "*";
    }
    tft->setTextColor(TFT_WHITE);
    tft->drawString(maskedPassword, 35, 150);

    String manualOptions[] = {"Enter SSID", "Enter Password", "Connect", "Back"};
    for (int i = 0; i < 4; i++) {
        if (i == state->selectedWiFiItem) {
            tft->setTextColor(TFT_BLACK);
            tft->fillRect(30, 180 + i * 20, 260, 18, TFT_CYAN);
        } else {
            tft->setTextColor(TFT_CYAN);
        }
        tft->drawString(String(i + 1) + ". " + manualOptions[i], 35, 183 + i * 20);
    }
}

void drawKeyboard(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(0x3186); 
  tft->setTextSize(1);

  // Header
  tft->fillRect(0, 0, tft->width(), 24, TFT_BLACK);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  const char* title = "Text Input";
  if (state->isEnteringSSID) title = "Enter SSID";
  if (state->isEnteringPassword) title = "Enter Password";
  tft->drawString(title, 10, 5);

  // Input field
  tft->fillRect(10, 30, 300, 24, TFT_WHITE);
  tft->setTextColor(TFT_BLACK);
  tft->setTextSize(2);
  String displayText = state->isEnteringPassword ? String("****************").substring(0, state->inputText.length()) : state->inputText;
  tft->drawString(displayText, 15, 34);

  if (millis() % 1000 < 500) {
    int16_t cursorX = 15 + tft->textWidth(displayText);
    tft->fillRect(cursorX, 32, 2, 20, TFT_BLACK);
  }

  int keyWidth = 28;
  int keyHeight = 24;
  int keySpacing = 4;
  int startY = 60;
  
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 10; col++) {
      int x = 10 + col * (keyWidth + keySpacing);
      int y = startY + row * (keyHeight + keySpacing);
      bool isSelected = (row == state->keyboardRow && col == state->keyboardCol && state->keyboardRow < 4);
      
      tft->fillRoundRect(x, y, keyWidth, keyHeight, 3, isSelected ? TFT_CYAN : TFT_DARKGREY);
      tft->setTextColor(isSelected ? TFT_BLACK : TFT_WHITE);
      tft->setTextSize(2);
      
      char keyChar = state->keyboardUpperCase ? keyboardUpper[row][col] : keyboard[row][col];
      tft->drawChar(keyChar, x + 8, y + 4);
    }
  }

  int specialY = startY + 4 * (keyHeight + keySpacing);
  bool shiftSelected = (state->keyboardRow == 4 && state->keyboardCol == 0);
  // *** FIXED LINE: Replaced TFT_SKYBLUE with TFT_BLUE ***
  tft->fillRoundRect(10, specialY, 60, keyHeight, 3, shiftSelected ? TFT_CYAN : (state->keyboardUpperCase ? TFT_BLUE : TFT_DARKGREY));
  tft->setTextColor(shiftSelected ? TFT_BLACK : TFT_WHITE);
  tft->drawString(state->keyboardUpperCase ? "ABC" : "abc", 15, specialY + 4);
  
  bool spaceSelected = (state->keyboardRow == 4 && state->keyboardCol == 1);
  tft->fillRoundRect(78, specialY, 120, keyHeight, 3, spaceSelected ? TFT_CYAN : TFT_DARKGREY);
  tft->setTextColor(spaceSelected ? TFT_BLACK : TFT_WHITE);
  tft->drawString("space", 95, specialY + 4);

  bool backspaceSelected = (state->keyboardRow == 4 && state->keyboardCol == 2);
  tft->fillRoundRect(206, specialY, 50, keyHeight, 3, backspaceSelected ? TFT_CYAN : TFT_DARKGREY);
  tft->setTextColor(backspaceSelected ? TFT_BLACK : TFT_WHITE);
  tft->drawString("del", 211, specialY + 4);

  bool returnSelected = (state->keyboardRow == 4 && state->keyboardCol == 3);
  tft->fillRoundRect(264, specialY, 50, keyHeight, 3, returnSelected ? TFT_CYAN : TFT_DARKGREEN);
  tft->setTextColor(returnSelected ? TFT_BLACK : TFT_WHITE);
  tft->drawString("OK", 274, specialY + 4);
}

void scanWiFiNetworks(AppState* state) {
  state->tft->fillScreen(TFT_BLACK);
  state->tft->setTextColor(TFT_YELLOW);
  state->tft->setTextSize(2);
  state->tft->drawString("Scanning...", 100, 100);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  state->foundNetworks = WiFi.scanNetworks();
  if (state->foundNetworks > 10) state->foundNetworks = 10;

  for (int i = 0; i < state->foundNetworks; i++) {
    state->networkNames[i] = WiFi.SSID(i);
    state->networkRSSI[i] = WiFi.RSSI(i);
    state->networkSecurity[i] = WiFi.encryptionType(i);
  }
  state->selectedWiFiItem = 0;
}

ConnectionStatus connectToWiFi(AppState* state) {
  const char* ssid = state->wifiSSID.c_str();
  const char* password = state->wifiPassword.c_str();

  int securityType = (state->selectedNetworkIndex != -1) ? state->networkSecurity[state->selectedNetworkIndex] : WIFI_AUTH_WPA2_PSK;
  
  if (securityType == WIFI_AUTH_OPEN) {
    WiFi.begin(ssid);
  } else {
    WiFi.begin(ssid, password);
  }

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    attempts++;
  }

  return (WiFi.status() == WL_CONNECTED) ? SUCCESS : FAILED;
}