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
const int RED_OUT = 4;
const int GREEN_OUT = 5;

// Definer serieporten for kommunikasjon med bluetooth
// Define the serial port for communication with bluetooth
PLabBTSerial btSerial (BT_TX, BT_RX);

// Oppsett av enheten og gi den til kjenne med BLE
// Set up the unit and start advertising with BLE
void setup()
{ 
  // Start kommunikasjon med konsoll
  // Start communication throuhg console
  Serial.begin (9600);
  // Linja under trengs kun for Leonardo (kan slettes om du bruker Arduino UNO)
  // The following line is only needed for Leonardo (can be deleted if you are using Arduino UNO)
  while (!Serial);
  // Skriv ut en velkomsthilsning
  // Print a velcome
  Serial.println ("Enkel knapp demonstrasjon med BLUETOOTH");
  
  // Setter utgangene for lyset
  // Set the output for our lights
  pinMode (RED_OUT, OUTPUT); 
  digitalWrite (RED_OUT, LOW);
  pinMode (GREEN_OUT, OUTPUT); 
  digitalWrite (GREEN_OUT, LOW);
  
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
    
    // Les inn bokstaven
    // Read the character
    char text[availableCount];
    btSerial.read (text, availableCount);
    
    // Tolk og utfoer kommando
    // Interpret and execute command
    readCommand(text);
  }
  
  // Hvis vi har lyst til aa kunne skrive kommandoer i konsollvinduet, tar vi med dette
  // If we want to be able to write commands in the console window, we include this
  if (Serial.available () > 0) {
    btSerial.write (Serial.read ());
  }
}

void readCommand (char *text) {
  // Del tekststrengen ved tegnet ':'. Dette gir oss starten paa siste halvdel strengen
  // Split the string at ':'. This gives us the start of second part of string
  // se strstr
  char* secondPart = strchr (text, ':');
  
  // Hvis vi ikke fant del 2 er det noe feil. Saa vi kan hoppe ut av loopen.
  // If we did not find part 2 something is wrong, so we can jump out of loop.
  if (secondPart == 0) {      // null peker sjekk // null pointer check
    // Dette skal ikke skje, saa vi kan si fra at det har skjedd
    // This should not happen, so we can tell that it did
    Serial.print ("Mottok ukjent kommando: ");
    Serial.println (text);
    return;
  }
  
  // Skriv ut kommandoen for aa vise at vi har mottatt noe
  // Write the received command to show we have received something
  Serial.print ("Mottok: ");
  Serial.println (text);
  
  // Foerste bokstav i andre streng maa vaere 0 for aa avslutte forste streng. Var ':'
  // First character in second string must be 0 to end first string. Was ':'
  secondPart[0] = 0;
  // Dette hopper til neste bokstav. Ogsaa kjent som pekeraritmetikk
  // This jumps to next character. Also known as pointer arithmetics
  secondPart++;
  
  // Bruk innebygde c/c++ funksjoner for aa sammenligne med knappenavn og kommandoer.
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
      Serial.print ("Mottok ukjent kommando: ");
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
      Serial.print ("Mottok ukjent kommando: ");
      Serial.println (secondPart);
    }
    
  } else {
    // Dette skal ikke skje, saa vi kan si fra at det har skjedd
    // This should not happen, so we can tell that it did
    Serial.print ("Mottok ukjent knapp: ");
    Serial.println (text);
  }
}


