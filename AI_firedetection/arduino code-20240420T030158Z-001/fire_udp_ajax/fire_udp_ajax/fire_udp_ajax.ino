//#include <BluetoothSerial.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "INDEX.h"
#include <WiFiClient.h>
#include <WebServer.h>
const char *ssid = "DVMS";
const char *password = "POEMSIFSDVMS1";
const int udp_port = 4446;

const IPAddress local_IP(192, 168, 1, 1);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

WiFiUDP udp;
WebServer server(80); 
void handleRoot() 
{
    String s = MAIN_page; //Read HTML contents
    server.send(200, "text/html", s); //Send web page
}
void fireADC1()
{int packetSize1 = udp.parsePacket();
  uint8_t packetBuffer[packetSize1];
   int a1 = (packetBuffer[0]);
    if (a1 == 1) 
    {
        String voltage1 = String("Fire detected");
        server.send(200, "text/html", voltage1);
        delay(2000);
    }
    else
    {
        String voltage1 = String("No issue");
        server.send(200, "text/html", voltage1); 
    }
}


void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.println("Hotspot IP address:");
  Serial.println(WiFi.softAPIP());
  Serial.print(WiFi.localIP());
   udp.begin(udp_port);

   
   server.on("/", handleRoot);
   server.on("/readADC", fireADC1);
   server.begin();
}

void loop() {
  int packetSize = udp.parsePacket();
  uint8_t packetBuffer[packetSize];
  udp.read(packetBuffer, packetSize);
  if (packetSize) {
    Serial.print("Received packet: ");
    for (int i = 0; i < packetSize; i++) {
    }
    Serial.println();
    int a = (packetBuffer[0]);
    Serial.println(a);
     server.handleClient();
     
  }
}