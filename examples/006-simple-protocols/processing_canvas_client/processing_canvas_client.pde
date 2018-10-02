/**
 * based on "Shared Drawing Canvas (Client)"
 * by Alexander R. Galloway.
 */

import processing.net.*;

Client c;
String input;
int data[];

// You can replace these values with your server's IP and port
String host = "127.0.0.1";
int port = 12345;

void setup()
{
  size(600, 200);
  background(204);
  stroke(0);

  // Slow it down a little. For this sketch, lowering the frame rate lowers the
  // speed at which data can be sent
  frameRate(10);


  // Connect to the server's IP address and port
  c = new Client(this, host, port);
}

void draw()
{
  if (mousePressed == true) {
    background(204);

    int value = mouseX;

    // draw feedback
    fill(0);
    rect(0, 0, value, 30);

    // Send mouse-driven value to server
    c.write(value + "\n");
  }
}
