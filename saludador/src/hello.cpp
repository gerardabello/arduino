#include <Arduino.h>

#include "lcd.h"
#include "wifi.h"
#include "http.h"
#include "servo.h"
#include "timer.h"

LCD lcd;
CustomServo servo;
Timer timer;

void checkMessages(){
  String message = getString(
      "http://trail-midnight-payment.glitch.me"
      );

  if (message != NULL_STRING) {
    lcd.print(message);
    timer.setTimeout([]() { servo.write(110); }, 0);
    timer.setTimeout([]() { servo.write(70); }, 500);
    timer.setTimeout([]() { servo.write(110); }, 1000);
    timer.setTimeout([]() { servo.write(70); }, 1500);
    timer.setTimeout([]() { servo.write(110); }, 2000);
    timer.setTimeout([]() { servo.write(70); }, 2500);
    timer.setTimeout([]() { servo.write(0); }, 3500);
    timer.setTimeout([]() { lcd.print(""); }, 8000);
  }
}

void setup(){

  lcd.print("Connecting...");
  setupWifi();
  lcd.print("Connected!");
  timer.setTimeout([]() { lcd.print(""); }, 3000);

  timer.setInterval(checkMessages, 10000);
}

void loop(){
  timer.loop();
  servo.loop();
}


