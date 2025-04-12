#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <SD.h>  // Include SD card library


// Create instances for the sensors
MPU6050 mpu;
Adafruit_BME680 bme;


// SD card chip select pin (use your actual pin)
const int chipSelect = 10;  // Usually pin 10 for most Arduino boards


File dataFile;


void setup() {
  // Start serial communication
  Serial.begin(115200);
  Wire.begin();


  // Initialize the MPU6050 sensor
  mpu.initialize();


  // Initialize the BME680 sensor
  if (!bme.begin()) {
    Serial.println("BME680 initialization failed with default address!");
    if (!bme.begin(0x76)) {  // Try address 0x76
      Serial.println("Could not find a valid BME680 sensor with address 0x76, check wiring!");
      while (1);  // If the sensor is not found, halt here
    } else {
      Serial.println("BME680 found at address 0x76!");
    }
  } else {
    Serial.println("BME680 found at default address!");
  }


  // Check if the MPU6050 is connected properly
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful!");
  } else {
    Serial.println("MPU6050 connection failed!");
  }


  // Initialize the SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");


  // Open the file to write data
  dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    Serial.println("Writing to data.txt...");
    dataFile.println("Timestamp,AccelX,AccelY,AccelZ,GyroX,GyroY,GyroZ,Temp_BME,Humidity_BME,Pressure_BME,Gas_Resistance");
    dataFile.close();
  } else {
    Serial.println("Error opening data.txt");
  }
}


void loop() {
  // Variables to store sensor data for MPU6050
  int16_t ax, ay, az;
  int16_t gx, gy, gz;


  // Read accelerometer and gyroscope data from MPU6050
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);


  // Variables to store BME680 sensor data
  float temperature, pressure, humidity, gasResistance;


  // Read BME680 sensor data
  if (bme.performReading()) {
    temperature = bme.temperature;
    humidity = bme.humidity;
    pressure = bme.pressure / 100.0;  // Convert to hPa
    gasResistance = bme.gas_resistance / 1000.0;  // Convert to KOhms


    // Print BME680 data to Serial
    Serial.print("Temp_BME: "); Serial.print(temperature);
    Serial.print("\tHumidity_BME: "); Serial.print(humidity);
    Serial.print("\tPressure_BME: "); Serial.print(pressure);
    Serial.print("\tGas Resistance: "); Serial.print(gasResistance);
  } else {
    Serial.println("Failed to read data from BME680 sensor.");
  }


  // Print accelerometer and gyroscope data to Serial (for plotting)
  Serial.print("\tAccelX: "); Serial.print(ax);
  Serial.print("\tAccelY: "); Serial.print(ay);
  Serial.print("\tAccelZ: "); Serial.print(az);
  Serial.print("\tGyroX: "); Serial.print(gx);
  Serial.print("\tGyroY: "); Serial.print(gy);
  Serial.print("\tGyroZ: "); Serial.println(gz);


  // Write data to SD card
  dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    unsigned long timestamp = millis();  // Get the timestamp in milliseconds
    dataFile.print(timestamp);
    dataFile.print(",");
    dataFile.print(ax); dataFile.print(",");
    dataFile.print(ay); dataFile.print(",");
    dataFile.print(az); dataFile.print(",");
    dataFile.print(gx); dataFile.print(",");
    dataFile.print(gy); dataFile.print(",");
    dataFile.print(gz); dataFile.print(",");
    dataFile.print(temperature); dataFile.print(",");
    dataFile.print(humidity); dataFile.print(",");
    dataFile.print(pressure); dataFile.print(",");
    dataFile.println(gasResistance);
    dataFile.close();
  } else {
    Serial.println("Error writing to SD card");
  }


  delay(100);  // Adjust delay for smoother plotting if needed
}
