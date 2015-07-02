void setup(){
  pinMode(5, INPUT);
  pinMode(8, OUTPUT);
}
 
void loop(){
  digitalWrite(8, digitalRead(5));
}
