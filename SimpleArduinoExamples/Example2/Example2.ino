const int ledPin = 6;   // LED kobles til pinne 7
const int potPin = A0;  // Potmeter kobles til analog inngang 0 (A0)
int delayTime;          // Variabelen delayTime av type int holder verdien vi leser av på A0
 
void setup(){
  pinMode( ledPin, OUTPUT );        // Setter pinne 7 til utgang
}
 
void loop(){
  delayTime = analogRead( potPin ); // Leser av A0 og lagrer verdien i variabelen delayTime
  digitalWrite( ledPin, HIGH );     // Slår på LED
  delay(delayTime);                 // Venter i delayTime antall millisekunder
  digitalWrite( ledPin, LOW );      // Slår av LED
  delay(delayTime);                 // Venter i delayTime antall millisekunder
}
