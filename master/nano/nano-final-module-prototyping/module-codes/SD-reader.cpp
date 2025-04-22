/*
  SD Card Prototype Sketch for Arduino Nano Every

  Power Pins:
    VCC   → 5V       // SD Card & BME680 power from 5V rail :contentReference[oaicite:0]{index=0}&#8203;:contentReference[oaicite:1]{index=1}
    GND   → GND      // Common ground :contentReference[oaicite:2]{index=2}&#8203;:contentReference[oaicite:3]{index=3}

  SPI Bus (shared):
    MOSI  → D11      // SPI MOSI :contentReference[oaicite:4]{index=4}&#8203;:contentReference[oaicite:5]{index=5}
    MISO  → D12      // SPI MISO :contentReference[oaicite:6]{index=6}&#8203;:contentReference[oaicite:7]{index=7}
    SCK   → D13      // SPI Clock :contentReference[oaicite:8]{index=8}&#8203;:contentReference[oaicite:9]{index=9}

  SD Card Module:
    CS    → D10      // chipSelect for SD :contentReference[oaicite:10]{index=10}&#8203;:contentReference[oaicite:11]{index=11}
*/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 10; // CS pin for SD Card Module

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for Serial USB to be ready (optional)

  // Initialize SD card
  Serial.println("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed. Check wiring and SD card!");
    while (true); // Stop here if fail
  }
  Serial.println("Initialization successful!");

  // Write data to file
  File dataFile = SD.open("example.txt", FILE_WRITE);
  
  if (dataFile) {
    Serial.println("Writing to example.txt...");
    dataFile.println("CanSat SD Card Prototype Test");
    dataFile.println("Logged Data: ");
    dataFile.println("Temperature: 25.6 C");
    dataFile.println("Pressure: 101.3 kPa");
    dataFile.close();
    Serial.println("Data written successfully.");
  } else {
    Serial.println("Error opening example.txt for writing.");
  }

  // Read data from file
  dataFile = SD.open("example.txt");
  if (dataFile) {
    Serial.println("Reading from example.txt:");
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
    Serial.println("\nFinished reading file.");
  } else {
    Serial.println("Error opening example.txt for reading.");
  }
}

void loop() {
  // Empty loop for prototype
}
