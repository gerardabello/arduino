#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal.h>

const int pinRS = D6;
const int pinE = D5;
const int pinData4 = D4;
const int pinData5 = D3;
const int pinData6 = D2;
const int pinData7 = D1;

class LCD
{
  private:
    LiquidCrystal lcd;

  public:
    LCD() : lcd(pinRS, pinE, pinData4, pinData5, pinData6, pinData7) {
      lcd.begin(16, 2);
    }

    template <typename T1, typename T2>
    void print(T1 first, T2 second)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(first);
      lcd.setCursor(0, 1);
      lcd.print(second);
    }

    template <typename T>
    void print(T first)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(first);
    }
};



#endif

