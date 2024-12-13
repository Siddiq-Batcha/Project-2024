#include <LiquidCrystal.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <dht11.h>



#include "Webpage.h"

#define heart 35
#define temp  33

WebServer server(80);

// Initialize the LCD interface pins
const int rs = 26, en = 25, d4 = 5, d5 = 23, d6 = 19, d7 = 18;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

dht11 DHT;
float read_temp;
bool countStatus;
int beat, bpm;
const float referenceVoltage = 3.3;
const float referenceResistor = 10000;
const float beta = 3950;
const float nominalTemperature =25;
const float nominalResistance = 10000;
unsigned long millisBefore;
 

const char* ssid = "Health Monitor";  // Enter SSID here
const char* password = "12345678";  //Enter Password here


/* Put IP Address details */
IPAddress local_ip(192,168,43,1);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);

int i=0;
float tempC;

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


void ReadTemp() 
{
 
   String Temp = String(read_temp);
   server.send(200, "text/html", Temp);
}
void ReadBeat() 
{
  String read_bpm = String(bpm);
  server.send(200, "text/html", read_bpm);
}

// the setup routine runs once when you press reset:
void setup()
{
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());
  delay(100);


  server.on("/", handleRoot);
  server.on("/readG1",ReadTemp);
  server.on("/readG2",ReadBeat);
  
  server.begin();
  Serial.println("HTTP server started");

  lcd.begin(16, 2);
  pinMode(heart, INPUT);
  pinMode(temp, INPUT);
  DHT.read(temp); 
}
 
// the loop routine runs over and over again forever:
void loop()
{
  
  server.handleClient();
  DHT.read(temp); 
  float tem = 33;
  // read the input on analog pin 0:
  int sensorValue = analogRead(heart);
   read_temp = DHT.temperature;
  Serial.println(read_temp);


  if (countStatus == 0)
  {
    if (sensorValue > 600)
    {
      countStatus = 1;
      beat++;
       lcd.setCursor(1,1);
      lcd.print("Beat: ");
      lcd.print(bpm);
  
      Serial.println(beat);
        
        
      Serial.println("tempC");
      lcd.setCursor(0,0);
      lcd.print("TempC: ");
 

      lcd.print(read_temp);
      
    }
  }
  else
  {
    if (sensorValue < 500)
    {
      countStatus = 0;
    }
  }

  if (millis() - millisBefore > 15000)
  {
    bpm = beat * 4;
   
    beat = 0;
    

    millisBefore = millis();
  }


  delay(300);        // delay in between reads for stability
}