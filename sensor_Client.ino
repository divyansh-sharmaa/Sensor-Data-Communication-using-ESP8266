#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "xyz";
const char* password = "abcd1234";
const char* serverIP = "192.168.137.222";

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();        
  lcd.backlight();   
  delay(10);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    
    if (client.connect(serverIP, 80)) {
        
      while (client.connected()) {
        if (client.available()) {
          String temperature = client.readStringUntil('\n');
          String humidity = client.readStringUntil('\n');
          Serial.print("Server temperature: ");
          Serial.println(temperature);
          Serial.print("Server humidity: ");
          Serial.println(humidity);
          
          temperature.trim();
          humidity.trim();
          
          if (!temperature.isEmpty() && !humidity.isEmpty()) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(temperature);
            lcd.setCursor(0, 1);
            lcd.print(humidity);
          }
        }
      }
    }
  }
}
