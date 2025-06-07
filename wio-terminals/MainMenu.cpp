#include "MainMenu.h"
#include "Theme.h" // Assuming you are using the theme file

void drawMainMenu(AppState* state) {
  TFT_eSPI* tft = state->tft;
  tft->fillScreen(THEME_BG);
  
  // --- Draw Header Bar ---
  tft->fillRect(0, 0, 320, 30, THEME_KEY_BG); // Header background
  tft->setTextColor(THEME_TEXT);
  tft->setTextSize(2);
  tft->drawString("Main Menu", PADDING, 7);
  tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);

  // --- Draw Menu Cards ---
  String menuItems[] = {"Settings", "Network Tools", "Sensors on Device"};
  String menuIcons[] = {">", "o", "#"}; // Simple icons for demonstration

  for (int i = 0; i < 3; i++) {
    int y_pos = 45 + i * 60;
    
    if (i == state->selectedMenuItem) {
      tft->fillRoundRect(PADDING, y_pos, 320 - (PADDING*2), 55, CORNER_RADIUS, THEME_PRIMARY);
      tft->setTextColor(THEME_BG);
    } else {
      tft->fillRoundRect(PADDING, y_pos, 320 - (PADDING*2), 55, CORNER_RADIUS, THEME_KEY_BG);
      tft->drawRoundRect(PADDING, y_pos, 320 - (PADDING*2), 55, CORNER_RADIUS, THEME_SECONDARY);
      tft->setTextColor(THEME_TEXT);
    }
    
    // Draw Icon and Text
    tft->setTextSize(3);
    tft->drawString(menuIcons[i], PADDING + 15, y_pos + 15); // Draw icon
    tft->setTextSize(2);
    tft->drawString(menuItems[i], PADDING + 50, y_pos + 18); // Draw text
  }

  // Footer
  tft->setTextColor(THEME_WARNING);
  tft->setTextSize(1);
  tft->drawString("NAV: 5-way | (A/OK) Select", 20, 220);
}