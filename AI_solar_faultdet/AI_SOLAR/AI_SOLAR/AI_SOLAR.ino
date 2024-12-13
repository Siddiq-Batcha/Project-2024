#include "index.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>


WebServer server(80);

const char* ssid = "AI Solar";  // Enter SSID here
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
#define    Shot  15

#define    Sensor1  33
#define    Sensor2  32      

int read_1, read_2, read_3, read_4, read_5, read_6, read_shot;

bool flag=false;
double vol3,vol2,vol1, vol4,vol5,vol6;

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}




void Relay1_2() 
{ 
  // pinMode(R1,OUTPUT);
  // pinMode(R2,OUTPUT);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  delay(3000);
 
  read_1 = analogRead(Sensor1);
  vol1 = ((read_1 *12 /4095));
  Serial.println(read_1);
  Serial.println(vol1);
  if(read_1<=500)
  {
    String Value1 = String("Issue on Solar Panel 1");
    server.send(200,"text/html",Value1);
  }

  else 
  {
  String Value1 = String(vol1);
  server.send(200, "text/html", Value1); //Send web page
  }
  delay(5000);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  delay(3000);
  
}
void Relay3_4() 
{ read_4= analogRead(Sensor2);
while (flag==true) 
{  String Value2 = String("Panel-2 ground detected");
  server.send(200,"text/html",Value2);
  Serial.println("gnd while");
  digitalWrite(R7, LOW);
  read_4= analogRead(Sensor2);
  if(read_4<=50)
  {
    flag=false;
    digitalWrite(R7, HIGH);
  }
}
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);
  delay(3000);
  Serial.println("R3");
  read_2 = analogRead(Sensor1);
  vol2 = ((read_2 * 12)/4095);
  Serial.println(read_4);
  Serial.println(vol2);
  if(read_2<=50)
  {
    String Value2 = String("Issue on Solar Panel 2");
    server.send(200,"text/html",Value2);
  }
  else if(read_4>=50)
  {
    String Value2 = String("Panel-2 ground detected");
    server.send(200,"text/html",Value2);
  }
  else
  {
  String Value2 = String(vol2);
  server.send(200, "text/html", Value2); //Send web page
  }
  delay(5000);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);
  delay(3000);
 
}
void Relay5_6() 
{
  digitalWrite(R5, LOW);
  digitalWrite(R6, LOW);
  delay(3000);
  Serial.println("R5");
  read_3 = analogRead(Sensor1);
  vol3 = ((read_3* 12 /4095));
  Serial.println(read_3);
  Serial.println(vol3);
  if(read_3<=50)
  {
      String Value3 = String("Issue on Solar Panel 3");
    server.send(200,"text/html",Value3);
  }
  else
  {
  String Value3 = String(vol3);
  server.send(200, "text/html", Value3); //Send web page
  }
  delay(5000);
  digitalWrite(R5, HIGH);
  digitalWrite(R6, HIGH);
  delay(3000);
 
}
void Short()
{
  read_shot = digitalRead(Shot);
  Serial.println("in shot");
  delay(5000);
  
  if(read_shot == 1)
  {
    Serial.println("shot");
    String Shot_Vale = String("Short Circuit");
    server.send(200,"text/html",Shot_Vale);
    delay(2000);
  }
  else
  {
    String Shot_Vale = String("No Issue ");
    server.send(200,"text/html",Shot_Vale);
  }

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
  server.on("/readADC1_2",Relay1_2);
  server.on("/readADC3_4",Relay3_4);
  server.on("/readADC5_6",Relay5_6);
  server.on("/readshot",Short);

  
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
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);
  digitalWrite(R5, HIGH);
  digitalWrite(R6, HIGH);
  digitalWrite(R7, HIGH);

}

void loop() 
{
  server.handleClient();
  read_shot = digitalRead(Shot);
  // Serial.println(read_shot);
  
  // digitalWrite(R1, LOW);
  // digitalWrite(R2, LOW);
  // delay(3000);
  // read_1 = analogRead(Sensor1);
  // vol1 = ((read_1 *12 /4095));
  // Serial.println(read_1);
  // Serial.println(vol1);
  // digitalWrite(R1, HIGH);
  // digitalWrite(R2, HIGH);
  // delay(3000);
  // read_4=analogRead(Sensor2);
  // if(read_4>=50)
  // { 
  //  flag = true;
  // }
  // read_shot = digitalRead(Shot);
  // Serial.println(read_shot);
  // else 
  // {
  // flag = true;
  //   digitalWrite(R7,HIGH);
  // }
  
  
  // read_2 = analogRead(Sensor2);

  // Serial.print("Sensor1: ");
  // Serial.print(read_1);
  // Serial.print(" Sensor2: ");
  // Serial.println(read_2);

}