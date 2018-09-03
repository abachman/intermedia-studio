
#include <Wire.h>
#include "Adafruit_Trellis.h"
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)

void setup() {
  Serial.begin(115200);

  delay(100);
  Serial.println("Trellis Demo");

  // start the trellis device at i2c address 0x70
  trellis.begin(0x70);

  for (uint8_t i=0; i<numKeys; i++) {
    // on
    trellis.setLED(i);
    trellis.writeDisplay();
    delay(10);

    // off
    trellis.clrLED(i);
    trellis.writeDisplay();
    delay(5);
  }
}

bool toggle = false;

void loop() {
  delay(30); // 30ms delay is required, dont remove me!

  // If a button was just pressed or released...
  if (trellis.readSwitches()) {
    // go through every button
    for (uint8_t i=0; i<numKeys; i++) {
      // if it was pressed...
      if (trellis.justPressed(i)) {
        Serial.print("v"); Serial.println(i);
        // toggle the pressed LED
        if (trellis.isLED(i)) {
          trellis.clrLED(i);
        } else {
          trellis.setLED(i);
        }
      }
    }
    // tell the trellis to set the LEDs we requested
    trellis.writeDisplay();
  }
}
