/*
  Pin Connections:
  ----------------
  Nano Every Board:
    +5V       → VCC (5 V power rail)
    GND       → GND (common ground)

  LED Circuit:
    D3 (PF5)  → 220 Ω resistor → LED Anode (+)
    GND       → LED Cathode (–)
*/

#include <Arduino.h>

const uint8_t LED_PIN = 3;  // D3 on Nano Every

void setup() {
  pinMode(LED_PIN, OUTPUT); // configure D3 as output
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // LED on
  delay(500);
  digitalWrite(LED_PIN, LOW);  // LED off
  delay(500);
}
