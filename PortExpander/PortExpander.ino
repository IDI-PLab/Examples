#include <Wire.h>
#include <Adafruit_MCP23008.h>
 
const int addr = 0;
Adafruit_MCP23008 mcp;
 
void setup(){
  mcp.begin(addr);
  mcp.pinMode(0, INPUT);
  mcp.pinMode(3, OUTPUT);
}
 
void loop(){
  if(mcp.digitalRead(0))
    mcp.digitalWrite(3, HIGH);
  else
    mcp.digitalWrite(3, LOW);
}
