#include "WiFiConnect.h"
#include "WiFiUtils.h"
#include "Theme.h"

void drawWiFiConnect(AppState* state) {
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(THEME_BG);
    tft->setTextColor(THEME_TEXT);
    tft->setTextSize(2);
    
    tft->drawString("WiFi Connect", 20, 20);
    
    tft->setTextSize(1);
    tft->drawString("SSID: " + state->wifiSSID, 20, 60);
    if(state->selectedNetworkIndex != -1) {
       tft->drawString("Security: " + getSecurityTypeString(state->networkSecurity[state->selectedNetworkIndex]), 20, 80);
    }

    // Status Message Area
    int y_status = 120;

    switch (state->wifiConnectionStatus) {
        case PENDING:
             tft->setTextColor(THEME_WARNING);
             if (state->selectedNetworkIndex != -1 && state->networkSecurity[state->selectedNetworkIndex] == WIFI_AUTH_OPEN) {
                tft->drawString("This is an open network.", 20, y_status);
                tft->drawString("Press CENTER to connect.", 20, y_status + 20);
             } else {
                tft->setTextColor(THEME_TEXT);
                tft->drawString("Password required.", 20, y_status);
                tft->drawString("Press CENTER to open keyboard.", 20, y_status + 20);
             }
            break;
        case CONNECTING:
            // TODO: Draw a spinner or loading animation here for better UX
            tft->setTextColor(THEME_WARNING);
            tft->drawString("Status: Connecting...", 20, y_status);
            break;
        case SUCCESS:
            tft->setTextColor(THEME_SUCCESS);
            tft->drawString("Status: Connected successfully!", 20, y_status);
            tft->setTextColor(THEME_TEXT);
            tft->drawString("IP: " + WiFi.localIP().toString(), 20, y_status + 20);
            tft->setTextColor(THEME_WARNING);
            tft->drawString("Press any button to continue.", 20, 180);
            break;
        case FAILED:
            tft->setTextColor(THEME_DANGER);
            tft->drawString("Status: Connection failed!", 20, y_status);
            tft->setTextColor(THEME_TEXT);
            tft->drawString("Wrong password or weak signal.", 20, y_status + 20);
            tft->setTextColor(THEME_WARNING);
            tft->drawString("Press any button to go back.", 20, 180);
            break;
    }
}