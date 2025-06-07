#include "WiFiScan.h"
#include "WiFiUtils.h"
#include "Theme.h" // Assuming you are using the theme file

// Helper function to draw WiFi signal strength icon
void drawSignalStrength(TFT_eSPI* tft, int x, int y, int rssi) {
    int bars = 0;
    if (rssi > -67) bars = 4;
    else if (rssi > -70) bars = 3;
    else if (rssi > -80) bars = 2;
    else if (rssi > -90) bars = 1;

    for (int i = 0; i < 4; i++) {
        int barHeight = 4 + (i * 3);
        uint16_t barColor = (i < bars) ? THEME_TEXT : THEME_SECONDARY;
        tft->fillRect(x + (i * 5), y - barHeight, 4, barHeight, barColor);
    }
}

// Helper function to draw lock icon
void drawLockIcon(TFT_eSPI* tft, int x, int y, uint16_t bgColor) {
    tft->fillRoundRect(x, y, 12, 10, 2, THEME_TEXT);
    tft->fillCircle(x + 6, y - 4, 5, THEME_TEXT);
    tft->fillCircle(x + 6, y - 4, 3, bgColor);
}

void drawWiFiScan(AppState* state) {
    const int MAX_VISIBLE_NETWORKS = 6; // จำนวนเครือข่ายสูงสุดที่จะแสดงในหนึ่งหน้าจอ
    TFT_eSPI* tft = state->tft;

    tft->fillScreen(THEME_BG);
    tft->setTextColor(THEME_TEXT);
    tft->setTextSize(2);
    tft->drawString("WiFi Networks", 20, 10);
    tft->setTextSize(1);

    if (state->foundNetworks == 0) {
        tft->setTextColor(THEME_DANGER);
        tft->drawString("No networks found.", 30, 80);
        tft->drawString("Press (A) to scan again.", 30, 100);
    } else {
        // --- Draw Scroll Indicators ---
        if (state->wifiScanScrollOffset > 0) {
            tft->fillTriangle(310, 40, 305, 50, 315, 50, THEME_SECONDARY); // Up Arrow
        }
        if (state->wifiScanScrollOffset + MAX_VISIBLE_NETWORKS < state->foundNetworks) {
            tft->fillTriangle(310, 210, 305, 200, 315, 200, THEME_SECONDARY); // Down Arrow
        }

        // --- Draw Network List with Scrolling ---
        for (int i = 0; i < MAX_VISIBLE_NETWORKS; i++) {
            int networkIndex = state->wifiScanScrollOffset + i;
            if (networkIndex >= state->foundNetworks) {
                break; // Stop if we have drawn all found networks
            }

            int y_pos = 50 + i * 28;
            uint16_t currentBgColor = THEME_BG;

            if (networkIndex == state->selectedWiFiItem) {
                tft->fillRoundRect(10, y_pos - 5, 290, 26, CORNER_RADIUS, THEME_PRIMARY);
                tft->setTextColor(THEME_BG);
                currentBgColor = THEME_PRIMARY;
            } else {
                tft->setTextColor(THEME_TEXT);
            }
            
            tft->drawString(state->networkNames[networkIndex], 20, y_pos);

            // Draw icons on the right side
            drawSignalStrength(tft, 230, y_pos + 12, state->networkRSSI[networkIndex]);
            if (state->networkSecurity[networkIndex] != WIFI_AUTH_OPEN) {
                drawLockIcon(tft, 260, y_pos + 2, currentBgColor);
            }
        }
    }
    tft->setTextColor(THEME_WARNING);    
    tft->setTextColor(THEME_TEXT);
    tft->drawString("NAV: 5-way | (A)Connect (B)Back (C)Home", 10, 220);
}