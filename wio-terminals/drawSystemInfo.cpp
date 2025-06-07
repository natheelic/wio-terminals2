// wio-terminals/drawSystemInfo.cpp

#include "drawSystemInfo.h"
#include "Theme.h"
#include <rpcWiFi.h> // เพื่อใช้ WiFi.macAddress()

void drawSystemInfo(AppState* state) {
    TFT_eSPI* tft = state->tft;
    tft->fillScreen(THEME_BG);

    // --- Draw Header Bar ---
    tft->fillRect(0, 0, 320, 30, THEME_KEY_BG);
    tft->setTextColor(THEME_TEXT);
    tft->setTextSize(2);
    tft->drawString("System Info", PADDING, 7);
    tft->drawLine(0, 30, 320, 30, THEME_SECONDARY);

    // --- Info List ---
    int y_pos = 55;
    int y_step = 30;
    int label_x = PADDING + 5;
    int value_x = 180;

    tft->setTextSize(2);

    // Firmware Version (Static value)
    tft->setTextColor(THEME_TEXT);
    tft->drawString("Firmware Ver:", label_x, y_pos);
    tft->setTextColor(THEME_PRIMARY);
    tft->drawString("1.0.0", value_x, y_pos);
    y_pos += y_step;

    // WiFi MAC Address
    tft->setTextColor(THEME_TEXT);
    tft->drawString("MAC Address:", label_x, y_pos);
    tft->setTextColor(THEME_PRIMARY);
    tft->drawString(WiFi.macAddress(), value_x, y_pos);
    y_pos += y_step;

    // Main MCU
    tft->setTextColor(THEME_TEXT);
    tft->drawString("Main MCU:", label_x, y_pos);
    tft->setTextColor(THEME_PRIMARY);
    tft->drawString("SAMD51", value_x, y_pos);
    y_pos += y_step;
    
    // WiFi Chip
    tft->setTextColor(THEME_TEXT);
    tft->drawString("WiFi Chip:", label_x, y_pos);
    tft->setTextColor(THEME_PRIMARY);
    tft->drawString("RTL8720DN", value_x, y_pos);
    y_pos += y_step;


    // --- Footer ---
    tft->setTextColor(THEME_WARNING);
    tft->setTextSize(1);
    tft->drawString("(B)Back | (C)Home", 20, 220);
}