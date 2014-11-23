// Inkluderinger som trengs for ADAFRUIT BLE enhet
// Inclusions needed for ADAFRUIT BLE unit
#include <SPI.h>
#include "Adafruit_BLE_UART.h"

// Definer inn/utgangspinnene som brukes. Dette er for aa bruke ADAFRUIT sin enhet
// Define I/O ports used. This is for ADAFRUIT unit
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);

// Siste status. Bruk for aa sjekke endringer
// Last status. Use to check for differences
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

// Siste leste verdi, for aa sjekke endringer
// Last read value, to check for changes
int prev_val = -1;

// Oppsett av enheten og gi den til kjenne med BLE
// Set up the unit and start advertising with BLE
void setup(void)
{ 
  Serial.begin (9600);
  while (!Serial);
  Serial.println ("Enkel analog verdi med ADAFRUIT");

  // Navnet kan maksimalt vaere 7 bokstaver
  // Name can max be 7 characters
  BTLEserial.setDeviceName ("Analog");

  BTLEserial.begin ();
}

void loop()
{
  // Les den nye verdien, pin 0
  // Read the new value, pin 0
  int new_val = analogRead (A0);
  
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

  // Hvis vi er tilkoblet
  // If we are connected
  if (status == ACI_EVT_CONNECTED) {
    
    // Hvis vi mottok noe, kan vi printe det. Vi skulle egentlig ikke faa noe.
    // If we reveived something, we can print it. We should not get anything here though
    if (BTLEserial.available ()) {
      while (BTLEserial.available ()) {
        Serial.print (BTLEserial.read ());
      }
    }
    
    
    // Vi kan naa sjekke om verdien har endra seg, og hvis den har det send den. Ha litt feilmarginer
    // We can now check if th value has changed, and if so send it. Have some morgins
    int diff = new_val - prev_val;
    if (abs(diff) > 5) {
      // Foerst trenger vi ett sted aa lagre teksten som skal sendes
      // First we need a place to store the text to send
      // Denne maaten garanterer vi har stort no rom til aa lagre verdien uansett hvilket tall det er
      // This way guarantees we have enough space no matter the number
      // Vi kunne brukt 5 siden vi vet selve tallet er mellom 0 og 1024 (4 tegn) og ett tegn til avslutningsbokstanven
      // We could have used 5 since we know the number is between 0 and 1024 (4 characters) and one character to the end character
      int txt_size = sizeof (int) * 3 + 1;
      char text[txt_size];
      // Det finnes alternativer til itoa, men den viker som den skal
      // The are alternatives to itoa, but it works as it should
      // 10 til slutt betyr vi faar tallet i desimal format (slik som vi bruker til vanlig)
      // 10 in the end means vi get the number in decimal format (which we normally use)
      itoa (new_val, text, 10);
      
      // sjekk den faktiske stoerrelsen paa teksten
      // Check the actual size of the text
      int used_size = 0;
      while ((used_size < txt_size ) && (text[used_size] != 0)) {
        used_size++;
      }
      
      // Send data
      // Send data
      // Vi trenger et annet format naar vi sender (dette er pga hvordan biblioteket vi bruker definerer send data) -> casting
      // We need another format when we send (due to how the library we use define send data) -> casting
      //BTLEserial.write (send_buffer, used_size);
      BTLEserial.write ((uint8_t*)text, used_size);
      
      // Husk aa oppdatere forrige verdi
      // Remember to update the last value
      prev_val = new_val;
    }
    
  }
}
