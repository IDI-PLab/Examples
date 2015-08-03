Examples PLab App and Arduino Integration
===
This folder contains examples that document the use of the PLab app for
controlling Bluetooth and Bluetooth LE units from your phone.

The app is a framework for constructing user interfaces fast through
[Processing][1]. The framework uses [Processing.js][2] to interpret Processing
code. The framework was originally created for the Programming Lab course at
[NTNU][3]. For more information, see [the project repo][4].

For examples that contain Arduino code it is assumed that the neccessary
libraries are installed. All (and more) are gathered in the course
[library folder][5]. In particular is the PLabBT library used.

The app has allways the file `InterfacesInc.pde` already loaded, so there is
NO NEED TO INCLUDE THIS FILE when running in the app.

Example Descriptions
---
### InterfacesInc
Serves as documentation for app functionality. Is not meant to run.

### Empty
Minimal code neccesary for successful setup of project.

To run in app, copy the following files to the Internet:
* `Empty.pde`

### MinimalBTExample
A small example that show how to use the Bluetooth capabilities through
Processing code. The Processing code can be run on a computer. Changes to
`AppReplacer.pde` neccessary to run on a particular computer should be limited
to changing the content of `portName` within `setupSerial()` to the correct
port on the intended computer.

To run in app, copy the following files to the Internet:
* `MinimalBTExample.pde`
Note: The line holding `setupSerial();` must be commented out to run properly
in app.

### Acceleration
An example that show how to use the app to report device acceleration.

To run in app, copy the following files to the Internet:
* `Acceleration.pde`

### AnalogValueExample
An example that reads an analog value from an Arduino, and reports it back to
the app.

To run in app, copy the following files to the Internet:
* `AnalogValueExamplei.pde`

### Orientation
An example that show how to use the app to report device orientation.

To run in app, copy the following files to the Internet:
* `Orientation.pde`

### RobotDriveOnOff
An example that shows how to control a Pololu Zumo robot remotely with the app.

To run in app, copy the following files to the Internet:
* `RobotDriveOnOff.pde`

### SimpleButtonExample
An example that shows how a push button may be implemented in the app, and
state reported to an Arduino through a Bluetooth device.

Two versions of Arduino code:
* One using `PLabBTSerial.h` located in our `PLabBT` library.
* One using only `SoftwareSerial.h` and a simple state machine to parse
incomming text

To run in app, copy the following files to the Internet:
* `SimpleButtonExample.pde`

### TwoButtonsExample
An example that show how two toggle buttons can be created, and their states
reported an Arduino through a Bluetooth device.

To run in app, copy the following files to the Internet:
* `TwoButtonsExample.pde`

### VibrateOnClick
An example to show how to control the phone vibration through the app.

To run in app, copy the following files to the Internet:
* `VibrateOnClick.pde`

[1]: https://processing.org			"Processing"
[2]: http://processingjs.org			"Processing.js"
[3]: http://www.ntnu.edu	"Norwegian University of Science and Technology - NTNU" 
[4]: https://github.com/IDI-PLAB/plab-mobile-framework	"PLab Mobile Framework"
[5]: https://github.com/IDI-PLAB/plab-library	"PLab Libraries"
