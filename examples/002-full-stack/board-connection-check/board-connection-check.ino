#define WIFI_SSID    "MICA-Open"
#define WIFI_PASS    ""

// ESP8266 WiFi + HTTP support
#include "ESP8266WiFi.h"
#include "WiFiClient.h"
// Install using the Arduino board manager:
//   https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide#install-the-esp8266-board-package-6-7


// A slightly nicer HTTP Client
#include "ArduinoHttpClient.h"
// Install using the Arduino library manager.
// * Search for "HttpClient" or "http client"
//
// Home / examples / documentation: https://github.com/arduino-libraries/ArduinoHttpClient


// JSON support
#include <ArduinoJson.h>
// Install using the Arduino library manager. Make sure you choose version 5.13.2 of the library!
// * Search for "json" or "arduino json"
//
// Installation guide: https://arduinojson.org/v5/doc/installation/



////////////////////////////////////////////////////////////////////////////////
//                     Variables supporting HTTP requests                     //
////////////////////////////////////////////////////////////////////////////////


// used in every request, change this to something unique that you / we will recognize
String board_id = "adam's tiny computer";

// base address for the server that's listening for incoming data
String server = "board-connection-check.glitch.me";  // <-- this should change to your app's address

// paths for requests from this board
String path = "/ping"; // <-- this should change if you change the path on server.js

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, 80);

String contentType = "application/json";
int status = WL_IDLE_STATUS;
int statusCode = 0;
String response;

// Variables supporting WiFi status
byte mac[6];
String ssid;
IPAddress ip;
long rssi;

void setup() {
  Serial.begin(115200);

  // put WiFi module into client mode (required with ESP8266)
  WiFi.mode(WIFI_STA);

  // start connection to local network
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(WIFI_SSID);
    delay(500);
  }

  // store network identifying information
  storeIdentifyingInformation();
  printWifiStatus();
}

void loop() {
  sendPingMessage();

  // Sleep for a bit. Glitch has a 4000 request per hour rate limit for apps.
  // One misbehaving microcontroller can very easily overwhelm the service.
  Serial.println("Wait 30 seconds\n");
  delay(30000);
}


// the function that sends data to our web application
void sendPingMessage() {
  // build the JSON request body...
  String postData;
  StaticJsonBuffer<512> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  // set all the key:value pairs
  root["mac"] = macAddressString();
  root["rssi"] = WiFi.RSSI(); // this may change every time we send data
  root["board_id"] = board_id;
  root["ssid"] = ssid;
  root["ip_address"] = ip.toString();

  // write the big JSON blob to a String
  root.printTo(postData);

  // make sure the outgoing JSON looks good
  Serial.print("preparing HTTP POST request, body: ");
  Serial.println(postData);

  // send the POST request
  client.post(path, contentType, postData);

  // ... response is coming

  // read the status code and body of the response
  statusCode = client.responseStatusCode();
  response = client.responseBody();

  // check the response from the service
  Serial.print("POST /ping status code: ");
  Serial.println(statusCode);
  Serial.print("POST /ping response: ");
  Serial.println(response);
}


/*
 * Hardware information gathering
 */

// Get your board's current WiFi network name (SSID), MAC address, and IP
// address. You only need to call this function once, in setup()
void storeIdentifyingInformation() {
  ssid = WiFi.SSID();
  WiFi.macAddress(mac);
  ip = WiFi.localIP();
}


// The MAC address of your board is a unique, hardware-level identifier that
// doesn't change. If for some reason you need to distinguish your board from
// among a group, you can use the MAC address
String macAddressString() {
  String addr;
  addr += String(mac[5], HEX); addr += ":";
  addr += String(mac[4], HEX); addr += ":";
  addr += String(mac[3], HEX); addr += ":";
  addr += String(mac[2], HEX); addr += ":";
  addr += String(mac[1], HEX); addr += ":";
  addr += String(mac[0], HEX);
  return addr;
}

// Print identifying info for the network you're attached to. This is not
// necessary for the script to function, but can be helpful to make sure that
// everything is setup correctly.
void printWifiStatus() {
  Serial.print("Network Identifier (SSID): ");
  Serial.println(ssid);

  Serial.print("Device IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  rssi = WiFi.RSSI();
  Serial.print("Received Signal Strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


