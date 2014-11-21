interface PLabBridge {
  public int getWidth ();
  public int getHeight ();
  public void write (String string);
  public void subscribeRead (PLabRead sub);
  public void subscribeError (PLabRead sub);
}

interface PLabRead {
  public void read(String string);
}

private PLabBridge plabBridge;

void bindPLabBridge (PLabBridge bridge) {
  plabBridge = bridge;
}
