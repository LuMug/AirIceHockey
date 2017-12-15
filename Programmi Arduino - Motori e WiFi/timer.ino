
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();
const int buttonPin = 2;
const int ledPin = 9;

const int MIN_SEC_MINUTE = 0;

int mIniziale = 1;
int s1 = MIN_SEC_MINUTE;
int s2 = MIN_SEC_MINUTE;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
          
  #ifndef __AVR_ATtiny85__
    Serial.begin(9600);
    Serial.println("7 Segment Backpack Test");
  #endif
    matrix.begin(0x70);
}

void loop() {
   int m = mIniziale;

   matrix.drawColon(true);
   matrix.writeDigitNum(0, 0, false);
   matrix.writeDigitNum(1, m, false);
   matrix.writeDigitNum(3, 0, false);
   matrix.writeDigitNum(4, 0, false);
   matrix.writeDisplay();
   
   //Parte al click del bottone
   if(digitalRead(buttonPin)){
     int t = 60*m;
     analogWrite(ledPin, LOW);
     for(int i = 0; i < t; i++){
       //Scrive sul 7segmenti
       matrix.drawColon(true);
       matrix.writeDigitNum(0, 0, false);
       matrix.writeDigitNum(1, m, false);
       matrix.writeDigitNum(3, s1, false);
       matrix.writeDigitNum(4, s2, false);
       matrix.writeDisplay();
    
       //Conto alla rovescia
       if(s1 == MIN_SEC_MINUTE && s2 == MIN_SEC_MINUTE){
        m--;
        s1 = 5;
        s2 = 9;
       }else if(s2 == MIN_SEC_MINUTE){
        s1--;
        s2 = 9;
       }else{
        s2--;
       }
    
       delay(1000);
       if(m == MIN_SEC_MINUTE && 
         s1 == MIN_SEC_MINUTE && 
         s2 == MIN_SEC_MINUTE){
          Serial.println("STOP");
          analogWrite(ledPin, HIGH);
       }
     }
   }
}
