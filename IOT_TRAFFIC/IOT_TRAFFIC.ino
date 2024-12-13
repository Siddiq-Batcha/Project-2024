#include <WiFi.h>
#include <WebServer.h>

#define st1  32
#define st2  33
#define sr1  14
#define sr2  25
#define st3 13
#define sr3 16
#define stgreen 5
#define rgreen 19
#define yellow 18

int irstraight1,irright1,irstraight2,irright2,irstraight3,irright3;
const char* ssid = "IOT TRAFFIC";  // Enter SSID here
const char* password = "12345678";  //Enter Password here
bool flagr,flagst;
/* Put IP Address details */
IPAddress local_ip(192,168,43,1);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);
bool Autostatus = LOW;
bool Rightstatus = LOW;
bool Straightstatus = LOW;
String Rightln = "Rightlane status:No Vehicle";
String Straightln = "Straightlane status:No Vehicle";



void handle_OnConnect() {
  
  Autostatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
//  irright1=digitalRead(sr1);
// irright2=digitalRead(sr2);
// irstraight1=digitalRead(st1);
// irstraight2=digitalRead(st2);
// irright3=digitalRead(sr3);
// irstraight3=digitalRead(st3);
// Serial.print("irst1=");
// Serial.println(irstraight1);
// Serial.print("irst2=");
// Serial.println(irstraight2);
// Serial.print("irst3=");
// Serial.println(irstraight3);
// Serial.print("irr1");
// Serial.println(irright1);
// Serial.print("irr2");
// Serial.println(irright2);
// Serial.print("irr3");
// Serial.println(irright3);
if(irright1==0&&irright2==0&&irright3==0)
{
  Rightln = "Rightlane status:HIGH";
}
else if(irright1==0&&irright2==0&&irright3==1)
{
  Rightln = "Rightlane status:MEDIUM";
}
else if(irright1==0&&irright2==1&&irright3==1)
{
 Rightln = "Rightlane status:LOW";
}
 else
 {
  Rightln = "Rightlane status:No Vehicle";
 } 

 if(irstraight1==0&&irstraight2==0&&irstraight3==0)
 {
  //Serial.println("Straightlane status:HIGH");
  Straightln = "Straightlane status:HIGH";
 }
 else if(irstraight1==0&&irstraight2==0&&irstraight3==1)
 {
 // Serial.println("Straightlane status:MEDIUM");
  Straightln = "Straightlane status:MEDIUM";
 }
else if(irstraight1==0&&irstraight2==1&&irstraight3==1)
 {
  //Serial.println("Straightlane status:LOW");
  Straightln = "Straightlane status:LOW";
 }
 else
 {
  Straightln = "Straightln status:No Vehicle";
 }
  //Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(Autostatus, Rightstatus, Straightstatus,Rightln,Straightln )); 
}

void handle_Autoon() {
  Autostatus = HIGH;
  Rightstatus = LOW;
  Straightstatus = LOW;
 
  server.send(200, "text/html", SendHTML(Autostatus, Rightstatus, Straightstatus,Rightln,Straightln ));  
}

void handle_Autooff() {
  
  Autostatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(Autostatus, Rightstatus, Straightstatus,Rightln,Straightln ));  
  
}

void handle_Righton() {
  Autostatus = LOW;
  Rightstatus = HIGH;
  Straightstatus = LOW;

  server.send(200, "text/html", SendHTML(Autostatus, Rightstatus, Straightstatus,Rightln,Straightln ));  
}

void handle_Rightoff() {
  
  Autostatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  
  
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(Autostatus, Rightstatus, Straightstatus,Rightln,Straightln ));  
  
}

void handle_Straighton() {
  Autostatus = LOW;
  Rightstatus = LOW;
  Straightstatus = HIGH;
  
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(Autostatus, Rightstatus, Straightstatus,Rightln,Straightln ));  
}

void handle_Straightoff() {
  
  Autostatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(Autostatus, Rightstatus, Straightstatus,Rightln,Straightln  ));  
  
}





void setup() {

   Serial.begin(9600);
   Serial.print("wifi");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());
  delay(100);
  
   server.on("/", handle_OnConnect);
  
  
  server.on("/Autoon", handle_Autoon);
  server.on("/Autooff", handle_Autooff);
  
  server.on("/Righton", handle_Righton);
  server.on("/Rightoff", handle_Rightoff);
  
  server.on("/Straighton", handle_Straighton);
  server.on("/Straightoff", handle_Straightoff);

