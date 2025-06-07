#include "Submenu3.h"
#include "Theme.h"

void drawSubmenu3(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);
  
  tft->fillRect(0, 0, 320, 30, THEME_KEY_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Input Result", PADDING, 7);
  tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);

  tft->fillRoundRect(PADDING, 50, 320-(PADDING*2), 100, CORNER_RADIUS, THEME_KEY_BG);
  tft->setTextSize(1);
  tft->drawString("You entered:", PADDING + 10, 65);
  
  tft->setTextColor(THEME_PRIMARY);
  tft->setTextSize(2);
  tft->drawString(state->inputText, PADDING + 10, 95);

  tft->setTextColor(THEME_WARNING);
  tft->setTextSize(1);
  tft->drawString("(B)Back | (C)Home", 20, 220);
}