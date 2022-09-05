#define LED_PIN1 13
#define LED_PIN2 12
#define LED_PIN3 8
void setup()
{
 pinMode(LED_PIN1, OUTPUT);
 pinMode(LED_PIN2, OUTPUT);
 pinMode(LED_PIN3, OUTPUT);
 Serial.begin(9600);

 digitalWrite(LED_PIN1, LOW);
 digitalWrite(LED_PIN2, LOW);
 digitalWrite(LED_PIN3, LOW);
}
void loop()
{
  //lightValue is from photoresistor
  int lightValue = analogRead(A0); 

  //For testing purpose
  Serial.println("Analog value : " + lightValue);

  //All LED's are off, shining flashlight
  if (lightValue >= 0 && lightValue <= 150) {
   digitalWrite(LED_PIN1, LOW);
   digitalWrite(LED_PIN2, LOW);
   digitalWrite(LED_PIN3, LOW);
 }

 //One LED on, ambient room light
 if (lightValue >= 150) {
   digitalWrite(LED_PIN1, HIGH);
   digitalWrite(LED_PIN2, LOW);
   digitalWrite(LED_PIN3, LOW);
 } 

 //Two LED's on, moderately covered
 if (lightValue >= 500) {
   digitalWrite(LED_PIN1, HIGH);
   digitalWrite(LED_PIN2, HIGH);
   digitalWrite(LED_PIN3, LOW);
 }
 
 //All LED's on, fully covered
 if (lightValue >= 650) {
   digitalWrite(LED_PIN1, HIGH);
   digitalWrite(LED_PIN2, HIGH);
   digitalWrite(LED_PIN3, HIGH);
 }
}
 
 
 
 

 