server.begin();
 
  pinMode(st1,INPUT);
  pinMode(st2,INPUT);
  pinMode(sr1,INPUT);
  pinMode(sr2,INPUT);
  pinMode(stgreen,OUTPUT); //green straight
  pinMode(rgreen,OUTPUT); //green right
  pinMode(yellow,OUTPUT);
  digitalWrite(stgreen,HIGH);
  digitalWrite(rgreen,HIGH);
  digitalWrite(yellow,HIGH);
  // put your setup code here, to run once:

}

void loop()
{
server.handleClient();

irright1=digitalRead(sr1);
irright2=digitalRead(sr2);
irstraight1=digitalRead(st1);
irstraight2=digitalRead(st2);
irright3=digitalRead(sr3);
irstraight3=digitalRead(st3);
if(Autostatus==HIGH)  //21
{/////////////
if(irright1==0&&irright2==0&&irright3==0)
{
  Rightln = "Rightlane status:HIGH";
}
else if(irright1==0&&irright2==0&&irright3==1)
{
  Rightln = "Rightlane status:MEDIUM";
}
else if(irright1==0&&irright2==1&&irright3==1)
{
 Rightln = "Rightlane status:LOW";
}
 else
 {
  Rightln = "Rightlane status:No Vehicle";
 } 

 if(irstraight1==0&&irstraight2==0&&irstraight3==0)
 {
  //Serial.println("Straightlane status:HIGH");
  Straightln = "Straightlane status:HIGH";
 }
 else if(irstraight1==0&&irstraight2==0&&irstraight3==1)
 {
 // Serial.println("Straightlane status:MEDIUM");
  Straightln = "Straightlane status:MEDIUM";
 }
else if(irstraight1==0&&irstraight2==1&&irstraight3==1)
 {
  //Serial.println("Straightlane status:LOW");
  Straightln = "Straightlane status:LOW";
 }
 else
 {
  Straightln = "Straightln status:No Vehicle";
 }
/////////
if(irright1==0 && irright2==0)//////////right 1 and 2
{ 
  Rightln ="Rightlane status:MEDIUM";
  Serial.println("yellow");
  digitalWrite(yellow,LOW);
  delay(3000);
  digitalWrite(yellow,HIGH);
  flagr=true;
 
  while(flagr==true) // wait for right side moving out
 {
  String Rightln ="Rightlane status:MEDIUM";
  digitalWrite(rgreen,LOW);
  irright1=digitalRead(sr1);
  irright2=digitalRead(sr2);
  Serial.print(irright1);
  Serial.print(irright2);
  Serial.println("right green");
  if((irright1==0 && irright2==1)||(irright1==1 && irright2==1))
  { 
   Serial.println("while if going to stop"); 
   delay(3000);
  digitalWrite(rgreen,HIGH);
   flagr=false;
  }
  }
}
/////////
if(irright1==0 && irright2==0 && irright3==0) /////////right 1,2 and 3
{ 
  Rightln ="Rightlane status:HIGH";
  Serial.println("yellow");
  digitalWrite(yellow,LOW);
  delay(3000);
  digitalWrite(yellow,HIGH);
  flagr=true;
 
  while(flagr==true) // wait for right side moving out
 {
   String Rightln ="Rightlane status:HIGH";
   digitalWrite(rgreen,LOW);
   irright1=digitalRead(sr1);
   irright2=digitalRead(sr2);
   Serial.print(irright1);
   Serial.print(irright2);
   Serial.println("right green");
   if((irright1==0 && irright2==1)||(irright1==1 && irright2==1))
   { 
     Serial.println("while if going to stop"); 
     delay(3000);
     digitalWrite(rgreen,HIGH);
     flagr=false;
   }
  }
}
/////////
    //else if((irright1==0 && irright2==1) && ((irstraight1==1 && irright2 == 1) ||(irstraight1==1 && irright2 == 0)))
else if(irright1==0 && irright2==1)//////right 1
{ 
  Rightln ="Rightlane status:LOW";
  Serial.println(" hey its 0,1 in right road green");
  digitalWrite(rgreen,LOW);
  delay(3000);
  digitalWrite(rgreen,HIGH);
}
/////
     //else if((irstraight1==0 && irstraight2==0)&& ((irright1==0 && irright2==1) || (irright1 == 1 && irright2==1) ||(irright1==1 && irright2==0))) 
else if(irstraight1==0 && irstraight2==0) //// straight 1,2
{
  Straightln ="Straightlane status:MEDIUM";
  Serial.println("yellow in Straight");
  digitalWrite(yellow,LOW);
  delay(3000);
  digitalWrite(yellow,HIGH);
  flagst=true;

  while(flagst==true)
  {
    String Straightln ="Straightlane status:MEDIUM";
    digitalWrite(stgreen,LOW);
    irstraight1=digitalRead(st1);
    irstraight2=digitalRead(st2);
    Serial.print(irstraight1);
    Serial.print(irstraight2);
    Serial.println("Straight green");
    if((irstraight1==0 && irstraight2==1)||(irstraight1==1 && irstraight2==1) )
    {
      Serial.println("while if going to stop");
      delay(3000);
      flagst=false;
      digitalWrite(stgreen,HIGH);
    }
  }
}
///////
else if(irstraight1==0 && irstraight2==0 && irstraight3==0)////straight 1,2 and 3
{
      Straightln ="Straightlane status:HIGH";

     Serial.println("yellow in Straight");
      digitalWrite(yellow,LOW);
      delay(3000);
     digitalWrite(yellow,HIGH);
      flagst=true;

        while(flagst==true)
          { String Straightln ="Straightlane status:HIGH";
           digitalWrite(stgreen,LOW);
           irstraight1=digitalRead(st1);
           irstraight2=digitalRead(st2);
           Serial.print(irstraight1);
           Serial.print(irstraight2);
            Serial.println("Straight green");
           if((irstraight1==0 && irstraight2==1)||(irstraight1==1 && irstraight2==1) )
             {
              Serial.println("while if going to stop");
               delay(3000);
               flagst=false;
               digitalWrite(stgreen,HIGH);
              }
          }
      }      
///////

       //else if((irstraight1==0 && irstraight2==1) && (irright1 == 1 && irright2 == 1 ||irright1 == 1 && irright2 == 0)) 
     else if(irstraight1==0 && irstraight2==1)  /////straight 1
     {
      Straightln ="Straightlane status:LOW";    
      Serial.println(" hey its 0,1 in Straight road green");
      digitalWrite(stgreen,LOW);
      delay(3000);
      digitalWrite(stgreen,HIGH);
      }
else //else13
{
  if(irright1==0&&irright2==0&&irright3==0)
  {
  Rightln = "Rightlane status:HIGH";
}
else if(irright1==0&&irright2==0&&irright3==1)
{
  Rightln = "Rightlane status:MEDIUM";
}
else if(irright1==0&&irright2==1&&irright3==1)
{
 Rightln = "Rightlane status:LOW";
}
 else
 {
  Rightln = "Rightlane status:No Vehicle";
 } 

 if(irstraight1==0&&irstraight2==0&&irstraight3==0)
 {
  //Serial.println("Straightlane status:HIGH");
  Straightln = "Straightlane status:HIGH";
 }
 else if(irstraight1==0&&irstraight2==0&&irstraight3==1)
 {
 // Serial.println("Straightlane status:MEDIUM");
  Straightln = "Straightlane status:MEDIUM";
 }
else if(irstraight1==0&&irstraight2==1&&irstraight3==1)
 {
  //Serial.println("Straightlane status:LOW");
  Straightln = "Straightlane status:LOW";
 }
 else
 {
  Straightln = "Straightln status:No Vehicle";
 }
 
}
  Serial.println("inside Else");
  digitalWrite(rgreen,LOW);
  delay(2000);
  digitalWrite(rgreen,HIGH);
  delay(1000);
  digitalWrite(yellow,LOW);
  delay(2000);
  digitalWrite(yellow,HIGH);
  delay(1000);
  digitalWrite(stgreen,LOW);
  delay(2000);
  digitalWrite(stgreen,HIGH);
  delay(1000);
  digitalWrite(yellow,LOW);
  delay(2000);
  digitalWrite(yellow,HIGH);
  delay(1000);
}
/////////////////////////////////////////////////
else
{
 Serial.println("Auto Else");
  digitalWrite(rgreen,LOW);
  delay(2000);
  digitalWrite(rgreen,HIGH);
  delay(1000);
  digitalWrite(yellow,LOW);
  delay(2000);
  digitalWrite(yellow,HIGH);
  delay(1000);
  digitalWrite(stgreen,LOW);
  delay(2000);
  digitalWrite(stgreen,HIGH);
  delay(1000);
  digitalWrite(yellow,LOW);
  delay(2000);
  digitalWrite(yellow,HIGH);
  delay(1000);
}

if(Rightstatus==HIGH)
{/////////////
if(irright1==0&&irright2==0&&irright3==0)
{
  Rightln = "Rightlane status:HIGH";
}
else if(irright1==0&&irright2==0&&irright3==1)
{
  Rightln = "Rightlane status:MEDIUM";
}
else if(irright1==0&&irright2==1&&irright3==1)
{
 Rightln = "Rightlane status:LOW";
}
 else
 {
  Rightln = "Rightlane status:No Vehicle";
 } 

 if(irstraight1==0&&irstraight2==0&&irstraight3==0)
 {
  //Serial.println("Straightlane status:HIGH");
  Straightln = "Straightlane status:HIGH";
 }
 else if(irstraight1==0&&irstraight2==0&&irstraight3==1)
 {
 // Serial.println("Straightlane status:MEDIUM");
  Straightln = "Straightlane status:MEDIUM";
 }
else if(irstraight1==0&&irstraight2==1&&irstraight3==1)
 {
  //Serial.println("Straightlane status:LOW");
  Straightln = "Straightlane status:LOW";
 }
 else
 {
  Straightln = "Straightln status:No Vehicle";
 }
/////////////
  //Serial.println("Rightlane");
//pinMode(rgreen, OUTPUT);
 digitalWrite(rgreen,LOW);
}
else
{
  //pinMode(rgreen, INPUT);
  digitalWrite(rgreen,HIGH);
}
 if(Straightstatus==HIGH)
{/////////
if(irright1==0&&irright2==0&&irright3==0)
{
  Rightln = "Rightlane status:HIGH";
}
else if(irright1==0&&irright2==0&&irright3==1)
{
  Rightln = "Rightlane status:MEDIUM";
}
else if(irright1==0&&irright2==1&&irright3==1)
{
 Rightln = "Rightlane status:LOW";
}
 else
 {
  Rightln = "Rightlane status:No Vehicle";
 } 

 if(irstraight1==0&&irstraight2==0&&irstraight3==0)
 {
  //Serial.println("Straightlane status:HIGH");
  Straightln = "Straightlane status:HIGH";
 }
 else if(irstraight1==0&&irstraight2==0&&irstraight3==1)
 {
 // Serial.println("Straightlane status:MEDIUM");
  Straightln = "Straightlane status:MEDIUM";
 }
else if(irstraight1==0&&irstraight2==1&&irstraight3==1)
 {
  //Serial.println("Straightlane status:LOW");
  Straightln = "Straightlane status:LOW";
 }
 else
 {
  Straightln = "Straightln status:No Vehicle";
 }
/////////
   //pinMode(stgreen, OUTPUT);
Serial.println("Straightlane");
digitalWrite(stgreen,LOW); 
}
else 
{
//pinMode(stgreen, INPUT);
  digitalWrite(stgreen,HIGH);
}

}



