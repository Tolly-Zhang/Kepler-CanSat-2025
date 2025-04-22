// File: MQ135-gas-sensor.cpp

#include <Arduino.h>  // must include when using .cpp files in PlatformIO/Arduino framework

/*
  MQ135 Gas Sensor Prototype
  --------------------------
  Wiring (per CanSat System Reference) :contentReference[oaicite:0]{index=0}&#8203;:contentReference[oaicite:1]{index=1}:
    • MQ135 VCC → 5 V
    • MQ135 GND → GND
    • MQ135 OUT → A3 (Analog pin A3)
*/

static constexpr int MQ135_PIN = A3;   // Analog input for MQ‑135

void setup() {
  Serial.begin(115200);
  while (!Serial) { /* wait for Serial to initialize */ }
  Serial.println("\n=== MQ‑135 Gas Sensor Prototype ===");
}

void loop() {
  // Read raw ADC (0–1023)
  int rawValue = analogRead(MQ135_PIN);

  // Convert to voltage (5 V reference)
  float voltage = rawValue * (5.0f / 1023.0f);

  // Print for debugging
  Serial.print("MQ‑135 Raw: ");
  Serial.print(rawValue);
  Serial.print("  |  Voltage: ");
  Serial.print(voltage, 3);
  Serial.println(" V");

  // Wait for next sample (5 s)
  delay(5000);
}
