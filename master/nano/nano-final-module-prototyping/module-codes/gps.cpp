/*
  GPS SW‑Serial Debug w/ Status
  -----------------------------
  Wiring (NEO‑6M → Nano Every):
    • VCC → 5V
    • GND → GND
    • GPS TX → D4 (SW‑Serial RX)
    • GPS RX → D5 (SW‑Serial TX)
    • (Common ground)
*/

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// SW‑Serial pins:
static const uint8_t GPS_RX_PIN = 4;  // Arduino reads from GPS TX
static const uint8_t GPS_TX_PIN = 5;  // Arduino writes to GPS RX

SoftwareSerial gpsSer(GPS_RX_PIN, GPS_TX_PIN);
TinyGPSPlus gps;

uint32_t lastStats = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println(F("\n=== GPS SW‑Serial Debug w/ Status ==="));
  gpsSer.begin(9600);               // NEO‑6M default baud
  Serial.println(F("Echoing raw NMEA + printing status every second..."));
}

void loop() {
  // 1) Echo raw NMEA bytes
  while (gpsSer.available()) {
    char c = gpsSer.read();
    Serial.write(c);
    gps.encode(c);
  }

  // 2) Once per second, print sats/HDOP/fix and Lat/Lng if valid
  if (millis() - lastStats >= 1000) {
    lastStats = millis();
    Serial.print(F("Satellites: "));
    Serial.print(gps.satellites.value());
    Serial.print(F("  HDOP: "));
    Serial.print(gps.hdop.hdop());
    Serial.print(F("  Fix: "));
    Serial.println(gps.location.isValid() ? F("Yes") : F("No"));

    if (gps.location.isValid()) {
      Serial.print(F("Lat: "));
      Serial.print(gps.location.lat(), 6);
      Serial.print(F("  Lng: "));
      Serial.println(gps.location.lng(), 6);
    }
  }
}
