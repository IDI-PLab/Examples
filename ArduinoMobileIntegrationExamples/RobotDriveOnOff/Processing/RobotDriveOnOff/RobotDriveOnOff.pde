// Interfacene er beskrevet i Interfaces eksempelet
// Interfaces described in the Interfaces example
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
private PLabBridge pBridge;

/**
 * ToggleButton er en rund knapp som endrer tilstand naar den trykkes paa.
 * Den har en farge naar den er paa, en annen naar av.
 * 
 * The ToggleButton is a circular button that changes state when clicked.
 * It has one color when on, and one when off.
 */
public class ToggleButton {
  // myRadius, myCenterX og myCenterY er lokasjon og stoerrelse paa knappen
  // myRadius, myCenterX and myCenterY is location and size of the button
  private float myRadius, myCenterX, myCenterY;
  // myOnColor og myOffColor er fargene for av og paa.
  // myOnColor and myOffColor is the colors for on and off. 
  private color myOnColor, myOffColor;
  // Tilstand og om knappen har endra tilstand siden sist den var lest
  // State and if the state has changed since last read
  private boolean state = false, changed = true;
  
  /**
   * Konstruktor. Lager en ny knapp som er, nylig endret med de dataene som er oppgitt.
   *
   * Constructor. Creates a new instance that is off, just changed with the data given.
   */
  public ToggleButton (float radius, float centerX, float centerY, color onColor, color offColor) {
    myRadius = radius;
    myOnColor = onColor;
    myOffColor = offColor;
    myCenterX = centerX;
    myCenterY = centerY;
  }
  
  /**
   * click () kalles med verdenskoordinater. Oppdaterer tilstanden om det er trykt inne i knappen.
   * 
   * click () is called with world coordinates. Updates the state of the butten when necessary.
   */ 
  public boolean click (float x, float y) {
    // Avstander fra klikk til sentrum
    // Distances from click to center
    float dx = myCenterX - x;
    float dy = myCenterY - y;
    
    // Sjekker om avstanden fra sentrum er mindre enn radius. Tenk Pytagoras
    // Checks if the distance from center is less than radius. Think on Pythagoras 
    boolean clicked = (myRadius * myRadius) > (dx * dx + dy * dy); 
    if (clicked) {
      changed = true;
      state = !state;
    }
    
    return clicked;
  }
  
  /**
   * Sjekker om tilstanden er endret siden den er lest sist.
   * 
   * Checks if the state is changed since last read.
   */
  public boolean hasChanged () {
    return changed;
  }
  
  /**
   * Leser tilstanden og setter endret siden sist til false.
   * 
   * Reads the state and sets changed flag to false.
   */
  public boolean readState () {
    changed = false;
    return state;
  }
  
  /**
   * Tegner knappen.
   * 
   * Draws the button.
   */
  public void draw () {
    // Svart omriss
    // Black stroke
    stroke (0);
    // Fyllfarge bestemt av tilstand.
    // Fill color decided by state
    fill (state ? myOnColor : myOffColor);
    /*
    // Dette er det samme som:
    // This is the same as:
    if (state) {
      fill (myOnColor);
    } else {
      fill (myOffColor);
    }
    */
    
    // Tegner knappen. Oversetter til skjermkoordinater. Bredden og hoeyden er to ganger radien
    // Draws the button. Translates to screen coordinates. Width and height is twice the radius
    ellipse (toScreenX (myCenterX), toScreenY (myCenterY), 2 * toScreenX (myRadius), 2 * toScreenY (myRadius));
  }
}

/**
 * Injiserer javascript interfacet med processing koden
 *
 * Injects the javascript interface with the processing code
 */
void bindPLabBridge (PLabBridge bridge) {
  // Bind brua til den faktiske instansen
  // Bind the bridge to the instance
  pBridge = bridge;
  // Sett stoerrelsen basert paa vindustoerrelsen 
  // Set the size based on window size
  size (bridge.getWidth (), bridge.getHeight ());
  
  update ();
}

// For aa faa relativ posisjon definerer vi verdens stoerrelse
// To get relative positions, we define world size
int worldWidth = 200;
int worldHeight = 250;

// Vi definerer egenskapene til knappen i verdenssystemet
// We define properties of our button in the world system
ToggleButton btn;

ToggleButton disconnectBtn;

// Oversettelse fra verdenskoordinater til skjermkoordinater
// Conversion from world coordinates to screen coordinates
float toScreenX (float x) {
  return width * x / worldWidth;
}
float toScreenY (float y) {
  return height * y / worldHeight;
}

// Oversettelse fra skjermkoordinater til verdenskoordinater
// Conversion from screen coordinates to world coordinates
float toWorldX (float sx) {
  return worldWidth * sx / width;
}
float toWorldY (float sy) {
  return worldHeight * sy / height;
}

// setup () brukes kun til testing
// setup () is only used for testing purposes
void setup () {
  // Lager knapp 1, roed
  // Create button 1, red
  btn = new ToggleButton (75, 100, 100, #7FFF7F, #550000);
  
  disconnectBtn = new ToggleButton(25, 25, 180, #FF0000, #CC0000);
  
  // Denne "Sett stoerrelsen" vil bli overkjoert naar brua blir bundet
  // This size set will be overridden when bridge is bound
  size (240, 360);
}

// Gjoer tegningen. Hovedloopen til eksempelet
// Does the drawing. Main loop of example
void draw () {
  // Hvis brua er satt, kjoer update. Dette vil sende de naavaerende tilstandene til arduino
  // If the bridge is set, run update. This will send the states to the arduino
  if (pBridge != null) {
    update ();
  }
  // graa bakgrunn
  // grey background
  background (#303030);
  
  // Tegn knappene
  // Draw the buttons
  btn.draw ();
  disconnectBtn.draw();
}

/**
 * Event naar det trykkes paa mus / touch
 * 
 * Event when mouse is clicked / touch
 */
void mouseClicked () {
  float mX = toWorldX (mouseX);
  float mY = toWorldY (mouseY);
  btn.click (mX, mY);
  disconnectBtn.click(mX, mY);
}

/**
 * update () sjeker om knappene er endret siden sist, og sender info videre til rammeverket
 * 
 * update () checks if the buttons have changed and sends the info on to the framework
 */
void update () {
  if (btn.hasChanged ()) {
    String val = btn.readState () ? "ON" : "OFF";
    if (pBridge != null) {
      pBridge.write ("BTN:" + val);
    }
  }
  if (disconnectBtn.readState() && pBridge != null) {
    pBridge.disconnect();
  }
}
