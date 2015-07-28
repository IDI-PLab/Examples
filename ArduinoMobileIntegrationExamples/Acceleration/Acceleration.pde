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
 * This example shows how to use the acceleration to detect motion.
 * Three bars are drawn to display acceleration in the different directions.
 * Gravitational acceleration is included in results.
 */
private PLabBridge plabBridge;

float x1 = 0, x2 = 0, x3 = 0;

void setup() {
  size(240,360);
}

void bindPLabBridge(PLabBridge bridge) {
  plabBridge = bridge;
  size (bridge.getWidth (), bridge.getHeight ());
  
  // Set how often the acceleration should be read (milliseconds)
  bridge.setDeviceAccelerationUpdateInterval(20);
  // Add acceleration read listener.
  bridge.addDeviceAccelerationListener(new PLabAccelerationListener(){
    public void deviceAcceleration(PLabAccelerationEvent event) {
      x1 = (10 + event.x) * width / 20;
      x2 = (10 + event.y) * width / 20;
      x3 = (10 + event.z) * width / 20;
    }
  });
}

void draw() {
  background(0);
  stroke(255);
  strokeWeight(7);
  
  // Draw three lines to display acceleration values.
  line(x1, 0, x1, height/3);
  line(x2, height/3, x2, 2*height/3);
  line(x3, 2*height/3, x3, height);
}
