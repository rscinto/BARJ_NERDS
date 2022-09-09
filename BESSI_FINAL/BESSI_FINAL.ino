#include <IRremote.h>

/*--------------------Program Constants---------------*/

#define TICK_LENGTH 50
#define HEADLIGHT_TICK_LENGTH 50


/*--------------------Program Globals---------------*/

unsigned long ticks = 0;

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
unsigned int darknessValue;
unsigned int waterValue;

//Circular array for brightness checking
unsigned int darknessValues[120];
unsigned int darknessValuesIndex = 0;

//Calculated average brightness
float darknessValuesAvg = 0;
float darknessValuesLowAvg = 0;

//Target and current LED brightness levels
unsigned int targetLEDBrightnessLevel = 0;
unsigned int currentLEDBrightnessLevel = 0;

//Function prototypes
void setCeiling();
void setFloor();
void blink();
void setupLights();
void headlights();


//--------------ULTRA SONIC-----------------------
#define ECHO 13
#define TRIG 12
#define BRAKE_DISTANCE 10
long durationOfSoundWave; 
int distanceToWall; 

// function prototype
int findDistanceToWall();

//--------------ULTRA SONIC END-----------------------






//--------------IR-----------------------
const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
//--------------IR END-----------------------






//--------------MOTOR-----------------------
//Motor A
const int motorPin1  = 8;  // Pin 14 of L293 +
const int motorPin2  = 9;  // Pin 10 of L293  -   //FIXED
//Motor B
const int motorPin3  = 10; // Pin  7 of L293  +
const int motorPin4  = 11;  // Pin  2 of L293 -

//function prototypes
void brake();
void forward();
void backward();
//--------------MOTOR END -----------------------







void setup()
{
  Serial.begin(9600);

//--------------ULTRA SONIC-----------------------
  pinMode(TRIG, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(ECHO, INPUT); // Sets the echoPin as an INPUT
//--------------ULTRA SONIC END-----------------------

  
//--------------IR-----------------------
  irrecv.enableIRIn();
  irrecv.blink13(true);
//--------------IR END-----------------------


//--------------MOTOR-----------------------
    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
//--------------MOTOR END -----------------------

    setupLights();
}





// BEGIN MAIN LOOP
void loop()
{
  // increment tick counter
  ++ticks;
  if (ticks > 4000000000) {
    ticks = 1;
  }
  
  headlights();

 /*
//--------------ULTRA SONIC-----------------------
//  if (findDistanceToWall() <= BRAKE_DISTANCE) 
//  {
//    brake();
//  }
//--------------ULTRA SONIC END-------------------
  
  
  if (irrecv.decode(&results))
  {
      if (results.value == 0XFFFFFFFF)
        results.value = key_value;

      switch(results.value)
      {
        case 0xFF30CF:
        Serial.println("1");
        forward();
        break ;
        case 0xFF18E7:
        Serial.println("2");
        brake();
        break ;
        case 0xFF7A85:
        Serial.println("3");
        backward();
        break ;
      }
      key_value = results.value;
      irrecv.resume(); 
  }
  */

  delay(TICK_LENGTH); // sleep for TICK_LENGTH milliseconds
}
// END LOOP



// Full function definitions

//This is called when CEILING_BUTTON (3) is pressed.
void setCeiling() {
  Serial.println("CEILING BUTTON PRESSED");
  
  maxDarkValue = analogRead(LIGHT_SENSOR);

  // above a certain value, just consider us at maximum brightness
  if (maxDarkValue > MAX_DARKNESS_VALUE) {
    maxDarkValue = MAX_DARKNESS_VALUE;
  }
  
  blink();
}

//This is called when FLOOR_BUTTON (2) is pressed.
void setFloor() {
  Serial.println("FLOOR BUTTON PRESSED");
  
  minDarkValue = analogRead(LIGHT_SENSOR);
  
  // below a certain value, just consider us at minimum darkness
  if (minDarkValue < MIN_DARKNESS_VALUE) {
    minDarkValue = MIN_DARKNESS_VALUE;
  }
  
  blink();
}

void blink() {
  Serial.println("BLINKING");
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  delay(250);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  delay(250);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  delay(250); 
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  delay(250);
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


// HEADLIGHT LOGIC for loop
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


// ULTRASONIC
int findDistanceToWall() {
    // Clears the trigPin condition
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  // Sets TRIG activ for 10 microseconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationOfSoundWave = pulseIn(ECHO, HIGH);
  
  // Calculating the distanceToWall
  distanceToWall = durationOfSoundWave * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  Serial.println("Distance to wall: " + String(distanceToWall) + " cm");
  return distanceToWall;
}


// MOTOR
void brake()
{
  //make the motors stop
  Serial.println("BRAKE");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void forward()
{
  //make motors go
  Serial.println("FORWARD");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);

  delay(5000);

  brake();
}

void backward()
{
  //make motors go backwards
  Serial.println("BACKWARD");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}
