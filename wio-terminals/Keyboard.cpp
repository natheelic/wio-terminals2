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
  tft->fillRect(PADDING+1, 31, 320 - (PADDING*2)-2, 28, THEME_BG);
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  String displayText = state->isEnteringPassword ? String("********************************").substring(0, state->inputText.length()) : state->inputText;
  tft->drawString(displayText, PADDING + 5, 36);

  // Blinking cursor
  if (millis() % 1000 < 500) {
    int16_t cursorX = PADDING + 5 + tft->textWidth(displayText);
    if(cursorX < 320 - (PADDING*2) - 2)
      tft->fillRect(cursorX, 34, 2, 20, THEME_TEXT);
  }

  int keyWidth = 28;
  int keyHeight = 28;
  int keySpacing = 4;
  int startY = 70;
  
  // Draw character keys based on the current mode
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 10; col++) {
      int x = 10 + col * (keyWidth + keySpacing);
      int y = startY + row * (keyHeight + keySpacing);
      bool isSelected = (row == state->keyboardRow && col == state->keyboardCol);
      
      tft->fillRoundRect(x, y, keyWidth, keyHeight, CORNER_RADIUS, isSelected ? THEME_PRIMARY : THEME_KEY_BG);
      tft->setTextColor(isSelected ? THEME_BG : THEME_KEY_TEXT);
      tft->setTextSize(2);
      
      char keyChar;
      if (state->keyboardMode == MODE_ALPHA_LOWER) {
        keyChar = keyboard[row][col];
      } else if (state->keyboardMode == MODE_ALPHA_UPPER) {
        keyChar = keyboardUpper[row][col];
      } else { // MODE_NUM_SYM
        keyChar = keyboardNumSym[row][col];
      }
      tft->drawChar(keyChar, x + 8, y + 6);
    }
  }

  int specialY = startY + 4 * (keyHeight + keySpacing);
  
  // NEW Special Keys Layout
  bool shiftSelected = (state->keyboardRow == 4 && state->keyboardCol == 0);
  tft->fillRoundRect(10, specialY, 120, keyHeight, CORNER_RADIUS, shiftSelected ? THEME_PRIMARY : THEME_KEY_BG);
  tft->setTextColor(shiftSelected ? THEME_BG : THEME_KEY_TEXT);
  if(state->keyboardMode == MODE_NUM_SYM) tft->drawString("abc", 50, specialY + 6);
  else tft->drawString("Shift", 45, specialY + 6);

  bool cancelSelected = (state->keyboardRow == 4 && state->keyboardCol == 1);
  tft->fillRoundRect(138, specialY, 80, keyHeight, CORNER_RADIUS, cancelSelected ? THEME_PRIMARY : THEME_DANGER);
  tft->setTextColor(cancelSelected ? THEME_BG : THEME_KEY_TEXT);
  tft->drawString("Cancel", 150, specialY + 6);

  bool okSelected = (state->keyboardRow == 4 && state->keyboardCol == 2);
  tft->fillRoundRect(226, specialY, 80, keyHeight, CORNER_RADIUS, okSelected ? THEME_PRIMARY : THEME_SUCCESS);
  tft->setTextColor(okSelected ? THEME_BG : THEME_KEY_TEXT);
  tft->drawString("OK", 254, specialY + 6);

  // NEW Footer with physical button hints
  tft->setTextColor(THEME_WARNING);
  tft->setTextSize(1);
  tft->drawString("(A)Mode (B)Del (C)Space", 10, 220);
}