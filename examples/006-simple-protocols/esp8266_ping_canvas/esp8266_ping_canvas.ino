/// sensor connection
#include <NewPing.h>
NewPing sonar(2, 16, 200); // needs both echo and trigger pins

/// network connection
#include <ESP8266WiFi.h>
const char* ssid     = "MICA-Open";
const char* password = "18261826";
const char* host = "10.10.18.125";

// Use WiFiClient class to create TCP connections
WiFiClient client;
const int serverPort = 12345;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(100);
  Serial.print("connecting to ");
  Serial.println(host);

  connect();
}

void connect() {
  int timeout = 1000;
  // try to reconnect until server can be reached
  while(!client.connected()) {
    if (!client.connect(host, serverPort)) {
      Serial.println("connection failed, retry");
      delay(timeout);  // wait a bit and then repeat the while loop
      timeout += 1000; // increase delay each time connection fails
    } else {
      Serial.println("connected!");
    }
  }
}

void loop() {
  
  // put your main code here, to run repeatedly:
  delay(50);

  int distance = sonar.ping_cm();

  // debugging: check distance value
  Serial.print("Ping: ");
  Serial.print(distance);
  Serial.println("cm");  

  // generate protocol payload and send
  String payload = String(distance) + "\n";
  client.print(payload);
  
  // check connection status and reconnect if necessary
  if (!client.connected()) {
    Serial.println("reconnecting...");
    connect();
  }
}
