/*
   Showing number 0-9 on a Common Anode 7-segment LED display
   Displays the numbers 0-9 on the display, with one second inbetween.
   A
   ---
   F |   | B
   | G |
   ---
   E |   | C
   |   |
   ---
   D
   This example code is in the public domain.
 */

// Pin 2-8 is connected to the 7 segments of the display.

int pinA = 6;
int pinB = 7;
int pinC = 8;
int pinD = 9;
int pinE = 10;
int pinF = 11;
int pinG = 12;
int D1 = 2;
int D2 = 3;
int D3 = 4;
int D4 = 5;

// the setup routine runs once when you press reset:
void setup() {                
  Serial.begin(9600);

  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);  

  Serial.write(0);
}

const int DELAY = 5;

void writeEmpty() {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH); 
}

void writeNumber(int number) {
  writeNumberDigit(D1, number % 10);
  delay(DELAY);
  writeNumberDigit(D2, number / 10 % 10);
  delay(DELAY);
  writeNumberDigit(D3, number / 100 % 10);
  delay(DELAY);
  writeNumberDigit(D4, number / 1000 % 10);
  delay(DELAY);
}

void writeNumberDigit(int displayIndex, int number) {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH); 
  digitalWrite(displayIndex, LOW); 

  switch (number) {
    case 0:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, HIGH);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, LOW);   
      return;

    case 1:
      digitalWrite(pinA, LOW);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, LOW);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, LOW);   
      digitalWrite(pinG, LOW);   
      return;
    case 2:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, LOW);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, HIGH);   
      digitalWrite(pinF, LOW);   
      digitalWrite(pinG, HIGH);     
      return;
    case 3:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, LOW);   
      digitalWrite(pinG, HIGH);     
      return;
    case 4:
      digitalWrite(pinA, LOW);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, LOW);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, HIGH);     
      return;
    case 5:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, LOW);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, HIGH);     
      return;
    case 6:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, LOW);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, HIGH);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, HIGH);     
      return;
    case 7:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, LOW);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, LOW);   
      digitalWrite(pinG, LOW);     

      return;
    case 8:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, HIGH);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, HIGH);     
      return;
    case 9:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, HIGH);     
      return;
  }
}

unsigned int number = millis() / 60000;

unsigned long toggleInMillis = 2000;
bool showNumber = true;

void loop() {

  if (Serial.available()) {
    unsigned int recievedByte = Serial.read();
    if (recievedByte == 0) {
      number = millis() / 60000;
    }else{
      number += recievedByte;
    }
  }

  unsigned int minutesLeft = number - (millis() / 60000);

  if (minutesLeft > 5 || showNumber) {
    writeNumber(minutesLeft);
  }else{
    writeEmpty();
  }

  if (millis() > toggleInMillis) {
    showNumber = !showNumber;
    toggleInMillis = millis() + 1000;
  }
}

