// Adafruit IO Digital Input Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.


/* 
 *  Requirements: 
 *  
 *  - voting / ballot box
 *  - buttons
 *  - 2 candidates 
 *  - save data
 *  - elections should be fair
 * 
 */

/* 
 *  Changes: 
 *   
 *  - [x] needs two buttons
 *  - [x] needs history (to record votes and report)
 *  - [] only record on press AND release
 *  - [] send current vote count
 */

#include "config.h"

// digital pins
#define BUTTON_PIN_1 5
#define BUTTON_PIN_2 4

// button states for button1 and button2
bool current[] = { false, false };
bool last[] = { false, false };

// votes for button1 and button2
int votes[] = { 0, 0, 0 }; 

// set up the 'digital' feed
AdafruitIO_Feed *digital = io.feed("digital");

void setup() {

  // set button pin as an input
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // grab the current state of the button.
  // we have to flip the logic because we are
  // using a pullup resistor.
  if(digitalRead(BUTTON_PIN_1) == LOW)
    current[0] = true;
  else
    current[0] = false;

  if(digitalRead(BUTTON_PIN_2) == LOW)
    current[1] = true;
  else
    current[1] = false;  

  // return if the value hasn't changed
  if(current[0] == last[0] && current[1] == last[1])
    return;

  for (int n = 0; n < 2; n++) {
    int candidate = n;
    // record a vote here IF button has gone from pressed to released
    if (current[candidate] != last[candidate] && current[candidate] == false                                  && ((candidate == 0 && votes[0] >= votes[1] && (candidate = 1)))  )  
    {
      // record vote
      votes[candidate] = votes[candidate] + 1;

      // record total votes 
      votes[2] = votes[2] + 1;
    }
  }
  
  // assume a vote might have been cast
  
  // save the current state to the 'digital' feed on adafruit io
  String message = String(votes[0]) + 
                   " : " + String(votes[1]);
  
  Serial.print("sending votes -> ");
  Serial.println(message);
  // I expect: "1, 2"
  digital->save(message);

  // store last button state
  last[0] = current[0];
  last[1] = current[1];

}
