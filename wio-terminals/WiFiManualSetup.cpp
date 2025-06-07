#include "WiFiManualSetup.h"
#include "Theme.h"

void drawWiFiManualSetup(AppState* state) {
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(THEME_BG);
    tft->setTextColor(THEME_TEXT);
    tft->setTextSize(2);
    tft->drawString("Manual WiFi Setup", 20, 10);

    tft->setTextSize(1);
    
    // SSID Field
    tft->drawString("SSID:", 20, 50);
    tft->drawRoundRect(20, 65, 280, 25, CORNER_RADIUS, THEME_SECONDARY);
    tft->setTextColor(THEME_TEXT);
    tft->drawString(state->wifiSSID, 28, 70);

    // Password Field
    tft->setTextColor(THEME_SECONDARY);
    tft->drawString("Password:", 20, 100);
    tft->drawRoundRect(20, 115, 280, 25, CORNER_RADIUS, THEME_SECONDARY);
    String maskedPassword = "";
    for (unsigned int i = 0; i < state->wifiPassword.length(); i++) {
        maskedPassword += "*";
    }
    tft->setTextColor(THEME_TEXT);
    tft->drawString(maskedPassword, 28, 120);

    // Options Menu
    String manualOptions[] = {"Enter SSID", "Enter Password", "Connect", "Back"};
    for (int i = 0; i < 4; i++) {
        int y_pos = 155 + i * 22;
        if (i == state->selectedWiFiItem) {
            tft->fillRoundRect(15, y_pos - 4, 290, 20, CORNER_RADIUS, THEME_PRIMARY);
            tft->setTextColor(THEME_BG);
        } else {
            tft->setTextColor(THEME_TEXT);
        }
        tft->drawString(String(i + 1) + ". " + manualOptions[i], 25, y_pos - 1);
    }
}