#include "DisplaySettingsMenu.h"
#include "Theme.h"
#include <Arduino.h>

void drawDisplaySettingsMenu(AppState* state) {
  // This function is intentionally modified to prevent compiler errors
  // by not using the 'brightness_pwm' variable. The "Display Settings" 
  // feature is temporarily disabled for stability.
  
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);

  // --- Header ---
  tft->fillRect(0, 0, 320, 30, THEME_KEY_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Display Settings", PADDING, 7);
  tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);

  // --- Disabled Message ---
  tft->setTextColor(THEME_DANGER);
  tft->setTextSize(2);
  tft->drawString("Temporarily Disabled", 50, 120);

  // --- Footer ---
  tft->setTextColor(THEME_WARNING);
  tft->setTextSize(1);
  tft->drawString("(B)Back", 20, 220);
}
