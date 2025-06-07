#include "WiFiScan.h"
#include "WiFiUtils.h"

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