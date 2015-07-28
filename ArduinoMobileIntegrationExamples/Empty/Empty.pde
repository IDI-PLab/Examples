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
 * The following is recommended pattern to get the PLab app
 * extended functionality.
 */

/**
 * A variable to hold the injected bridge to the plab app
 */
private PLabBridge plabBridge;

/**
 * setup is run once, as in normal Processing code.
 */
void setup() {
  // We recommend setting size and init what can be initialized here to see results and do development offline
  size(240,360);
}

/**
 * Injection function. Needed to get the functionality provided by our app. Use as setup for app specific functionality.
 */
void bindPLabBridge (PLabBridge bridge) {
  // Maintain the object for future use.
  plabBridge = bridge;
  // Set new size based on screen size of device app is running on. This will ensure smooth graphics.
  size(bridge.getWidth (), bridge.getHeight ());
}

/**
 * draw is run in a loop, as in normal Processing code.
 */
void draw() {}
