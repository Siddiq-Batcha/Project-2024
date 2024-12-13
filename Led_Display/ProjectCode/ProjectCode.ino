#include<dht11.h>
#define dht_apin 5
int x =0;
int hr1,hr12;


dht DHT;
int temp,hum;
#include <SPI.h>        
#include <DMD.h>        
#include <TimerOne.h>   
#include "SystemFont5x7.h"
#include "Arial_black_16.h"
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup()
{
   Serial.begin(9600);
   DHT.read11(dht_apin);  
   temp = DHT.temperature;
   hum = DHT.humidity;
  Serial.println(DHT.temperature);
  Serial.println(hum);
   delay(6000); 
   Timer1.initialize( 5000 );
   Timer1.attachInterrupt( ScanDMD ); 
   dmd.clearScreen( true ); 
   Serial.begin(9600);
  
}

void loop()
{ 
   DHT.read11(dht_apin);  
//  temp = DHT.temperature;
 // hum = DHT.humidity;
  Serial.println(DHT.temperature);
  Serial.println(hum);
  //delay(2000);
  
  char t [3];
  String str2;
  str2=String(temp);
  str2.toCharArray(t,3);
  char h [3];
  String str3;
  str3=String(hum);
  str3.toCharArray(h,3);
 
 
   
 
     dmd.clearScreen( true );
     dmd.selectFont(System5x7);
     for (byte x=0;x<DISPLAYS_ACROSS;x++) {
     for (byte y=0;y<DISPLAYS_DOWN;y++)   {
     dmd.drawString(  0+(32*x),  0+(16*y), "T:", 2, GRAPHICS_NORMAL );
     dmd.drawString(  0+(32*x),  9+(16*y), "H:", 2, GRAPHICS_NORMAL );
     }
     }
    
     dmd.selectFont(System5x7);
     for (byte x=0;x<DISPLAYS_ACROSS;x++) {
     for (byte y=0;y<DISPLAYS_DOWN;y++)   {
     dmd.drawString(  11+(32*x),  0+(16*y), t, 3, GRAPHICS_NORMAL );
     dmd.drawString(  11+(32*x),  9+(16*y), h, 3, GRAPHICS_NORMAL );
     }
     }

     dmd.drawCircle( 24,  1,  1, GRAPHICS_NORMAL );
     
     dmd.selectFont(System5x7);
     for (byte x=0;x<DISPLAYS_ACROSS;x++) {
     for (byte y=0;y<DISPLAYS_DOWN;y++)   {
     dmd.drawString(  27+(32*x),  0+(16*y), "C", 2, GRAPHICS_NORMAL );
     dmd.drawString(  27+(32*x),  9+(16*y), "%", 2, GRAPHICS_NORMAL );
     }
     }

     delay(100);

 }
