#include <WiFi.h>
#include <WiFiUdp.h>
#define Relay1   23
#define Relay2   22
const char* ssid = "Smart Ring";
const char* password = "12345678";
const int udpPort = 1234;
bool flag = true;
WiFiUDP udp;
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  udp.begin(udpPort);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
}

void loop() {
  // Add your code here
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    char packetBuffer[255];
    int bytesRead = udp.read(packetBuffer, 255);
    packetBuffer[bytesRead] = '\0';
    // digitalWrite(Buz, HIGH);
    Serial.print("Received packet: ");
    Serial.println(packetBuffer);
    while(flag == true)
    {
      Serial.println("HI for Message");
      digitalWrite(Relay1, LOW);
      digitalWrite(Relay2, LOW);
      pinMode(Relay1, OUTPUT);
      pinMode(Relay2, OUTPUT);
      delay(500);
    }
  }
  else 
  {
    Serial.println("Relay OFF");
    digitalWrite(Relay1, HIGH);
    digitalWrite(Relay2, HIGH);
    pinMode(Relay1, INPUT);
    pinMode(Relay2, INPUT);
  }
  
  delay(10);
}
