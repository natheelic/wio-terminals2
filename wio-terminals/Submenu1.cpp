#include "Submenu1.h"
#include "Theme.h"

void drawSubmenu1(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Settings Menu", 20, 10);
  tft->setTextSize(1);

  String settingsItems[] = {"WiFi Configuration", "Display Settings", "System Info", "Reset Device"};
  for (int i = 0; i < 4; i++) {
    int y_pos = 50 + i * 30;
    if (i == state->selectedWiFiItem) {
      tft->fillRoundRect(15, y_pos - 5, 290, 28, CORNER_RADIUS, THEME_PRIMARY);
      tft->setTextColor(THEME_BG);
    } else {
      tft->drawRoundRect(15, y_pos - 5, 290, 28, CORNER_RADIUS, THEME_SECONDARY);
      tft->setTextColor(THEME_TEXT);
    }
    tft->drawString("- " + settingsItems[i], 25, y_pos);
  }

  tft->setTextColor(THEME_WARNING);
  tft->drawString("NAV: 5-way | (A)OK (B)Back (C)Home", 10, 220);
  // tft->drawString("UP/DOWN: Navigate, CENTER: Select, LEFT: Back", 10, 220);
}