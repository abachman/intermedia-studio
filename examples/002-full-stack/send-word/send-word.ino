#define WIFI_SSID    "normalnet"
#define WIFI_PASS    "the bachman family"

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
// Install using the Arduino library manager. Make sure you choose version 5 of the library!
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
String path = "/word";

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, 80);

String contentType = "application/json";
int status = WL_IDLE_STATUS;
int statusCode = 0;
String response;

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

  Serial.print("connected with IP Address ");
  Serial.println(WiFi.localIP());
}


// ------------------------------------------------


void loop() {
  sendWord();

  // sleep on it for a bit
  Serial.println("Wait 30 seconds\n");
  delay(30000);
}

char *words[] = {
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
  // building the JSON request body...
  String postData;
  StaticJsonBuffer<348> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  // setting all the key:value pairs
  root["board_id"] = board_id;

  // this can be anything and you can use any mechanism you'd like
  root["word"] = words[random(word_count)];

  // writing the big JSON blob to a String
  root.printTo(postData);

  // make sure the outgoing JSON looks good
  Serial.print("preparing HTTP POST request, body: ");
  Serial.println(postData);

  // send the POST request
  client.post(path, contentType, postData);

  // read the status code and body of the response
  statusCode = client.responseStatusCode();
  response = client.responseBody();

  // check the response from the service
  Serial.print("POST /word status code: ");
  Serial.println(statusCode);
  Serial.print("POST /word response: ");
  Serial.println(response);
}

