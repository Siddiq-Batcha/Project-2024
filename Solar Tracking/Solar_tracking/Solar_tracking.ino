#define LDR1   0
#define LDR2   1
#define R1     2
#define R2     3

bool flag1 = true;
bool flag2 = true;
void setup() 
{
  Serial.begin(9600);
  pinMode(LDR1,INPUT);
  pinMode(LDR2,INPUT);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  digitalWrite(R1,HIGH);
  digitalWrite(R2,HIGH);
}

void loop() {
  int read1 = digitalRead(LDR1);
  int read2 = digitalRead(LDR2);
  int count = 0; 
  int  count2 = 0;
  if(read1 == 0)
  {
    count++;
    if(count == 1 && flag1 == true)
    {
      Serial.println("COunt 1 and r on"); 
      digitalWrite(R1,LOW);
      flag1 = false;
      flag2 = true;
    }
  }
  else
  {
    digitalWrite(R1, HIGH);
    count = 0;
  }

  if(read2 == 0)
  {
    count2++;
    if(count2 == 1 && flag2 == true)
    {
      Serial.println("COunt 2 and r on");
      digitalWrite(R2,LOW);
      flag1 = true;
      flag2 = false;
    }
  }
  else
  {
    count2 = 0;
    digitalWrite(R2, HIGH);
  }

  // put your main code here, to run repeatedly:

}
