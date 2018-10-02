/*
 *  A Processing sketch that connects to Adafruit IO and listens for new
 *  messages on a feed.
 */

import mqtt.*;
MQTTClient client;
// Install MQTT via the Processing library manager
// Go to the "Sketch" menu, 
//   then "Import Libray >", 
//   then "Add Library..." and search for 'mqtt'

// get these from your Adafruit IO account  
String io_username = ""; // plug this in yourself
String io_key = "";      // plug this in yourself

// create two feeds, one for sending shape values to the sketch, one for
// sending messages back from the sketch
String shape_feed_key = "";    // plug this in yourself
String messages_feed_key = ""; // plug this in yourself

// Adafruit IO's API requires MQTT connections to use "topics" in the form:
// 
//   {username}/feeds/{feed key}
// 
// For us, that looks like this:
String shape_feed = io_username + "/feeds/" + shape_feed_key; 
String messages_feed = io_username + "/feeds/" + messages_feed_key;

String shape;

void setup() {
  size(640, 640);
  ellipseMode(CENTER);
  rectMode(CENTER);
  fill(0, 200, 0);

  shape = "";
  
  // connect to Adafruit IO, get the most recent value from the shape feed
  client = new MQTTClient(this);
  client.connect("mqtts://" + io_username + ":" + io_key + "@io.adafruit.com");
  client.subscribe(shape_feed);
  client.publish(shape_feed + "/get");
}

void draw() {
  background(0);

  if (shape.length() > 0) {
    if (shape.equals("rectangle") || shape.equals("square") || shape.equals("box")) {
      fill(200, 0, 0);
      rect(100, 100, 50, 50);
    } else if (shape.equals("circle")) {
      fill(0, 200, 0);
      ellipse(100, 100, 50, 50);
    } else if (shape.equals("ellipse")) {
      fill(0, 0, 200);
      if (random(0.0, 1.0) > 0.5) {
        ellipse(100, 100, 50, 40);
      } else {
        ellipse(100, 100, 40, 50);
      }
    } else if (shape.equals("grow")) {
      // ???
    }
  }
}

void messageReceived(String topic, byte[] payload) {
  shape = new String(payload);
  println("new message: " + topic + " - " + shape + "(" + shape.length() + ") bytes");

  // send notification back to IO
  delay(30);
  client.publish(messages_feed, "message received on Processing at " + Integer.toString(millis()) + " (" + shape.length() + ") bytes");
  println("sent message");
}