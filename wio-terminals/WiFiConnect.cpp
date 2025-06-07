#include "WiFiConnect.h"
#include "WiFiUtils.h"
#include "Theme.h"

void drawWiFiConnect(AppState* state) {
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(THEME_BG);
    
    tft->fillRect(0, 0, 320, 30, THEME_KEY_BG);
    tft->setTextColor(THEME_TEXT);
    tft->setTextSize(2);
    tft->drawString("WiFi Connect", PADDING, 7);
    tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);

    tft->fillRoundRect(PADDING, 40, 320-(PADDING*2), 150, CORNER_RADIUS, THEME_KEY_BG);
    tft->setTextSize(1);
    tft->drawString("SSID: " + state->wifiSSID, PADDING + 10, 55);
    if(state->selectedNetworkIndex != -1) {
       tft->drawString("Security: " + getSecurityTypeString(state->networkSecurity[state->selectedNetworkIndex]), PADDING + 10, 70);
    }
    
    int y_status = 110;
    const char* footer_text = "";

    switch (state->wifiConnectionStatus) {
        case PENDING:
             tft->setTextColor(THEME_WARNING);
             tft->drawString("Password required. Press (A) for keyboard.", PADDING + 10, y_status);
             footer_text = "(A)Keyboard (B)Back (C)Home";
            break;
        case CONNECTING:
            tft->setTextColor(THEME_WARNING);
            tft->drawString("Status: Connecting...", PADDING + 10, y_status);
            break;
        case SUCCESS:
            tft->setTextColor(THEME_SUCCESS);
            tft->drawString("Status: Connected successfully!", PADDING + 10, y_status);
            tft->setTextColor(THEME_TEXT);
            tft->drawString("IP: " + WiFi.localIP().toString(), PADDING + 10, y_status + 15);
            footer_text = "(A)Continue (B)Back (C)Home";
            break;
        case FAILED:
            tft->setTextColor(THEME_DANGER);
            tft->drawString("Status: Connection failed!", PADDING + 10, y_status);
            tft->setTextColor(THEME_TEXT);
            tft->drawString("Wrong password or weak signal.", PADDING + 10, y_status + 15);
            footer_text = "(A)Retry (B)Back (C)Home";
            break;
    }

    tft->setTextColor(THEME_WARNING);
    tft->setTextSize(1);
    tft->drawString(footer_text, 10, 220);
}