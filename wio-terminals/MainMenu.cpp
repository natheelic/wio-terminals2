#include "MainMenu.h"
#include "Theme.h"

void drawMainMenu(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("WIO Terminal Menu", 60, 20);

  String menuItems[] = {"1. Settings", "2. Data View", "3. Text Input"};
  for (int i = 0; i < 3; i++) {
    int y_pos = 65 + i * 40;
    if (i == state->selectedMenuItem) {
      tft->fillRoundRect(20, y_pos - 5, 280, 30, CORNER_RADIUS, THEME_PRIMARY);
      tft->setTextColor(THEME_BG);
    } else {
      tft->drawRoundRect(20, y_pos - 5, 280, 30, CORNER_RADIUS, THEME_SECONDARY);
      tft->setTextColor(THEME_TEXT);
    }
    tft->drawString(menuItems[i], 30, y_pos);
  }

  tft->setTextColor(THEME_WARNING);
  tft->setTextSize(1);
  tft->drawString("UP/DOWN: Navigate, CENTER: Select", 20, 220);
}