#include <IRremote.h>

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void brake()
{
  //make the motors stop
  Serial.println("BRAKE");
}

void forward()
{
  //make motors go
  Serial.println("FORWARD");
}

void backward()
{
  //make motors go backwards
  Serial.println("BACKWARD");
}




void loop()
{
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
