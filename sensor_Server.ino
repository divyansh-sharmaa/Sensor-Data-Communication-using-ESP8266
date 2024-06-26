#include <ESP8266WiFi.h>
#include "DHT.h"

const char* ssid = "xyz";
const char* password = "abcd1234";

WiFiServer server(80);

#define DHTPIN 4        
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(10);

  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Start the server
  server.begin();
  Serial.println(WiFi.localIP());
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("Client connected");}
  while(client) {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      client.println("Failed to read from DHT sensor!");
    }
    else {
          String temperatureData = "Temp: " + String(temperature) + " C";
          String humidityData = "Hum: " + String(humidity) + " %";
          Serial.println(temperatureData);
          Serial.println(humidityData);
          client.println(temperatureData);
          client.println(humidityData);
        }
        
    delay(3000);
  }    
    
    
  
}
