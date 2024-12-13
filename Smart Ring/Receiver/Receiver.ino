#include <WiFiUdp.h>
#include <WiFi.h>  
#include <WiFiClient.h>
#include <WebServer.h>

#define Relay1   23
#define Relay2   22

WebServer server(80);

/* Put your SSID & Password */
const char* ssid = "Safty Ring";  // Enter SSID here
const char* password = "12345678";  // Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 43, 3); // Different IP address from the sender
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);
const int udpPort = 1234; // Different port from the sender

WiFiUDP udp;

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Start UDP server
  udp.begin(udpPort);

  // Set relay pins as output
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
}

void loop() {
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    char packetBuffer[255];
    udp.read(packetBuffer, 255);
    packetBuffer[packetSize] = '\0'; // Ensure null-termination
    
    // Process the received packet
    if (strcmp(packetBuffer, "Hello, Asking for Help!") == 0) {
      // Activate relays
      digitalWrite(Relay1, LOW);
      digitalWrite(Relay2, LOW);
      Serial.println("Relays ON");
    } else {
      // Deactivate relays if not help request
      digitalWrite(Relay1, HIGH);
      digitalWrite(Relay2, HIGH);
      Serial.println("Relays OFF");
      pinMode(Relay1, INPUT);
      pinMode(Relay2, INPUT);
    }
  } else {
    // Deactivate relays if no packet received
    digitalWrite(Relay1, HIGH);
    digitalWrite(Relay2, HIGH);
    pinMode(Relay1, INPUT);
      pinMode(Relay2, INPUT);
    Serial.println("Relays OFF");
  }
  
  delay(10);
}

