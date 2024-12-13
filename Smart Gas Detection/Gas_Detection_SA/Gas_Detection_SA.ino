#define Sensor1    34
#define Sensor2    35
#define Sensor3    32

#define Relay      25

int read_1,read_2,read_3;

float Pre_1, Pre_2, Pre_3;


void setup()
{
  Serial.begin(9600);
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);
  pinMode(Relay, OUTPUT);
}

void loop()
{
  read_1 = analogRead(Sensor1);
  read_2 = analogRead(Sensor2);
  read_3 = analogRead(Sensor3);

  Pre_1 = ((read_1 / 4095)*100);
  Pre_2 = ((read_1 / 4095)*100);
  Pre_3 = ((read_1 / 4095)*100);
  Serial.print("sen1 =");
  Serial.println(Pre_1);
  Serial.print("sen2 =");
  Serial.println(Pre_2);
  
  Serial.print("sen3 =");
  Serial.println(Pre_3);
  delay(1000);
  if(Pre_1 > 50 || Pre_2 > 50 || Pre_3 > 50)
  {
    Serial.println("Relay ON");
    digitalWrite(Relay, LOW);
  }
  else 
  {
    Serial.println("Relay OFF");
    digitalWrite(Relay, HIGH);
  }
}