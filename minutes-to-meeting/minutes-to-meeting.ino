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

int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;


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

int dcount = 0;

void writeNumber(int number) {
  delay(1);

  // Crude PWN cause I forgot to use the correct pins for the cathodes.
  int d = dcount % 10 == 0 ? 1 : 0;
  dcount++;

  writeNumberDigit(D1, number % 10);
  delay(d);

  if (number > 9) {
    writeNumberDigit(D2, number / 10 % 10);
  }else{
    writeEmpty();
  }
  delay(d);


  if (number > 99) {
    writeNumberDigit(D3, number / 100 % 10);
  }else{
    writeEmpty();
  }
  delay(d);


  if (number > 999) {
    writeNumberDigit(D4, number / 1000 % 10);
  }else{
    writeEmpty();
  }
  delay(d);

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

long tempNumber = 0;
long number = millis() / 1000;
int step = -2;

void numberControler() {
  if (Serial.available()) {
    unsigned int recievedByte = Serial.read();
    if (recievedByte == 201) {
      tempNumber = millis() / 1000;
      step = 0;
    }else if (recievedByte == 202){
      // Number is finished
      number = tempNumber;
      step = -1;
    }else if (step >= 0){
      tempNumber += recievedByte * pow(200, step);
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

