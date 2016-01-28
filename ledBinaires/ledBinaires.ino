#include <PololuLedStrip.h>
#include <EEPROM.h>

// Create an ledStrip object on pin 11.
#define LED_SIGNAL_PIN 11
PololuLedStrip<LED_SIGNAL_PIN> ledStrip;

#define NEXT_PATTERN_BUTTON_PIN  2  // button between this pin and ground
#define AUTOCYCLE_SWITCH_PIN  3  // switch between this pin and ground

#define LED_COUNT 150
rgb_color colors[LED_COUNT];

#define COUNTER_WORDS (LED_COUNT/32)

// system timer, incremented by one every time through the main loop
unsigned int loopCount[COUNTER_WORDS];

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
  
  for(int i = 0; i < COUNTER_WORDS; i++) {
    loopCount[i] = 0;
  }
 
}

// main loop
void loop()
{
  delay(20);
  
  if(loopCount[0] % LED_COUNT == 0) {
    color = getRandomColor();
  }
  
  clearOff();
  for (int i = 0; i < LED_COUNT/2; i++)
  {
    int bit = i % 32;
    if ((loopCount[i / 32] & (1 << bit)) != 0) {
      colors[i*2] = color;
    }
  }
  ledStrip.write(colors, LED_COUNT);

  incrementCounter(loopCount);
}

void incrementCounter(unsigned int *p) {
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


