
// friday      ->  left 
// saturday    ->  right
// Mode Switch ->  Straight
#include <WiFi.h>
#include <WebServer.h>


/* Put your SSID & Password */
const char* ssid = "Power Management";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,43,1);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

#define CurrentSensor   18
#define VoltageSensor   33
#define Relay1          19
#define Relay2          21
#define Relay3          22


int readCur, count = 0, readVolt;
int switchCount = 0;
int saleCount = 0, saleCount1 = 0 ,EBcount = 0, EBcount1 = 0;
bool flag = true, saleFlag = true, EBflag = true;

bool Leftstatus = LOW;
bool Rightstatus = LOW;
bool Straightstatus = LOW;
bool Autostatus = LOW;
bool Infostatus = LOW;

String Info = " ";
void setup()
{
  Serial.begin(9600);


  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());
  delay(100);
  
  server.on("/", handle_OnConnect);
  
  server.on("/Lefton", handle_Lefton);
  server.on("/Leftoff", handle_Leftoff);
  
  server.on("/Righton", handle_Righton);
  server.on("/Rightoff", handle_Rightoff);
  
  server.on("/Straighton", handle_Straighton);
  server.on("/Straightoff", handle_Straightoff);

  server.on("/Autoon", handle_Autoon);
  server.on("/Autooff", handle_Autooff);

  server.on("/Infoon", handle_Infoon);
  server.on("/Infooff", handle_Infoon);


  pinMode(CurrentSensor, INPUT);
  pinMode(VoltageSensor, INPUT);
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);

  server.begin();
  Serial.println("HTTP server started");
}


void loop()
{
  server.handleClient();

  readCur  = digitalRead(CurrentSensor);
  readVolt = analogRead(VoltageSensor);
  Serial.print("Current: ");
  Serial.println(readCur);
  Serial.print("Voltage: ");
  Serial.println(readVolt);
  if(Autostatus == HIGH)
  {
    if (readCur == 1 && readVolt <=70) 
    {
      EBcount++;
      Serial.print("EB count:");
      Serial.println(EBcount);
      delay(500);
      if(EBcount >=5)
      {
        
        while (EBflag == true)
        {
          
          readCur = digitalRead(CurrentSensor);
          Serial.println(readCur);
          digitalWrite(Relay1, LOW);
          digitalWrite(Relay2, HIGH);
          digitalWrite(Relay3, HIGH);
          if(readCur == 0)
          {
            EBcount1++;
            Serial.print("EB count2:");
            Serial.println(EBcount1);
            delay(500);
            if(EBcount1 > 20)
            {
              EBflag = false;
              Serial.print("EB-False");
              // Info = " ";
            }
            
          }
          else 
          {
              EBcount1 = 0;
              // EBcount = 0;
              // saleCount = 0;
          }
        }
      }
  
      
    }
    else if (readCur == 1 && readVolt >500 && readVolt <= 2500)
    {
      saleCount++;
      Serial.print("saleCount:");
      Serial.println(saleCount);
      if(saleCount >= 5)
      {
        
        // delay(3000);
        while ( saleFlag == true)
        {
          
          readCur = digitalRead(CurrentSensor);
          Serial.print("Current");
          Serial.println(readCur);
          Serial.println("solar to home");
          digitalWrite(Relay2, LOW);
          digitalWrite(Relay1, HIGH);
          digitalWrite(Relay3, HIGH);
          if (readCur == 0)
          {
            saleCount1++;
            Serial.print("sale count1:");
            Serial.println(saleCount1);
            delay(500);
            if(saleCount1 > 20)
            {
              saleFlag = false;
              Serial.print("Sale-False");
              // Info = " ";
            }
          }
          else 
          {
            saleCount1 = 0;
          }
        }
      }
      
      
      Serial.println("Solra to Home");
    }
    else if ( readCur == 0 && readVolt>300 )
    {
      
      Serial.print("Sale to EB");
      digitalWrite(Relay3, LOW);
      digitalWrite(Relay1, HIGH);
      digitalWrite(Relay2, HIGH);
    }
    else 
    {
      // Info = " ";
      saleFlag = true;
      EBflag = true;
      flag = true;
      digitalWrite(Relay1, HIGH);
      digitalWrite(Relay2, HIGH);
      digitalWrite(Relay3, HIGH);
    }
  } 

  if (Infostatus == HIGH)
  {
    if (readCur == 1 && readVolt <=70) 
    {
      Serial.println("WOrkin in EB");
      Info = "Working in EB";
    } 
    else if (readCur == 1 && readVolt >500 && readVolt <= 2500)
    {
      Serial.println("WOrkin in Solar");
        Info = "Working in Solar";
    }
    else if ( readCur == 0 && readVolt>300 )
    {
      Serial.println("Sale in EB");
      Info = "Sale to EB";
    }
    else 
    {
      Info = " ";
    }
  }


  if (Straightstatus == HIGH)
  {
    
    digitalWrite(Relay1, LOW);
    digitalWrite(Relay2, HIGH);
    digitalWrite(Relay3, HIGH);
    Serial.println(" Mode Switch");
  }
  if(Rightstatus == HIGH)
  {
    digitalWrite(Relay1, HIGH);
    digitalWrite(Relay2, LOW);
    digitalWrite(Relay3, HIGH);
  }
  if (Leftstatus == HIGH)
  {
    digitalWrite(Relay3, LOW);
    digitalWrite(Relay1, HIGH);
    digitalWrite(Relay2, HIGH);
  }
    
  
  delay(300);

}

