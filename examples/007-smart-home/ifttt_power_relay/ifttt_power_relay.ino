// Adafruit IO Digital Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-output
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

#define IO_USERNAME  ""
#define IO_KEY       ""

#define WIFI_SSID       ""
#define WIFI_PASS       ""

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/************************ Example Starts Here *******************************/

// digital pin 15
#define RELAY_PIN 13
#define LED_PIN   0

// set up the 'control' feed
AdafruitIO_Feed *control = io.feed("control");

// feedback into IO for debugging / tracking
AdafruitIO_Feed *messages = io.feed("messages");

void setup() {

  // set led pin as a digital output
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // start the serial connection
  Serial.begin(115200);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'control' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  control->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  messages->save("audiopanic test connected");
}

void loop() {

  io.run();

}

// this function is called whenever an 'control' feed message
// is received from Adafruit IO. it was attached to
// the 'control' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");

  if(data->toPinLevel() == LOW) {
    messages->save("audiopanic ALL CLEAR");
    Serial.println("All clear");
    digitalWrite(RELAY_PIN, LOW); // relay NC
  } else {
    messages->save("audiopanic PANICKING!");
    Serial.println("PANIC!");
    digitalWrite(RELAY_PIN, HIGH); // relay NO
  }
}
