#include <Arduino.h>

const int ledPin = 23;
const int channel = 0;
const int freq = 5000;
const int resolution = 8;

void setup() {
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(ledPin, channel);
}

void loop() {
  for (int duty = 0; duty <= 255; duty++) {
    ledcWrite(channel, duty);
    delay(10);
  }

  for (int duty = 255; duty >= 0; duty--) {
    ledcWrite(channel, duty);
    delay(10);
  }
}