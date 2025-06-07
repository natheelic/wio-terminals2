#include "WiFiConnect.h"
#include "WiFiUtils.h"

void drawWiFiConnect(AppState* state) {
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(TFT_DARKGREEN);
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    
    tft->drawString("WiFi Connect", 70, 20);
    
    tft->setTextSize(1);
    tft->drawString("SSID: " + state->wifiSSID, 30, 60);
    if(state->selectedNetworkIndex != -1) {
       tft->drawString("Security: " + getSecurityTypeString(state->networkSecurity[state->selectedNetworkIndex]), 30, 80);
    }

    switch (state->wifiConnectionStatus) {
        case PENDING:
             tft->setTextColor(TFT_YELLOW);
             if (state->selectedNetworkIndex != -1 && state->networkSecurity[state->selectedNetworkIndex] == WIFI_AUTH_OPEN) {
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