// install MQTT via the Processing library manager
import mqtt.*;
MQTTClient client;

// get these from your Adafruit IO account
String io_username = ""; // plug this in yourself
String io_key = "";      // plug this in yourself

// create two feeds, one for sending shape values to the sketch, one for
// sending messages back from the sketch
String shape_feed = "";    // plug this in yourself
String messages_feed = ""; // plug this in yourself

String shape;

void setup() {
  size(200, 200);
  ellipseMode(CENTER);
  rectMode(CENTER);
  fill(0, 200, 0);

  shape = "";

  client = new MQTTClient(this);
  client.connect("mqtts://" + io_username + ":" + io_key + "@io.adafruit.com");
  client.subscribe(shape_feed);
  client.publish(shape_feed + "/get");
}

void draw() {
  background(0);

  if (shape.length() > 0) {
    if (shape.equals("rectangle")) {
      fill(200, 0, 0);
      rect(100, 100, 50, 50);
    } else if (shape.equals("circle")) {
      fill(0, 200, 0);
      ellipse(100, 100, 50, 50);
    } else if (shape.equals("ellipse")) {
      fill(0, 0, 200);
      if (random(0.0, 1.0) > 0.5) {
        ellipse(100, 100, 50, 10);
      } else {
        ellipse(100, 100, 10, 50);
      }
    }
  }
}

void messageReceived(String topic, byte[] payload) {
  shape = new String(payload);
  println("new message: " + topic + " - " + shape + "(" + shape.length() + ") bytes");

  // send notification back to IO
  client.publish(messages_feed, "message received at " + Integer.toString(millis()) + " (" + shape.length() + ") bytes");
}
