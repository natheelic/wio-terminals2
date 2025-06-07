#include "Submenu3.h"

void drawSubmenu3(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_MAROON);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("Input Result", 80, 20);
  
  tft->setTextSize(1);
  tft->drawString("You entered:", 30, 70);
  
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString(state->inputText, 30, 100);

  tft->setTextColor(TFT_YELLOW);
  tft->setTextSize(1);
  tft->drawString("Press any button to return", 20, 200);
}