#include <Arduino.h>

/*
  CanSat MQ‑4 Sensor Prototype (module uses A0 pin)
  -------------------------------------------------
  Peripheral: MQ‑4 (methane) gas sensor
  
  Wiring:
    • Sensor A0 pin → Nano Every A1  (or A0 if you change MQ4_PIN)
    • VCC            → 5 V
    • GND            → GND
  
  Source: CanSat System Reference :contentReference[oaicite:0]{index=0}&#8203;:contentReference[oaicite:1]{index=1}
*/

const uint8_t MQ4_PIN    = A1;       // change to A0 if you prefer wiring to Arduino A0
const int     THRESHOLD  = 300;      // adjust after calibration

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("\n=== CanSat MQ‑4 Sensor Prototype ===");
  Serial.print  ("Reading module A0 on Arduino ");
  Serial.println(MQ4_PIN == A1 ? "A1" : "A0");
}

void loop() {
  int raw = analogRead(MQ4_PIN);
  float voltage = raw * (5.0 / 1023.0);

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("  (");
  Serial.print(voltage, 3);
  Serial.print(" V)  → ");

  if (raw < THRESHOLD) {
    Serial.println("OK: gas < threshold");
  } else {
    Serial.println("WARNING: gas ≥ threshold");
  }

  delay(1000);
}
