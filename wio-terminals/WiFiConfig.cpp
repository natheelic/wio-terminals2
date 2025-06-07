#include "WiFiConfig.h"
#include "Theme.h"

void drawWiFiConfig(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);

  // --- Draw Header Bar ---
  tft->fillRect(0, 0, 320, 30, THEME_KEY_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("WiFi Configuration", PADDING, 7);
  tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);

  // --- Draw Status Card ---
  tft->fillRoundRect(PADDING, 40, 320 - (PADDING*2), 60, CORNER_RADIUS, THEME_KEY_BG);
  tft->setTextSize(1);
  if (WiFi.status() == WL_CONNECTED) {
    tft->setTextColor(THEME_SUCCESS);
    tft->drawString("STATUS: CONNECTED", PADDING + 10, 48);
    tft->setTextColor(THEME_TEXT);
    tft->drawString("SSID: " + WiFi.SSID(), PADDING + 10, 65);
    tft->drawString("IP: " + WiFi.localIP().toString(), PADDING + 10, 80);
  } else {
    tft->setTextColor(THEME_DANGER);
    tft->drawString("STATUS: DISCONNECTED", PADDING + 10, 48);
  }

  // --- Draw Menu Options ---
  String wifiOptions[] = {"Scan Networks", "Manual Setup", "Forget Network", "Back"};
  for (int i = 0; i < 4; i++) {
    int y_pos = 110 + i * 25;
     if (i == state->selectedWiFiItem) {
      tft->fillRoundRect(PADDING, y_pos, 320 - (PADDING*2), 23, CORNER_RADIUS, THEME_PRIMARY);
      tft->setTextColor(THEME_BG);
    } else {
      tft->setTextColor(THEME_TEXT);
    }
    tft->drawString(wifiOptions[i], PADDING + 10, y_pos + 4);
  }
  
  // Footer
  tft->setTextColor(THEME_WARNING);
  tft->setTextSize(1);
  tft->drawString("NAV: 5-way | (A)OK (B)Back (C)Home", 10, 220);
}