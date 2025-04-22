/*
  OLED Pin    Connected To
  VCC         3.3 V rail
  GND         GND rail
  SDA         A4 (Nano SDA)
  SCL         A5 (Nano SCL)
*/

// Includes section
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize Wire
  Wire.begin();
  // Initialize OLED Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear and set up the display configuration
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  // Display initial message
  display.println("Hello from Nano Every!");
  display.display();
}

void loop() {
  // Empty loop for future code
}
