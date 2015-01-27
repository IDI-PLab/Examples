// Inkluderer bibliotek for aa gjnnomfoere seriell kommunikasjon med bluetooth
// Including library to do serial communication with bluetooth
#include <SoftwareSerial.h>

// Definer inn/utgangspinnene som brukes for send (TX) og motta (RX) for bluetooth
// Define I/O ports used for transmit (TX) and receive (RX)
const int BT_RX = 10;
const int BT_TX = 11;


// Hvilken utgang vi har lysene paa
// Which output we have the lights connected to
const int RED_OUT = 4;
const int GREEN_OUT = 5;

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
    } else {
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
  if (strcmp ("B1", text) >= 0) {
    
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
    
  } else if (strcmp ("B2", text) >= 0) {
    
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


