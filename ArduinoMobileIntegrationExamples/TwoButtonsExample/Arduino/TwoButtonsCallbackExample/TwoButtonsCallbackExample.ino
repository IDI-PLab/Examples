// Including library to do serial communication with bluetooth
#include <SoftwareSerial.h>
#include <PLabBTCallback.h>

// Define I/O ports used for transmit (TX) and receive (RX)
const int BT_RX = 10;
const int BT_TX = 11;

// Which output we have the lights connected to
const int RED_OUT = 4;
const int GREEN_OUT = 5;

// Define the callback controller
// Last is message divider. The sign that is between the command and argument. This is the same as the default value, ':'
PLabBTCallback btCallback(BT_RX, BT_TX, ':');


// Set up communication and functions that listen
void setup()
{
  // Start communication throuhg console
  Serial.begin (9600);
  // Print a velcome
  Serial.println ("Enkel knapp demonstrasjon med BLUETOOTH og callback");
  
  // Set the output for our lights
  pinMode (RED_OUT, OUTPUT); 
  digitalWrite (RED_OUT, LOW);
  pinMode (GREEN_OUT, OUTPUT); 
  digitalWrite (GREEN_OUT, LOW);
  
  // Register callback functions
  // Light controls
  btCallback.registerCallback("B1", redLightControl);
  btCallback.registerCallback("B2", greenLightControl);
  // Add an additional to listen to B2. Shows that multiple functions can be registered to single command
  btCallback.registerCallback("B2", printMessage);
  // Register callback just in case we receive a message without ':'. This is not needed, but included for debugging and demonstration
  btCallback.registerNoCommandCallback(printMessage);
  
  // Start communication with bluetooth unit
  btCallback.begin (9600);
}

void loop()
{
  // Get the callback controller to update its data structures.
  btCallback.update();
  // Nothing else needed
}

// ------ The functions used for callback
// Controlling the red light
void redLightControl(char *arg) {
  if (strcmp ("ON", arg) == 0) {
    digitalWrite (RED_OUT, HIGH);
  } else if (strcmp("OFF", arg) == 0) {
    digitalWrite (RED_OUT, LOW);
  } else {
    // This should not happen, so we can tell that it did
    Serial.print ("Mottok ukjent kommando for green lys: ");
    Serial.println (arg);
  }
}

// Controlling the green light
void greenLightControl(char *arg) {
  if (strcmp ("ON", arg) == 0) {
    digitalWrite (GREEN_OUT, HIGH);
  } else if (strcmp("OFF", arg) == 0) {
    digitalWrite (GREEN_OUT, LOW);
  } else {
    // This should not happen, so we can tell that it did
    Serial.print ("Mottok ukjent kommando for green lys: ");
    Serial.println (arg);
  }
}

// Demonstration that only prints message
void printMessage(char *arg) {
  Serial.println(arg);
}

