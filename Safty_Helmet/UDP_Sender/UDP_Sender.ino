#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "index.h"


#define Sensor1    34
#define Sensor2    33
#define Sensor3    32


#define Buz        23

WebServer server(80);

const char *ssid = "Safty Helmet";
const char *password = "12345678";

const char *udpAddress = "192.168.43.2"; // IP address of the UDP receiver
const int udpPort = 1234;

IPAddress local_ip(192, 168, 43, 1);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiUDP udp;

float Read_1, Read_2, Read_3, Pre_1, Pre_2, Pre_3;


void handleRoot() 
{
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


void WebPage() 
{
 if(Pre_1 > 80 || Pre_2 > 50 || Pre_3 > 50)
 {
    String Value = String("Warning....");
    server.send(200, "text/html", Value);
 }
 else 
 {
    String Value = String("Worker's in Safe Zone....");
    server.send(200, "text/html", Value);
 }
}


void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());
  delay(100);

  Serial.println("Connected to WiFi");

  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);
  pinMode(Buz, OUTPUT);

  server.on("/", handleRoot);
  server.on("/readsensor",WebPage);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {

  server.handleClient();
  udp.beginPacket(udpAddress, udpPort);
  
  Read_1 = analogRead(Sensor1);
  Read_2 = analogRead(Sensor2);
  Read_3 = analogRead(Sensor3);


  Pre_1 = ((Read_1/4095)*100);
  Pre_2 = ((Read_2/4095)*100);
  Pre_3 = ((Read_3/4095)*100);

Serial.print(Pre_1);
Serial.print(",");
Serial.print(Pre_2);
Serial.print(",");
Serial.print(Pre_3);


  if(Pre_1 > 80 || Pre_2 > 50 || Pre_3 > 50)
  {
    Serial.println("Buz on");
    int bytesSent = udp.print("Hello, Buzzer is ON!");
    digitalWrite(Buz, HIGH);
  }
  else 
  {
    Serial.println("Buz OFF");
    digitalWrite(Buz, LOW);
  }
  
  // int bytesSent = udp.print("Hello, UDP Receiver!");
  udp.endPacket();


  
  delay(1000); // Wait for a second before sending the next packet
}
