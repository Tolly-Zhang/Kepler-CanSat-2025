/*
  CanSat SGP30 Air‑Quality Sensor Prototype
  -----------------------------------------
  Pin Mappings (from CanSat_System_Reference.md):
    • SGP30 VIN → 3.3 V
    • SGP30 GND → GND
    • SGP30 SDA → A4 (I²C SDA) :contentReference[oaicite:0]{index=0}
    • SGP30 SCL → A5 (I²C SCL) :contentReference[oaicite:1]{index=1}
*/

#include <Wire.h>
#include <Adafruit_SGP30.h>

Adafruit_SGP30 sgp;

void setup() {
  Serial.begin(115200);
  while (!Serial) { /* wait for Serial */ }
  Serial.println("\n=== CanSat SGP30 Prototype ===");

  // Initialize I²C (uses SDA/A4 and SCL/A5 by default)
  Wire.begin();

  // Initialize SGP30 sensor
  if (!sgp.begin()) {
    Serial.println("ERROR: SGP30 not found! Check wiring.");
    while (1);
  }
  Serial.println("SGP30 sensor found.");

  // Print sensor serial number (built‑in array)
  Serial.print("SGP30 Serial # (HEX): ");
  for (uint8_t i = 0; i < 3; i++) {
    Serial.print(sgp.serialnumber[i], HEX);
    if (i < 2) Serial.print(":");
  }
  Serial.println();

  // Start Indoor Air Quality measurement
  if (!sgp.IAQinit()) {
    Serial.println("ERROR: IAQ init failed!");
    while (1);
  }
  Serial.println("IAQ measurement initialized.");
}

void loop() {
  // Trigger a new IAQ measurement
  if (sgp.IAQmeasure()) {
    Serial.print("eCO2: ");
    Serial.print(sgp.eCO2);
    Serial.print(" ppm\tTVOC: ");
    Serial.print(sgp.TVOC);
    Serial.println(" ppb");
  } else {
    Serial.println("Measurement failed.");
  }
  delay(1000); // sample at ~1 Hz
}
