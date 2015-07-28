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
  * This example shows how to use vibration on phone
  */
private PLabBridge plabBridge;

void bindPLabBridge (PLabBridge bridge) {
  plabBridge = bridge;
  size (bridge.getWidth (), bridge.getHeight ());
}

boolean previousPressed = false;

void setup() {
  size(240, 360);
}

void draw() {
  // if mouse state changed
  if (mousePressed != previousPressed) {
    previousPressed = mousePressed;
    if (mousePressed) {
      // If pressed, vibrate for a second
      if (plabBridge != null) {
        plabBridge.vibrate(1000);
      }
    }
  }
  
  // Draw background color. Different color if mouse is pressed to give feedback even if vibration is not present.
  if (mousePressed) {
    background(#FF0033);
  } else {
    background(#333333);
  }
}
