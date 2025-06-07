// wio-terminals/drawResetConfirm.cpp

#include "drawResetConfirm.h"
#include "Theme.h"

void drawResetConfirm(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);

  // --- Dialog Box ---
  tft->fillRoundRect(40, 70, 240, 100, CORNER_RADIUS, THEME_KEY_BG);
  tft->drawRoundRect(40, 70, 240, 100, CORNER_RADIUS, THEME_SECONDARY);

  // --- Text ---
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Are you sure?", 85, 85);
  
  tft->setTextSize(1);
  tft->drawString("This will restart the device.", 75, 110);

  // --- Buttons (Yes/No) ---
  // เราจะใช้ `state->selectedMenuItem` ชั่วคราวเพื่อเก็บว่าเลือก Yes (0) หรือ No (1)
  tft->setTextSize(2);
  
  // YES Button
  if (state->selectedMenuItem == 0) { // 0 for YES
    tft->fillRoundRect(60, 130, 80, 30, CORNER_RADIUS, THEME_DANGER); // ใช้สีแดงเพื่อเน้น
    tft->setTextColor(THEME_BG);
  } else {
    tft->drawRoundRect(60, 130, 80, 30, CORNER_RADIUS, THEME_SECONDARY);
    tft->setTextColor(THEME_TEXT);
  }
  tft->drawString("Yes", 85, 137);

  // NO Button
  tft->setTextColor(THEME_TEXT); // Reset color
  if (state->selectedMenuItem == 1) { // 1 for NO
    tft->fillRoundRect(180, 130, 80, 30, CORNER_RADIUS, THEME_PRIMARY);
    tft->setTextColor(THEME_BG);
  } else {
    tft->drawRoundRect(180, 130, 80, 30, CORNER_RADIUS, THEME_SECONDARY);
    tft->setTextColor(THEME_TEXT);
  }
  tft->drawString("No", 210, 137);
  
  // --- Footer ---
  tft->setTextColor(THEME_WARNING);
  tft->setTextSize(1);
  tft->drawString("NAV: Left/Right | (A/OK) Select", 20, 220);
}