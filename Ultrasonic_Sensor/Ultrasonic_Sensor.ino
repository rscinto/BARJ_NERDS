#define ECHO 2 
#define TRIG 3 

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  Serial.begin(9600); 
  
  pinMode(TRIG, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(ECHO, INPUT); // Sets the echoPin as an INPUT
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  // Sets TRIG activ for 10 microseconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  // Displays the distance on the Serial Monitor
  Serial.println("Distance: " + String(distance) + " cm");
  delay(1000);
}
