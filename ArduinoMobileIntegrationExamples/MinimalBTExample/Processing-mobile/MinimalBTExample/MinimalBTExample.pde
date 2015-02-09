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
 * ------------ REMOVED ---------------------------------
 */
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
  // REMOVED
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
