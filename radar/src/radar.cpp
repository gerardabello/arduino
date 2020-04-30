#include <Arduino.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

// defines pins numbers
const int trigPin = 11;
const int echoPin = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  Serial.begin(9600);
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

int servo_pos = 0;    // variable to store the servo position
bool servo_dir = false;

void updateServoPos() {
  if (servo_dir) {
    servo_pos += 5;
    if (servo_pos >= 180) {
      servo_dir = false;
    }
  }else{
    servo_pos -= 5;
    if (servo_pos <= 0) {
      servo_dir = true;
    }
  }

    myservo.write(servo_pos);
}

long continue_in_millis = millis();

void loop() {
  unsigned int distance = readDistance();
  Serial.println(distance);
  updateServoPos();

  long currentMillis = millis();
  if (currentMillis < continue_in_millis) {
    delay(continue_in_millis - currentMillis);
  }
  
  continue_in_millis = millis() + 200;
}
