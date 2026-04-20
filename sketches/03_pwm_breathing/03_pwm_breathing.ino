const int LED_PIN = 9;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  for (int value = 0; value <= 255; value++) {
    analogWrite(LED_PIN, value);
    delay(8);
  }

  for (int value = 255; value >= 0; value--) {
    analogWrite(LED_PIN, value);
    delay(8);
  }
}
