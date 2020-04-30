#ifndef HTTP_H
#define HTTP_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>

String postJSON (String URL, String json) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, URL);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(json);

    String error;

    // Negative httpcode is error
    if (httpCode > 0) {
      if (httpCode != HTTP_CODE_OK) {
        error = "http code: " + String(httpCode);
      }
    } else {
      error = http.errorToString(httpCode).c_str();
    }

    http.end();

    return error;
}

#endif
