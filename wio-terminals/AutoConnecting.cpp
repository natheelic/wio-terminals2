#include "AutoConnecting.h"

void drawAutoConnecting(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("Auto-Connect", 80, 40);
  
  tft->setTextSize(1);
  tft->drawString("Loading saved network...", 40, 80);
  tft->drawString("SSID: " + state->wifiSSID, 40, 100);

  if (state->wifiConnectionStatus == CONNECTING) {
      tft->setTextColor(TFT_YELLOW);
      tft->drawString("Status: Connecting...", 40, 140);
  } else if (state->wifiConnectionStatus == SUCCESS) {
      tft->setTextColor(TFT_GREEN);
      tft->drawString("Status: Connected!", 40, 140);
  } else if (state->wifiConnectionStatus == FAILED) {
      tft->setTextColor(TFT_RED);
      tft->drawString("Status: Failed to connect.", 40, 140);
  }
}