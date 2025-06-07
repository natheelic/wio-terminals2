#include "config.h"
#include "display.h"
#include "input.h"

// สร้าง instance ของ AppState และ TFT
TFT_eSPI tft = TFT_eSPI();
AppState appState;

void setup() {
  // เริ่มต้นการทำงานของ Serial
  Serial.begin(115200);

  // ตั้งค่าเริ่มต้นสำหรับ AppState
  appState.tft = &tft;
  appState.currentState = MAIN_MENU;
  appState.selectedMenuItem = 0;
  appState.selectedWiFiItem = 0;
  appState.keyboardRow = 0;
  appState.keyboardCol = 0;
  appState.keyboardUpperCase = false;
  appState.isEnteringPassword = false;
  appState.isEnteringSSID = false;
  appState.foundNetworks = 0;
  appState.selectedNetworkIndex = 0;
  appState.wifiConnectionStatus = PENDING;

  // เริ่มต้นการทำงานของจอและปุ่มกด
  initDisplay(appState.tft);
  initButtons();

  // วาดหน้าจอเริ่มต้น
  drawMainMenu(&appState);
}

void loop() {
  // จัดการการกดปุ่มใน loop ตลอดเวลา
  handleButtons(&appState);

  // เพิ่ม delay เล็กน้อยเพื่อลดภาระ CPU
  delay(50);
}