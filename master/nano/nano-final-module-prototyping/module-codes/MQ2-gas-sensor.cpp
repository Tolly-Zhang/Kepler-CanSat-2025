#include <Arduino.h>            // ← makes all the Arduino API available

/*
  MQ2 Gas Sensor — Analog‑Only Prototype
  --------------------------------------
  Reads the raw analog voltage from the MQ2 and applies a software threshold.

  Wiring (per CanSat System Reference) :contentReference[oaicite:0]{index=0}&#8203;:contentReference[oaicite:1]{index=1}:
    • MQ2 VCC  → 5 V
    • MQ2 GND  → GND
    • MQ2 A0   → A0 (Arduino analog input A0) :contentReference[oaicite:2]{index=2}&#8203;:contentReference[oaicite:3]{index=3}

  Notes:
    • We leave the module’s D0 pin unconnected.
    • Adjust RAW_THRESHOLD as needed (0–1023 scale).
    • SAMPLE_INTERVAL_MS matches the 5 s batch interval.
*/

const uint8_t MQ2_PIN           = A0;        // Analog input A0
const int     RAW_THRESHOLD    = 512;       // e.g. 512/1023 ≈ 2.5 V threshold
const unsigned long SAMPLE_INTERVAL_MS = 5000;

void setup() {
  Serial.begin(115200);
  while (!Serial) { /* wait for USB serial */ }
  Serial.println("\n=== MQ2 Analog‑Only Prototype ===");
  Serial.print("Threshold = raw ≥ ");
  Serial.println(RAW_THRESHOLD);
  Serial.print("Sampling every ");
  Serial.print(SAMPLE_INTERVAL_MS / 1000);
  Serial.println(" seconds\n");
}

void loop() {
  // 1) Read raw ADC (0–1023)
  int raw = analogRead(MQ2_PIN);
  // 2) Convert to volts
  float volts = raw * (5.0 / 1023.0);
  // 3) Software threshold check
  bool alarm = (raw >= RAW_THRESHOLD);

  // 4) Print results
  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("  (");
  Serial.print(volts, 3);
  Serial.print(" V)  → ");
  Serial.println(alarm
    ? "ALARM: gas ≥ threshold"
    : "OK: gas < threshold");

  delay(SAMPLE_INTERVAL_MS);
}
