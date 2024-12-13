#include "DFRobotDFPlayerMini.h"

HardwareSerial mySerial(2);  // Use UART2 for communication
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(115200);        // Debugging via Serial Monitor
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // TX=16, RX=17 for DFPlayer
  Serial.println("Initializing DFPlayer...");

  if (!myDFPlayer.begin(mySerial)) { // Initialize DFPlayer Mini
    Serial.println("Unable to initialize DFPlayer!");
    Serial.println("1. Check connections.");
    Serial.println("2. Insert SD card.");
    while (true); // Stay here if initialization fails
  }

  Serial.println("DFPlayer Mini ready!");
  myDFPlayer.volume(20);  // Set volume level (0 to 30)
}

void loop() {
  if (Serial.available()) { // Check if input from Serial Monitor
    int songNumber = Serial.parseInt(); // Read input as integer
    if (songNumber >= 1 && songNumber <= 10) {
      Serial.printf("Playing song %d...\n", songNumber);
      myDFPlayer.play(songNumber); // Play the song by its number
    } else {
      Serial.println("Invalid input! Enter a number between 1 and 10.");
    }
  }
}
