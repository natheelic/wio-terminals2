#include "AutoConnecting.h"
#include "Theme.h"

void drawAutoConnecting(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);

  tft->fillRect(0, 0, 320, 30, THEME_KEY_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Auto-Connect", PADDING, 7);
  tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);

  tft->fillRoundRect(PADDING, 50, 320-(PADDING*2), 120, CORNER_RADIUS, THEME_KEY_BG);
  tft->setTextSize(1);
  tft->drawString("Attempting to connect to saved network...", PADDING + 10, 65);
  tft->drawString("SSID: " + state->wifiSSID, PADDING + 10, 85);

  if (state->wifiConnectionStatus == CONNECTING) {
      tft->setTextColor(THEME_WARNING);
      tft->drawString("Status: Connecting...", PADDING + 10, 120);
  } else if (state->wifiConnectionStatus == SUCCESS) {
      tft->setTextColor(THEME_SUCCESS);
      tft->drawString("Status: Connected!", PADDING + 10, 120);
  } else if (state->wifiConnectionStatus == FAILED) {
      tft->setTextColor(THEME_DANGER);
      tft->drawString("Status: Failed to connect.", PADDING + 10, 120);
  }
}