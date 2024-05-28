#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "tealchemist";
const char* password = "madhatter7522";

void setup() {
  // Start the Serial communication to send messages to the computer
  Serial.begin(115200);
  delay(10);

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
}

void loop() {
  // Print "Hello, World!" to the serial monitor
  Serial.println("Hello, World!");
  delay(2000); // Wait for 2 seconds before repeating
}
