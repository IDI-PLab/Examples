// Inkluderer bibliotek for aa gjnnomfoere seriell kommunikasjon med bluetooth
// Including library to do serial communication with bluetooth
#include <SoftwareSerial.h>

// Definer inn/utgangspinnene som brukes for send (TX) og motta (RX) for bluetooth
// Define I/O ports used for transmit (TX) and receive (RX)
const int BT_RX = 10;
const int BT_TX = 11;

// Definer serieporten for kommunikasjon med bluetooth
// Define the serial port for communication with bluetooth
SoftwareSerial btSerial (BT_RX, BT_TX);

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
    btSerial.write ((uint8_t*)text, used_size);
    
    // Husk aa oppdatere forrige verdi
    // Remember to update the last value
    prev_val = new_val;
  }
}
