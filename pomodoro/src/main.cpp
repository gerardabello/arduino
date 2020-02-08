#include "Arduino.h"

const int BUZZER_PIN = 11;

const int LED_GROUND_PIN = 10;
const int LED_8 = 12;
const int LED_7 = 9;
const int LED_6 = 8;
const int LED_5 = 7;
const int LED_4 = 6;
const int LED_3 = 5;
const int LED_2 = 4;
const int LED_1 = 3;
const int LED_0 = 2;

const int START_PAUSE_PIN = A6;
const int SET_RESET_PIN= A7;

void setup()
{

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
  pinMode(LED_8, OUTPUT);
  pinMode(LED_8, OUTPUT);
  pinMode(LED_GROUND_PIN, OUTPUT);


}

int state = 0; // 0:init 1:running 2:finished 3:paused
int time_left_setting = 1;
long time_left = 15L * 1000;
long total_time = 45L * 1000;


long last_millis = -1;

void setTimer(int t) {
  time_left = t * 1000L;
  last_millis = -1;
}

void upateTime() {
  if (last_millis != -1 && state == 1) {
    time_left -= (millis() - last_millis);
  }


  last_millis = millis();
}

void writeLeds()
{
  bool flash_state = (millis() / (state == 3 ? 300 : 1000)) % 2 == 0;


  if (state == 0) {
    float percent_left = max(0.0, float(time_left) / float(total_time));

    float percent_unit = 1.0 / 9.0;

    digitalWrite(LED_0, percent_left > percent_unit * 0 ? HIGH : LOW);
    digitalWrite(LED_1, percent_left > percent_unit * 1 ? HIGH : LOW);
    digitalWrite(LED_2, percent_left > percent_unit * 2 ? HIGH : LOW);
    digitalWrite(LED_3, percent_left > percent_unit * 3 ? HIGH : LOW);
    digitalWrite(LED_4, percent_left > percent_unit * 4 ? HIGH : LOW);
    digitalWrite(LED_5, percent_left > percent_unit * 5 ? HIGH : LOW);
    digitalWrite(LED_6, percent_left > percent_unit * 6 ? HIGH : LOW);
    digitalWrite(LED_7, percent_left > percent_unit * 7 ? HIGH : LOW);
    digitalWrite(LED_8, percent_left > percent_unit * 8 ? HIGH : LOW);


    return;
  }

  if (state == 3) {
    float percent_left = max(0.0, float(time_left) / float(total_time));

    float percent_unit = 1.0 / 9.0;

    digitalWrite(LED_0, percent_left > percent_unit * 0 && flash_state ? HIGH : LOW);
    digitalWrite(LED_1, percent_left > percent_unit * 1 && flash_state ? HIGH : LOW);
    digitalWrite(LED_2, percent_left > percent_unit * 2 && flash_state ? HIGH : LOW);
    digitalWrite(LED_3, percent_left > percent_unit * 3 && flash_state ? HIGH : LOW);
    digitalWrite(LED_4, percent_left > percent_unit * 4 && flash_state ? HIGH : LOW);
    digitalWrite(LED_5, percent_left > percent_unit * 5 && flash_state ? HIGH : LOW);
    digitalWrite(LED_6, percent_left > percent_unit * 6 && flash_state ? HIGH : LOW);
    digitalWrite(LED_7, percent_left > percent_unit * 7 && flash_state ? HIGH : LOW);
    digitalWrite(LED_8, percent_left > percent_unit * 8 && flash_state ? HIGH : LOW);

    return;
  }

  if (state == 1) {
    float percent_left = max(0.0, float(time_left) / float(total_time));

    float percent_unit = 1.0 / 9.0;

    int lastLed = floor(percent_left / percent_unit);

    digitalWrite(LED_0, percent_left > percent_unit * 0 && (lastLed != 0 || flash_state)? HIGH : LOW);
    digitalWrite(LED_1, percent_left > percent_unit * 1 && (lastLed != 1 || flash_state)? HIGH : LOW);
    digitalWrite(LED_2, percent_left > percent_unit * 2 && (lastLed != 2 || flash_state)? HIGH : LOW);
    digitalWrite(LED_3, percent_left > percent_unit * 3 && (lastLed != 3 || flash_state)? HIGH : LOW);
    digitalWrite(LED_4, percent_left > percent_unit * 4 && (lastLed != 4 || flash_state)? HIGH : LOW);
    digitalWrite(LED_5, percent_left > percent_unit * 5 && (lastLed != 5 || flash_state)? HIGH : LOW);
    digitalWrite(LED_6, percent_left > percent_unit * 6 && (lastLed != 6 || flash_state)? HIGH : LOW);
    digitalWrite(LED_7, percent_left > percent_unit * 7 && (lastLed != 7 || flash_state)? HIGH : LOW);
    digitalWrite(LED_8, percent_left > percent_unit * 8 && (lastLed != 8 || flash_state)? HIGH : LOW);

    return;
  }


  if (state == 2) {
    float percent_left = abs(sin(millis() / 600.0));
    float percent_unit = 1.0 / 9.0;

    digitalWrite(LED_0, percent_left > percent_unit * 0 ? HIGH : LOW);
    digitalWrite(LED_1, percent_left > percent_unit * 1 ? HIGH : LOW);
    digitalWrite(LED_2, percent_left > percent_unit * 2 ? HIGH : LOW);
    digitalWrite(LED_3, percent_left > percent_unit * 3 ? HIGH : LOW);
    digitalWrite(LED_4, percent_left > percent_unit * 4 ? HIGH : LOW);
    digitalWrite(LED_5, percent_left > percent_unit * 5 ? HIGH : LOW);
    digitalWrite(LED_6, percent_left > percent_unit * 6 ? HIGH : LOW);
    digitalWrite(LED_7, percent_left > percent_unit * 7 ? HIGH : LOW);
    digitalWrite(LED_8, percent_left > percent_unit * 8 ? HIGH : LOW);

    return;
  }
}

