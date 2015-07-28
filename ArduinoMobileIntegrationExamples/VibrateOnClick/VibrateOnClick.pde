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
  if (mousePressed) {
    background(#FF0033);
  } else {
    background(#333333);
  }
}
