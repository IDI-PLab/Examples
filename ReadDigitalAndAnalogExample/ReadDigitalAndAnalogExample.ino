/*
  Read Digital and Analog Example
  
  This is code reads an digital and an analog input and displays the result in console to the user.
  
  Created by Inge Edward Halsaunet, 2015
  Released into the public domain
*/

const int analogIn = A0; // The analog pin we will use
const int digitalIn = 2; // The digital pin we will use

void setup() {
  // Start communication wirh console
  Serial.begin(9600);
  // Set input mode for digial pin
  pinMode(digitalIn, INPUT);
}

void loop() {
  // Read digital input and tell result to user.
  Serial.print("Digital: ");
  if (digitalRead(digitalIn) == HIGH) {
    Serial.print("High\t");
  } else {
    Serial.print("Low\t");
  }
  
  // Read analog input and tell result to user.
  Serial.print("Analog: ");
  Serial.println(analogRead(analogIn));
  // Wait for 1 second before next read
  delay(1000);
}
