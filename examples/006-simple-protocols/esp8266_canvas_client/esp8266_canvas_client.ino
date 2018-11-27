/*

Publish from an ESP8266 to a generic TCP server. 

This sketch uses the simplest protocol possible 
to send numbers over the wire.

*/

#include <ESP8266WiFi.h>
const char* ssid     = "";
const char* password = "";

// The server that all clients will connect to. host and port are dependent on 
// the computer / network you would like to connect to.
const char* host = ""; // this can be a hostname or an IP address
const int   port = 0;

// Use WiFiClient class to create TCP connections
WiFiClient client;

// This function will attempt to connect to the server at host:port until it is 
// available.
void connectToServer() {
  while(!client.connected()) {
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      delay(2000);
    } else {
      Serial.println("connected!");
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // while the wifi is connecting, this loop will print "......"
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println("My IP address: ");
  Serial.println(WiFi.localIP());

  // And then connecting to a specific server
  connectToServer();
}

int counter = 0;

void loop() {
  delay(1000);
  ++counter;

  int width = random(0, 450);

  // our protocol! 
  // number + newline character
  String payload = String(width) + "\n";

  Serial.print("sending payload ");
  Serial.print(counter);
  Serial.print(" -> ");
  Serial.println(payload);
  
  // This will send the request to the server, printing the bytes of the payload 
  // across the network.
  client.print(payload);

  if (!client.connected()) {
    Serial.println("server went away, reconnecting...");
    connectToServer();
  }
}

