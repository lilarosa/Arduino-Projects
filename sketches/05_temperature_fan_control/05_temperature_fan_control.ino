#include <math.h>

const int analogPin = A0;
const int ledPin = 6;
const int fanPin = 10;

const float targetTempC = 20.0;
const float hysteresisC = 0.5;

bool fanOn = false;
unsigned long lastLogTime = 0;
const unsigned long logIntervalMs = 2000;

const int fixedResistor = 10000;
const int betaValue = 3950;
const int r0 = 10000;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
}

void loop() {
  int raw = analogRead(analogPin);
  if (raw <= 0) {
    delay(500);
    return;
  }

  float rNtc = fixedResistor * (1023.0 / raw - 1.0);
  float tempK = 1.0 / (1.0 / 298.15 + (1.0 / betaValue) * log(rNtc / r0));
  float tempC = tempK - 273.15;

  if (millis() - lastLogTime >= logIntervalMs) {
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" C");
    lastLogTime = millis();
  }

  if (!fanOn && tempC > targetTempC + hysteresisC) {
    digitalWrite(fanPin, HIGH);
    digitalWrite(ledPin, HIGH);
    fanOn = true;
  } else if (fanOn && tempC < targetTempC - hysteresisC) {
    digitalWrite(fanPin, LOW);
    digitalWrite(ledPin, LOW);
    fanOn = false;
  }

  delay(200);
}
