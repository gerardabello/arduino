#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>

const int servoPin = D7;

class CustomServo
{
  private:
    float degrees;
    float target;

  public:
    CustomServo() {
      pinMode(servoPin, OUTPUT);
      degrees = 0;
      target = 0;
    }

    int degreesToDelay(float deg) {
      float res = 9.4444 * deg + 600;
      return int(res + 0.5);
    }

    void write(float val)
    {
      target = val;
    }

    void loop()
    {
      degrees += (target - degrees) / 10.0;

      int delay = this->degreesToDelay(degrees);
      digitalWrite(servoPin, HIGH);
      delayMicroseconds(delay); 

      digitalWrite(servoPin, LOW);
      delayMicroseconds(20000 - delay); // 20ms - duration of the pusle
    }
};



#endif

