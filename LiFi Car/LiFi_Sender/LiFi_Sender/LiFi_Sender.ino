
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>


#define Switch1   33
#define Switch2   26
#define Switch3   35
#define Switch4   23



const char *udpAddress = "192.168.43.2"; // IP address of the UDP receiver
const int udpPort = 1234;









WiFiUDP udp;

const char* ssid = "LiFi Car";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

int read_SW1, read_SW2, read_SW3, read_SW4;
/* Put IP Address details */
IPAddress local_ip(192,168,43,1);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);



void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi. mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());
  delay(100);

  pinMode(Switch1,INPUT);
  pinMode(Switch2,INPUT);
  pinMode(Switch3,INPUT);
  pinMode(Switch4,INPUT);
  
  
 
}

void loop() 
{
  // read the state of the switch into a local variable:
  udp.beginPacket(udpAddress, udpPort);
  read_SW1 = digitalRead(Switch1);
  read_SW2 = digitalRead(Switch2);
  read_SW3 = digitalRead(Switch3);
  read_SW4 = digitalRead(Switch4);

  if(read_SW1 == LOW)
  {
    int bytesSent = udp.print("1");
  }
  else if (read_SW2 == LOW)
  {
    int bytesSent1 = udp.print("2");
  }
  else if (read_SW3 == LOW)
  {
    int bytesSent3 = udp.print("3");
  }
  else if (read_SW4 ==LOW)
  {
    int bytesSent4 = udp.print("4");
  }


  
  udp.endPacket();
  delay(10);
}
