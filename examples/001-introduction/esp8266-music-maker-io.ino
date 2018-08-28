// Specifically for use with the Adafruit Feather, the pins are pre-set here!

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>

// These are the pins used
#define VS1053_RESET   -1     // VS1053 reset pin (not used!)

// Feather ESP8266
#if defined(ESP8266)
  #define VS1053_CS      16     // VS1053 chip select pin (output)
  #define VS1053_DCS     15     // VS1053 Data/command select pin (output)
  #define CARDCS          2     // Card chip select pin
  #define VS1053_DREQ     0     // VS1053 Data request, ideally an Interrupt pin
#endif

//////// music maker featherwing
Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

/////// Adafruit IO
#include "AdafruitIO_WiFi.h"

#define IO_USERNAME  ""
#define IO_KEY       ""

#define WIFI_SSID       "MICA-Open"
#define WIFI_PASS       ""

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *control = io.feed("demo.music-control");
AdafruitIO_Feed *messages = io.feed("demo.messages");

void setup() {
  Serial.begin(115200);
  delay(100);


//// Music setup

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }

  Serial.println(F("VS1053 found"));

  musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  Serial.println("SD OK!");

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(10,10);

  // If DREQ is on an interrupt pin we can do background audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int



//// IO setup

  // connect to io.adafruit.com
  io.connect();
  control->onMessage(handleMessage);
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  messages->save("music player is connected");
}

void loop() {
  io.run(); // <- sits and waits for new messages
}

void handleMessage(AdafruitIO_Data *data) {
  String command = data->toString();

  Serial.print(F("/demo.music-control got <- "));
  Serial.println(command);

  if (command.equals("stop")) {
    musicPlayer.stopPlaying();
  } else if (command.equals("play1")) {
    musicPlayer.stopPlaying();
    delay(50); // keep this between stop and start

    // .startPlayingFile() plays file "in the background", so device can stay
    // active and listening for new messages. .playFullFile() is "blocking" and
    // will prevent other tasks from running.
    musicPlayer.startPlayingFile("track001.mp3");
  } else if (command.equals("play2")) {
    musicPlayer.stopPlaying();
    delay(50); // keep this between stop and start

    musicPlayer.startPlayingFile("track002.mp3");
  }
}


