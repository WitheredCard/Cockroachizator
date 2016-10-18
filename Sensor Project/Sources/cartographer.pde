
// Constante variable
// ultrasonic [5V/TRIG/ECHO/GND]
const int triggerPin = 2;
const int echoPin = 3;
const float centimeterDivisor = 27.6233;
// button [5V/BUTTON]
//const int buttonPin = 13;

// Initialize variable
int buttonState = LOW;
float distanceUS = 0;
float distanceIR = 0;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT_FAST);
  pinMode(echoPin, INPUT_FAST);
  //pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    distanceUS = calcDistance(timing());
    distanceIR = analogRead(A0);
    if (distanceUS < 100 && distanceUS > 400) {
      // warningLed
      Serial.println("Outside Range");
    } else {
      // sendPos
    }
  }
}

float calcDistance(long microsec) {
  return microsec / centimeterDivisor / 2.0;
}

long timing() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH);
}

