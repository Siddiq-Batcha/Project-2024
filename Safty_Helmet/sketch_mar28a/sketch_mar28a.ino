#define  Sensor1   35
#define  Sensor2   34
#define  Sensor3   32

#define  Buzz      23


int read_sensor1, read_sensor2, read_sensor3;

float Per_Sen1, Per_Sen2, Per_Sen3;

void setup()
{
  Serial.begin(9600);
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);

  pinMode(Buzz, OUTPUT);

}


void loop()
{
  read_sensor1 = analogRead(Sensor1);
  read_sensor2 = analogRead(Sensor2);
  read_sensor3 = analogRead(Sensor3);


  Per_Sen1 = ((read_sensor1/4095)*100);
  Per_Sen2 = ((read_sensor2/4095)*100);
  Per_Sen3 = ((read_sensor3/4095)*100);

  if(Per_Sen1 >=50 || Per_Sen2 >=50 || Per_Sen3 >=50)
  {
    digitalWrite(Buzz, HIGH);
    Serial.println("Buzz on");
    Serial.println("Sending data to ESP32");
    Serial.print("Sensor1: ");
    Serial.println(Per_Sen1);
    Serial.print("Sensor2: ");
    Serial.println(Per_Sen2);
    Serial.print("Sensor3: ");
    Serial.println(Per_Sen3);
  }
  else
  {
    digitalWrite(Buzz, LOW);
  }

}