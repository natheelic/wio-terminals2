#include "WiFiScan.h"
#include "WiFiUtils.h"
#include "Theme.h"

// Helper function to draw WiFi signal strength icon
void drawSignalStrength(TFT_eSPI* tft, int x, int y, int rssi) {
    int bars = 0;
    if (rssi > -67) bars = 4;
    else if (rssi > -70) bars = 3;
    else if (rssi > -80) bars = 2;
    else if (rssi > -90) bars = 1;

    for (int i = 0; i < 4; i++) {
        int barHeight = 4 + (i * 3);
        if (i < bars) {
            tft->fillRect(x + (i * 5), y - barHeight, 4, barHeight, THEME_TEXT);
        } else {
            tft->fillRect(x + (i * 5), y - barHeight, 4, barHeight, THEME_SECONDARY);
        }
    }
}

// Helper function to draw lock icon
void drawLockIcon(TFT_eSPI* tft, int x, int y) {
    tft->fillRoundRect(x, y, 12, 10, 2, THEME_TEXT);
    tft->fillCircle(x + 6, y - 4, 5, THEME_TEXT);
    tft->fillCircle(x + 6, y - 4, 3, THEME_BG);
}


void drawWiFiScan(AppState* state) {
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(THEME_BG);
    tft->setTextColor(THEME_TEXT);
    tft->setTextSize(2);
    tft->drawString("WiFi Networks", 20, 10);
    tft->setTextSize(1);

    if (state->foundNetworks == 0) {
        tft->setTextColor(THEME_DANGER);
        tft->drawString("No networks found.", 30, 80);
        tft->drawString("Press CENTER to scan again.", 30, 100);
    } else {
        for (int i = 0; i < state->foundNetworks && i < 7; i++) { // Show up to 7 networks
            int y_pos = 40 + i * 28;
            if (i == state->selectedWiFiItem) {
                tft->fillRoundRect(10, y_pos - 5, 300, 26, CORNER_RADIUS, THEME_PRIMARY);
                tft->setTextColor(THEME_BG);
            } else {
                tft->setTextColor(THEME_TEXT);
            }
            
            tft->drawString(state->networkNames[i], 20, y_pos);

            // Draw icons on the right side
            drawSignalStrength(tft, 250, y_pos + 12, state->networkRSSI[i]);
            if (state->networkSecurity[i] != WIFI_AUTH_OPEN) {
                drawLockIcon(tft, 280, y_pos + 2);
            }
        }
    }
    tft->setTextColor(THEME_WARNING);
    tft->drawString("NAV: 5-way | (A)Connect (B)Back (C)Home", 10, 220);
    // tft->drawString("UP/DOWN: Select, CENTER: Connect, LEFT: Back", 10, 220);
}