#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>

const char* ssid = "react";
const char* password = "";

void setupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //WiFi.localIP();
}


#endif
