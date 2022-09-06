
#define LED_PIN1 5
#define LED_PIN2 6
void setup()
{
 Serial.begin(9600);
 pinMode(LED_PIN1, OUTPUT);
 pinMode(LED_PIN2, OUTPUT);

 digitalWrite(LED_PIN1, LOW);
 digitalWrite(LED_PIN2, LOW);
}
void loop()
{
  //lightValue is from photoresistor
  int lightValue = analogRead(A0); 

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
  Serial.println("Analog value : " + String(lightValue));

  // Map "measured environmental light values to RGB LED's lowest to highest brightness settings
  int lightLevel = map(lightValue, 45, 700, 0, 255);

  // Assign LEDs to analog light level based on environment
  analogWrite(LED_PIN1, lightLevel);
  analogWrite(LED_PIN2, lightLevel);
  delay(100); // use delay for user perceived smoothness
}
 
 
 
 

 