#include "MainMenu.h"

void drawMainMenu(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("WIO Terminal Menu", 60, 20);

  String menuItems[] = {"1. Settings", "2. Data View", "3. Text Input"};
  for (int i = 0; i < 3; i++) {
    if (i == state->selectedMenuItem) {
      tft->setTextColor(TFT_BLACK);
      tft->fillRect(20, 60 + i * 40, 280, 30, TFT_CYAN);
    } else {
      tft->setTextColor(TFT_WHITE);
    }
    tft->drawString(menuItems[i], 30, 65 + i * 40);
  }

  tft->setTextColor(TFT_YELLOW);
  tft->setTextSize(1);
  tft->drawString("UP/DOWN: Navigate, CENTER: Select", 20, 200);
}