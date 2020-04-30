#ifndef HTTP_H
#define HTTP_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>

String NULL_STRING = String("NULL");

String getString (String URL) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, URL);

    int httpCode = http.GET();

    String error = NULL_STRING;
    String message;

    // Negative httpcode is error
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_NO_CONTENT) {
        return NULL_STRING;
      }else if (httpCode != HTTP_CODE_OK) {
        error = "http code: " + String(httpCode);
      }else {
        message = http.getString();
      }
    } else {
      error = http.errorToString(httpCode).c_str();
    }

    http.end();

    if (error != NULL_STRING) {
      return error;
    }
    return message;
}

#endif
