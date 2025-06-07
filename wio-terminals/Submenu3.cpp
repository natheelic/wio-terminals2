#include "Submenu3.h"
#include "Theme.h"

void drawSubmenu3(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Input Result", 20, 10);
  
  tft->setTextSize(1);
  tft->drawString("You entered:", 30, 70);
  
  tft->setTextColor(THEME_PRIMARY);
  tft->setTextSize(2);
  tft->drawString(state->inputText, 30, 100);

  tft->setTextColor(THEME_WARNING);
  tft->setTextSize(1);
  tft->drawString("Press any button to return", 20, 220);
}