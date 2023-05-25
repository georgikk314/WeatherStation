/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include "DHTesp.h"

// Replace with your network credentials
const char* ssid     = "ZTE_12A4E1";
const char* password = "3T7GT62Q3U";

//const char* ssid     = "141";
//const char* password = "141123@#";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Assign output variables to GPIO pins
int output12 = 12;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
DHTesp dht;

void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  dht.setup(output12, DHTesp::DHT22);
  server.begin();
}

void loop(){
  delay(dht.getMinimumSamplingPeriod());

  
  delay(2000);
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected()) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            float h = dht.getHumidity();
            float t = dht.getTemperature();
          
            Serial.print(dht.getStatusString());
            Serial.print("\t");
            Serial.print(h, 1);
            Serial.print("\t\t");
            Serial.print(t, 1);
            Serial.print("\t\t");
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<body><p>Temperature: ");
            client.print(t);
            client.print("</p><p>Humidity: ");
            client.print(h);
            client.print("</p>");
            client.println("</body></html>");
 
            delay(1000);
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    delay(2000);
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
