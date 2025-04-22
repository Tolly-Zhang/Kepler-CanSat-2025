/*
  MQ9 CO + Combustibles Sensor
  -----------------------------
  • AO → A2 (analog input)
  • Heater internal, tied to 5 V
*/

#include <Arduino.h>

const uint8_t MQ9_PIN      = A2;
const int     SAMPLE_MS    = 5000;   // 5 s between reads

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("\n=== MQ-9 CO/Combustibles Prototype ==="));
  Serial.println(F("→ Pre‑heat sensor at 5 V for ≥24 h before flight."));
}

void loop() {
  int raw = analogRead(MQ9_PIN);
  float voltage = raw * (5.0 / 1023.0);

  Serial.print(F("MQ9 Raw: "));
  Serial.print(raw);
  Serial.print(F("  ("));
  Serial.print(voltage, 3);
  Serial.println(F(" V)"));

  // Optional: convert raw→ppm via your own calibration curve

  delay(SAMPLE_MS);
}
