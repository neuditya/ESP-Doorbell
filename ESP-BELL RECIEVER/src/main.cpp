#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int buzzerPin = 18;

void handleBell() {
  server.send(200, "text/plain", "OK");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BELL IS RUNG!");
  
  // Play a "Ding-Dong" tone sequence
  tone(buzzerPin, 660, 200); // E5
  delay(250);
  tone(buzzerPin, 523, 400); // C5
  delay(500);
  noTone(buzzerPin);
  
  delay(3000); 
  lcd.clear();
  lcd.print("Ready...");
}

void setup() {
  Serial.begin(115200);
  
  lcd.init();
  lcd.backlight();
  lcd.print("Booting...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  // Print IP for the Bell to use
  Serial.print("Receiver IP: ");
  Serial.println(WiFi.localIP()); 
  
  lcd.clear();
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());

  server.on("/ring", handleBell);
  server.begin();
}

void loop() {
  server.handleClient();
}