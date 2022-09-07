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
#define MAX_LIGHT_VALUE 700
#define MIN_LIGHT_VALUE 45

//For Calibration
int floorLightValue;
int ceilingLightValue;

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
  if(lightValue > MAX_LIGHT_VALUE){
    lightValue = MAX_LIGHT_VALUE;
  }
  else if(lightValue < MIN_LIGHT_VALUE )
  {
    lightValue = MIN_LIGHT_VALUE ;
  }

  //For testing purpose
  Serial.println("Analog Light value: " + String(lightValue));
  Serial.println("Analog Water value: " + String(waterValue));

  // Map "measured environmental light values to RGB LED's lowest to highest brightness settings
  int lightLevel = map(lightValue, MIN_LIGHT_VALUE , MAX_LIGHT_VALUE, 0, 255);

  // Assign LEDs to analog light level based on environment
  analogWrite(LED_1, lightLevel);
  analogWrite(LED_2, lightLevel);
  delay(100); // use delay for user perceived smoothness

  
  while(waterValue > WATER_THRESHOLD)
  {
    Serial.print("\nWater detected!\n");
    analogWrite(LED_1, 255);
    analogWrite(LED_2, 255);
    delay(50);
    waterValue = analogRead(WATER_SENSOR);
  }
  

  Serial.println("floorLightValue: " + String(floorLightValue));
  Serial.println("ceilingLightValue: " + String(ceilingLightValue));
  delay(100);
}

//This is called when CEILING_BUTTON (3) is pressed.
//The 
void setCeiling() {
  ceilingLightValue = analogRead(LIGHT_SENSOR);
  
  if(ceilingLightValue > MAX_LIGHT_VALUE) {
    ceilingLightValue = MAX_LIGHT_VALUE;
  }

}

void setFloor() {
  floorLightValue = analogRead(LIGHT_SENSOR);

  if(floorLightValue < MIN_LIGHT_VALUE ) {
    floorLightValue = MIN_LIGHT_VALUE ;
  }

}
 
 
 
 

 
