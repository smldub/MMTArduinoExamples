#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

//This will be the name and password of the wifi network your car is on
//Choose a different name so that you can uniquely identify your car
const char *ssid = "yourAP";
const char *password = "yourPassword";

WiFiServer server(80);
//Naming the Variables and assigning the PIN number 
//These PIN numbers will be the ones on the board that are turned on and off
const int output0 = 0;
const int output4 = 4;
const int output16 = 16;
const int output17 = 17;

void setup() {
  //Telling the Microcontroller that we want control over the pins
  //we defined earlier
  pinMode(output0, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output16, OUTPUT);
  pinMode(output17, OUTPUT);
  //The next section is just setting up wifi stuff so its 
  //okay to ignore it. Start reading again where it says
  //HERE HERE!!!
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/F\">here</a> to turn ON the Forward.<br>");
            client.print("Click <a href=\"/B\">here</a> to turn ON the Backward.<br>");
            client.print("Click <a href=\"/R\">here</a> to turn ON the RIGHT.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn ON the LEFT.<br>");
            client.print("Click <a href=\"/off\">here</a> to turn OFF.<br>");           
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        
        //HERE HERE !!! HERE HERE!!!
        //Here is where we define how to go Forward
        //Think about what relays you need to turn off/on to make
        //the car go forward
        if (currentLine.endsWith("GET /F")) {
          //This command turns on PIN0
          //copy and paste this command while changing which pin
          //you want to turn on (HIGH) or off (LOW) in order to 
          //make the car go forward
          digitalWrite(output0, HIGH); 
        }
        //This Section tells the car to go backward 
        //hint: just reverse order of forward
        else if (currentLine.endsWith("GET /B")) {
          digitalWrite(output4, HIGH);
        }
        //This section tells the car to turn right
        else if (currentLine.endsWith("GET /R")) {
          digitalWrite(output16, HIGH);    
          }
        //This section tells the car to turn left
        else if (currentLine.endsWith("GET /L")) {
          digitalWrite(output17, HIGH); 
        }
        //This section stops the car
        //Think about what condition needs to be met with the relays
        //so that none of the engines are on
        else if (currentLine.endsWith("GET /off")) {
          digitalWrite(output0, LOW);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}