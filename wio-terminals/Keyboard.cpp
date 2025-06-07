#include "Keyboard.h"

void drawKeyboard(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(0x3186); 
  tft->setTextSize(1);

  // Header
  tft->fillRect(0, 0, tft->width(), 24, TFT_BLACK);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(2);
  const char* title = "Text Input";
  if (state->isEnteringSSID) title = "Enter SSID";
  if (state->isEnteringPassword) title = "Enter Password";
  tft->drawString(title, 10, 5);

  // Input field
  tft->fillRect(10, 30, 300, 24, TFT_WHITE);
  tft->setTextColor(TFT_BLACK);
  tft->setTextSize(2);
  String displayText = state->isEnteringPassword ? String("****************").substring(0, state->inputText.length()) : state->inputText;
  tft->drawString(displayText, 15, 34);

  if (millis() % 1000 < 500) {
    int16_t cursorX = 15 + tft->textWidth(displayText);
    tft->fillRect(cursorX, 32, 2, 20, TFT_BLACK);
  }

  int keyWidth = 28;
  int keyHeight = 24;
  int keySpacing = 4;
  int startY = 60;
  
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 10; col++) {
      int x = 10 + col * (keyWidth + keySpacing);
      int y = startY + row * (keyHeight + keySpacing);
      bool isSelected = (row == state->keyboardRow && col == state->keyboardCol && state->keyboardRow < 4);
      
      tft->fillRoundRect(x, y, keyWidth, keyHeight, 3, isSelected ? TFT_CYAN : TFT_DARKGREY);
      tft->setTextColor(isSelected ? TFT_BLACK : TFT_WHITE);
      tft->setTextSize(2);
      
      char keyChar = state->keyboardUpperCase ? keyboardUpper[row][col] : keyboard[row][col];
      tft->drawChar(keyChar, x + 8, y + 4);
    }
  }

  int specialY = startY + 4 * (keyHeight + keySpacing);
  bool shiftSelected = (state->keyboardRow == 4 && state->keyboardCol == 0);
  tft->fillRoundRect(10, specialY, 60, keyHeight, 3, shiftSelected ? TFT_CYAN : (state->keyboardUpperCase ? TFT_BLUE : TFT_DARKGREY));
  tft->setTextColor(shiftSelected ? TFT_BLACK : TFT_WHITE);
  tft->drawString(state->keyboardUpperCase ? "ABC" : "abc", 15, specialY + 4);
  
  bool spaceSelected = (state->keyboardRow == 4 && state->keyboardCol == 1);
  tft->fillRoundRect(78, specialY, 120, keyHeight, 3, spaceSelected ? TFT_CYAN : TFT_DARKGREY);
  tft->setTextColor(spaceSelected ? TFT_BLACK : TFT_WHITE);
  tft->drawString("space", 95, specialY + 4);

  bool backspaceSelected = (state->keyboardRow == 4 && state->keyboardCol == 2);
  tft->fillRoundRect(206, specialY, 50, keyHeight, 3, backspaceSelected ? TFT_CYAN : TFT_DARKGREY);
  tft->setTextColor(backspaceSelected ? TFT_BLACK : TFT_WHITE);
  tft->drawString("del", 211, specialY + 4);

  bool returnSelected = (state->keyboardRow == 4 && state->keyboardCol == 3);
  tft->fillRoundRect(264, specialY, 50, keyHeight, 3, returnSelected ? TFT_CYAN : TFT_DARKGREEN);
  tft->setTextColor(returnSelected ? TFT_BLACK : TFT_WHITE);
  tft->drawString("OK", 274, specialY + 4);
}