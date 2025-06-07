#include "Submenu1.h"

void drawSubmenu1(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_NAVY);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("Settings Menu", 80, 20);
  tft->setTextSize(1);

  String settingsItems[] = {"WiFi Configuration", "Display Settings", "System Info", "Reset Device"};
  for (int i = 0; i < 4; i++) {
    if (i == state->selectedWiFiItem) {
      tft->setTextColor(TFT_BLACK);
      tft->fillRect(20, 60 + i * 30, 280, 25, TFT_CYAN);
    } else {
      tft->setTextColor(TFT_CYAN);
    }
    tft->drawString("- " + settingsItems[i], 30, 65 + i * 30);
  }

  tft->setTextColor(TFT_YELLOW);
  tft->drawString("UP/DOWN: Navigate, CENTER: Select, LEFT: Back", 10, 200);
}