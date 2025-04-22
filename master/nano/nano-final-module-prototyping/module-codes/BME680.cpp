#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

// ── Pin Connections ──────────────────────────────────────────────
// BME680 VIN   → Nano Every 5V
// BME680 GND   → Nano Every GND
// BME680 SCK   → Nano Every D13 (SPI SCK)
// BME680 SDI   → Nano Every D11 (SPI MOSI)
// BME680 SDO   → Nano Every D12 (SPI MISO)
// BME680 CS    → Nano Every D8  (SPI Chip Select)
// ────────────────────────────────────────────────────────────────

#define BME_CS_PIN 8    // Chip‑select on D8

// Instantiate for hardware SPI by passing CS pin into the constructor:
Adafruit_BME680 bme(BME_CS_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  // Ensure CS is HIGH (deselected) before SPI.begin()
  pinMode(BME_CS_PIN, OUTPUT);
  digitalWrite(BME_CS_PIN, HIGH);

  // Initialize SPI bus (MOSI=D11, MISO=D12, SCK=D13)
  SPI.begin();

  // Initialize the sensor over SPI
  if (!bme.begin()) {
    Serial.println("Could not find valid BME680 on SPI!");
    while (1) {}
  }

  // Configure sensor oversampling & filter
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling   (BME680_OS_2X);
  bme.setPressureOversampling   (BME680_OS_4X);
  bme.setIIRFilterSize          (BME680_FILTER_SIZE_3);
  bme.setGasHeater              (320, 150);  // 320 °C for 150 ms
}

void loop() {
  // Wrap SPI access in a transaction if you share the bus (e.g. with SD card)
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  bool success = bme.performReading();
  SPI.endTransaction();

  if (!success) {
    Serial.println("Failed to perform reading :(");
  } else {
    Serial.print("Temperature: "); Serial.print(bme.temperature);    Serial.println(" °C");
    Serial.print("Humidity:    "); Serial.print(bme.humidity);       Serial.println(" %");
    Serial.print("Pressure:    "); Serial.print(bme.pressure / 100); Serial.println(" hPa");
    Serial.print("Gas Resist.: "); Serial.print(bme.gas_resistance / 1000); Serial.println(" kΩ");
    Serial.println();
  }

  delay(2000);
}
