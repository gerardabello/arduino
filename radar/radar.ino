/*
* Ultrasonic Sensor HC-SR04
*/

// defines pins numbers
const int trigPin = 3;
const int echoPin = 2;
const int buzzerPin = 5;
const int ledPin = 6;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(buzzerPin, OUTPUT); 
  pinMode(ledPin, OUTPUT); 
}


int readDistance() {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int duration = pulseIn(echoPin, HIGH);

  int distance = duration*0.034/2;

  return distance;
}

unsigned long toneInMillis = 100;

void loop() {
  unsigned int distance = readDistance();

  unsigned long currentMillis = millis();

  if (currentMillis >= toneInMillis) {
    int toneLength = 50 + distance / 4;
    tone(buzzerPin, 8000 - toneLength * 10, toneLength);
    toneInMillis = currentMillis + toneLength * 2;
  }

  analogWrite(ledPin, min(distance / 10, 255));

  delay(50);
}
