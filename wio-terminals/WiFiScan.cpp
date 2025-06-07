#include "WiFiScan.h"
#include "WiFiUtils.h"
#include "Theme.h"

// --- REVISED HELPER FUNCTIONS ---

// Helper function to draw WiFi signal strength icon
// NOW ACCEPTS COLORS AS PARAMETERS
void drawSignalStrength(TFT_eSPI* tft, int x, int y, int rssi, uint16_t activeColor, uint16_t inactiveColor) {
    int bars = 0;
    if (rssi > -67) bars = 4;
    else if (rssi > -70) bars = 3;
    else if (rssi > -80) bars = 2;
    else bars = 1;

    for (int i = 0; i < 4; i++) {
        int barHeight = 4 + (i * 3);
        uint16_t barColor = (i < bars) ? activeColor : inactiveColor;
        tft->fillRect(x + (i * 5), y - barHeight, 4, barHeight, barColor);
    }
}

// Helper function to draw lock icon
// NOW ACCEPTS COLORS AS PARAMETERS
void drawLockIcon(TFT_eSPI* tft, int x, int y, uint16_t iconColor, uint16_t bgColor) {
    tft->fillRoundRect(x, y, 12, 10, 2, iconColor);
    tft->fillCircle(x + 6, y - 4, 5, iconColor);
    tft->fillCircle(x + 6, y - 4, 3, bgColor);
}


// --- REVISED MAIN DRAW FUNCTION ---

void drawWiFiScan(AppState* state) {
    const int MAX_VISIBLE_NETWORKS = 5;
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(THEME_BG);

    // Header Bar
    tft->fillRect(0, 0, 320, 30, THEME_KEY_BG);
    tft->setTextColor(THEME_TEXT);
    tft->setTextSize(2);
    tft->drawString("WiFi Networks", PADDING, 7);
    tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);

    if (state->foundNetworks == 0) {
        tft->setTextColor(THEME_DANGER);
        tft->drawString("No networks found.", 30, 100);
        tft->drawString("Press (A) to scan again.", 30, 120);
    } else {
        // Scroll Indicators
        if (state->wifiScanScrollOffset > 0) tft->fillTriangle(310, 40, 305, 50, 315, 50, THEME_SECONDARY);
        if (state->wifiScanScrollOffset + MAX_VISIBLE_NETWORKS < state->foundNetworks) tft->fillTriangle(310, 210, 305, 200, 315, 200, THEME_SECONDARY);

        // Network List
        for (int i = 0; i < MAX_VISIBLE_NETWORKS; i++) {
            int networkIndex = state->wifiScanScrollOffset + i;
            if (networkIndex >= state->foundNetworks) break;

            int y_pos = 45 + i * 32;
            uint16_t iconActiveColor, iconInactiveColor, iconBgColor;

            if (networkIndex == state->selectedWiFiItem) {
                tft->fillRoundRect(PADDING, y_pos - 5, 320 - (PADDING*2), 30, CORNER_RADIUS, THEME_PRIMARY);
                tft->setTextColor(THEME_BG);
                // Set icon colors for selected state
                iconActiveColor = THEME_BG;
                iconInactiveColor = THEME_BG;
                iconBgColor = THEME_PRIMARY;
            } else {
                tft->setTextColor(THEME_TEXT);
                // Set icon colors for default state
                iconActiveColor = THEME_TEXT;
                iconInactiveColor = THEME_SECONDARY;
                iconBgColor = THEME_BG;
            }
            
            tft->drawString(state->networkNames[networkIndex], PADDING + 10, y_pos);

            // Call helper functions with correct colors
            drawSignalStrength(tft, 230, y_pos + 12, state->networkRSSI[networkIndex], iconActiveColor, iconInactiveColor);
            if (state->networkSecurity[networkIndex] != WIFI_AUTH_OPEN) {
                drawLockIcon(tft, 260, y_pos + 2, iconActiveColor, iconBgColor);
            }
        }
    }
    // Footer
    tft->setTextColor(THEME_WARNING);
    tft->setTextSize(1);
    tft->drawString("NAV: 5-way | (A)Connect (B)Back (C)Home", 10, 220);
}