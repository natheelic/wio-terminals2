#include "Submenu2.h"

void drawSubmenu2(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(TFT_DARKGREEN);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  tft->drawString("Data View", 100, 20);
  
  tft->setTextSize(1);
  tft->setTextColor(TFT_GREEN);
  tft->drawString("Temperature: 25.6 C", 30, 70);
  tft->drawString("Humidity: 65%", 30, 90);
  
  tft->setTextColor(TFT_YELLOW);
  tft->drawString("Press any button to return", 20, 200);
}