#include "WiFiConfig.h"
#include "Theme.h"

void drawWiFiConfig(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("WiFi Configuration", 20, 10);
  
  tft->setTextSize(1);
  if (WiFi.status() == WL_CONNECTED) {
    tft->setTextColor(THEME_SUCCESS);
    tft->drawString("Status: Connected", 20, 50);
    tft->setTextColor(THEME_TEXT);
    tft->drawString("SSID: " + WiFi.SSID(), 20, 70);
    tft->drawString("IP: " + WiFi.localIP().toString(), 20, 90);
  } else {
    tft->setTextColor(THEME_DANGER);
    tft->drawString("Status: Disconnected", 20, 50);
  }
  
  tft->setTextColor(THEME_TEXT);
  String wifiOptions[] = {"Scan Networks", "Manual Setup", "Forget Network", "Back"};
  for (int i = 0; i < 4; i++) {
    int y_pos = 120 + i * 25;
    if (i == state->selectedWiFiItem) {
      tft->fillRoundRect(15, y_pos - 5, 290, 23, CORNER_RADIUS, THEME_PRIMARY);
      tft->setTextColor(THEME_BG);
    } else {
      tft->drawRoundRect(15, y_pos - 5, 290, 23, CORNER_RADIUS, THEME_SECONDARY);
      tft->setTextColor(THEME_TEXT);
    }
    tft->drawString(String(i + 1) + ". " + wifiOptions[i], 25, y_pos);
  }
  
  tft->setTextColor(THEME_WARNING);
  tft->drawString("UP/DOWN: Navigate, CENTER: Select", 20, 220);
}