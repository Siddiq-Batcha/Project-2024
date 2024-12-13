#include "INDEX.h"
// #include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <dht11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP280.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; 

#define smoke 14
#define temp 13
#define Relay 27

WebServer server(80);
const char* ssid = "Mines";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

IPAddress local_ip(192,168,43,1);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);
String readTemp;
dht11 DHT11;
int smk,tem;
float readPa;
void handleRoot() 
{
    String s = MAIN_page; //Read HTML contents
    server.send(200, "text/html", s); //Send web page
}


void smokeADC1()
{
     smk = analogRead(smoke);
    if(smk ==0)
    {
        String voltage1 = String("Toxic gas detected ");
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
      tem = DHT11.read(temp);
  //float read Hum = DHT11.humidity;
  float readTemp  = DHT11.temperature;

    if(readTemp >= 40)
    {
        String voltage2 = String(" abnormal temperature in mine");
        server.send(200, "text/html", voltage2);
        Serial.println("abnormal temperature");
        Serial.println(readTemp);
    }
    else 
    {
        // digitalWrite(Relay, HIGH);
        String voltage2 = String("No issue ");
        server.send(200, "text/html", voltage2);
    }
}

void tempADC3()
{  
  tem = DHT11.read(temp);
  //float read Hum = DHT11.humidity;
  float readTemp  = DHT11.temperature;
  int inttemp = int (38.5);
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
    
    server.on("/", handleRoot);
    server.on("/readADC", smokeADC1);
    server.on("/readADC2", tempADC2);
    server.on("/readADC3", tempADC3);
    digitalWrite(Relay, HIGH);



    while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    lcd.begin();
    // Turn on the backlight (if available)
    // lcd.backlight();
    lcd.clear();
    server.begin();
}

void loop() 
{
     server.handleClient();
     smk = analogRead(smoke);
     tem = DHT11.read(temp);
     readPa = bmp.readPressure();
     Serial.println(smk);

     float readTemp  = DHT11.temperature;
     
     if(smk>= 700||readTemp>=40)
     {
        pinMode(Relay, OUTPUT);
        Serial.println("in");
        digitalWrite(Relay,LOW);
        lcd.setCursor(0,0);
        lcd.print("TempC: ");
        lcd.print(41.5);
        lcd.setCursor(1,1);
        lcd.print("Pressure: ");
        lcd.print(readPa);
     }
     else 
     {
        lcd.setCursor(0,0);
        lcd.print("TempC: ");
        lcd.print(38.5);
        lcd.setCursor(1,1);
        lcd.print("Pressure: ");
        lcd.print(readPa);
        pinMode(Relay, INPUT);
        digitalWrite(Relay,HIGH);
     }
    // put your main code here, to run repeatedly:
}
