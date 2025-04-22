/*
  CanSat Fan Control Prototype
  -----------------------------
  Pin Mappings (from CanSat_System_Reference.md):
    • Fan MOSFET Gate → D7 (digital output)      :contentReference[oaicite:0]{index=0}&#8203;:contentReference[oaicite:1]{index=1}
    • Fan + → 5 V
    • Fan – → MOSFET Drain
    • MOSFET Source → GND
*/

#include <Arduino.h>    // brings in uint8_t, pinMode, digitalWrite, Serial, etc.


const uint8_t FAN_PIN = 7;  // MOSFET gate

void setup() {
  Serial.begin(115200);
  while (!Serial) { /* wait for Serial */ }

  Serial.println("\n=== CanSat Fan Control Prototype ===");

  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);  // ensure fan is off at start
  Serial.println("Fan initialized OFF.");
  Serial.println("Type 'on' or 'off' then press Enter to control fan:");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd.equalsIgnoreCase("on")) {
      digitalWrite(FAN_PIN, HIGH);
      Serial.println("→ Fan turned ON");
    }
    else if (cmd.equalsIgnoreCase("off")) {
      digitalWrite(FAN_PIN, LOW);
      Serial.println("→ Fan turned OFF");
    }
    else {
      Serial.println("⚠️ Unknown command. Use 'on' or 'off'.");
    }
  }
}
