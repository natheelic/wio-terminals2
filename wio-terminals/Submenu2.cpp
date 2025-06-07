#include "Submenu2.h"
#include "Theme.h"

// Helper function to draw a simple thermometer icon
void drawTempIcon(TFT_eSPI* tft, int x, int y) {
    tft->fillCircle(x, y + 12, 8, THEME_PRIMARY);
    tft->fillRoundRect(x - 4, y - 10, 8, 25, 4, THEME_PRIMARY);
    tft->fillCircle(x, y + 12, 5, THEME_BG);
}

// Helper function to draw a simple humidity/drop icon
void drawHumidIcon(TFT_eSPI* tft, int x, int y) {
    tft->fillTriangle(x, y - 10, x - 8, y + 5, x + 8, y + 5, THEME_PRIMARY);
    tft->fillCircle(x, y + 5, 8, THEME_PRIMARY);
}


void drawSubmenu2(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);
  
  // --- Draw Header Bar ---
  tft->fillRect(0, 0, 320, 30, THEME_KEY_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Data View", PADDING, 7);
  tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);

  // --- Draw Temperature Card ---
  int card_y1 = 45;
  tft->fillRoundRect(PADDING, card_y1, 320 - (PADDING*2), 75, CORNER_RADIUS, THEME_KEY_BG);
  drawTempIcon(tft, PADDING + 30, card_y1 + 35);
  
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(1);
  tft->drawString("TEMPERATURE", PADDING + 70, card_y1 + 15);
  tft->setTextSize(4);
  tft->drawString("25.6", PADDING + 70, card_y1 + 35);
  tft->setTextSize(2);
  tft->drawString("C", PADDING + 180, card_y1 + 48);


  // --- Draw Humidity Card ---
  int card_y2 = card_y1 + 75 + PADDING;
  tft->fillRoundRect(PADDING, card_y2, 320 - (PADDING*2), 75, CORNER_RADIUS, THEME_KEY_BG);
  drawHumidIcon(tft, PADDING + 30, card_y2 + 35);
  
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(1);
  tft->drawString("HUMIDITY", PADDING + 70, card_y2 + 15);
  tft->setTextSize(4);
  tft->drawString("65", PADDING + 70, card_y2 + 35);
  tft->setTextSize(2);
  tft->drawString("%", PADDING + 125, card_y2 + 48);


  // Footer
  tft->setTextColor(THEME_WARNING);
  tft->setTextSize(1);
  tft->drawString("(B)Back | (C)Home", 20, 220);
}