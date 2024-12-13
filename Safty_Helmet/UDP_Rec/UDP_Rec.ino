#include <WiFi.h>
#include <WiFiUdp.h>

#define Buz  23

const char *ssid = "Safty Helmet";
const char *password = "12345678";
const int udpPort = 1234;

IPAddress local_ip(192, 168, 4, 2);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  udp.begin(udpPort);

  pinMode(Buz, OUTPUT);
  Serial.println("UDP server started");
}

void loop() {
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    char packetBuffer[255];
    int bytesRead = udp.read(packetBuffer, 255);
    packetBuffer[bytesRead] = '\0';
    digitalWrite(Buz, HIGH);
    Serial.print("Received packet: ");
    Serial.println(packetBuffer);
    delay(1000);
  }
  else {
    digitalWrite(Buz, LOW);
  }
  
  delay(10);
}
