private PLabBridge plabBridge;

float x1 = 0, x2 = 0, x3 = 0;

void setup() {
  size(240,360);
}

void bindPLabBridge(PLabBridge bridge) {
  plabBridge = bridge;
  size (bridge.getWidth (), bridge.getHeight ());
  
  bridge.addDeviceOrientationListener(new PLabOrientationListener(){
    public void deviceOrientation(PLabOrientationEvent event) {
      x1 = event.alpha * width / 360;
      x2 = (180 + event.beta) * width / 360;
      x3 = (180 + event.gamma) * width / 360;
    }
  });
}

void draw() {
  background(0);
  stroke(255);
  strokeWeight(7);
  
  line(x1, 0, x1, height/3);
  line(x2, height/3, x2, 2*height/3);
  line(x3, 2*height/3, x3, height);
}
