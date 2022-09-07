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
int maxLightValue;
int minLightValue;

void setup()
{
 Serial.begin(9600);

 pinMode(LED_1, OUTPUT);
 pinMode(LED_2, OUTPUT);

 pinMode(WATER_SENSOR, INPUT);

 pinMode(FLOOR_BUTTON, INPUT);
 pinMode(CEILING_BUTTON, INPUT);

 digitalWrite(LED_1, LOW);
 digitalWrite(LED_2, LOW);

 attachInterrupt(digitalPinToInterrupt(FLOOR_BUTTON), setFloor, CHANGE);
 attachInterrupt(digitalPinToInterrupt(CEILING_BUTTON), setCeiling, CHANGE);

}
void loop()
{
  //lightValue is from photoresistor
  int lightValue = analogRead(LIGHT_SENSOR); 
  //waterValue is from water sensor 
  int waterValue = analogRead(WATER_SENSOR);


  /* LightValue calibration
     At a certain point light values get arbitrarily too high or too low so correct
  */
  if(lightValue > MAX_DARKNESS_VALUE){
    lightValue = MAX_DARKNESS_VALUE;
  }
  else if(lightValue < MIN_DARKNESS_VALUE)
  {
    lightValue = MIN_DARKNESS_VALUE ;
  }

  //For testing purpose
  Serial.println("Analog Light value: " + String(lightValue));
  Serial.println("Analog Water value: " + String(waterValue));
  Serial.println("maxLightValue: " + String(maxLightValue));
  Serial.println("minLightValue: " + String(minLightValue));

  // Map "measured environmental light values to RGB LED's lowest to highest brightness settings
  int lightLevel = map(lightValue, MIN_DARKNESS_VALUE, MAX_DARKNESS_VALUE, 0, 255);

  // Assign LEDs to analog light level based on environment
  
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
  

  
  delay(1000);
}

//This is called when CEILING_BUTTON (3) is pressed.
//The 
void setCeiling() {
  minLightValue = analogRead(LIGHT_SENSOR);
  
  if(minLightValue > MAX_DARKNESS_VALUE) {
    minLightValue = MAX_DARKNESS_VALUE;
  }

  Serial.println("BUTTON PRESSED");
}

void setFloor() {
  maxLightValue = analogRead(LIGHT_SENSOR);

  if(maxLightValue < MIN_DARKNESS_VALUE ) {
    maxLightValue = MIN_DARKNESS_VALUE ; 
  }

  Serial.println("BUTTON PRESSED");
}
 
 
 
 

 
