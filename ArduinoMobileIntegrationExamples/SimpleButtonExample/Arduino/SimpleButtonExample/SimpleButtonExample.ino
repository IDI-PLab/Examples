// Inkluderer bibliotek for aa gjnnomfoere seriell kommunikasjon med bluetooth
// Including library to do serial communication with bluetooth
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>

// Definer inn/utgangspinnene som brukes for send (TX) og motta (RX) for bluetooth
// Define I/O ports used for transmit (TX) and receive (RX)
const int BT_RX = 11;  // Connect to RXD on Bluetooth unit
const int BT_TX = 10;  // Connect to TXD on Bluetooth unit


// Hvilken utgang vi har lysene paa
// Which output we have the lights connected to
const int LIGHT_OUT = 4;

// Definer serieporten for kommunikasjon med bluetooth
// Define the serial port for communication with bluetooth
PLabBTSerial btSerial (BT_TX, BT_RX);

// Oppsett av enheten og gi den til kjenne med BLE
// Set up the unit and start advertising with BLE
void setup(void)
{ 
  // Start kommunikasjon med konsoll
  // Start communication throuhg console
  Serial.begin (9600);
  // Linja under trengs kun for Leonardo (kan slettes om du bruker Arduino UNO)
  // The following line is only needed for Leonardo (can be deleted if you are using Arduino UNO)
  while (!Serial);
  Serial.println ("Enkel knapp demonstrasjon med BLUETOOTH");
  
  // Setter utgangen for lyset
  // Set the output for our light
  pinMode (LIGHT_OUT, OUTPUT); 
  digitalWrite (LIGHT_OUT, LOW);
  
  // Start kommunikasjonen med bluetooth enhet
  // Start communication with bluetooth unit
  btSerial.begin (9600);
}

void loop()
{
  // Se etter om vi har mottatt en ny bokstav
  // See if we have received a new character
  int availableCount = btSerial.available();
  if (availableCount > 0) {
    char text[availableCount];
    
    btSerial.read(text, availableCount);
    
    readCommand(text);
  }
  
  // Hvis vi har lyst til aa kunne skrive kommandoer i konsollvinduet, tar vi med dette
  // If we want to be able to write commands in the console window, we include this
  if (Serial.available () > 0) {
    btSerial.write (Serial.read ());
  }
}

void readCommand (char *text) {
  Serial.print ("Mottok: ");
  Serial.println (text);
  if (0 == strcmp ("ON", text)) {
    digitalWrite (LIGHT_OUT, HIGH);
    Serial.println("Lys paa");
  } else if (0 == strcmp("OFF", text)) {
    digitalWrite (LIGHT_OUT, LOW);
    Serial.println("Lys av");
  } else {
    // Dette skal ikke skje, saa vi kan si fra at det har skjedd
    // This should not happen, so we can tell that it did
    Serial.print ("Ukjent kommando!");
  }
}
