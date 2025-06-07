#include "WiFiManualSetup.h"

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
    for (unsigned int i = 0; i < state->wifiPassword.length(); i++) {
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