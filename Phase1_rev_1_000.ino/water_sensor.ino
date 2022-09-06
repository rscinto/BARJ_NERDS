#define LED_PIN     2
#define POWER_PIN   7
#define SIGNAL_PIN  A5
#define THRESHOLD   100

int value = 0; // variable to store the sensor value

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN,   OUTPUT);   // configure D2 pin as an OUTPUT
  pinMode(SIGNAL_PIN, INPUT);
  digitalWrite(LED_PIN,   LOW); // turn LED OFF
}

void loop() {                 
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  Serial.print("Water Value: ");
  Serial.println(value);

  if (value > THRESHOLD) {
    Serial.print("The water is detected");
    digitalWrite(LED_PIN, HIGH);  // turn LED ON
  } else {
    digitalWrite(LED_PIN, LOW);   // turn LED OFF
  }
}
