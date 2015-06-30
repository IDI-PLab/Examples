const int potPin = A0;
const int motorPin = 9;
int potReading;
int motorSpeed;
 
 
void setup(){
  pinMode(motorPin, OUTPUT);
}
 
void loop(){
  potReading = analogRead(potPin);
  motorSpeed = map(potReading, 0, 1023, 0, 255);
  analogWrite(motorPin, motorSpeed);
}
