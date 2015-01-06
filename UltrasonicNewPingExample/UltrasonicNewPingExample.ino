/*
  Ultrasound Example
  
  Dette er et eksempel paa hvordan du kan bruke en HC-SR04 ultralyd sensor med biblioteket NewPing for aa maale avstand. Lengde (i centimeter) maales og skrives ut hvert sekund.
  
  Eksempelet viser foerst hvordan du kan gjoere oppsett. Deretter bruker det biblioteket for aa beregne avstand.
  
  Kretsen:
    - HC-SR04 (ultralyd sensor)
  
  Bibliotek
    - NewPing
  
  
  This is an example on how you may use a HC-SR04 ultrasonic sensor with the library NewPing to detect distance. Distance (in centimetres) is measured and printed every second.
  
  The example first show how to initialize. Afterwards it uses the library to calculate distance.
  
  Circuit
    - HC-SR04 (ultrasonic sensor)
  
  Library
    - NewPing
 */

// Inkluder biblioteket
// Including the library
#include <NewPing.h>

// Pinnen vi skal motta ekkosignal paa
// The pin we will receive echo calls from
const int echoPin = 7;
// Pinnen vi bruker for aa sende signal
// The pin we will use to send the signal
const int triggerPin = 8;
// Maks lengde (i cm)
// Max distance (in cm)
const int maxDistance = 300;

// Initialiser en "sonar" med triggerpinne, ekkopinne og maks lengde
// Initialize a "sonar" with trigger pin, echo pin and max distance
NewPing sonar(triggerPin, echoPin, maxDistance);


void setup() {
  // Starter seriekommunikasjon for pc utskrift
  // Starting serial communication to print to pc
  Serial.begin(9600);
}

void loop() {
  // Faa hvor lang tid det tar med en ping rundtur
  // Get the time for one ping trip
  unsigned int time = sonar.ping();
  
  // Beregn hvor langt dette var
  // Calculate how far this time represent
  float distance = time / US_ROUNDTRIP_CM;
  
  // Saa printer vi ut resultatet
  // We then print the result
  Serial.println(distance);
  // Og venter ett sekund foer vi gjentar
  // And wait for a second before we repeat
  delay(1000);
}
