#include "index.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <WiFiUdp.h>

const char *udpAddress = "192.168.43.2"; // IP address of the UDP receiver
const int udpPort = 1234;
#define Buzzer 4

const int buttonPin = 14;          // the number of the pushbutton pin
int buttonState = HIGH;           // the current reading from the input pin
int lastButtonState = HIGH;       // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
volatile int buttonPressedCount = 0; // variable to store the number of button presses




WebServer server(80);

WiFiUDP udp;

const char* ssid = "Smart Ring";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

int reading;
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
  reading = digitalRead(buttonPin);
  if(buttonPressedCount >= 3)
  {
      Serial.println("Buzzer on");
      digitalWrite(Buzzer,LOW);
      Serial.println("Success");
      String value = String("Asking For Help...");
      server.send(200, "text/html", value);
      // String value1 = String("10.69616253801708, 79.09581082061369");
      // server.send(200, "text/html", value1);
      int bytesSent = udp.print("Hello, Buzzer is ON!");
  }
 
}

void handleADC1() 
{
  reading = digitalRead(buttonPin);
  if(buttonPressedCount >= 3)
  {
      Serial.println("Buzzer on");
      digitalWrite(Buzzer,LOW);
      Serial.println("Success");
      // String value = String("Asking For Help...");
      // server.send(200, "text/html", value);
      String value1 = String("10.69616253801708, 79.09581082061369");
      server.send(200, "text/html", value1);
      int bytesSent = udp.print("Hello, Buzzer is ON!");
  }
 
}


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, HIGH);

  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());
  delay(100);
  
  
  server.on("/", handleRoot);
  server.on("/readADC",handleADC);
  server.on("/readADC1",handleADC1);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // read the state of the switch into a local variable:
  server.handleClient();
  udp.beginPacket(udpAddress, udpPort);
   reading = digitalRead(buttonPin);
   Serial.println(reading);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        buttonPressedCount++; // increment the count on button press
        if(buttonPressedCount >= 3)
       {
       Serial.println("Buzzer on");
      digitalWrite(Buzzer,LOW);
      Serial.println("Success");
      // String value = String("Asking For Help...");
      // server.send(200, "text/html", value);
     
      int bytesSent = udp.print("Hello, Buzzer is ON!");
   }
   
       
      }
    }
  }
  // if(buttonPressedCount >= 3)
  // {
   
    
  // }
  // else 
  // {
  //  digitalWrite(Buzzer, LOW);
  // }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  
  udp.endPacket();
  delay(10);
}
