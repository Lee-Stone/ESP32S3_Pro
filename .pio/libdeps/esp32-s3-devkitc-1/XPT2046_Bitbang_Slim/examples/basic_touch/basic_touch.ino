#include <XPT2046_Bitbang.h>

#define MOSI_PIN 32
#define MISO_PIN 39
#define CLK_PIN  25
#define CS_PIN   33

XPT2046_Bitbang touchscreen(MOSI_PIN, MISO_PIN, CLK_PIN, CS_PIN);

void setup() {
  Serial.begin(115200);

  // Initialize the touchscreen
  touchscreen.begin();
}

void loop() {
  TouchPoint touch = touchscreen.getTouch();

  // Display touches that have a pressure value (Z)
  if (touch.zRaw != 0) {
    Serial.print("Touch at X: ");
    Serial.print(touch.x);
    Serial.print(", Y: ");
    Serial.println(touch.y);
  }

  delay(100);  // Adjust delay as needed for responsiveness vs. serial output frequency
}
