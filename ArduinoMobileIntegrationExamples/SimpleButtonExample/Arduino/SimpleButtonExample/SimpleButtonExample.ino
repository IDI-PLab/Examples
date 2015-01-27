// Inkluderer bibliotek for aa gjnnomfoere seriell kommunikasjon med bluetooth
// Including library to do serial communication with bluetooth
#include <SoftwareSerial.h>

// Definer inn/utgangspinnene som brukes for send (TX) og motta (RX) for bluetooth
// Define I/O ports used for transmit (TX) and receive (RX)
const int BT_RX = 10;
const int BT_TX = 11;


// Hvilken utgang vi har lysene paa
// Which output we have the lights connected to
const int LIGHT_OUT = 4;

// Maksimalt antall bokstaver vi kan motta
// Max number of characters we can accept
const int MAX_CHARS = 20;

// Vi vet en beskjed har en maksimumsstoerrelse, vi maa kunne holde denne verdien pluss en 0 tilslutt
// We know a message has a maximum size, we must hold be able to hold this value plus an ending 0.
char text[MAX_CHARS+1];
int charNum = 0;

// Definer serieporten for kommunikasjon med bluetooth
// Define the serial port for communication with bluetooth
SoftwareSerial btSerial (BT_RX, BT_TX);

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
  if (btSerial.available () > 0) {
    
    // Les inn bokstaven
    // Read the character
    text[charNum] = btSerial.read ();
    Serial.write (text[charNum]);
    // Se etter om dette var siste bokstaven i en instruksjon
    // See if this was the last character in an instruction
    if (text[charNum] == ';') {
      // Sletter semikolonet, setter det som enden paa teksten
      // Removes the semicolon, set the character to end of string
      text[charNum] = 0;
      // Neste bokstav er foerste bokstav i en ny instruksjon
      // Next character is the first character in a new instruction
      charNum = 0;
      // Tolk og utoer kommando
      // Interpret and execute command
      readCommand ();
      // Overse carraige return og newline
      // Do not count carriage return or newline
    } else if (!((text[charNum] == '\n') || (text[charNum] == '\r'))){
      // Neste bokstav er nummer
      // Next character is number
      charNum++;
    }
    
    // Forsikre at vi neste gang ikke gaar ut over maks lengden vaar
    // Ensure that we next time do not exceed the max length of a string
    if (charNum == MAX_CHARS) {
      Serial.println ("For lang tekst!");
      charNum--;
    }
  }
  
  // Hvis vi har lyst til aa kunne skrive kommandoer i konsollvinduet, tar vi med dette
  // If we want to be able to write commands in the console window, we include this
  if (Serial.available () > 0) {
    btSerial.write (Serial.read ());
  }
}

void readCommand () {
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
