const int hallPin = 7;
const int ledPin = 8;
 
 
void setup() {
  pinMode( ledPin, OUTPUT );
  pinMode( hallPin, INPUT );
}
 
 
void loop(){
   
  if( digitalRead( hallPin ) == HIGH ){
    digitalWrite( ledPin, HIGH );
  } else {
    digitalWrite( ledPin, LOW );
  }  
}
