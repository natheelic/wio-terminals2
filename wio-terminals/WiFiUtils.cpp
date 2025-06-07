#include "WiFiUtils.h"
#include "Buzzer.h"

// --- ส่วนที่เปลี่ยนแปลง ---
// ประกาศ `extern` เพื่อให้ไฟล์นี้รู้จัก object ที่สร้างไว้ใน .ino
extern FlashStorageClass<WifiCredentials> credentials_storage;
// --- จบส่วนที่เปลี่ยนแปลง ---

String getSecurityTypeString(int securityType) {
  switch (securityType) {
    case WIFI_AUTH_OPEN: return "Open";
    case WIFI_AUTH_WEP: return "WEP";
    case WIFI_AUTH_WPA_PSK: return "WPA";
    case WIFI_AUTH_WPA2_PSK: return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2";
    default: return "Unknown";
  }
}

void scanWiFiNetworks(AppState* state) {
  state->tft->fillScreen(TFT_BLACK);
  state->tft->setTextColor(TFT_YELLOW);
  state->tft->setTextSize(2);
  state->tft->drawString("Scanning...", 100, 100);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  state->foundNetworks = WiFi.scanNetworks();
  if (state->foundNetworks > 10) state->foundNetworks = 10;
  for (int i = 0; i < state->foundNetworks; i++) {
    state->networkNames[i] = WiFi.SSID(i);
    state->networkRSSI[i] = WiFi.RSSI(i);
    state->networkSecurity[i] = WiFi.encryptionType(i);
  }
  state->selectedWiFiItem = 0;
}

ConnectionStatus connectToWiFi(AppState* state) {
  const char* ssid = state->wifiSSID.c_str();
  const char* password = state->wifiPassword.c_str();
  
  bool is_open = false;
  if (state->selectedNetworkIndex != -1 && state->selectedNetworkIndex < state->foundNetworks) {
    if (state->networkSecurity[state->selectedNetworkIndex] == WIFI_AUTH_OPEN) {
      is_open = true;
    }
  } 
  else if (state->selectedNetworkIndex == -1 && state->wifiPassword.length() == 0) {
    is_open = true;
  }
  
  if (is_open) {
    WiFi.begin(ssid);
  } else {
    WiFi.begin(ssid, password);
  }

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
      saveWiFiCredentials(state);
      beep_success();
      return SUCCESS;
  }
  
  beep_fail();
  return FAILED;
}

void saveWiFiCredentials(AppState* state) {
  WifiCredentials creds;
  strncpy(creds.ssid, state->wifiSSID.c_str(), 32);
  strncpy(creds.password, state->wifiPassword.c_str(), 64);
  creds.ssid[32] = '\0'; 
  creds.password[64] = '\0';
  credentials_storage.write(creds);
}

void clearWiFiCredentials() {
    WifiCredentials emptyCreds;
    memset(emptyCreds.ssid, 0, 33);
    memset(emptyCreds.password, 0, 65);
    credentials_storage.write(emptyCreds);
}