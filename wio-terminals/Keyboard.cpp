#include "Keyboard.h"
#include "Theme.h"

void drawKeyboard(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG); 
  tft->setTextSize(1);

  // Header
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  const char* title = "Text Input";
  if (state->isEnteringSSID) title = "Enter SSID";
  if (state->isEnteringPassword) title = "Enter Password";
  tft->drawString(title, PADDING, 5);

  // Input field
  tft->fillRoundRect(PADDING, 30, 320 - (PADDING*2), 30, CORNER_RADIUS, THEME_SECONDARY);
  tft->fillRect(PADDING+1, 31, 320 - (PADDING*2)-2, 28, THEME_BG); // Inner BG
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  String displayText = state->isEnteringPassword ? String("****************").substring(0, state->inputText.length()) : state->inputText;
  tft->drawString(displayText, PADDING + 5, 36);

  // Blinking cursor
  if (millis() % 1000 < 500) {
    int16_t cursorX = PADDING + 5 + tft->textWidth(displayText);
    tft->fillRect(cursorX, 34, 2, 20, THEME_TEXT);
  }

  int keyWidth = 28;
  int keyHeight = 28;
  int keySpacing = 4;
  int startY = 70;
  
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 10; col++) {
      int x = 10 + col * (keyWidth + keySpacing);
      int y = startY + row * (keyHeight + keySpacing);
      bool isSelected = (row == state->keyboardRow && col == state->keyboardCol && state->keyboardRow < 4);
      
      tft->fillRoundRect(x, y, keyWidth, keyHeight, CORNER_RADIUS, isSelected ? THEME_PRIMARY : THEME_KEY_BG);
      tft->setTextColor(isSelected ? THEME_BG : THEME_KEY_TEXT);
      tft->setTextSize(2);
      
      char keyChar = state->keyboardUpperCase ? keyboardUpper[row][col] : keyboard[row][col];
      tft->drawChar(keyChar, x + 8, y + 6);
    }
  }

  int specialY = startY + 4 * (keyHeight + keySpacing);
  // Special Keys (Shift, Space, Del, OK)
  bool shiftSelected = (state->keyboardRow == 4 && state->keyboardCol == 0);
  tft->fillRoundRect(10, specialY, 60, keyHeight, CORNER_RADIUS, shiftSelected ? THEME_PRIMARY : (state->keyboardUpperCase ? THEME_PRIMARY : THEME_KEY_BG));
  tft->setTextColor(shiftSelected ? THEME_BG : THEME_KEY_TEXT);
  tft->drawString("Shift", 20, specialY + 6);
  
  bool spaceSelected = (state->keyboardRow == 4 && state->keyboardCol == 1);
  tft->fillRoundRect(78, specialY, 120, keyHeight, CORNER_RADIUS, spaceSelected ? THEME_PRIMARY : THEME_KEY_BG);
  tft->setTextColor(spaceSelected ? THEME_BG : THEME_KEY_TEXT);
  tft->drawString("Space", 110, specialY + 6);

  bool backspaceSelected = (state->keyboardRow == 4 && state->keyboardCol == 2);
  tft->fillRoundRect(206, specialY, 50, keyHeight, CORNER_RADIUS, backspaceSelected ? THEME_PRIMARY : THEME_KEY_BG);
  tft->setTextColor(backspaceSelected ? THEME_BG : THEME_KEY_TEXT);
  tft->drawString("Del", 216, specialY + 6);

  bool returnSelected = (state->keyboardRow == 4 && state->keyboardCol == 3);
  tft->fillRoundRect(264, specialY, 50, keyHeight, CORNER_RADIUS, returnSelected ? THEME_PRIMARY : THEME_SUCCESS);
  tft->setTextColor(returnSelected ? THEME_BG : THEME_KEY_TEXT);
  tft->drawString("OK", 278, specialY + 6);
}