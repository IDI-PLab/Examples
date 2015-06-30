const int potPin = A0;
const int ledPin = 9;
int potReading;
int ledIntensity;
 
 
void setup(){
  pinMode(ledPin, OUTPUT);
}
 
void loop(){
  potReading = analogRead(potPin);
  ledIntensity = map(potReading, 0, 1023, 0, 255);
  analogWrite(ledPin, ledIntensity);
}
