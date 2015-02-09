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
    
    // Send a message to show we are connected
    port.write("Hello world!\n");
    // Buffer data until a newline character is reached
    //port.bufferUntil('\n');
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

void setupSerial(String portName) {
  // Display all installed serial ports on computer
  println(Serial.list());
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
    String msg = p.readString();
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
  // ---------------------- THIS IS INDIVIDUAL TO EACH COMPUTER!!! ----------------
  // The com port here is found since I know which one in the list is the paired device.
  // Which one can be seen by name of the port and setting of paired device
  // There may be some issues when arduino is connected directly to the computer,
  // here, on this computer, it actually sends all that is written to serial port of Arduino
  // to the virtual port I connect to. It should not, but it does. Fix by using different
  // computers for Arduino and this sketch, or use external powersupply to Arduino (not connected to computer) 
  setupSerial(Serial.list()[1]);
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