void sound_end() {
  tone(11, 220 * 1.68, 150);
  delay(200);
  tone(11, 440, 150);
  delay(200);
  tone(11, 440 * 1.68, 150);
  delay(200);
  tone(11, 880, 400);
  delay(400);
}

void sound_start() {
  tone(11, 220, 150);
  delay(200);
  tone(11, 440, 150);
  delay(200);
  tone(11, 880, 150);
  delay(200);
}

void sound_pause() {
  tone(11, 440, 150);
  delay(200);
  tone(11, 440, 150);
  delay(200);
}

void sound_resume() {
  tone(11, 440, 150);
  delay(200);
  tone(11, 880, 150);
  delay(200);
}

void sound_reset() {
  tone(11, 880, 150);
  delay(200);
  tone(11, 440, 150);
  delay(200);
  tone(11, 220, 150);
  delay(200);
}

void sound_restart() {
  tone(11, 880, 150);
  delay(200);
}

void sound_set() {
  tone(11, 880, 150);
  delay(200);
}

void set_time_to_setting() {
    if (time_left_setting == 1){
      setTimer(15);
      writeLeds();
    }else if (time_left_setting == 2){
      setTimer(30);
      writeLeds();
    }else if (time_left_setting == 3){
      setTimer(45);
      writeLeds();
    }
}

void loop()
{

  upateTime();

  analogWrite(LED_GROUND_PIN, 155.0);


  if (state == 0 && analogRead(START_PAUSE_PIN) > 512) {
    sound_start();
    state = 1;
  } else if (state == 0 && analogRead(SET_RESET_PIN) > 512) {
    if (time_left_setting == 1){
      time_left_setting = 2;
    }else if (time_left_setting == 2){
      time_left_setting = 3;
    }else if (time_left_setting == 3){
      time_left_setting = 1;
    }

    set_time_to_setting();
    sound_set();
  }else if (state == 1 && analogRead(START_PAUSE_PIN) > 512) {
    state = 3;
    sound_pause();
  }else if (state == 1 && (time_left < 0)) {
    state = 2;
    sound_end();
  }else if (state == 3 && analogRead(SET_RESET_PIN) > 512) {
    state = 0;
    set_time_to_setting();
    sound_reset();
  }else if (state == 2 && (analogRead(SET_RESET_PIN) > 512 || analogRead(START_PAUSE_PIN) > 512)) {
    state = 0;
    set_time_to_setting();
    sound_restart();
  }else if (state == 3 && analogRead(START_PAUSE_PIN) > 512) {
    state = 1;
    sound_resume();
  }



  writeLeds();



}
