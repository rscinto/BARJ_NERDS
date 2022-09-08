//L293D
https://www.instructables.com/How-to-use-the-L293D-Motor-Driver-Arduino-Tutorial/
//Motor A
#define MOTOR_PIN1  = 5;  // Pin 14 of L293
#define MOTOR_PIN2  = 6;  // Pin 10 of L293
//Motor B
#define MOTOR_PIN3  = 10; // Pin  7 of L293
#define MOTOR_PIN5  = 9;  // Pin  2 of L293

//Ultrasonic Sensors
#define ECHO 2 
#define TRIG 3 
#define BRAKE_DISTANCE 10

long durationOfSoundWave; 
int distanceToWall; 

void setup() {

  
  //Motor pins
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);

    
  pinMode(TRIG, OUTPUT)
  pinMode(ECHO, INPUT); 

  //test the motor's key functionality
  test();
  
}


void loop() {
  if (findDistanceToWall() <= BRAKE_DISTANCE) {
    brake();
  }
}


void test() {

  //Motor Control - Motor A: MOTOR_PIN1,MOTOR_PIN2 & Motor B: MOTOR_PIN3,MOTOR_PIN4
  
  //This code  will turn Motor A clockwise for 2 sec.
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
  delay(2000); 
  
  //This code will turn Motor A counter-clockwise for 2 sec.
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, HIGH);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
  delay(2000);
    
  //This code will turn Motor B clockwise for 2 sec.
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, HIGH);
  digitalWrite(MOTOR_PIN4, LOW);
  delay(2000); 
  
  //This code will turn Motor B counter-clockwise for 2 sec.
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, HIGH);
  delay(2000);    
    
  //And this code will stop motors
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
}



void brake() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
}


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
