#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

#define WIFI_SSID "ZTE_12A4E1"
#define WIFI_PASSWORD "3T7GT62Q3U"

#define API_ENDPOINT "http://c53f720eec8d09.lhr.life/api/WeatherRecords"  // Replace with your API endpoint URL
#define DHT_PIN 12
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  dht.begin();
}

void loop() {
  
  // Read temperature and humidity from the DHT22 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any readings failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read sensor data!");
    return;
  }

  // Create JSON payload
  String payload = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";

  // Send HTTP POST request to the API endpoint
  WiFiClient client;
  HTTPClient http;

  if (http.begin(client, API_ENDPOINT)) {
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(payload);

      if (httpResponseCode > 0) {
      Serial.printf("HTTP POST request sent. Response code: %d\n", httpResponseCode);
    } else {
      Serial.printf("HTTP POST request failed. Error code: %s\n", http.errorToString(httpResponseCode).c_str());
    }
  }
  
  delay(60000);

}
