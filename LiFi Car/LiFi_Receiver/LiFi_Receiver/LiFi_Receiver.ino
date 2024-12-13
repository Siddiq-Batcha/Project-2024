#include <WiFi.h>
#include <WiFiUdp.h>
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

const char* ssid = "LiFi Car";
const char* password = "12345678";
const int udpPort = 1234;

#define LeftIR     33
#define RightIR    35


#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))   // Using a soft serial port
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/16, /*tx =*/17);
#define FPSerial softSerial
#else
#define FPSerial Serial1
#endif

DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
int read_left, read_right;

WiFiUDP udp;
void setup() {
  Serial.begin(115200);


  // Connect to Wi-Fi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  udp.begin(udpPort);

  pinMode(LeftIR, INPUT);
  pinMode(RightIR, INPUT);
#if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1, /*rx =*/16, /*tx =*/17);
#else
  FPSerial.begin(9600);
#endif

  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);

}

void loop() {
  // Add your code here
  read_left = digitalRead(LeftIR);
  read_right = digitalRead(RightIR);
  int packetSize = udp.parsePacket();
  static unsigned long timer = millis();
  
  if (packetSize) {
    char packetBuffer[255];
    int bytesRead = udp.read(packetBuffer, 255);
    packetBuffer[bytesRead] = '\0';
    // digitalWrite(Buz, HIGH);
    Serial.print("Received packet: ");
    Serial.println(packetBuffer);
    if (strcmp(packetBuffer, "1") == 0) {
    Serial.println("IN 1");
    if (millis() - timer > 3000)
    {
    // myDFPlayer.volumeUp();
      timer = millis();
      myDFPlayer.play(4);  //Play next mp3 every 3 second. speedbreaker
      // delay(5000);
    }
    
  }

  if (strcmp(packetBuffer, "2") == 0) {
    Serial.println("IN 2");
    if (millis() - timer > 3000)
    {
    // myDFPlayer.volumeUp();
      timer = millis();
      myDFPlayer.play(5);  //Play next mp3 every 3 second.over taking
      // delay(5000);
    }
    
  }

  if (strcmp(packetBuffer, "3") == 0) {
    Serial.println("IN 3");
    
    if (millis() - timer > 3000)
    {
    // myDFPlayer.volumeUp();
      timer = millis();
      myDFPlayer.play(6);  //Play next mp3 every 3 second. horn prohibited
      // delay(5000);
    }
    
  }

  if (strcmp(packetBuffer, "4") == 0) {
    Serial.println("IN 4");
    if (millis() - timer > 3000)
    {
    // myDFPlayer.volumeUp();
      timer = millis();
      myDFPlayer.play(7);  //Play next mp3 every 3 second. speed limit for 80km
      // delay(5000);
    }
    
  }
  else 
  {
    // Serial.println("Relay OFF");

  }
  
  delay(10);
}

 if (read_left == 0 && read_right == 1)
  {
    Serial.println("Left Turn");
    if (millis() - timer > 3000) 
   {
    // myDFPlayer.volumeUp();
      timer = millis();
      myDFPlayer.play(2);  //Play next mp3 every 3 second.
      // delay(5000);
    }
  }
  else if(read_right == 0 && read_left == 1 )
  {
    Serial.println("Right Turn");
    if (millis() - timer > 3000)
    {
    // myDFPlayer.volumeUp();
      timer = millis();
      myDFPlayer.play(1);  //Play next mp3 every 3 second.
      // delay(5000);
    }
  }
  else if (read_right == 0 && read_left == 0)
  {
    Serial.println("Both Turn");
    if (millis() - timer > 3000)
    {
    // myDFPlayer.volumeUp();
      timer = millis();
      myDFPlayer.play(3);  //Play next mp3 every 3 second.
      // delay(5000);
    }
  }
   
  
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }

}



void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}
