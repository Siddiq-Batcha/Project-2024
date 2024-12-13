#include "INDEX.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#define V1 35
#define V2 34
#define V3 33
#define V4 32
#define Relay 23
#define shot 15                                             

WebServer server(80);

const char* ssid = "DVMS";  // Enter SSID here
const char* password = "POEMSIFSDVMS1";  //Enter Password here

IPAddress local_ip(192,168,43,1);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);

void handleRoot() 
{
    String s = MAIN_page; //Read HTML contents
    server.send(200, "text/html", s); //Send web page
}

void solarv1()
{
    int solarvolt1 = analogRead(V1);
    Serial.print(solarvolt1);
    Serial.print("=1=");
    float sovo1 = (solarvolt1 * 12.0 )/ 4095.0;
    int voltage1_int = int(sovo1);
    Serial.println(voltage1_int);
    String volt1 = String(voltage1_int);
    server.send(200, "text/html", volt1);
}

void solarv2()
{
    int solarvolt2 = analogRead(V2);
    Serial.print(solarvolt2);
    Serial.print("=2=");
    float sovo2 = (solarvolt2 * 12.0) / 4095.0;
    int voltage2_int = int(sovo2);
    Serial.println(voltage2_int);
    String volt2 = String(voltage2_int);
    server.send(200, "text/html", volt2);
}

void solarv3()
{
    int solarvolt3 = analogRead(V3);
    Serial.print(solarvolt3);
    Serial.print("=3=");
    float sovo3 = (solarvolt3 * 12.0) / 4095.0;
    int voltage3_int = int(sovo3);
    Serial.println(voltage3_int);
    String volt3 = String(voltage3_int);
    server.send(200, "text/html", volt3);
}

void solarADC1()
{
    int solarvolt1 = analogRead(V1);
    if(solarvolt1 <= 50)
    {
        String voltage1 = String("line fault detected");
        server.send(200, "text/html", voltage1);
       // Serial.println("1st Solar line fault");
    }
    else
    {
        String voltage1 = String("No issue");
        server.send(200, "text/html", voltage1); // Send response even in the 'else' block
    }
}

void solarADC2()
{  
    int solarvolt2 = analogRead(V2);
    int solarvolt4 = analogRead(V4);
    if(solarvolt2 <= 50)
    {
        String voltage2 = String(" line fault detected");
        server.send(200, "text/html", voltage2);
        //Serial.println("2nd Solar line fault");
    }
    else if(solarvolt4 > 300 && solarvolt4 <= 400)
    {
        String voltage2 = String("line fault detected");
        digitalWrite(Relay, LOW);
        server.send(200, "text/html", voltage2);
    }
    else 
    {
        digitalWrite(Relay, HIGH);
        String voltage2 = String("No issue");
        server.send(200, "text/html", voltage2);
    }
}

void solarADC3()
{
    int solarvolt3 = analogRead(V3);
    if(solarvolt3 <= 50)
    {
        String voltage3 = String("line fault detected");
        server.send(200, "text/html", voltage3);
        //Serial.println("line fault detected");
    }
    else 
    {
        String voltage3 = String("No issue");
        server.send(200, "text/html", voltage3);
    }
}
void SHOT()
{
    int shotcir = analogRead(shot);
    Serial.println(shotcir);
    if(shotcir == 0)
    {
        String shotsrt = String("Short circuit fault detected");
        server.send(200, "text/html", shotsrt);
        //Serial.println("line fault detected");
    }
    else 
    {
        String shotsrt = String("No issue");
        server.send(200, "text/html", shotsrt);
    }
}

void setup() 
{
    Serial.println("Booting Sketch...");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid, password);
    Serial.println(WiFi.softAPIP());
    delay(100);
      
    
    pinMode(V1, INPUT);
    pinMode(V2, INPUT);
    pinMode(V3, INPUT);
    pinMode(V4, INPUT);
    pinMode(Relay, OUTPUT);
    pinMode(shot,INPUT_PULLUP);
    
    server.on("/", handleRoot);
    server.on("/readADC", solarADC1);
    server.on("/readADC2", solarADC2);
    server.on("/readADC3", solarADC3);
    server.on("/readADC4", solarv1);
    server.on("/readADC5", solarv2);
    server.on("/readADC6", solarv3);
    server.on("/readADC7", SHOT);
    server.begin();
}

void loop() 
{
    server.handleClient();
    // put your main code here, to run repeatedly:
}
