/*
  Ultrasound Example
  
  Dette er et eksempel paa hvordan du kan bruke en HC-SR04 ultralyd sensor for aa maale avstand. Lengde (i meter) maales og skrives ut hvert sekund.
  
  Eksempelet viser foerst hvordan du kan gjoere oppsett. Deretter gjoer det ekko kall og beregner avstand.
  
  Kretsen:
    - HC-SR04 (ultralyd sensor)
  
  
  This is an example on how you may use a HC-SR04 ultrasonic sensor to detect distance. Distance (in metres) is measured and printed every second.
  
  The example first show how to initialize. Afterwards it does echo calls and calculates the distance.
  
  Circuit
    - HC-SR04 (ultrasonic sensor)
 */


// Pinnen vi skal motta ekkosignal paa
// The pin we will receive echo calls from
const int echoPin = 7;
// Pinnen vi bruker for aa sende signal
// The pin we will use to send the signal
const int triggerPin = 8;


void setup() {
  // Starter seriekommunikasjon for pc utskrift
  // Starting serial communication to print to pc
  Serial.begin(9600);
  
  // Setter opp pinnene. Den som sender (trigger) er en utgang, mens den som mottar (echo) er en inngang
  // Sets up the pins. The one sending (trigger) is output, while the receiving (echo) is input
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // For aa ha en ren hoey puls for aa maale avstand, starter vi med aa sette triggerpinnen lav og tar en veldig kort pause.
  // To get a clean high pulse for distance measurement we set the trigger pin low and takes a short break.
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  
  // Saa starter vi selve ekko signalet. For aa starte det maa vi sende en minimum 10 mikrosekunders puls til HC-SR04
  // We then start the echo signal itself. To start we must send a pulse of at least 10 microseconds to HC-SR04
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  
  // Deretter kan vi sette signalet lavt igjen.
  // And we can allow the trigger to go low.
  digitalWrite(triggerPin, LOW);
  
  
  // Saa er det til aa maale lengden det tar aa sende ut signalet til det kommer tilbake.
  // Then we measure the time it takes the signal from send to receive.
  long duration = pulseIn(echoPin, HIGH);
  
  // Saa er det over til aa beregne hvor langt dette tilsvarer
  // Then we should calculate how far this is equal to
  
  /*
  Lydhastighet er ca. 340 m/s
  Den maalte tiden er tiden det tar aa bevege seg fram og tilbake (to ganger faktisk lengde)
  Forholdet mellom lengde, tid og hastighet kan beskrives med
  v = d / t -> d = v * t -> d = 340 * duration / 1 000 000
  Men dette er dobbel lengde. Saa vi maa dele paa 2
  distance = d / 2 = duration * 340 / (2 * 1 000 000) = duration * 0,00017

  
  The speed of sound is approximately 340 m/s
  The measured time is the time it takes to move back and forth (twice the actual distance)
  The relationship between distance, time and speed can be described with
  v = d / t -> d = v * t -> d = 340 * duration / 1 000 000
  But this is double the distance. So we must divide by 2
  distance = d / 2 = duration * 340 / (2 * 1 000 000) = duration * 0,00017
  */
  float distance = duration * 0.00017;  
  
  
  // Saa printer vi ut resultatet
  // We then print the result
  Serial.println(distance);
  // Og venter ett sekund foer vi gjentar
  // And wait for a second before we repeat
  delay(1000);
}
