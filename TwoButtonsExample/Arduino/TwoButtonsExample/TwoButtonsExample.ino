// Inkluderinger som trengs for ADAFRUIT BLE enhet
// Inclusions needed for ADAFRUIT BLE unit
#include <SPI.h>
#include "Adafruit_BLE_UART.h"

// Definer inn/utgangspinnene som brukes. Dette er for aa bruke ADAFRUIT sin enhet
// Define I/O ports used. This is for ADAFRUIT unit
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9

// Hvilken utgang vi har lysene paa
// Which output we have the lights connected to
#define RED_OUT 4
#define GREEN_OUT 5

// Maksimalt antall bokstaver vi kan motta
// Max number of characters we can accept
#define MAX_CHARS 20

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);

// Siste status. Bruk for aa sjekke endringer
// Last status. Use to check for differences
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

// Oppsett av enheten og gi den til kjenne med BLE
// Set up the unit and start advertising with BLE
void setup(void)
{ 
  Serial.begin (9600);
  while (!Serial);
  Serial.println ("Enkel knapp demonstrasjon med ADAFRUIT");
  
  // Setter utgangen for lyset
  // Set the output for our light
  pinMode (RED_OUT, OUTPUT); 
  digitalWrite (RED_OUT, LOW);
  pinMode (GREEN_OUT, OUTPUT); 
  digitalWrite (GREEN_OUT, LOW);

  // Navnet kan maksimalt vaere 7 bokstaver
  // Name can max be 7 characters
  BTLEserial.setDeviceName ("Knapper");

  BTLEserial.begin ();
}

void loop()
{
  // Faa enheten til aa oppdatere sed
  // Make the unit update itself
  BTLEserial.pollACI();

  // Etterspoer status
  // Ask for current status
  aci_evt_opcode_t status = BTLEserial.getState();
  
  // Hvis statusen er endra
  // If the status has changed
  if (status != laststatus) {
    // Skiv den ut
    // print it
    if (status == ACI_EVT_DEVICE_STARTED) {
        Serial.println ("  Her er jeg!");
    }
    if (status == ACI_EVT_CONNECTED) {
        Serial.println ("  Tilkoblet");
    }
    if (status == ACI_EVT_DISCONNECTED) {
        Serial.println ("  Frakoblet");
    }
    
    // Husk denne statusen til neste gang
    // Remember this status for next time
    laststatus = status;
  }

  // Hvis vi er tilkoblet kan vi se om vi har mottatt en instruksjon
  // If we are connected, we can check if we have an instruction waiting
  if ((status == ACI_EVT_CONNECTED) && BTLEserial.available ()) {
    
    // Vi vet en beskjed har en maksimumsstoerrelse, vi maa kunne holde denne verdien pluss en 0 tilslutt
    // We know a message has a maximum size, we must hold be able to hold this value plus an ending 0.
    char text[MAX_CHARS+1];
    int char_num = 0;
    
    // Les bokstavene en etter en
    // Read the characters one by one
    while (BTLEserial.available () && (char_num < MAX_CHARS)) {
      text[char_num] = BTLEserial.read ();
      char_num++;
    }
    
    // Sett siste bokstav
    // Set ending character
    text[char_num] = 0;
    
    // Del tekststrengen ved tegnet ':'. Dette gir oss starten paa siste halvdel strengen
    // Split the string at ':'. This gives us the start of second part of string
    // se strstr
    char* secondPart = strchr (text, ':');
    
    // Hvis vi ikke fant del 2 er det noe feil. Saa vi kan hoppe ut av loopen.
    // If we did not find part 2 something is wrong, so we can jump out of loop.
    if (secondPart == 0) {      // null peker sjekk // null pointer check
      // Dette skal ikke skje, saa vi kan si fra at det har skjedd
      // This should not happen, so we can tell that it did
      Serial.print ("    Mottok ukjent kommando: ");
      Serial.println (text);
      return;
    }
    
    // Foerste bokstav i andre streng maa vaere 0 for aa avslutte forste streng. Var ':'
    // First character in second string must be 0 to end first string. Was ':'
    secondPart[0] = 0;
    // Dette hopper til neste bokstav. Ogsaa kjent som pekeraritmetikk
    // This jumps to next character. Also known as pointer arithmetics
    secondPart++;
    
    // Bruk innebygde c/c++ funksjoner for aa sammenligne med knappenavn og kommandoer
    // Use built in c/c++ functions to compare with button names and commandoes
    if (strcmp ("B1", text) == 0) {
      
      // Roed knapp
      // Red button
      if (strcmp ("ON", secondPart) == 0) {
        digitalWrite (RED_OUT, HIGH);
      } else if (strcmp("OFF", secondPart) == 0) {
        digitalWrite (RED_OUT, LOW);
      } else {
        // Dette skal ikke skje, saa vi kan si fra at det har skjedd
        // This should not happen, so we can tell that it did
        Serial.print ("    Mottok ukjent kommando: ");
        Serial.println (secondPart);
      }
      
    } else if (strcmp ("B2", text) == 0) {
      
      // Groenn knapp
      // Green button
      if (strcmp ("ON", secondPart) == 0) {
        digitalWrite (GREEN_OUT, HIGH);
      } else if (strcmp("OFF", secondPart) == 0) {
        digitalWrite (GREEN_OUT, LOW);
      } else {
        // Dette skal ikke skje, saa vi kan si fra at det har skjedd
        // This should not happen, so we can tell that it did
        Serial.print ("    Mottok ukjent kommando: ");
        Serial.println (secondPart);
      }
      
    } else {
      // Dette skal ikke skje, saa vi kan si fra at det har skjedd
      // This should not happen, so we can tell that it did
      Serial.print ("    Mottok ukjent knapp: ");
      Serial.println (text);
    }
  }
}
