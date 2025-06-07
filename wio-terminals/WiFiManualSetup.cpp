#include "WiFiManualSetup.h"
#include "Theme.h"

void drawWiFiManualSetup(AppState* state) {
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(THEME_BG);

    // --- Draw Header Bar ---
    tft->fillRect(0, 0, 320, 30, THEME_KEY_BG);
    tft->setTextColor(THEME_TEXT);
    tft->setTextSize(2);
    tft->drawString("Manual WiFi Setup", PADDING, 7);
    tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);
    
    // --- Draw Form Fields ---
    tft->setTextSize(1);
    tft->setTextColor(THEME_TEXT);
    tft->drawString("SSID:", PADDING, 45);
    tft->fillRoundRect(PADDING, 60, 320-(PADDING*2), 30, CORNER_RADIUS, THEME_KEY_BG);
    tft->drawRoundRect(PADDING, 60, 320-(PADDING*2), 30, CORNER_RADIUS, THEME_SECONDARY);
    tft->setTextColor(THEME_TEXT);
    tft->setTextSize(2);
    tft->drawString(state->wifiSSID, PADDING + 5, 67);

    tft->setTextSize(1);
    tft->setTextColor(THEME_TEXT);
    tft->drawString("Password:", PADDING, 100);
    tft->fillRoundRect(PADDING, 115, 320-(PADDING*2), 30, CORNER_RADIUS, THEME_KEY_BG);
    tft->drawRoundRect(PADDING, 115, 320-(PADDING*2), 30, CORNER_RADIUS, THEME_SECONDARY);
    String maskedPassword = "";
    for (unsigned int i = 0; i < state->wifiPassword.length(); i++) maskedPassword += "*";
    tft->setTextColor(THEME_TEXT);
    tft->setTextSize(2);
    tft->drawString(maskedPassword, PADDING + 5, 122);

    // --- Draw Menu Options ---
    String manualOptions[] = {"Enter SSID", "Enter Password", "Connect", "Back"};
    tft->setTextSize(1);
    for (int i = 0; i < 4; i++) {
        int y_pos = 155 + i * 18;
        if (i == state->selectedWiFiItem) {
            tft->fillRoundRect(PADDING, y_pos, 320 - (PADDING*2), 17, CORNER_RADIUS, THEME_PRIMARY);
            tft->setTextColor(THEME_BG);
        } else {
            tft->setTextColor(THEME_TEXT);
        }
        tft->drawString(manualOptions[i], PADDING + 5, y_pos + 2);
    }
    
    // Footer
    tft->setTextColor(THEME_WARNING);
    tft->setTextSize(1);
    tft->drawString("NAV: 5-way | (A)OK (B)Back (C)Home", 10, 220);
}