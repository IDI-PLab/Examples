const int ledPin = 6;
const int potPin = A0;
const int switchPin = 8;
int lightIntensity;
 
 
void setup(){
  pinMode( ledPin, OUTPUT ); 
  pinMode( switchPin, INPUT );
}
 
void loop(){
  if( digitalRead( switchPin ) == HIGH ){       // Her tester vi om bryteren er trykket inn
    lightIntensity = analogRead( potPin );      // Leser verdien fra potmeteret
    analogWrite( ledPin, lightIntensity / 4 );  // Setter lysstyrken på LED
  } else {
    analogWrite( ledPin, 0 ); // Setter lysstyrken til 0 hvis bryteren ikke er trykket inn 
  }
}
