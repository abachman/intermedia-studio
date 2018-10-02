/**
 * based on "Shared Drawing Canvas (Server)" by Alexander R. Galloway from the
 * built-in Processing examples.
 */


import processing.net.*;

/// required global network variables
Server s;
Client c;
int port = 12345;

// global variables for dealing with incoming values
String input;
int data;
byte NEWLINE = 10; // the ASCII byte value of "\n"

void setup()
{
  size(450, 450);
  background(204);
  stroke(0);
  fill(0);
  s = new Server(this, port); // Start a simple server on port 12345

  println("server running at " + Server.ip() + ":" + port);
  rectMode(CENTER);
}

long messageCount = 0;

void draw() {

  // Receive data from a client. The available() function gives us a new network Client object.
  c = s.available();
  if (c != null) {
    // redraw background
    background(204);

    // read first line of incoming data
    input = c.readStringUntil(NEWLINE); // read up to the next newline character

    messageCount++;

    // debugging message
    // println("reading message " + messageCount + " from client at " + c.ip() + " <- " + input);

    data = int(input); // assume input is a single value
    rect(width/2, height/2, data, data);
  }
}

// ClientEvent message is generated when a client disconnects.
void disconnectEvent(Client someClient) {
  print("client " + someClient.ip() + " has disconnected");
}
