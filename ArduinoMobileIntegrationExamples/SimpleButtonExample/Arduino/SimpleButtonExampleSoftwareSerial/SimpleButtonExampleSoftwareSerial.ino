/*
 * SimpleButtonExample SoftwareSerial
 * 
 * Fjernstyr en LED på Arduine ved hjelp av SoftwareSerial og en tilstandsmaskin.
 * 
 * Remotely controlled LED on Arduino using SoftwareSerial and a simple state machine.
 */
#include <SoftwareSerial.h>

// Enum definisjon. Brukt for å parse innkommende tekst
// Enum definition. Used to parse incomming text.
enum ReadState { INIT, O_ACCEPTED, F_ACCEPTED, END };

// State of parser
ReadState myState = INIT;

// Definer inn/utgangspinnene som brukes for send (TX) og motta (RX) for bluetooth
// Define I/O ports used for transmit (TX) and receive (RX)
const int BT_RX = 10;
const int BT_TX = 11;


// Hvilken utgang vi har lysene paa
// Which output we have the lights connected to
const int LIGHT_OUT = 4;


// Definer serieporten for kommunikasjon med bluetooth
// Define the serial port for communication with bluetooth
SoftwareSerial btSerial (BT_RX, BT_TX);

void setup() {
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

void loop() {
  // Sjekker om vi har mottatt noe fra bluetooth enhet
  // See if anything has been received by Bluetooth unit
  if (btSerial.available()) {
    // Les mottatt bokstav
    // Read received character
    char recv = btSerial.read();

    // Gjør valg avhengig av tilstand
    // Do choises dependent on state
    switch (myState)
    {
      // INIT og END tilstand er egentlig like
      // INIT and END state are actually the same
      case INIT:  // Fallthrough
      case END:
        // Første bokstav vi aksepterer er kun en 'O'
        // First accepted is only an 'O'
        if (recv == 'O')
          myState = O_ACCEPTED;
        else
          myState = END;
        break;
      case O_ACCEPTED:
        // Andre bokstav kan enten være en ny 'O', en 'N' eller 'F'
        // Second character can either be an 'O', 'N' or 'F'
        switch(recv) {
          case 'O':
            myState = O_ACCEPTED;
            break;
          case 'N':
            myState = END;
            digitalWrite(LIGHT_OUT, HIGH);
            break;
          case 'F':
            myState = F_ACCEPTED;
            break;
          default:
            myState = END;
        }
        break;
      case F_ACCEPTED:
        // 'O' og 'F' er akseptable bokstaver
        // 'O' and 'F' are acceptable characters
        switch(recv) {
          case 'O':
            myState = O_ACCEPTED;
            break;
          case 'F':
            myState = END;
            digitalWrite(LIGHT_OUT, LOW);
            break;
          default:
            myState = END;
        }
        break;
    }
  }
  // Hvis vi har lyst til aa kunne skrive kommandoer i konsollvinduet, tar vi med dette
  // If we want to be able to write commands in the console window, we include this
  if (Serial.available () > 0) {
    btSerial.write (Serial.read ());
  }
}
