#include <Arduino.h>

#include "lcd.h"
#include "wifi.h"
#include "weather.h"
#include "http.h"

LCD lcd;
Weather weather;

void setup(void){
  Serial.begin(74880);

  lcd.print("Connecting...");
  setupWifi();
  lcd.print("Connected to wifi");
  delay(1000);
}

void loop(void){
  String status = weather.getStatusString();
  float t = weather.getTemperature();
  float h = weather.getHumidity();

  lcd.print(String(t) + " C",String(h) + " %");

  String httpError = postJSON(
    "http://triangular-order-8b07xjr2ne.glitch.me/test",
    "{\"temp\":"+String(t)+",\"humidity\":"+String(h)+"}"
    );

  delay(300);

  if (httpError != NULL){
    lcd.print(httpError);
  }

  delay(2000);
}


