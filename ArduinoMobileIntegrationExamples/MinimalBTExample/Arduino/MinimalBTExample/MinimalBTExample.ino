// Libraries:
// The SoftwareSerial is used for serial communcation using any two pins on the arduino.
// If PLabBTSerial is used, it must be included to make your code compile
#include <SoftwareSerial.h>
// PLabBTSerial is used to simplify gathering of text to lines. It extends SoftwareSerial.
#include <PLabBTSerial.h>

// rx (receive from) bluetooth pin. Connected to tx on bt unit
const int btRxPin = 2;
// tx (transmit to) bluetooth pin. Connected to rx on bt unit
const int btTxPin = 6;

// Creates a PLabBTSerial object. The rx (receive) and tx (transmit) pins MUST be defined.
// rx refers to input to arduino, that is what is transmitted (tx) from the device. tx works the same way.
// inverse_logic is inherited from SoftwareSerial. Set this to true if your device responds to active low. The argument is optional and defaults to false.
// bufferSize is the size of the internal buffer of PLabBTSerial. Set this to be able to include the longest message you expect to receive. Defaults to 50
PLabBTSerial btSerial(btRxPin, btTxPin /*, false optional, default: false, 100 optional, default: 50*/);

void setup() {
  // Start debug output
  Serial.begin(9600);
  Serial.println("Hello world!");
  // Start communication with your bluetooth device
  btSerial.begin(9600);
}

void loop() {
  // Check if some data has come from bt device
  int availableCount = btSerial.available();
  if (availableCount > 0) {
    // Create a char array (c-string) to hold the incomming data.
    char text[availableCount];
    // Read the incomming data. bufferSize refers to the buffer you are giving as an argument
    btSerial.read(text, availableCount);
    // Print the incomming data to console
    Serial.print("Incomming: ");
    Serial.println(text);
    Serial. println("Echo");
    // Echo text back
    btSerial.println(text);
  }
  // If some data has been written in the console, send this to bt unit
  while (Serial.available() > 0) {
    char letter = Serial.read();
    btSerial.write(letter);
  }
}
