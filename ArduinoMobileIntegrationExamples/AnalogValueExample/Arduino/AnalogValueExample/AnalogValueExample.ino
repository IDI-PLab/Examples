// Inkluderer bibliotek for aa gjnnomfoere seriell kommunikasjon med bluetooth
// Including library to do serial communication with bluetooth
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>

// Definer inn/utgangspinnene som brukes for send (TX) og motta (RX) for bluetooth
// Define I/O ports used for transmit (TX) and receive (RX)
const int BT_RX = 10;
const int BT_TX = 11;

// Definer serieporten for kommunikasjon med bluetooth
// Define the serial port for communication with bluetooth
PLabBTSerial btSerial (BT_RX, BT_TX);

// Siste leste verdi, for aa sjekke endringer
// Last read value, to check for changes
int prev_val = -1;

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
  Serial.println ("Enkel analog verdi med BLUETOOTH");
  
  // Start kommunikasjonen med bluetooth enhet
  // Start communication with bluetooth unit
  btSerial.begin (9600);
}

void loop()
{
  // Hvis vi har mottatt noe, skriv det til konsollen
  // If we have received something, write it to console
  if (btSerial.available () > 0) {
    Serial.write (btSerial.read ());
  }
  
  // Les den nye verdien, pin 0
  // Read the new value, pin 0
  int new_val = analogRead (A0);
    
  // Vi kan naa sjekke om verdien har endra seg, og hvis den har det send den. Ha litt feilmarginer
  // We can now check if th value has changed, and if so send it. Have some margins
  int diff = new_val - prev_val;
  if (abs(diff) > 5) {
    // Uten marginer kommer vi nok til aa proeve aa sende alt for ofte.
    // Without the margin, we will probably try to send way too often
    
    // Siden det er bare ett tall som skal sendes, og vi maa avslutte med ny linje, kaller vi bare println.
    // Since it is only one number that should be sent, and that number has to be ended by a newline, we just use println
    btSerial.println(new_val);
    
    // Husk aa oppdatere forrige verdi
    // Remember to update the last value
    prev_val = new_val;
  }
}
