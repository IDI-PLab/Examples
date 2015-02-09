/*
 * ---------- Interfaces that make conversion to mobile simpler ----------
 */
// Interface documented in InterfacesExample
interface PLabBridge {
  public int getWidth ();
  public int getHeight ();
  public void write (String string);
  public void subscribeRead (PLabRead sub);
  public void subscribeError (PLabRead sub);
  public void disconnect();
}

// Interface documented in InterfacesExample
interface PLabRead {
  public void read(String string);
}

// Class implementing the PLabRead interface, only outputs data to console
class OutputMessages implements PLabRead {
  public void read(String string) {
    //println(string);
    // Echo it back
    if (plabBridge != null) {
      plabBridge.write("Echo: " + string);
    }
  }
}


/*
 * ---------- Serial communication for computer area ---------------------
 * ------------ REMOVED ---------------------------------
 */
/*
 * ---------- Binding the code with call javascript/serial port ----------
 */
private PLabBridge plabBridge;

void bindPLabBridge (PLabBridge bridge) {
  plabBridge = bridge;
  
  bridge.subscribeRead(new OutputMessages());
  
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
  // REMOVED
}

void draw() {
  // Draw some nice squares
  background(0);
  stroke(255);
  fill(127);
  rect(25,25,50,50);
}

void mouseClicked() {
  // Send a message to bt unit
  if (plabBridge != null) {
    plabBridge.write("Hello");
  }
}
