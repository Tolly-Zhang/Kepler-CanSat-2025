/*
  CanSat Servo Control Prototype
  --------------------------------
  Pin Mappings (from CanSat_System_Reference.md):
    • Servo (filter) signal → D6 (PF4)  [PWM]
    • Servo VCC → 5 V
    • Servo GND → GND

  Nano Every PWM Pins (for reference):
    • D6 (~PWM) → PF4               :contentReference[oaicite:2]{index=2}&#8203;:contentReference[oaicite:3]{index=3}
*/

#include <Arduino.h>
#include <Servo.h>

const uint8_t SERVO_PIN = 6;  // D6 PWM

Servo filterServo;

void setup() {
  Serial.begin(115200);
  while (!Serial) { /* wait for Serial */ }
  Serial.println("\n=== CanSat Servo Control Prototype ===");
  
  filterServo.attach(SERVO_PIN);
  Serial.print("Servo attached to D6. Current angle: ");
  Serial.println(filterServo.read());  // defaults to 0
  Serial.println("Type an angle (0–180) and press Enter:");
}

void loop() {
  // If user sends a number over Serial, parse and move servo
  if (Serial.available() > 0) {
    int requestedAngle = Serial.parseInt();      // read integer
    requestedAngle = constrain(requestedAngle, 0, 180);
    filterServo.write(requestedAngle);
    Serial.print("→ Moved servo to ");
    Serial.print(requestedAngle);
    Serial.println("°");
    
    // Clear any remaining input
    while (Serial.available() > 0) {
      Serial.read();
    }
    Serial.println("Type next angle (0–180):");
  }

  // -- Example automated sweep (modified) --
  static unsigned long lastMove = 0;
  static int angle = 0;
  static int step = 5;  // move in 5° increments
  
  if (millis() - lastMove > 200) {  // update every 200ms
    filterServo.write(angle);
    Serial.print("Auto‑sweep → ");
    Serial.print(angle);
    Serial.println("°");
    
    angle += step;
    if (angle >= 180 || angle <= 0) {
      step = -step;  // reverse direction at boundaries
    }
    lastMove = millis();
  }
}
