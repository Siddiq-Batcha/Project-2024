#include "index.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
const int LED_BUILTIN = 2; // 
WebServer server(80);

const char* ssid = "Fire Detector";  // Enter SSID here
const char* password = "12345678";  //Enter Password here


/* Put IP Address details */
IPAddress local_ip(192,168,43,1);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


void handleADC() 
{
  if (Serial.available() > 0)
   {
    char incomingByte1 = Serial.read();
    if (incomingByte1 == 'a') 
    {
      String value = String("Fire is Detected");
      server.send(200, "text/html", value);

      digitalWrite(LED_BUILTIN, HIGH); // Turn on LED
      delay(1000); // Delay for 1 second
      digitalWrite(LED_BUILTIN, LOW); // Turn off LED
    }
    
  }
  else 
  {
      String value1 = String("0");
    server.send(200, "text/html", value1);
    
    
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
  
  
  server.on("/", handleRoot);
  server.on("/readADC",handleADC);
  
  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
   server.handleClient();

  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    if (incomingByte == 'a') {
      digitalWrite(LED_BUILTIN, HIGH); // Turn on LED
      delay(1000); // Delay for 1 second
      digitalWrite(LED_BUILTIN, LOW); // Turn off LED
    }
  }
  
}
