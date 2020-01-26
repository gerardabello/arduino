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

  // Allows cli to know when it has booted
  Serial.write(0);
}


void writeEmpty() {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH); 

  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);   
}

void writeDashes() {
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW); 
  digitalWrite(pinG, HIGH);     
}

int DELAY = 2;

void writeNumber(int number) {
  writeNumberDigit(D1, number % 10);
  delay(DELAY);
  writeNumberDigit(D2, number / 10 % 10);
  delay(DELAY);
  writeNumberDigit(D3, number / 100 % 10);
  delay(DELAY);
  writeNumberDigit(D4, number / 1000 % 10);
  delay(DELAY);
  writeEmpty();
}

void writeNumberDigit(int displayIndex, int number) {
  writeEmpty();

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

long number = millis() / 1000;
int step = -2;

void numberControler() {
  if (Serial.available()) {
    unsigned int recievedByte = Serial.read();
    if (recievedByte == 201) {
      number = millis() / 1000;
      step = 0;
    }else if (recievedByte == 202){
      // Number is finished
      step = -1;
    }else if (step >= 0){
      number += recievedByte * pow(200, step);
      step += 1;
    }
  }
}

unsigned long toggleInMillis = 2000;
bool showNumber = true;

void toggleShowNumber() {
  if (millis() > toggleInMillis) {
    showNumber = !showNumber;
    toggleInMillis = millis() + 1000;
  }
}

void loop() {
  long currentSeconds = millis() / 1000;

  numberControler();

  unsigned long secondsLeft = max(0, (number - currentSeconds));
  unsigned long minutesLeft = secondsLeft / 60;

  if (step == -2) {
    writeDashes();
  }else{ 
    if (minutesLeft > 2 || showNumber) {
      writeNumber(minutesLeft);
    }else{
      writeEmpty();
    }
  }

  toggleShowNumber();

}

