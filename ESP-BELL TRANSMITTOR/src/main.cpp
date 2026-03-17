#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
// Wokwi typically assigns 10.10.0.2 to the first device on the network
const char* serverUrl = "http://10.10.0.2/ring"; 

void setup() {
  Serial.begin(115200);
  
  // Connect to Wokwi Simulation WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected! Sending signal...");
    HTTPClient http;
    http.begin(serverUrl);
    int httpResponseCode = http.GET();
    Serial.printf("Response code: %d\n", httpResponseCode);
    http.end();
  } else {
    Serial.println("\nWiFi Failed");
  }

  // Set up wakeup: Trigger when GPIO 33 goes HIGH (3.3V)
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1); 

  Serial.println("Entering Deep Sleep...");
  esp_deep_sleep_start();
}

void loop() {}