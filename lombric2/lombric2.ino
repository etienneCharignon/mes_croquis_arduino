#include "LPD8806.h"
#include "SPI.h"

int iteration;
uint8_t v,b;
int lombric;

// You can optionally use hardware SPI for faster writes, just leave out
// the data and clock pin parameters.  But this does limit use to very
// specific pins on the Arduino.  For "classic" Arduinos (Uno, Duemilanove,
// etc.), data = pin 11, clock = pin 13.  For Arduino Mega, data = pin 51,
// clock = pin 52.  For 32u4 Breakout Board+ and Teensy, data = pin B2,
// clock = pin B1.  For Leonardo, this can ONLY be done on the ICSP pins.
LPD8806 strip = LPD8806(150);

void setup() {
  // Start up the LED strip
  strip.begin();
  Serial.begin(9600);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  
  // Update the strip, to start they are all 'off'
  strip.show();

  lombric = 0; 
  v = random(20) * 6;
  b = random(20) * 6;     
  
  iteration = 0;
}


void loop() {
  dessinLombric(iteration, 0, v, b);      
  strip.show();
  delay(1000);
  
  iteration++;
}


void dessinLombric(int iteration, uint8_t r, uint8_t v, uint8_t b){
    int i, j;
    int sequence = iteration % 6;
    j = lombric;
    strip.setPixelColor(j, 0, 0, 0);
    if(sequence == 5) {
      strip.setPixelColor(j++, 0, 0, 0);
      lombric++;
    }
    for(i=0; i < 2; i++){
      strip.setPixelColor(j++, 127, v, b);
    }
    for(i=0; i < 5; i++){
      strip.setPixelColor(j++, r, v, b);
      if(sequence == 0 && i == 4) {
        strip.setPixelColor(j++, 0, 0, 0);
      }
      if(sequence == 1 && i == 3) {
        strip.setPixelColor(j++, 0, 0, 0);
      }
      if(sequence == 2 && i == 2) {
        strip.setPixelColor(j++, 0, 0, 0);
      }
      if(sequence == 3 && i == 1) {
        strip.setPixelColor(j++, 0, 0, 0);
      }
      if(sequence == 4 && i == 0) {
        strip.setPixelColor(j++, 0, 0, 0);
      }
    }
    for(i=0; i < 2; i++){
      strip.setPixelColor(j++, 127, v, b);
    }
    if(lombric > strip.numPixels()) {
      lombric = 0;
   } 
}


