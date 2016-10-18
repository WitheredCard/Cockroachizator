// Constante variable

const int numberSignal = 10;
const int triggerPin = 2;
const int echoPin = 3; 
const float centimeterDivisor = 27.6233;

//////////////////////
// Initialize variable

int x = 0;
float distanceUS = 0;
float distanceIR = 0;

//////////////////////
// Main function

void setup() {
  Serial.begin(9600);
  // set Pin
  pinMode(triggerPin, OUTPUT_FAST);
  pinMode(echoPin, INPUT_FAST);
}

void loop() {
  for (int i = 0; i < numberSignal; i++) {
      distanceUS = calcDistance(timing());
      distanceIR = analogRead(A0);
      Serial.print(distanceUS);
      Serial.print(" , ");
      Serial.println(distanceIR);
      delay(1000);
  }
}

////////////////////
// Ultrason function

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

/////////////////////
