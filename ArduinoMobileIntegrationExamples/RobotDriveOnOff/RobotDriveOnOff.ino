#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoBuzzer.h>
#include <ZumoReflectanceSensorArray.h>
#include <SoftwareSerial.h>

ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

ZumoReflectanceSensorArray reflectanceSensors;


// This is the maximum speed the motors will be allowed to turn.
// (400 lets the motors go at top speed; decrease to impose a speed limit)
const int MAX_SPEED = 400;

const int btRxPin = 2;
const int btTxPin = 6;

// Define the serial port for communication with bluetooth
SoftwareSerial btSerial (btRxPin, btTxPin);

// If we should enable the zumo robot
boolean robotEnabled = true;

// Max number of characters we can accept
const int MAX_CHARS = 100;

// We know a message has a maximum size, we must hold be able to hold this value plus an ending 0.
char text[MAX_CHARS+1];
int charNum = 0;


void setup()
{
  Serial.begin(9600);
   // Start communication with bluetooth unit
  btSerial.begin (9600);
  
  // Wait for the user button to be pressed and released
  button.waitForButton();
  
  motors.setSpeeds(100,100); //set left and right motor speed
  delay(1000);
  motors.setSpeeds(0,0);
  Serial.println("Hello world");
}

void loop()
{
  // Bluetooth stuff:
  // See if we have received a new character
  if (btSerial.available () > 0) {
    // Read the character
    text[charNum] = btSerial.read ();
    Serial.print(text[charNum]);
    // See if this was the last character in an instruction
    if (text[charNum] == ';') {
      // Removes the semicolon, set the character to end of string
      text[charNum] = 0;
      // Next character is the first character in a new instruction
      charNum = 0;
      // Interpret and execute command
      readCommand ();
      // Do not count carriage return or newline
    } else if (!((text[charNum] == '\n') || (text[charNum] == '\r') || (text[charNum] == 0))){
      // Next character is number
      charNum++;
    }
    
    // Ensure that we next time do not exceed the max length of a string
    if (charNum == MAX_CHARS) {
      Serial.println ("For lang tekst!");
      charNum--;
    }
  }
  
  if (robotEnabled) {
    motors.setSpeeds(100,100);
  } else {
    motors.setSpeeds(0,0);
  }
}

void readCommand () {
  Serial.println("\nCommand received");
  // Split the string at ':'. This gives us the start of second part of string
  // see strstr
  char* secondPart = strchr (text, ':');
  
  // If we did not find part 2 something is wrong, so we can jump out of loop.
  if (secondPart == 0) {      // null pointer check
    // This should not happen
    return;
  }
  
  // First character in second string must be 0 to end first string. Was ':'
  secondPart[0] = 0;
  // This jumps to next character. Also known as pointer arithmetics
  secondPart++;
  
  // Use built in c/c++ functions to compare with button names and commandoes

  if (strcmp ("B1", text) == 0) {
    if (strcmp ("ON", secondPart) == 0) {
      robotEnabled = true;
      //digitalWrite(1, HIGH);
    } else if (strcmp("OFF", secondPart) == 0) {
      robotEnabled = false;
      //digitalWrite(1, LOW);
    }
  }
}
