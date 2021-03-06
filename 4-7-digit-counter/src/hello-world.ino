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

int pinA = 5;
int pinB = 7;
int pinC = 2;
int pinD = 3;
int pinE = 6;
int pinF = 8;
int pinG = 4;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pins as outputs.
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
}

const int DELAY = 5;

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

// the loop routine runs over and over again forever:
void loop() {
  while(true) {
    writeNumber(millis() / 1);
  }
}

