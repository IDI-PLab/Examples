boolean reading;
const int sensorPin = 5;
const int ledPin = 8;
 
void setup(){
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}
 
void loop(){
  reading = digitalRead( sensorPin );
  if( reading == HIGH ){
    digitalWrite( ledPin, HIGH );
  } else {
    digitalWrite( ledPin, LOW );
  }
}
