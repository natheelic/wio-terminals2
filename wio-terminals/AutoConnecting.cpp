#include "AutoConnecting.h"
#include "Theme.h"

void drawAutoConnecting(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Auto-Connect", 80, 40);
  
  tft->setTextSize(1);
  tft->drawString("Loading saved network...", 40, 80);
  tft->drawString("SSID: " + state->wifiSSID, 40, 100);

  // TODO: Draw a spinner or loading animation here for better UX
  
  if (state->wifiConnectionStatus == CONNECTING) {
      tft->setTextColor(THEME_WARNING);
      tft->drawString("Status: Connecting...", 40, 140);
  } else if (state->wifiConnectionStatus == SUCCESS) {
      tft->setTextColor(THEME_SUCCESS);
      tft->drawString("Status: Connected!", 40, 140);
  } else if (state->wifiConnectionStatus == FAILED) {
      tft->setTextColor(THEME_DANGER);
      tft->drawString("Status: Failed to connect.", 40, 140);
  }
}