/*
 * ---------- Interfaces that make conversion to mobile simpler ----------
 */
// Interfaces documented in InterfacesExample
interface PLabBridge {
  public int getWidth ();
  public int getHeight ();
  public void write (String string);
  public void subscribeRead (PLabRead sub);
  public void subscribeError (PLabRead sub);
  public void disconnect();
}
interface PLabRead {
  public void read(String string);
}


/*
 * ---------- Serial communication for computer area ---------------------
 */
import processing.serial.*;

class BridgeReplacer implements PLabBridge {
  Serial port;
  PLabRead subscribedRead = null;
  
  BridgeReplacer(Serial serialPort) {
    port = serialPort;
    port.clear();
    
    // Buffer data until a newline character is reached
    port.bufferUntil('\n');
  } 
  public int getWidth () {
    return width;
  }
  public int getHeight () {
    return height;
  }
  public void write (String string) {
    port.write(string + "\n");
    println("Sent: " + string);
  }
  public void subscribeRead (PLabRead sub) {
    subscribedRead = sub;
  }
  public void subscribeError (PLabRead sub) { /* We do not care about this while developing */ }
  public void disconnect() { /* We do not care about this while developing */ }
}

BridgeReplacer bridgeReplacer;

void setupSerial() {
  // Get and display all installed serial ports on computer
  String[] serials = Serial.list();
  println(serials);
  // We need to connect to a port.
  // ---------------------- THIS IS INDIVIDUAL TO EACH COMPUTER!!! ----------------
  // On Windows computer, which one can be seen by name of the port and setting of paired device.
  // On a Mac/unix system, it should be the one containing the name of the device preceeded by tty
  String portName;
  // The com port here is found since I know which one in the list is the paired device, and I am on a Windows computer
  portName = "COM12";
  // ----- Basic search algorithm. Uncomment to use on Mac
  /*
  for (int i = 0; i < serials.length; i++) {
    portName = serials[i];
    // The name of the handed out bt devices contains the phrase "PLab". The first element containing this phrase should be the correct port.
    if (portName != null && portName.contains("PLab")) {
      break;
    }
  }
  */
   
  // Init a new serial connection
  Serial port = new Serial(this, portName, 9600);
  // Set up our replacement for the plab bridge
  bridgeReplacer = new BridgeReplacer(port);
  // "bind" the replacer instead of the javascript used in mobile devices (replace javascript injection)
  bindPLabBridge(bridgeReplacer);
}

// Event handler when something happens to the serial port
void serialEvent(Serial p) {
  // Ensure the was event was fired from the correct port
  if (p == bridgeReplacer.port) {
    // Try to read until a newline is found
    String msg = p.readStringUntil('\n');
    // Check the event was fired because a newline was received, and that we have a receiver
    if (msg != null && bridgeReplacer.subscribedRead != null) {
      // Send message to the one listening
      bridgeReplacer.subscribedRead.read(msg);
    }
  }
}


/*
 * ---------- Binding the code with call javascript/serial port ----------
 */
private PLabBridge pBridge;
private int displayColor = 255;
private String received = null;

void bindPLabBridge (PLabBridge bridge) {
  pBridge = bridge;
  
  // Subscribe to messages. Print incomming messages and change color of drawing
  bridge.subscribeRead(new PLabRead() {
    public void read (String string) {
      println("Incomming: " + string);
      displayColor = (displayColor + 64) % 256;
    }
  });
  
  // Not really needed, but included as it is needed to fill screen on mobile device
  size(bridge.getWidth (), bridge.getHeight ());
}

/*
 * ---------- Ordinary Processing code ----------
 */
void setup() {
  // Setup a size for the sketch
  size(100,100);
  // Call setupSerial to run serial communication with com port. Comment out/remove when moving code to mobile device
  setupSerial();
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
    pBridge.write("Hello");
  }
}
