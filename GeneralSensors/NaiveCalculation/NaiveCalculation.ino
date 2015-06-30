float reading, voltage, temp;
 
 
void setup(){
}
 
 
void loop(){
  reading=analogRead(A0);          // Leser av spenningen på A0 
  voltage=reading/204.6;          // Regner om avlesning til spenning
  temp=( voltage * 40 ) - 100;    // Tallet 40 er 200/5 som tilsvarer antall grader per volt
}                                   // Vi må trekke fra 100 siden 0V tilsvarer -100°C
