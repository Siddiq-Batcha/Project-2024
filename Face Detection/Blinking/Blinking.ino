#include <WiFi.h>
#include <WiFiUdp.h>
const char* ssid = "Abnormal Detection";
const char* password = "12345678";
const int udp_port = 4446;
const IPAddress local_IP(192, 168, 1, 1); // Set your desired static IP address
const IPAddress gateway(192, 168, 1, 1);  // Set your desired gateway IP address
const IPAddress subnet(255, 255, 255, 0); // Set your desired subnet mask
//  bool flag = true;
WiFiUDP udp;
#define  Relay1 15



void setup() {
  pinMode(Relay1,OUTPUT);


  Serial.begin(115200);

  // Start hotspot with static IP address
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);

  Serial.println("Hotspot IP address:");
  Serial.println(WiFi.softAPIP());
  udp.begin(udp_port);

  digitalWrite(Relay1,HIGH);


 
}



  // Check if data has been received
void loop() 
{
  int packetSize = udp.parsePacket();
  if (packetSize) 
  {
    uint8_t packetBuffer[packetSize];
    udp.read(packetBuffer, packetSize);
    
    // Serial.println("Received packet:");
    // for (int i = 0; i < packetSize; i++) 
    // {
    //   Serial.print(packetBuffer[i], HEX); // Print byte in hexadecimal format
    //   Serial.print(" ");
    // }
    // Serial.println();

    int Abnormal = packetBuffer[2];
    Serial.print("Abnormal= ");
    Serial.println(Abnormal);

    if(Abnormal == 1  )
    {
      Serial.println("Relay 1 ON");
     
      digitalWrite(Relay1, LOW);
      pinMode(Relay1, OUTPUT);
      delay(2000);
   
    }
    else
    {
     
      Serial.println("Relay 1 OFF");
      pinMode(Relay1, INPUT);
      Serial.println("Relay 2 OFF");
      digitalWrite(Relay1,HIGH);

    }
    int manuelButo = packetBuffer[3];
    Serial.print("manuelButo= ");
    Serial.println(manuelButo);


    if(manuelButo == 1)
    {
      pinMode(Relay1, OUTPUT);
      digitalWrite(Relay1, LOW);
      delay(1000);
    }
    else 
    {
      pinMode(Relay1, INPUT);
      digitalWrite(Relay1, HIGH);
    }


  }
}
