#include <ZumoMotors.h>
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>

// Motors of the robot
ZumoMotors motors;

// Definer inn/utgangspinnene som brukes for send (TX) og motta (RX) for bluetooth
// Define I/O ports used for transmit (TX) and receive (RX)
const int BT_RX = 6;  // Connect to RXD on Bluetooth unit
const int BT_TX = 2;  // Connect to TXD on Bluetooth unit

// Define the serial port for communication with bluetooth
PLabBTSerial btSerial (BT_TX, BT_RX);

// If we should enable the zumo robot
boolean robotEnabled = false;

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello world");
  // Start communication with bluetooth unit
  btSerial.begin (9600);
}

void loop()
{
  // Bluetooth stuff:
  // See if we have received new characters
  int availableCount = btSerial.available();
  if (availableCount > 0) {
    
    // Define string (character array) large enough to hold all characters
    char text[availableCount];
    // Read the character. Remember to bring along size of the character array to avoid overflow
    btSerial.read(text, availableCount);
    
    // Output the received text
    Serial.println(text);
    
    // Split the text at ':', the command is made up of two parts
    char* secondPart = strchr (text, ':');
    // Ensure the split was successful (nullpointer check)
    if (secondPart == 0) {
      Serial.println("Illegal command received, stopping robot");
      robotEnabled = false;
    } else {
      // The split was succesful
      
      // The first character of secondPart is now ':', but it should be the end character ('\0' == 0) to end the first string
      secondPart[0] = '\0';
      // And the first character of the secondPart should be moved one step foreward
      secondPart++;
      
      // Now we should recognize the command
      if (strcmp ("BTN", text) == 0) {    // There is no difference between the strings
        if (strcmp ("ON", secondPart) == 0) {  // There is no difference between the strings
          // Robot should be turned on
          robotEnabled = true;
        } else if (strcmp("OFF", secondPart) == 0) {
          // Robot should stop
          robotEnabled = false;
        }
      }
    }
  }
  
  // If robot is enabled, it should move.
  if (robotEnabled) {
    motors.setSpeeds(100, 100);
  } else {
    // Else it should stop
    motors.setSpeeds(0, 0);
  }
}

