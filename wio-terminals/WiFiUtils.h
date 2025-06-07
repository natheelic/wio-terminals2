#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include "config.h"

struct AppState;

// --- ส่วนที่เปลี่ยนแปลง ---
// ย้าย Struct มาไว้ที่นี่เพื่อให้ไฟล์อื่น #include ไปใช้ได้
struct WifiCredentials {
  char ssid[33];
  char password[65];
};

// ประกาศให้ไฟล์อื่นรู้ว่ามี object นี้อยู่ โดยใช้ชื่อคลาสของไลบรารี
extern FlashStorageClass<WifiCredentials> credentials_storage;
// --- จบส่วนที่เปลี่ยนแปลง ---

// Function Prototypes
String getSecurityTypeString(int securityType);
void scanWiFiNetworks(AppState* state);
ConnectionStatus connectToWiFi(AppState* state);
void saveWiFiCredentials(AppState* state);
void clearWiFiCredentials();

#endif