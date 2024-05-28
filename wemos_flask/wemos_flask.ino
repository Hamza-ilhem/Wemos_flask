#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// WiFi credentials
const char* ssid = "tealchemist";
const char* password = "madhatter7522";
const char* serverUrl = "http://192.168.43.160:5000";

// Define the pin that controls the pump
const int pumpPin = D3;  // Change to the appropriate GPIO pin

void setup() {
  Serial.begin(115200);
  delay(10);

  // Set the pump pin as an output
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW); // Ensure the pump is off initially

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Wait until the ESP8266 has connected to the WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Test the pump control
  Serial.println("Turning pump ON for 5 seconds...");
  digitalWrite(pumpPin, HIGH);
  delay(5000);
  digitalWrite(pumpPin, LOW);
  Serial.println("Pump OFF");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverUrl); 
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);

      // Control the pump based on the server response
      if (payload == "ON") {
        digitalWrite(pumpPin, HIGH); // Turn the pump on
        Serial.println("Pump ON");
      } else if (payload == "OFF") {
        digitalWrite(pumpPin, LOW); // Turn the pump off
        Serial.println("Pump OFF");
      }
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end();
  }
  delay(5000); // Wait for 5 seconds before making another request
}
