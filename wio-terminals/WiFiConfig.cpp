#include "WiFiConfig.h"

void drawWiFiConfig(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_BLUE);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("WiFi Configuration", 50, 20);
  
  tft->setTextSize(1);
  if (WiFi.status() == WL_CONNECTED) {
    tft->setTextColor(TFT_GREEN);
    tft->drawString("Status: Connected", 30, 60);
    tft->setTextColor(TFT_WHITE);
    tft->drawString("SSID: " + WiFi.SSID(), 30, 80);
    tft->drawString("IP: " + WiFi.localIP().toString(), 30, 100);
  } else {
    tft->setTextColor(TFT_RED);
    tft->drawString("Status: Disconnected", 30, 60);
  }
  
  tft->setTextColor(TFT_CYAN);
  String wifiOptions[] = {"Scan Networks", "Manual Setup", "Disconnect", "Back"};
  for (int i = 0; i < 4; i++) {
    if (i == state->selectedWiFiItem) {
      tft->setTextColor(TFT_BLACK);
      tft->fillRect(20, 140 + i * 20, 280, 18, TFT_CYAN);
    } else {
      tft->setTextColor(TFT_CYAN);
    }
    tft->drawString(String(i + 1) + ". " + wifiOptions[i], 30, 143 + i * 20);
  }
  
  tft->setTextColor(TFT_YELLOW);
  tft->drawString("UP/DOWN: Navigate, CENTER: Select", 20, 220);
}