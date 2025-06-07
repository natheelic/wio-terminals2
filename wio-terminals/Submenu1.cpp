#include "Submenu1.h"
#include "Theme.h"

void drawSubmenu1(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);

  // --- Draw Header Bar ---
  tft->fillRect(0, 0, 320, 30, THEME_KEY_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Settings Menu", PADDING, 7);
  tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);

  // --- Draw Menu Cards ---
  String settingsItems[] = {"WiFi Configuration", "Display Settings", "System Info", "Reset Device"};
  for (int i = 0; i < 4; i++) {
    int y_pos = 45 + i * 45; // Adjusted spacing for smaller cards
    if (i == state->selectedWiFiItem) {
      tft->fillRoundRect(PADDING, y_pos, 320 - (PADDING*2), 40, CORNER_RADIUS, THEME_PRIMARY);
      tft->setTextColor(THEME_BG);
    } else {
      tft->fillRoundRect(PADDING, y_pos, 320 - (PADDING*2), 40, CORNER_RADIUS, THEME_KEY_BG);
      tft->drawRoundRect(PADDING, y_pos, 320 - (PADDING*2), 40, CORNER_RADIUS, THEME_SECONDARY);
      tft->setTextColor(THEME_TEXT);
    }
    tft->setTextSize(2);
    tft->drawString(settingsItems[i], PADDING + 15, y_pos + 12);
  }

  // Footer
  tft->setTextColor(THEME_WARNING);
  tft->setTextSize(1);
  tft->drawString("NAV: 5-way | (A)OK (B)Back (C)Home", 10, 220);
}