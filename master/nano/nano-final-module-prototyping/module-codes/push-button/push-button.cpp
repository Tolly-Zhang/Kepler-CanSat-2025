/*
 * CanSat Button Press Threshold Prototype
 *
 * Pin Mapping:
 *   One‑Button → D2  (button to GND; use INPUT_PULLUP) :contentReference[oaicite:0]{index=0}&#8203;:contentReference[oaicite:1]{index=1}
 */

 #include <Arduino.h>

 const uint8_t buttonPin = 2;        // One‑Button input
 
 // debounce & press timing
 bool     buttonPressed       = false;
 bool     longPressTriggered  = false;
 bool     lastButtonState     = HIGH;
 uint32_t pressStartTime      = 0;
 uint32_t lastDebounceTime    = 0;
 
 const uint32_t debounceDelay    = 50;    // ms
 const uint32_t longPressThresh  = 3000;  // ms until long‑press :contentReference[oaicite:2]{index=2}&#8203;:contentReference[oaicite:3]{index=3}
 
 void setup() {
   Serial.begin(115200);
   pinMode(buttonPin, INPUT_PULLUP);
   Serial.println("CanSat Button Threshold Prototype Ready");
 }
 
 void loop() {
   bool reading = digitalRead(buttonPin);
 
   // — Debounce input —
   if (reading != lastButtonState) {
     lastDebounceTime = millis();
   }
 
   if (millis() - lastDebounceTime > debounceDelay) {
     // — Press start? —
     if (reading == LOW && !buttonPressed) {
       buttonPressed      = true;
       longPressTriggered = false;
       pressStartTime     = millis();
     }
     // — Release? —
     else if (reading == HIGH && buttonPressed) {
       // if long‑press already fired, do nothing; otherwise it’s a short‑press
       if (!longPressTriggered) {
         Serial.print("Short press detected (");
         Serial.print(millis() - pressStartTime);
         Serial.println(" ms)");
       }
       buttonPressed = false;
     }
   }
 
   // — While still held, check for long‑press threshold —
   if (buttonPressed && !longPressTriggered) {
     if (millis() - pressStartTime >= longPressThresh) {
       longPressTriggered = true;
       Serial.print("Long press detected (");
       Serial.print(millis() - pressStartTime);
       Serial.println(" ms)");
       // → put your calibration/health‑check call here
     }
   }
 
   lastButtonState = reading;
 }
 