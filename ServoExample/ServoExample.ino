#include <Servo.h>    // Inkluderer Servo-iblioteket i koden
 
 
Servo minServo;       // Lager et servo-objekt
 
 
const int potPin = A5;
const int servoPin = 9;
int potVerdi;
int vinkel;
 
 
void setup(){
  minServo.attach(servoPin); // Knytter servo-objektet til pinne 9
}
 
void loop(){
  potVerdi = analogRead(potPin);
  vinkel = map(potVerdi, 0, 1023, 0, 179);
  minServo.write(vinkel);
  delay(15);
}
