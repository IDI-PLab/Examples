/*
  Button Example
  
  This is an example to show the most simple way of reading the state of a button. When the state changes, the new state is printed to the console.
  
  Circuit
    - Button
    - 10 kiloohm resistor
*/

// A constant value that defines which pin we should read button state from.
const int buttonPin = 6;
// Remember the old value of the button. Needed to not print something each loop.
int oldVal = 0;

void setup() {
  // Start communication with the console
  Serial.begin(9600);
  // Define that the button pin should be an input
  pinMode(buttonPin, INPUT);
}

void loop () {
  // Something to store the new value in.
  int val;
  // Read the value
  val = digitalRead(buttonPin);
  
  // If the value has changed, do the following
  if (val != oldVal) {
    
    // Update the old value.
    oldVal = val;
    
    // Determine what to print
    if (val == HIGH) {
      // if the button is pushed
      Serial.println("Trykket paa knappen");
    } else if (val == LOW) {
      // if the button is released
      Serial.println("Slapp knappen");
    } else {
      // if no sensible value is read. THIS SHOULD NEVER HAPPEN, if it does, the Arduino has failed.
      Serial.println("Ukjent verdi lest");
    }
  }
  
  // Delay to ensure sensor stability
  delay(1);
}
