/*
 * CanSat Button Progress‑Bar Prototype
 *
 * Pin Mapping:
 *   One‑Button → D2  (button to GND; use INPUT_PULLUP) :contentReference[oaicite:0]{index=0}&#8203;:contentReference[oaicite:1]{index=1}
 */

 #include <Arduino.h>

 const uint8_t buttonPin     = 2;       // One‑Button input
 const uint32_t debounceDelay = 50;     // ms
 const uint32_t longPressThresh = 3000; // ms until long‑press :contentReference[oaicite:2]{index=2}&#8203;:contentReference[oaicite:3]{index=3}
 const uint8_t  barWidth      = 20;     // characters in progress bar
 
 // state tracking
 bool     buttonPressed      = false;
 bool     longPressTriggered = false;
 bool     lastButtonState    = HIGH;
 uint32_t pressStartTime     = 0;
 uint32_t lastDebounceTime   = 0;
 uint8_t  lastTicks          = 0;
 
 void setup() {
   Serial.begin(115200);
   pinMode(buttonPin, INPUT_PULLUP);
   Serial.println("CanSat Button Progress‑Bar Ready");
 }
 
 void loop() {
   bool reading = digitalRead(buttonPin);
 
   // — Debounce —
   if (reading != lastButtonState) {
     lastDebounceTime = millis();
   }
 
   if (millis() - lastDebounceTime > debounceDelay) {
     // — Press start —
     if (reading == LOW && !buttonPressed) {
       buttonPressed      = true;
       longPressTriggered = false;
       pressStartTime     = millis();
       lastTicks          = 0;
       // print initial empty bar
       Serial.print("Pressing: [");
       for (uint8_t i = 0; i < barWidth; i++) Serial.print(' ');
       Serial.print("]   0%");  // no newline; we'll overwrite with '\r'
     }
     // — Release —
     else if (reading == HIGH && buttonPressed) {
       // if long‑press already fired, do nothing extra
       if (!longPressTriggered) {
         Serial.println();  // finish the bar line
         Serial.print("Short press detected (");
         Serial.print(millis() - pressStartTime);
         Serial.println(" ms)");
       }
       buttonPressed = false;
     }
   }
 
   // — While held, update progress bar & check for long‑press —
   if (buttonPressed && !longPressTriggered) {
     uint32_t elapsed = millis() - pressStartTime;
     // compute ticks (0..barWidth)
     uint8_t ticks = map(min(elapsed, longPressThresh), 0, longPressThresh, 0, barWidth);
     if (ticks != lastTicks) {
       lastTicks = ticks;
       // build bar
       Serial.print('\r');              // return to line start
       Serial.print("Pressing: [");
       for (uint8_t i = 0; i < ticks; i++)   Serial.print('#');
       for (uint8_t i = ticks; i < barWidth; i++) Serial.print(' ');
       Serial.print("] ");
       // percent
       uint8_t pct = (elapsed * 100) / longPressThresh;
       if (pct > 100) pct = 100;
       if (pct < 10) Serial.print(' '); // align 3‑digit field
       if (pct < 100) Serial.print(' ');
       Serial.print(pct);
       Serial.print('%');
     }
     // long‑press threshold reached?
     if (elapsed >= longPressThresh) {
       longPressTriggered = true;
       Serial.println();  // finish the bar line
       Serial.print("Long press detected (");
       Serial.print(elapsed);
       Serial.println(" ms)");
       // TODO: fire calibration/health‑check here
     }
   }
 
   lastButtonState = reading;
 }
 