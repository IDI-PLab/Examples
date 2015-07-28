private PLabBridge plabBridge;

float x1 = 0, x2 = 0, x3 = 0;

void setup() {
  size(240,360);
}

void bindPLabBridge(PLabBridge bridge) {
  plabBridge = bridge;
  size (bridge.getWidth (), bridge.getHeight ());
  
  bridge.setDeviceAccelerationUpdateInterval(20);
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
  
  line(x1, 0, x1, height/3);
  line(x2, height/3, x2, 2*height/3);
  line(x3, 2*height/3, x3, height);
}
