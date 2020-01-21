void setup() {
  pinMode(3, OUTPUT);
    Serial.begin(9600);

}

void loop() {
  int sensorValue = analogRead(A1);
  float voltage = sensorValue * (5.0 / 1023.0);
  analogWrite(3, voltage / 5.0 * 255.0);
  Serial.println(voltage);
}

