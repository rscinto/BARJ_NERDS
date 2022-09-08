#include <IRremote.h>


//--------------ULTRA SONIC-----------------------
#define ECHO 13
#define TRIG 12 
#define BRAKE_DISTANCE 10
long durationOfSoundWave; 
int distanceToWall; 
//--------------ULTRA SONIC END-----------------------



//--------------IR-----------------------
const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
//--------------IR END-----------------------






//--------------MOTOR-----------------------
//Motor A
const int motorPin1  = 5;  // Pin 14 of L293
const int motorPin2  = 6;  // Pin 10 of L293
//Motor B
const int motorPin3  = 10; // Pin  7 of L293
const int motorPin4  = 9;  // Pin  2 of L293


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
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
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

}






void loop()
{
  
//--------------ULTRA SONIC-----------------------
  if (findDistanceToWall() <= BRAKE_DISTANCE) 
  {
    brake();
  }
//--------------ULTRA SONIC END-----------------------
  
  
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
}
