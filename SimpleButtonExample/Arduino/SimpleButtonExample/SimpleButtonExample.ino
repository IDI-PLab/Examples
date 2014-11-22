// Inkluderinger som trengs for ADAFRUIT BLE enhet
// Inclusions needed for ADAFRUIT BLE unit
#include <SPI.h>
#include "Adafruit_BLE_UART.h"

// Definer inn/utgangspinnene som brukes. Dette er for aa bruke ADAFRUIT sin enhet
// Define I/O ports used. This is for ADAFRUIT unit
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9

// Hvilken utgang vi har lyset paa
// Which output we have the light connected to
#define LIGHT_OUT 4

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
  pinMode (LIGHT_OUT, OUTPUT); 
  digitalWrite (LIGHT_OUT, LOW);

  // Navnet kan maksimalt vaere 7 bokstaver
  // Name can max be 7 characters
  BTLEserial.setDeviceName ("Knapp");

  BTLEserial.begin ();
}

boolean is_on (char* commando) {
  char on[2] = { 'O', 'N' };
  for (int i = 0; i < 2; i++) {
    if (commando[i] != on[i]) {
      return false;
    }
  }
  
  return true;
}

boolean is_off (char* commando) {
  char off[3] = { 'O', 'F', 'F' };
  for (int i = 0; i < 3; i++) {
    if (commando[i] != off[i]) {
      return false;
    }
  }
  
  return true;
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
    text[char_num] = '\0';
    
    // Vi kan naa sjekke hva vi skal gjoear
    // We can now check what we should do
    if (is_on (text)) {
      // Slaa paa lyset
      // Turn on the light
      digitalWrite (LIGHT_OUT, HIGH);
    } else if (is_off (text)) {
      // Slaa av lystet
      // Turn the light off
      digitalWrite (LIGHT_OUT, LOW);
    } else {
      // Dette skal ikke skje, saa vi kan si fra at det har skjedd
      // This should not happen, so we can tell that it did
      Serial.print ("    Mottok ukjent kommando: ");
      Serial.println (text);
    }
  }
}
