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
 * Injiserer javascript interfacet med processing koden
 *
 * Injects the javascript interface with the processing code
 */
void bindPLabBridge (PLabBridge bridge) {
  // Bind brua til den faktiske instansen
  // Bind the bridge to the instance
  pBridge = bridge;
  
  // Vi trenger noe som hoerer etter endringer i verdi
  // We need something that listens to a change in the value
  // Vi bruker en anonym indre klasse for dette
  // We use an anonymous inner class for this
  bridge.subscribeRead (new PLabRead() {
    public void read (String string) {
      myVal = int (string);
    }
  });
  
  // Sett stoerrelsen basert paa vindustoerrelsen 
  // Set the size based on window size
  size (bridge.getWidth (), bridge.getHeight ());
}

// En font holder hvilken skrift du skal bruke. Vi trenger en saann for aa faa ut tekst
// A font holds which font you should use. We need one of those to get text on screen
PFont myFont;
// Vi planlegger aa tegne noe basert paa en verdi som varierer mellom to verdier. Vi definerer minimum og maksimum
// We plan to draw something based on a value that varies between two values. We define min an max
int minVal = 0;
int maxVal = 1023;
// Vi trenger ogsaa en variabel som holder selve verdien
// We also need a variable to hold the actual value
int myVal = minVal;

// setup() kjører en gang. Her setter vi opp ting som stoerrelse (som blir overkjoert senere), lager font objektet og lignende.
// setup() run once. Here we set up size (that will be overridden later), make font objects and similar.
void setup () {
  size (320, 410);
  myFont = createFont ("Arial", 16, true);
}


// Draw kjører i loop (hvis vi ikke har kalt noLopp() tidligere i koden vaar). Her gjoer vi alle tegneinstruksjonene, animasjoner og andre oppdateringer.
// Draw runs in a loop (if we have not defined noLoop() earlier in the code). Here we do all drawing, animations and other updates.
void draw () {
  
  // Vi vil ha en bakgrunn aa tegne paa. Her er den svart
  // We need a background to draw on. Here it is black
  background (0);
  
  // Vi skal tegne headeren først.
  // We draw the header first
  drawHeader ();
  
  // Saa tegner vi selve naala, som viser veriden
  // Then we draw the needle, which show the value
  drawNeedle ();
}

// Denne metoden er ansvarlig for aa tegne teksten paa toppen
// This method is responsible to draw the text on top
void drawHeader() {
  // Vi klargjoer skriftstoerrelsen
  // We prepare the font size
  textFont (myFont, 36);
  // Setter skriftfargen
  // Sets its color
  fill (255,0,127);
  // Setter hvordan teksten skal posisjoneres
  // Set how to align the text
  textAlign (CENTER);
  // Og tegner teksten
  // And draw the text
  text ("Navn på verdi", width / 2, 40);
  
  // Vi gjentar for andre tekstelementer, men naa med mindre skrift
  // We repeat for other text elements, but with smaller font
  textFont (myFont, 20);
  fill (127);
  // Men naa vil vi ikke ha teksten sentrert
  // But we do not want the text centered
  textAlign (RIGHT);
  text ("Verdi: ", width / 2, 70);
  
  // Og en gang til for selve verdien
  // And once more for the actual value
  textAlign (LEFT);
  text (myVal, width / 2, 70);
}

// Denne metoden er ansvarlig for å tegne naala vaar.
// This method is responsible for drawing our needle
void drawNeedle () {
  // Her er det to muligheter som finnes.
  // Den mest direkte og intutive er kanskje å tegne ei nål direkte på verdien vi har
  // Den litt mer avanserte måten er å bruke transformasjoner, det vil si rotasjoner, translasjoner (flyttinger) og skaleringer
  // Bruk av transformasjoner vil gjøre det enklere å gjøre avanserte ting.
  // Siden dette skal være et enkelt eksempel, bruker vi den direkte måten
  
  // Vi vil skifte fargen på naala basert på verdi, fra groenn til roed
  // We want to change the color of our needle based on value, from green to red
  int r = 255 * myVal / maxVal; // Roed gaar fra 0 til 255 // Red goes from 0 to 255 
  int g = 255 - r ; // g = 255 - 255 * myVal / maxVal; // Groenn gaar fra 255 til 0 // Green goes from 255 to 0
  int b = 31; // vi vil bare ha litt blaa // We just want a tiny amount of blue
  stroke (r, g, b);
  
  // sentrum for naala vaar vil vi ha som
  // Center of our needle we want as
  int centrumX = width / 2;           // midt paa // The middle
  int centrumY = height * 3 / 4;      // 3/4 ned  // 3/4 down
  
  // Total lengde for naala lar vi være 1/3 av bredden vaar
  // Total length of needle we set as 1/3 of the width
  int needleLength = width / 3;
  
  // vi trenger vinkelen til naala. Processing bruker radianer som default. Vi kan oversette fra vanlige grader til radianer
  // We need the angle for the needle. Processing uses radians as default. We can translate for regular degrees to radians
  float degrees = 180 * (float)myVal / (float) maxVal;
  
  // Vi kan naa bruke sentrum og regne oss fram til de to siste variablene vaare
  // We can now use the center and calculate the last to varialbes
  int endX = centrumX - (int)(cos(radians(degrees)) * needleLength);
  int endY = centrumY - (int)(sin(radians(degrees)) * needleLength);
  
  // Og så tegner vi naala
  // And the draw the needle
  line (centrumX, centrumY, endX, endY);
}

void mouseClicked() {
  if (pBridge != null) {
    pBridge.disconnect();
  }
}
