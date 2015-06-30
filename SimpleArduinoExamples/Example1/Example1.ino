                                // Dette er en kommentar
const int ledPin = 6;           // Definerer en konstant ledPin som innehar verdien 7
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
