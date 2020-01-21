
// include the library code:
#include <LiquidCrystal.h>

const int pinRS = 4;
const int pinE = 6;
const int pinData4 = 10;
const int pinData5 = 11;
const int pinData6 = 12;
const int pinData7 = 13;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(pinRS, pinE, pinData4, pinData5, pinData6, pinData7);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("HELLO!");
}

void loop() {
  // when characters arrive over the serial port...
  if (Serial.available()) {
    String message = Serial.readStringUntil('$');
    lcd.clear();
    lcd.print("message: " + message);
    Serial.println(message);
  }
}

