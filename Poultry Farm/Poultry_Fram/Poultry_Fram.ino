#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "Webpage.h"
// #define  Ethylene_Gas   32
// #define  Methane_Gas    33
#define  CO2_Gas           34
// #define  Hazd_Gas       35
#define  Relay          23



float ReadCO2;
int  Per_CO2;

WebServer Server(80);

const char* ssid      = "Poultry Farm";
const char* password  = "12345678";



IPAddress local_IP      (192,168,43,1);
IPAddress local_Gateway (192,168,43,1);
IPAddress subnet        (255,255,255,0) ;


void setup()
{
  Serial.begin(9600);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP,local_Gateway,subnet);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());
  pinMode(CO2_Gas,     INPUT);
  
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH);

  Server.on("/", handleRoot);

  Server.on("/readAllSensors", Read_All_Sensors);


  Server.begin();
}

void loop()
{
  Server.handleClient();

  
  ReadCO2  = analogRead(CO2_Gas);
  
  

 
  Per_CO2  = ((ReadCO2/4095)*100);
  Serial.println(Per_CO2);
  if(Per_CO2 >= 50 )
  {
    // Serial.println("Relay on");
    digitalWrite(Relay, LOW);
    pinMode(Relay, OUTPUT);
  }
  else
  {
    // Serial.println("Relay OFF");
    digitalWrite(Relay, HIGH);
    pinMode(Relay, INPUT);

  }
  delay(500);
}



void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 Server.send(200, "text/html", s); //Send web page
}

void Read_All_Sensors() 
{
  String sensorData = String(Per_CO2);
  Server.send(200, "text/plain", sensorData);
}


