#include <PololuLedStrip.h>
#include <EEPROM.h>

// Create an ledStrip object on pin 11.
#define LED_SIGNAL_PIN 11
PololuLedStrip<LED_SIGNAL_PIN> ledStrip;

#define NEXT_PATTERN_BUTTON_PIN  2  // button between this pin and ground
#define AUTOCYCLE_SWITCH_PIN  3  // switch between this pin and ground

#define LED_COUNT 150
rgb_color colors[LED_COUNT];

#define WORD_SIZE 8 // use 8 size words to match EEPROM capacity.
#define WORDS_COUNT (1+(LED_COUNT/2)/WORD_SIZE)

#define PERIODE 20 // millisecondes

// system timer, incremented by one every time through the main loop
byte loopCount[WORDS_COUNT];

unsigned int seed = 0;  // used to initialize random number generator

rgb_color color = getRandomColor();

// initialization stuff
void setup()
{
  // initialize the random number generator with a seed obtained by
  // summing the voltages on the disconnected analog inputs
  for (int i = 0; i < 8; i++)
  {
    seed += analogRead(i);
  }
  seed += EEPROM.read(0);  // get part of the seed from EEPROM
  randomSeed(seed);
  // save a random number in EEPROM to be used for random seed
  // generation the next time the program runs
  EEPROM.write(0, random(256));
  clearOff();
  
  for(int i = 0; i < WORDS_COUNT; i++) {
    //loopCount[i] = 0; // first run that programme with that line, for 1 minute then comment and uncomment the next one
    loopCount[i] = EEPROM.read(i+1);
  }
 
}

// main loop
void loop()
{
  delay(PERIODE);
  
  if(loopCount[0] % (1000/PERIODE * 3)== 0) {
    color = getRandomColor();
  }
  
  if(loopCount[0] % (1000/PERIODE * 60) == 0) { // write eeprom every minutes
    for(int i = 0; i < WORDS_COUNT; i++) {
      EEPROM.write(i+1, loopCount[i]);
    }
  }
  
  clearOff();
  for (int i = 0; i < LED_COUNT/2; i++)
  {
    int bit = i % WORD_SIZE;
    if ((loopCount[i / WORD_SIZE] & (1 << bit)) != 0) {
      colors[i*2] = color;
    }
  }
  ledStrip.write(colors, LED_COUNT);

  incrementCounter(loopCount);
}

void incrementCounter(byte *p) {
  while(!++*(p++));
}

void clearOff() {
  for (int i = 0; i < LED_COUNT; i++)
  {
    colors[i] = (rgb_color){0, 0, 0};
  }
}

rgb_color getRandomColor() {
  int color_interval = 40;
  rgb_color randomColor = (rgb_color){0, 0, 0};
  while(randomColor.red == 0 && randomColor.green == 0 && randomColor.blue == 0) {
    randomColor = (rgb_color){random(3)*color_interval, random(3)*color_interval, random(3)*color_interval};
  }
  return randomColor;
}


