/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "DHTesp.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

const long utcOffsetInSeconds = 10800;     //UTC offset in seconds
char weekDays[7][12]  = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
DHTesp dht;
 
const char* ssid = "M-Tel_7A6F";
const char* password = "4857544300398D9B";

String currentDate = ""; // ne sum go testval nadqvam se da raboti :)

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;

unsigned long timerDelay = 5000;

void setup() {
  timeClient.begin();
  timeClient.setTimeOffset(10800);


  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

  dht.setup(2, DHTesp::DHT22);
  
}

void loop() {

    timeClient.update();

    time_t epochTime = timeClient.getEpochTime();
    String formattedTime = timeClient.getFormattedTime();

    //Get a time structure
    struct tm *ptm = gmtime ((time_t *)&epochTime); 
    int monthDay = ptm->tm_mday;
    int currentMonth = ptm->tm_mon+1;
    int currentYear = ptm->tm_year+1900;
    if(currentMonth < 0){
      String currentDate = String(currentYear) + "-" + "0" + currentMonth + "-" + String(monthDay);

    }
    else{
      String currentDate = String(currentYear) + "-" + currentMonth + "-" + String(monthDay);
    }

     String currentTimeAndDate = "\"" + currentDate + "T" + formattedTime + "\"";
    Serial.println(currentTimeAndDate);
  
  delay(dht.getMinimumSamplingPeriod());

  delay(2000);

  // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = "http://843d2737add278.lhr.life/api/WeatherRecords";
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
     

      float t = dht.getTemperature();
      float h = dht.getHumidity();
     
      String payload = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + ",\"time\":" + String(currentTimeAndDate) + "}"; 
      Serial.println(payload);      


       //If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json"); 
      int httpResponseCode = http.POST(payload);
      
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
             
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

