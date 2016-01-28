#include "LPD8806.h"
#include "SPI.h"

// Example to control LPD8806-based RGB LED Modules in a strip

/*****************************************************************************/

// Number of RGB LEDs in strand:
int nLEDs = 180;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 11;
int clockPin = 13;

const int NOMBRE_DE_LOMBRICS = 10;
int iteration, nombreDeLombricEnJeu;
uint8_t v[NOMBRE_DE_LOMBRICS],b[NOMBRE_DE_LOMBRICS];
int lombric[NOMBRE_DE_LOMBRICS];


// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
//LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

// You can optionally use hardware SPI for faster writes, just leave out
// the data and clock pin parameters.  But this does limit use to very
// specific pins on the Arduino.  For "classic" Arduinos (Uno, Duemilanove,
// etc.), data = pin 11, clock = pin 13.  For Arduino Mega, data = pin 51,
// clock = pin 52.  For 32u4 Breakout Board+ and Teensy, data = pin B2,
// clock = pin B1.  For Leonardo, this can ONLY be done on the ICSP pins.
LPD8806 strip = LPD8806(nLEDs);

  


void setup() {
  int lombricIndex;
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

  for(lombricIndex = 0; lombricIndex < NOMBRE_DE_LOMBRICS; lombricIndex++) {
    lombric[lombricIndex] = 0; 
    v[lombricIndex] = random(20) * 6;
    b[lombricIndex] = random(20) * 6;     
  }
  
  iteration = 0;
  nombreDeLombricEnJeu = 1;
}


void loop() {
  int lombricIndex;
  
  if(iteration % (12 * 10) == 0) {
    nombreDeLombricEnJeu = min(nombreDeLombricEnJeu + 1, NOMBRE_DE_LOMBRICS);
  }
  
  for(lombricIndex = 0; lombricIndex < nombreDeLombricEnJeu;  lombricIndex++) {
    dessinLombric(lombricIndex, iteration, 0, v[lombricIndex], b[lombricIndex]);      
  }
  strip.show();
  delay(40);
  
  iteration++;
}


void dessinLombric(int lombricIndex, int iteration, uint8_t r, uint8_t v, uint8_t b){
    int j;
    const int TAIL_INTENCITE_ROUGE = 10;
    const int TAILLE_ONDE = 2;
    int positionOnde = iteration % 12;
    if (positionOnde == 0){
      lombric[lombricIndex] += TAILLE_ONDE;
    }
    
    int tete = lombric[lombricIndex];
    strip.setPixelColor(tete - 12, 0, 0, 0); 
    for(j=0; j < 12; j++){
      if(j == positionOnde || j == positionOnde + 1){
        strip.setPixelColor(tete - j, 0, 0, 0); 
      }
      else {
        if(j == 10|| j == 11) strip.setPixelColor(tete - j, TAIL_INTENCITE_ROUGE, 0, 0);
        else if(j == 7|| j == 8|| j == 9) strip.setPixelColor(tete - j, 127, v, b);
        else strip.setPixelColor(tete - j, r, v, b); 
      }
    }
 
    if(lombric[lombricIndex] > strip.numPixels() + 12) {
      lombric[lombricIndex] = 0;
   } 
}


