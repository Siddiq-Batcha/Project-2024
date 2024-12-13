#define  Buzz      23

void setup() {
  Serial.begin(9600);
  pinMode(Buzz, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    if (data == "Buzz on") {
      Serial.println("BUzz on");
      digitalWrite(Buzz, HIGH);
    // } else if (data.startsWith("Sensor1:")) {
    //   float sensor1_value = data.substring(8).toFloat();
    //   // Process sensor1_value as needed
    // } else if (data.startsWith("Sensor2:")) {
    //   float sensor2_value = data.substring(8).toFloat();
    //   // Process sensor2_value as needed
    // } else if (data.startsWith("Sensor3:")) {
    //   float sensor3_value = data.substring(8).toFloat();
    //   // Process sensor3_value as needed
    }
  }
}
