#include "WiFiUtils.h"

String getSecurityTypeString(int securityType) {
  switch (securityType) {
    case WIFI_AUTH_OPEN: return "Open";
    case WIFI_AUTH_WEP: return "WEP";
    case WIFI_AUTH_WPA_PSK: return "WPA";
    case WIFI_AUTH_WPA2_PSK: return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2-Enterprise";
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
  
  int securityType = (state->selectedNetworkIndex != -1) ? state->networkSecurity[state->selectedNetworkIndex] : WIFI_AUTH_WPA2_PSK;
  
  if (state->wifiPassword.length() == 0 && state->selectedNetworkIndex == -1) {
      securityType = WIFI_AUTH_OPEN;
  }

  if (securityType == WIFI_AUTH_OPEN) {
    WiFi.begin(ssid);
  } else {
    WiFi.begin(ssid, password);
  }

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    attempts++;
  }

  return (WiFi.status() == WL_CONNECTED) ? SUCCESS : FAILED;
}