
#define st1  35
#define st2  34
#define sr1  13
#define sr2  12
#define stgreen 23
#define rgreen 22
#define yellow 3

int irstraight1,irright1,irstraight2,irright2;
bool flagr,flagst;
/* Put IP Address details */

void setup() {
  Serial.begin(9600);
  pinMode(st1,INPUT);
  pinMode(st2,INPUT);
  pinMode(sr1,INPUT);
  pinMode(sr2,INPUT);
  pinMode(stgreen,OUTPUT); //green straight
  pinMode(rgreen,OUTPUT); //green right
  pinMode(yellow,OUTPUT);
  
 
  // put your setup code here, to run once:

}

void loop()
{
irright1=digitalRead(sr1);
irright2=digitalRead(sr2);
irstraight1=digitalRead(st1);
irstraight2=digitalRead(st2);
Serial.print(" right1:");
  Serial.print(irright1);
  Serial.print("  right2:");
  Serial.println(irright2);
    Serial.print("whileright1:");
  Serial.print(irright1);
  Serial.print("  whileright2:");
  Serial.println(irright2);
if((irright1==0 && irright2==0) && ((irstraight1==0 && irright2==1) ||(irstraight1==1 && irright2==1) ||(irstraight1==1 && irright2==0 )))
{ 
  Serial.print(" right1:");
  Serial.print(irright1);
  Serial.print("  right2:");
  Serial.println(irright2);
  digitalWrite(yellow,HIGH);
  delay(3000);
  flagr=true;
 
  while(flagr==true) // wait for right side moving out
 {
  digitalWrite(rgreen,HIGH);
  irright1=digitalRead(sr1);
  irright2=digitalRead(sr2);
  Serial.print("  whileright1:");
  Serial.print(irright1);
  Serial.print("  whileright2:");
  Serial.println(irright2);

  if(irright1=1 && irright2==0)
  {  
   delay(3000);
    flagr=false;
  }
  }
}
/////////
    else if((irright1==0 && irright2==1) && ((irstraight1==1 && irright2 == 1) ||(irstraight1==1 && irright2 == 0)))
       { 
       digitalWrite(rgreen,HIGH);
       delay(3000);
        }
/////
     else if((irstraight1==0 && irstraight2==0)&& ((irright1==0 && irright2==1) || (irright1 == 1 && irright2==1) ||(irright1==1 && irright2==0))) 
     {

      Serial.print("  straight1=");
      Serial.print(irstraight1);
      Serial.print("  straight2=");
      Serial.println(irstraight2);
      digitalWrite(yellow,HIGH);
      delay(3000);
      flagst=true;

        while(flagst==true)
          { 
           digitalWrite(stgreen,HIGH);
           delay(3000);
           irstraight1=digitalRead(st1);
           irstraight2=digitalRead(st2);
           Serial.print("  whilestraight1=");
           Serial.print(irstraight1);
           Serial.print("  whilestraight2=");
           Serial.println(irstraight2);

           if(irright1=1&&irright2==0)
             {
               delay(3000);
                flagst=false;
              }
          }
      }
///////

       else if((irstraight1==0 && irstraight2==1) && (irright1 == 1 && irright2 == 1 ||irright1 == 1 && irright2 == 0)) 
     {
          digitalWrite(stgreen,HIGH);
          delay(3000);
      }
else //else13
{
  digitalWrite(rgreen,HIGH);
  delay(2000);
  digitalWrite(yellow,HIGH);
  delay(2000);
  digitalWrite(stgreen,HIGH);
  delay(2000);
}
}
/////////////////////////////////////////////////







