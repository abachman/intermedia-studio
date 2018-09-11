// Adafruit IO Publish Example
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

/************************** Configuration ***********************************/

#include "secrets.h"

/************************ Example Starts Here *******************************/

// set up the 'words' feed
AdafruitIO_Feed *words = io.feed("words");

void setup() {
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
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

  sendWord();

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);
}

char *word_list[] = {
  "return", "medicate", "blindside", "boogie", "flap",
  "trip", "trap", "snoop", "explode", "sketch",
  "scatter", "challenge", "bury", "splatter", "peddle",
  "balance", "boggle", "poke", "critique",
  // by sending the raw unicode byte sequence, we can use emoji!
  "\U0001F643", // upside down face
  "\U0001F98A"  // fox face
};

// length of *words[]
int word_count = 21;

void sendWord() {
  // pick a random word
  char *a_word = word_list[random(word_count)];

  // show which word was picked
  Serial.print("sending -> ");
  Serial.println(a_word);

  words->save(a_word);
}
