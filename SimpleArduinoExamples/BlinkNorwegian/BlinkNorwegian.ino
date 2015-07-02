/*
 * BlinkNorwegian
 * 
 * Slår på en lysdiode (LED) i ett sekund, før den slåes av.
 * Koden er en variant av Arduino eksempelet Blink, men med kommentarer på norsk og en annen pinne brukt som utgang.
 * 
 * Kretsen
 *   1 x LED
 *   1 x 220 ohm motstand
 */
                                // Dette er en kommentar
/*
 * Dette er også en kommentar
 */
const int ledPin = 7;           // Definerer en konstant ledPin som innehar verdien 7
                                // dvs at lysdioden skal kobles til digital pinne 7
void setup(){
  pinMode( ledPin, OUTPUT );    // Angir at digital pinne 7 skal være en utgang
}
 
void loop(){
  digitalWrite( ledPin, HIGH );     // Setter pinne 7 høy
  delay(1000);                  // Venter i 1000ms
  digitalWrite( ledPin, LOW );  // Setter pinne 7 lav
  delay(1000);                  // Venter i 1000ms
}
