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
#define MAX_DARKNESS_VALUE 700
#define MIN_DARKNESS_VALUE 45

//For Calibration
int minDarkValue;
int maxDarkValue;

void setup()
{
 Serial.begin(9600);

 pinMode(LED_1, OUTPUT);
 pinMode(LED_2, OUTPUT);

 pinMode(WATER_SENSOR, INPUT);

 pinMode(FLOOR_BUTTON, INPUT_PULLUP);
 pinMode(CEILING_BUTTON, INPUT_PULLUP);

 digitalWrite(LED_1, LOW);
 digitalWrite(LED_2, LOW);

 attachInterrupt(digitalPinToInterrupt(FLOOR_BUTTON), setFloor, RISING);
 attachInterrupt(digitalPinToInterrupt(CEILING_BUTTON), setCeiling, RISING);

 // Setup default variable values
 minDarkValue = MIN_DARKNESS_VALUE;
 maxDarkValue = MAX_DARKNESS_VALUE;

}
void loop()
{
  //lightValue is from photoresistor
  int lightValue = analogRead(LIGHT_SENSOR); 
  //waterValue is from water sensor 
  int waterValue = analogRead(WATER_SENSOR);


  /* LightValue calibration
     At a certain point light values get arbitrarily too high or too low so correct
  
  if(lightValue > MAX_DARKNESS_VALUE){
    lightValue = MAX_DARKNESS_VALUE;
  }
  else if(lightValue < MIN_DARKNESS_VALUE)
  {
    lightValue = MIN_DARKNESS_VALUE ;
  }

  */

  //For testing purpose
  Serial.println("Analog Light value: " + String(lightValue));
  Serial.println("Analog Water value: " + String(waterValue));
  Serial.println("minDarkValue: " + String(minDarkValue));
  Serial.println("maxDarkValue: " + String(maxDarkValue));

  // Map "measured environmental light values to RGB LED's lowest to highest brightness settings
  int lightLevel = map(lightValue, minDarkValue, maxDarkValue, 0, 255);

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

//This is called when CEILING_BUTTON (3) is pressed.
//The 
void setCeiling() {
  maxDarkValue = analogRead(LIGHT_SENSOR);
  
  /*
  for(int i = 0; i < 5; i++) {
    blink();
  }
  */
  Serial.println("CEILING BUTTON PRESSED");
}

void setFloor() {
  minDarkValue = analogRead(LIGHT_SENSOR);
  
  /*
  for(int i = 0; i < 5; i++) {
    blink();
  }
  */
}


void blink() {
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  delay(200);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  delay(200);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  delay(200); 
  Serial.println("BLINKING");
} 
 
 

 