void handle_OnConnect() {
  
  Leftstatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  Autostatus = LOW;
  Infostatus = LOW;

  
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info, Autostatus, Infostatus)); 
}

void handle_Lefton() {
  Leftstatus = HIGH;
  Rightstatus = LOW;
  Straightstatus = LOW;
  Autostatus = LOW;
  Infostatus = LOW;
  
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info, Autostatus, Infostatus ));  
}

void handle_Leftoff() {
  
  Leftstatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  Autostatus = LOW;
  Infostatus = LOW;
  
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info, Autostatus, Infostatus ));  
  
}

void handle_Righton() {
  Leftstatus = LOW;
  Rightstatus = HIGH;
  Straightstatus = LOW;
  Autostatus = LOW;
  Infostatus = LOW;
  
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info, Autostatus, Infostatus ));  
}

void handle_Rightoff() {
  
  Leftstatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  Autostatus = LOW;
  Infostatus = LOW;
  
  
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info, Autostatus, Infostatus ));  
  
}

void handle_Straighton() {
  Leftstatus = LOW;
  Rightstatus = LOW;
  Straightstatus = HIGH;
  Autostatus = LOW;
  Infostatus = LOW;
  
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info, Autostatus, Infostatus ));  
}

void handle_Straightoff() {
  
  Leftstatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  Autostatus = LOW;
  Infostatus = LOW;
  
  Serial.println("GPIO7 Status: OFF");

  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info, Autostatus, Infostatus  ));  
  
}


void handle_Autoon() {
  Leftstatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  Autostatus = HIGH;
  Infostatus = LOW;
  
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info , Autostatus, Infostatus));  
}

void handle_Autooff() {
  
  Leftstatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  Autostatus = LOW;
  Infostatus = LOW;
  
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info, Autostatus, Infostatus ));  
  
}

void handle_Infoon() {
  Leftstatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  Autostatus = LOW; 
  Infostatus = HIGH; 
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info, Autostatus, Infostatus ));  
}

void handle_Infooff() {
  
  Leftstatus = LOW;
  Rightstatus = LOW;
  Straightstatus = LOW;
  Autostatus = LOW;
  Infostatus = LOW;
  
  
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(Leftstatus, Rightstatus, Straightstatus, Info, Autostatus, Infostatus ));  
  
}


String SendHTML(uint8_t Leftstat,uint8_t Rightstat, uint8_t Straight, String Infomation, uint8_t Autostat, uint8_t Infostat ){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Solar Fault </title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  // ptr +="<script>function autoRefresh() {  window.location = window.location.href;} setInterval('autoRefresh()', 2000); </script>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1> AI Solor Falut Detection </h1>\n";
  ptr +="<h1> Infomation: "+ Infomation +" </h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
  
   if(Leftstat)
  {ptr +="<p>Friday: ON</p><a class=\"button button-off\" href=\"/Leftoff\">OFF</a>\n";}
  else
  {ptr +="<p>Friday: OFF</p><a class=\"button button-on\" href=\"/Lefton\">ON</a>\n";}

  if(Rightstat)
  {ptr +="<p>Saturday: ON</p><a class=\"button button-off\" href=\"/Rightoff\">OFF</a>\n";}
  else
  {ptr +="<p>Saturday: OFF</p><a class=\"button button-on\" href=\"/Righton\">ON</a>\n";}

   if(Straight)
  {ptr +="<p>Mode: ON</p><a class=\"button button-off\" href=\"/Straightoff\">OFF</a>\n";}
  else
  {ptr +="<p>Mode: OFF</p><a class=\"button button-on\" href=\"/Straighton\">ON</a>\n";}
  if(Autostatus)
  {ptr +="<p>Auto: ON</p><a class=\"button button-off\" href=\"/Autooff\">OFF</a>\n";}
  else
  {ptr +="<p>Auto: OFF</p><a class=\"button button-on\" href=\"/Autoon\">ON</a>\n";}
  if(Infostat)
  {ptr +="<p>Info: ON</p><a class=\"button button-off\" href=\"/Infooff\">OFF</a>\n";}
  else
  {ptr +="<p>Info: OFF</p><a class=\"button button-on\" href=\"/Infoon\">ON</a>\n";}

   


  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
