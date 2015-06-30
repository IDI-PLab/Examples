int reading, temp;
 
 
void setup(){
}
 
 
void loop(){
  reading = analogRead(A0);
  temp = map( reading, 0, 1023, -100, 100);
}
