/*-----------------------HEADLIGHTS-------------------*/

// LED definitions
#define LED_1 5
#define LED_2 6

//Button Definitions
#define FLOOR_BUTTON 2
#define CEILING_BUTTON 3

// Sensor Definitions
#define LIGHT_SENSOR A0
#define WATER_SENSOR A1

// Arbitrary Value Definitions
#define WATER_THRESHOLD 100
#define MIN_DARKNESS_VALUE 75
#define MAX_DARKNESS_VALUE 700

//For Calibration
int minDarkValue;
int maxDarkValue;

//Sensor Values
int darknessValue;
int waterValue;

//Unsigned so the lightLevel will never be negative
unsigned int lightLevel;

/*-----------------------END HEADLIGHTS---------------*/

void setup()
{
  Serial.begin(9600);

  setupLights();
}
void loop()
{
  headlights();
}

//This is called when CEILING_BUTTON (3) is pressed.
//The 
void setCeiling() {
  maxDarkValue = analogRead(LIGHT_SENSOR);
  if (maxDarkValue > MAX_DARKNESS_VALUE) {
    maxDarkValue = MAX_DARKNESS_VALUE;
  }
  
  for(int i = 0; i < 3; i++) {
    blink();
  }
  
  Serial.println("CEILING BUTTON PRESSED");
}

void setFloor() {
  minDarkValue = analogRead(LIGHT_SENSOR);
  if (minDarkValue < MIN_DARKNESS_VALUE) {
    minDarkValue = MIN_DARKNESS_VALUE;
  }
  
  
  for(int i = 0; i < 3; i++) {
    blink();
  }
  Serial.println("FLOOR BUTTON PRESSED");
}


void blink() {
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  delay(750);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  delay(750);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  delay(750); 
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  delay(750);
  Serial.println("BLINKING");
} 


void setupLights() {
 pinMode(LED_1, OUTPUT);
 pinMode(LED_2, OUTPUT);

 pinMode(WATER_SENSOR, INPUT);

 pinMode(FLOOR_BUTTON, INPUT_PULLUP);
 pinMode(CEILING_BUTTON, INPUT_PULLUP);

 digitalWrite(LED_1, LOW);
 digitalWrite(LED_2, LOW);

 //Listen for button presses
 attachInterrupt(digitalPinToInterrupt(FLOOR_BUTTON), setFloor, RISING);
 attachInterrupt(digitalPinToInterrupt(CEILING_BUTTON), setCeiling, RISING);

 // Setup default variable values
 minDarkValue = MIN_DARKNESS_VALUE;
 maxDarkValue = MAX_DARKNESS_VALUE;
}


void headlights() {
  darknessValue = analogRead(LIGHT_SENSOR); 
  waterValue = analogRead(WATER_SENSOR);

  if (darknessValue< MIN_DARKNESS_VALUE) {
    darknessValue = MIN_DARKNESS_VALUE;
  }

  if (darknessValue > MAX_DARKNESS_VALUE) {
    darknessValue = MAX_DARKNESS_VALUE;
  }

  //For testing purpose
  Serial.println("Analog Darkness value: " + String(darknessValue));
  Serial.println("Light Level: " + String(lightLevel));
  Serial.println("Analog Water value: " + String(waterValue));
  Serial.println("minDarkValue: " + String(minDarkValue));
  Serial.println("maxDarkValue: " + String(maxDarkValue));

  // Map measured environmental light values to RGB LED's lowest to highest brightness settings
  lightLevel = map(darknessValue, minDarkValue, maxDarkValue, 0, 255);

  delay(100); // use delay for user perceived smoothness

  if (waterValue > WATER_THRESHOLD)
  {
    Serial.print("\nWater detected!\n");
    lightLevel = 255;
    delay(50);
    waterValue = analogRead(WATER_SENSOR);
  }

  analogWrite(LED_1, lightLevel);
  analogWrite(LED_2, lightLevel);

  delay(100);
}
 

 
