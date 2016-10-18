int TIMER = 500;

int degree[] = {0,10,20,30,40,50,60,70,80,90,100};
int adc[] = {264,360,461,560,649,726,788,838,878,908,932};
int arraySize = sizeof(adc) / sizeof(adc[0]) - 1;
int result = 0;
int scale = pow(10, 2);

void setup() {
  Serial.begin(9600);
}

boolean checkLimit(int adcValue) {
  if (adcValue < adc[0] || adcValue > adc[arraySize]) {
    Serial.println("Error : The value is outside the range !!!");
    return false;
  }
  return true;
}

int interpolationAdc(int adcValue, int minAdc, int maxAdc) {
    // tempX = temp0 + (adcX - adc0) * (temp1 - temp0) / (adc1 - adc0)
    return (degree[minAdc] * scale) + (((adcValue * scale - adc[minAdc] * scale) * ((degree[maxAdc] * scale) - (degree[minAdc] * scale))) / (adc[maxAdc] * scale - adc[minAdc] * scale));
}

// utiliser des pointeurs afin de réduire la consommation de donnée
void binarySearch(int adcValue, int *midVal, int *minVal, int *maxVal) {
  int cnt = *midVal;
  int minAdc = *minVal;
  int maxAdc = *maxVal;
  
  if (adcValue == adc[cnt]) {
    result = degree[cnt];
  } else if (minAdc != maxAdc - 1) {
    if (adcValue < adc[cnt]) {
      maxAdc = cnt;
      cnt = cnt / 2 + ((minAdc == cnt / 2) ? 1 : 0);
    } else {
      minAdc = cnt;
      cnt = (arraySize - cnt) / 2 + cnt % 2 + ((cnt > (arraySize / 2)) ? cnt : 0);
    }
  binarySearch(adcValue, &cnt, &minAdc, &maxAdc);
  return ;
  } else {
    result = interpolationAdc(adcValue, minAdc, maxAdc);
  }
  Serial.print("Temperature : ");
  Serial.print(result / scale);
  if (scale > 0) {
    Serial.print(".");
    Serial.print(result % (int)(scale));
  }
  Serial.println();
  return ;
}

void loop() {
  int adcValue = analogRead(A0);
  int cnt = arraySize / 2;
  int minAdc = 0;
  int maxAdc = arraySize;
  
  if (checkLimit(adcValue)) {
    binarySearch(adcValue, &cnt, &minAdc, &maxAdc);
  }
    delay(TIMER);
}
