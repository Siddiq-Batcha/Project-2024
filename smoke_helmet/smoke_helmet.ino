#include "INDEX.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <dht11.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define smoke 14
#define temp 13
#define Relay 32
//#define Buzzer 34
#include <Wire.h> 
WebServer server(80);
const char* ssid = "DVMS";  // Enter SSID here
const char* password = "POEMSIFSDVMS1";  //Enter Password here

IPAddress local_ip(192,168,43,1);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);
String readTemp;
dht11 DHT11;
void handleRoot() 
{
    String s = MAIN_page; //Read HTML contents
    server.send(200, "text/html", s); //Send web page
}


void smokeADC1()
{
    int smk = digitalRead(smoke);
    if(smk ==0)
    {
        String voltage1 = String("smoke detected in tunnel");
        server.send(200, "text/html", voltage1);
        Serial.println("smoke detected");
        Serial.println(smk);
    }
    else
    {
        String voltage1 = String("No issue");
        server.send(200, "text/html", voltage1); // Send response even in the 'else' block
    }
}

void tempADC2()
{  
     int tem = DHT11.read(temp);
  //float read Hum = DHT11.humidity;
  float readTemp  = DHT11.temperature;

    if(readTemp >= 40)
    {
        String voltage2 = String(" Abnormal temperture in tunnel");
        server.send(200, "text/html", voltage2);
        Serial.println("abnormal temperature");
        Serial.println(readTemp);
    }
    else 
    {
        digitalWrite(Relay, HIGH);
        String voltage2 = String("No issue ");
        server.send(200, "text/html", voltage2);
    }
}

void tempADC3()
{  
     int tem = DHT11.read(temp);
  //float read Hum = DHT11.humidity;
  float readTemp  = DHT11.temperature;
  int inttemp = int (readTemp);
  String strtemp = String(inttemp);
  server.send(200, "text/html", strtemp);  
}
void setup() 
{
    Serial.println("Booting Sketch...");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid, password);
    Serial.println(WiFi.softAPIP());
    delay(100);
    Serial.begin(9600);
    pinMode(temp, INPUT);
    pinMode(smoke, INPUT);
    pinMode(Relay, OUTPUT);
    // pinMode(Buzzer,OUTPUT);
    pinMode(Relay,HIGH);
    server.on("/", handleRoot);
    server.on("/readADC", smokeADC1);
    server.on("/readADC2", tempADC2);
    server.on("/readADC3", tempADC3);


    server.begin();
}

void loop() 
{
    server.handleClient();  
    int smk1 = digitalRead(smoke);
    if(smk1 ==0)
    {
      digitalWrite(Relay,LOW);
    }
    else 
    {
    digitalWrite(Relay,HIGH);
    }
 
 
} 
