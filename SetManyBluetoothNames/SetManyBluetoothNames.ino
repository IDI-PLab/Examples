/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
#include <SoftwareSerial.h>

//SoftwareSerial mySerial(12, 13); // RX, TX
SoftwareSerial units[] = {
  SoftwareSerial(12,13),
  SoftwareSerial(10,11),
  SoftwareSerial(8,9),
  SoftwareSerial(6,7),
  SoftwareSerial(4,5),
  SoftwareSerial(2,3),
};

char chars[4];

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Serial.println("Starting SoftwareSerials");
  for (int i = 0; i < 6; i++) {
    units[i].begin(9600);
  }
  
  Serial.println("Skriv inn startnummer");
}

void loop() // run over and over
{
  int num = 0;
  if (Serial.available()) {
    num = Serial.parseInt();
  }
  
  for (int i = 0; i < 6; i++) {
    while (units[i].available()) {
      Serial.write(units[i].read());
    }
    
    if (num > 0) {
      char chars[20];
      sprintf(chars, "AT+NAMEPLabBLE%02u", num+i);
      units[i].print(chars);
    }
  }
}

