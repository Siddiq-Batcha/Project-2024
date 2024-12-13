#include "BluetoothSerial.h"
#include <dht11.h>

#define Temp 33 
#define Pumping 23

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
dht11 DHT;
int receivedValue = 40;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32 Temp"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(Temp, INPUT);
  pinMode(Pumping, OUTPUT);
  digitalWrite(Pumping, HIGH);
  DHT.read(Temp); 
 
}

void loop() {
  // if (Serial.available()) {
  //   SerialBT.write(Serial.read());
  // }
  DHT.read(Temp); 

  float read = DHT.temperature;
  float per = (read / 4095)*100;
  
  SerialBT.print("Temp: ");
  SerialBT.println(read);
  
  if (SerialBT.available())
  {
    String message = SerialBT.readStringUntil('\n');
    // Convert the received message to an integer
     receivedValue = message.toInt();

    // Print the received value
    Serial.println(receivedValue);
    // Serial.print("Analog percentage: ");
    // Serial.println(per);
    

    

  

  }

    if (read >= receivedValue) {
      Serial.println("Inside if");
      delay(500);
      // Add your actions here if the condition is met
      // For example, you might want to control a pump:
      digitalWrite(Pumping, LOW);
    }
    else {
    digitalWrite(Pumping, HIGH);
    }
  delay(20);
}