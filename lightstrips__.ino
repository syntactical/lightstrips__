#include <Adafruit_NeoPixel.h>

#define PIN 6
#define LENGTH_OF_TAIL 4
#define NUMBER_OF_LEDS 30
#define MAX_8_BIT_VALUE 255

Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMBER_OF_LEDS, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUMBER_OF_LEDS, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUMBER_OF_LEDS, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(NUMBER_OF_LEDS, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(NUMBER_OF_LEDS, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(NUMBER_OF_LEDS, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(NUMBER_OF_LEDS, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(NUMBER_OF_LEDS, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip10 = Adafruit_NeoPixel(NUMBER_OF_LEDS, 10, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strips[9] = {strip2, strip3, strip4, strip5, strip6, strip7, strip8, strip9, strip10}; 

int brightestPixels[9];
float delayTimesArray[8];

#define NUMSTRIPS (sizeof(strips)/sizeof(strips[0]))

int pixelNumber;
int colorValue;

float minDelay;
float maxDelay;

int analogPin = A0;

unsigned long previousMillis = 0;
unsigned long interval;

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(1));
  
  minDelay = 30;
  maxDelay = 2000;
  
  for (int stripNumber = 0; stripNumber < NUMSTRIPS; stripNumber++) {
    brightestPixels[stripNumber] = random(0, NUMBER_OF_LEDS);
    strips[stripNumber].begin();
    strips[stripNumber].show();
  }
}

void loop() {
  int sensorValue = analogRead(A0);
  long delayTime = long(clamp((4000/clamp(sensorValue-50,1,1023))-60, minDelay, maxDelay));
 
//  Serial.println(delayTime);
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= delayTime) {
    previousMillis = currentMillis;
      for (int stripNumber = 0; stripNumber < NUMSTRIPS; stripNumber++) {
        for (int i=0; i<=LENGTH_OF_TAIL; i++)  {
          float attenuation = i * (256 / LENGTH_OF_TAIL);
          int scale = clamp(int(256 - attenuation), 0, 255);
          int target = (NUMBER_OF_LEDS + brightestPixels[stripNumber] - i) % NUMBER_OF_LEDS;
          strips[stripNumber].setPixelColor(target, scale, scale, scale);
        }
     
        strips[stripNumber].show();
        brightestPixels[stripNumber] = (brightestPixels[stripNumber] + 1) % NUMBER_OF_LEDS;
      }
  }
}

inline float clamp(float x, float a, float b){
    return x < a ? a : (x > b ? b : x);
}

