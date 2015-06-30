const int ledPin = 6;
const int potPin = A0;
int lightIntensity;
 
 
void setup(){
  pinMode( ledPin, OUTPUT ); 
}
 
void loop(){
  lightIntensity = analogRead( potPin );    
  analogWrite( ledPin, lightIntensity / 4 );  // Deler lightIntensity på 4 for å få en verdi mellom 0 og 255
}
