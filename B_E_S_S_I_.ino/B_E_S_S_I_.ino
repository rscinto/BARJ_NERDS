// LED definitions
#define LED_PIN1 5
#define LED_PIN2 6

// Sensor Definitions
#define LIGHT_SENSOR A0
#define WATER_SENSOR A1

// Arbitrary Value Definitions
#define WATER_THRESHOLD 100

void setup()
{
 Serial.begin(9600);
 pinMode(LED_PIN1, OUTPUT);
 pinMode(LED_PIN2, OUTPUT);
 pinMode(WATER_SENSOR, INPUT);

 digitalWrite(LED_PIN1, LOW);
 digitalWrite(LED_PIN2, LOW);
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
  if(lightValue > 700){
    lightValue = 700;
  }
  else if(lightValue < 45)
  {
    lightValue = 45;
  }

  //For testing purpose
  Serial.println("Analog Light value: " + String(lightValue));
  Serial.println("Analog Water value: " + String(waterValue));

  // Map "measured environmental light values to RGB LED's lowest to highest brightness settings
  int lightLevel = map(lightValue, 45, 700, 0, 255);

  // Assign LEDs to analog light level based on environment
  analogWrite(LED_PIN1, lightLevel);
  analogWrite(LED_PIN2, lightLevel);
  delay(100); // use delay for user perceived smoothness

  while(waterValue > WATER_THRESHOLD)
  {
    Serial.print("\nWater detected!\n");
    analogWrite(LED_PIN1, 255);
    analogWrite(LED_PIN2, 255);
    delay(50);
    waterValue = analogRead(WATER_SENSOR);
  }
}
 
 
 
 

 