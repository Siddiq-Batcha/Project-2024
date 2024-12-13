#include "index.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>


WebServer server(80);

const char* ssid = "Brick Detector";  // Enter SSID here
const char* password = "12345678";  //Enter Password here


/* Put IP Address details */
IPAddress local_ip(192,168,43,1);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);

#define    R1    18
#define    R2    19
#define    R3    26
#define    R4    25
#define    R5    23
#define    R6    22
#define    R7    17

#define    Sensor1  33
#define    Sensor2  32      

int read_1, read_2;




void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


void handleADC() 
{
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  delay(3000);
  Serial.println("R1");
  String Val = String(read_1);
  server.send(200, "text/html", Val); //Send web page
  delay(5000);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  delay(3000);
 
}


void setup() {
  // put your setup code here, to run once:\

  Serial.begin(9600);

  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());
  delay(100);
  
  
  server.on("/", handleRoot);
  server.on("/readADC",handleADC);
  
  server.begin();
  Serial.println("HTTP server started");

  
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);

  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  digitalWrite(R1,HIGH);
  digitalWrite(R2,HIGH);
  digitalWrite(R3,HIGH);
  digitalWrite(R4,HIGH);
  digitalWrite(R5,HIGH);
  digitalWrite(R6,HIGH);
  digitalWrite(R7,HIGH);
}

void loop() 
{
  server.handleClient();

  read_1 = analogRead(Sensor1);
  // read_2 = analogRead(Sensor2);

  // Serial.print("Sensor1: ");
  // Serial.print(read_1);
  // Serial.print(" Sensor2: ");
  // Serial.println(read_2);

}