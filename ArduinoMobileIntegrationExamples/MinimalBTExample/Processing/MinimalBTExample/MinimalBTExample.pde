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
 * The following example shows how to communicate with a bluetooth device.
 * The code is written so it is easy to run on both a computer and through the
 * PLab app. Comment/uncomment one line in setup to run in app/on computer.
 *
 * When running in app, ONLY this file is neccesary to run.
 * AppReplacer is only used to run on computer.
 */
private PLabBridge pBridge;
private int displayColor = 255;
private String received = null;

void bindPLabBridge (PLabBridge bridge) {
  pBridge = bridge;
  
  // Subscribe to messages. Print incomming messages and change color of drawing
  bridge.subscribeMessages(new PLabRecv() {
    public void receive (String string) {
      println("Incomming: " + string);
      displayColor = (displayColor + 64) % 256;
    }
  });
  
  // Not striclty needed, but included as it is needed to fill screen on mobile device
  size(bridge.getWidth (), bridge.getHeight ());
}

void setup() {
  // Setup a size for the sketch
  size(100,100);
  // Call setupSerial to run serial communication with com port. Comment out/remove when moving code to mobile device
  setupSerial(); // COMMENT OUT THIS LINE TO RUN ON MOBILE DEVICE
}

void draw() {
  // Draw some nice squares
  background(0);
  stroke(255);
  fill(displayColor);
  rect(25,25,50,50);
}

void mouseClicked() {
  // Send a message to bt unit
  if (pBridge != null) {
    pBridge.send("Hello");
  }
}
