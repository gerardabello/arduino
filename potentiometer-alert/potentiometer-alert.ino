// defines pins numbers
const int potentiometerPitchPin = A0;
const int potentiometerDurationPin = A1;
const int buzzerPin = 5;
const int ledPin = 6;

void setup() {
  pinMode(buzzerPin, OUTPUT); 
  pinMode(ledPin, OUTPUT); 
}

unsigned long toneInMillis = 100;

void loop() {
   float pitch = analogRead(potentiometerPitchPin) / 1024.0;
   float duration = analogRead(potentiometerDurationPin) / 1024.0;

  unsigned long currentMillis = millis();

  if (currentMillis >= toneInMillis) {
    int toneLength = duration * 800;
    tone(buzzerPin, 5000 - pitch * 4000, toneLength);
    toneInMillis = currentMillis + toneLength * 1.2;
  }

  analogWrite(ledPin, pitch * 255);
}
