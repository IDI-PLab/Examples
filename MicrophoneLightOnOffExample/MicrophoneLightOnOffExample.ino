/*
  Microphone Light On/Off Example
  
  This is an example that show how a light can be turned on and off by a high sound.
  The light stays in its state unil a new high sound arrives.
  
  Circuit
    - Electret microphone
    - 220 ohm resistor
    - LED
  
  Created by Inge Edward Halsaunet, 2015
  Released into the public domain
*/


const int micIn = 2;    // Digital pin the microphone is connected to
const int ledOut = 3;   // Digital pin the led is connected to

int previousSensorReading = 0;  // Remember the previous reading of our microphone
int state = LOW;                // Current led state (HIGH or LOW)

void setup() {
  // Start serial communication with console
  Serial.begin(9600);
  // Initialize inputs and outputs
  pinMode(micIn, INPUT);
  pinMode(ledOut, OUTPUT);
}

void loop() {
  // Read the current microphone level
  int sensorRead = digitalRead(micIn);
  // See if reading has changed since last time
  if (previousSensorReading != sensorRead) {
    // Remember to update previous reading
    previousSensorReading = sensorRead;
    Serial.print("Changed, now: ");
    
    // When senosor is in high state, only notify user.
    if (sensorRead == HIGH) {
      Serial.println("High");
    } else {
      // When sensor changes to low state, we change the state of our output light.
      // This prevents the light from just giva a short flash, but instead remain on or off.
      Serial.println("Low");
      if (state == HIGH) {
        state = LOW;
      } else {
        state = HIGH;
      }
    }
  }
  // Update output light value
  digitalWrite(ledOut, state);
  // Short delay to ensure sensor stability
  delay(1);
}
