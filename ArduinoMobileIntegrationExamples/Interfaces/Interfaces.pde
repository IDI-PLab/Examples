/**
 * PLabBridge is the interface we have for communicating with the plab app.
 */
interface PLabBridge {
  /**
   * gets the width we have available to draw on
   */
  public int getWidth ();
  /**
   * gets the height we have available to draw on
   */
  public int getHeight ();
  /**
   * sends a string to a connected bluetooth device. Can not send more than 20 characters.
   */
  public void send (String string);
  /**
   * register callback function that will get the data sent from the connected device
   */
  public void subscribeMessages (PLabRecv sub);
  /**
   * Disconnects the device and returns to main menu
   */
  public void disconnect();
}

/**
 * A simple interface that defines the callback read function
 */
interface PLabRecv {
  /**
   * The callback function. Will be called when the connected device sends something to this program.
   */
  public void receive(String message);
}

/**
 * A variable to hold the injected bridge to the plab app
 */
private PLabBridge plabBridge;

/**
 * Injection function. Needed to get the functionality provided by our app. Use as setup.
 */
void bindPLabBridge (PLabBridge bridge) {
  plabBridge = bridge;
}
