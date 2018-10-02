
import processing.net.*;

// global variables (data that should be available in every function
Server s;
ArrayList<Client> clients;
int port = 12345;
byte NEWLINE = 10;

void setup()
{
  size(600, 600);

  stroke(0);
  strokeWeight(3);
  noFill();
  colorMode(HSB, 100); // HSB mode uses (Hue, Saturation, Brightness) as arguments
                       // to color functions instead of the default (Red, Green, Blue)

  s = new Server(this, port);        // Start a simple server on port 12345
  clients = new ArrayList<Client>(); // initialize the list of clients that will be connecting

  println("server running at " + Server.ip() + ":" + port);
  rectMode(CENTER);
}

void draw() {
  // draw semi-transparent rectangle covering the whole viewport instead of 
  // re-drawing the background
  noStroke();
  fill(80, 0, 80, 6);
  rect(width/2, height/2, width, height);
  noFill();
  
  int count = clients.size();
  
  // Receive data from all connected clients. Loop through the list backwards
  // because we may end up removing clients from the list. Each time the code 
  // in the loop runs, the variable `i` will be 1 smaller.
  for (int i = count - 1; i >= 0; i--) {
    
    // get the client at index: i from the list of clients
    Client c = clients.get(i);

    // for each client in the collection, check if new data exists
    if (c.available() > 0) {

      // read first line of incoming data
      String input = c.readStringUntil(NEWLINE);
      input = input.substring(0, input.indexOf("\n")); // Only up to the newline

      // debugging message
      // println("reading message from client "+ i +" at "+ c.ip() +" <- "+ input);

      int data = int(input); // convert input, which is a string, to an integer

      // pick color based on: 
      // 1) location in collection and 
      // 2) number of clients connected
      stroke(map(i, 0, count, 0, 100), 100, 100);
      
      // Draw at the center of the view vertically and along the center
      // line horizontally depending on the client.
      ellipse(map(i, 0, count, 0, width), height/2, data, data);      

    } else if (!c.active()) {

      // client is having trouble, just disconnect it
      c.stop();
      clients.remove(i);
      println("removed client " + i);

    }
  }
}

// disconnectEvent message is generated when a client disconnects.
void disconnectEvent(Client someClient) {
  println("client at " + someClient.ip() + " has left the building");

  // remove disconnected client from collection immediately
  int i = clients.indexOf(someClient);
  clients.remove(i);
}

// serverEvent message is generated when a new client connects
// to an existing server.
void serverEvent(Server server, Client someClient) {
  println("We have a new client: " + someClient.ip());

  // add newly connected client to the collection
  clients.add(someClient);
}
