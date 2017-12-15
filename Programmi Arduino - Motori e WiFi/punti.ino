
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();
const int buttonPin = 2;
//Scrive il punteggio la prima volta
int i = 1;

//Punteggio primo giocatore
int p1 = 0;
//Aggiunge un punto
boolean a = false;

void setup() {
pinMode(buttonPin, INPUT);

#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);

  //attachInterrupt(digitalPinToInterrupt(buttonPin), punteggio, HIGH);
}

void loop() {
  /* 
   *  writeDigitNum(position, value, point)
   *  position --> posizione in cui scrivere (0-4, 2 escluso)
   *  value    --> numero che si vuole scrivere (0-9)
   *  point    --> se il punto del relativo numero è attivo o meno (true/false)
   *  
   *  drawColon(twoPoint)
   *  twoPoint --> se i due punti sono attivi o meno (true/false)
   *  
   *  Pin:
   *  + 3.3V
   *  - GND
   *  D A4
   *  C A5
   */
   //Scrive sul 7segmenti
   matrix.drawColon(true);
   matrix.writeDigitNum(0, 0, false);
   matrix.writeDigitNum(1, 0, false);
   matrix.writeDigitNum(3, 0, false);
   matrix.writeDigitNum(4, p1, false);

   matrix.writeDisplay();

   if(digitalRead(buttonPin)){
      p1++;
      delay(1000);
   }
}

void punteggio(){
   //p1++;
}