String SendHTML(uint8_t Autostat,uint8_t Rightstat, uint8_t Straight,String Rig, String Str)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>TRAFFIC</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="<script>function autoRefresh() {  window.location = window.location.href;} setInterval('autoRefresh()', 2000); </script>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1> Traffic Management and Control System</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
  ptr +="<h3> "+ Rig+" </h1>\n";
  ptr +="<h3> "+ Str+" </h1>\n";
  
   if(Autostat)
  {ptr +="<p>Auto: ON</p><a class=\"button button-off\" href=\"/Autooff\">OFF</a>\n";}
  else
  {ptr +="<p>Auto: OFF</p><a class=\"button button-on\" href=\"/Autoon\">ON</a>\n";}

  if(Rightstat)
  {ptr +="<p>RightLane: ON</p><a class=\"button button-off\" href=\"/Rightoff\">OFF</a>\n";}
  else
  {ptr +="<p>RightLane: OFF</p><a class=\"button button-on\" href=\"/Righton\">ON</a>\n";}

   if(Straight)
  {ptr +="<p>StraightLane: ON</p><a class=\"button button-off\" href=\"/Straightoff\">OFF</a>\n";}
  else
  {ptr +="<p>StraightLane: OFF</p><a class=\"button button-on\" href=\"/Straighton\">ON</a>\n";}

   


  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}


