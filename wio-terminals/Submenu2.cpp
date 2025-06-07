#include "Submenu2.h"
#include "Theme.h"

void drawSubmenu2(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Data View", 20, 10);
  
  tft->setTextSize(1);
  tft->setTextColor(THEME_TEXT);
  tft->drawString("Temperature: 25.6 C", 30, 70);
  tft->drawString("Humidity: 65%", 30, 90);
  
  tft->setTextColor(THEME_WARNING);
  tft->drawString("Press any button to return", 20, 220);
}