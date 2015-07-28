/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * This example shows how a button can be created and used to send messages to remote device
 */
private PLabBridge pBridge;

/**
 * Bruker denne som setup
 *
 * Uses this as setup
 */
void bindPLabBridge (PLabBridge bridge) {
  // Bind brua til den faktiske instansen
  // Bind the bridge to the instance
  pBridge = bridge;
  // Sett stoerrelsen basert paa vindustoerrelsen 
  // Set the size based on window size
  size (bridge.getWidth (), bridge.getHeight ());
  btnChanged ();
}

// For aa faa relativ posisjon definerer vi verdens stoerrelse
// To get relative positions, we define world size
int worldWidth = 100;
int worldHeight = 100;

// Vi definerer egenskapene til knappen i verdenssystemet
// We define properties of our button in the world system
int buttonX = 25;                         // worldWidth / 4
int buttonY = 25;                         // worldHeight / 4
int buttonSize = 50;                      // worldWidth / 2 or worldHeight / 2
boolean buttonPressed = false;

// Oversettelse fra verdenskoordinater til skjermkoordinater
// Conversion from world coordinates to screen coordinates
int bToScreenX (int x) {
  // Eksplisitt casting paa grunn av appen har javascript oppfoersel
  // Explicit cast done because of app javascript behaviour
  return (int) (width * x / worldWidth);
}
int bToScreenY (int y) {
  // Eksplisitt casting paa grunn av appen har javascript oppfoersel
  // Explicit cast done because of app javascript behaviour
  return (int) (height * y / worldHeight);
}

// Oversettelse fra skjermkoordinater til verdenskoordinater
// Conversion from screen coordinates to world coordinates
int bToWorldX (int sx) {
  // Eksplisitt casting paa grunn av appen har javascript oppfoersel
  // Explicit cast done because of app javascript behaviour
  return (int) (worldWidth * sx / width);
}
int bToWorldY (int sy) {
  // Eksplisitt casting paa grunn av appen har javascript oppfoersel
  // Explicit cast done because of app javascript behaviour
  return (int) (worldHeight * sy / height);
}

// setup () brukes kun til testing
// setup () is only used for testing purposes
void setup () {
  // Denne "Sett stoerrelsen" vil bli overkjoert naar brua blir bundet
  // This size set will be overridden when bridge is bound
  size (240, 360);
}

// Gjoer tegningen. Hovedloopen til eksempelet
// Does the drawing. Main loop of example
void draw () {
  // Kjoer update () for aa sjekke om knappen er trykt ned
  // Run update () to check if button is pressed
  bUpdate ();
  // graa bakgrunn
  // grey background
  background (#7F7F7F);
  // svart omriss til knappen
  // black stroke around the button
  stroke (#000000);
  // Fyll farge settes basert paa om knappen er trykt ned
  // Set fill color based on pressed status
  if (buttonPressed) {
    // Trykket -> svart knapp
    // Pressed -> black button
    fill (#000000);
  } else {
    // Uroert -> hvit knapp
    // Unpressed -> white button
    fill (#FFFFFF);
  }
  
  // Tegn knappen
  // Draw the button
  // Husk aa oversette til verdenskoordinater
  // Remember to translate coordinates to world coordinates
  rect (bToScreenX (buttonX), bToScreenY (buttonY), bToScreenX (buttonSize), bToScreenY (buttonSize));
}

void bUpdate () {
  boolean oldPressed = buttonPressed;
  // Standardverdien til knappen er alltid av
  // Default press status to false
  buttonPressed = false;
  // Hvis musa er trykt
  // If mouse is pressed
  if (mousePressed) {
    // Oversett musekoordinater (skjermkoordinater) til verdenskoordinater
    // Translate mouse coordinates (screen coordinates) to world coordinates
    int mX = bToWorldX (mouseX);
    int mY = bToWorldY (mouseY);
    // Sjekk om musa er innenfor i x-retning
    // Check if mouse is within bounds in x direction
    buttonPressed = mX >= buttonX && mX <= (buttonX + buttonSize);
    // Sjekk om musa er innenfor i y-retning
    // Check if mouse is within bounds in y direction
    buttonPressed = buttonPressed && mY >= buttonY && mY <= (buttonY + buttonSize); 
  }
  
  // Hvis statusen til knappen er endret, si ifra til brua. Dette gir oss minimalt med kommunikasjon
  // If the new status is changed, notify the bridge. This minimizes communication
  if (oldPressed != buttonPressed) {
    btnChanged ();
  }
}

void btnChanged () {
  // Denne kalles naar statusen til knappen har endra seg. Si ifra til brua
  // This is called when status of button has changed. Notify bridge
  // SJEKK ALLTID OM DET ER NULL FOR AA UNNGAA FEIL
  // ALLWAYS CHECK FOR NULL TO AVOID ERRORS
  
  if (pBridge != null) {
    String send;
    if (buttonPressed) {
      send = "ON";
    } else {
      send = "OFF";
    }
    pBridge.send (send);
  }
  
}
