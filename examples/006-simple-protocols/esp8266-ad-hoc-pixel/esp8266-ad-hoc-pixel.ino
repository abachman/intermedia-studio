/*

Publish from an ESP8266 to a generic TCP server. 

This sketch uses the simplest protocol possible 
to send numbers over the wire.

*/

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

#define NEO_DATA_PIN 4
#define NUM_PIXELS 12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEO_DATA_PIN, NEO_GRB + NEO_KHZ800);


const char* ssid     = "virus-pilot";
const char* password = "";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);

  // while the wifi is connecting, this loop will print "......"
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println("My IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

int counter = 0;

void loop() {
  Serve();
}

WiFiClient client;

void Serve() {
  client = server.available();
  if (client) {
    if (client.connected()) {
      Serial.println("client connected"); 
    }

    if (client.available() > 0) {
      String message = "";
      char inChar = client.read();
      while (inChar) {
        message += inChar;
        inChar = client.read();
      }
      
      Serial.print("got message -> ");
      Serial.println(message);
    }
  }
}

