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

Adafruit_NeoPixel strips1[3] = {strip2, strip3, strip4};
Adafruit_NeoPixel strips2[3] = {strip5, strip6, strip7};
Adafruit_NeoPixel strips3[3] = {strip8, strip9, strip10};

int brightestPixels[9];

#define STRIPS_IN_GROUP (sizeof(strips1)/sizeof(strips1[0]))

float minDelay;
float maxDelay;

int sensor1Pin = A0;
int sensor2Pin = A1;
int sensor3Pin = A2;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(3));
  
  minDelay = 30;
  maxDelay = 2000; 

  for (int stripNumber = 0; stripNumber < STRIPS_IN_GROUP; stripNumber++) {
    brightestPixels[stripNumber] = random(0, NUMBER_OF_LEDS);
    strips1[stripNumber].begin();
    strips1[stripNumber].show();
    strips2[stripNumber].begin();
    strips2[stripNumber].show();
    strips3[stripNumber].begin();
    strips3[stripNumber].show();
  }
}

void loop() {
  int sensor1Value = analogRead(sensor1Pin);
  int sensor2Value = analogRead(sensor2Pin);
  int sensor3Value = analogRead(sensor3Pin);

  long delayTime1 = long(clamp((4000/clamp(sensor1Value-50,1,1023))-60, minDelay, maxDelay));
  long delayTime2 = long(clamp((4000/clamp(sensor2Value-50,1,1023))-60, minDelay, maxDelay));
  long delayTime3 = long(clamp((4000/clamp(sensor3Value-50,1,1023))-60, minDelay, maxDelay));

  if (!isEngaged(delayTime1) && isEngaged(delayTime2) && isEngaged(delayTime3)){
    delayTime1 = delayTime2;
  } else if (isEngaged(delayTime1) && !isEngaged(delayTime2) && isEngaged(delayTime3)){
//    TODO: What happens here?
    delayTime2 = delayTime3;
  } else if (isEngaged(delayTime1) && isEngaged(delayTime2) && !isEngaged(delayTime3)){
    delayTime3 = delayTime2;
  } else if (isEngaged(delayTime1) && !isEngaged(delayTime2) && !isEngaged(delayTime3)){
    delayTime2 = delayTime1;
    delayTime3 = delayTime1;
  } else if (!isEngaged(delayTime1) && isEngaged(delayTime2) && !isEngaged(delayTime3)){
    delayTime1 = delayTime2;
    delayTime3 = delayTime2;
  } else if (!isEngaged(delayTime1) && !isEngaged(delayTime2) && isEngaged(delayTime3)){
    delayTime1 = delayTime3;
    delayTime2 = delayTime3;
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= delayTime1) {
    previousMillis1 = currentMillis;
      for (int stripNumber = 0; stripNumber < STRIPS_IN_GROUP; stripNumber++) {
        for (int i=0; i<=LENGTH_OF_TAIL; i++)  {
          float attenuation = i * (256 / LENGTH_OF_TAIL);
          int scale = clamp(int(256 - attenuation), 0, 255);
          int target = (NUMBER_OF_LEDS + brightestPixels[stripNumber] - i) % NUMBER_OF_LEDS;
          strips1[stripNumber].setPixelColor(target, scale, scale, scale);
        }
 
        strips1[stripNumber].show();
        brightestPixels[stripNumber] = (brightestPixels[stripNumber] + 1) % NUMBER_OF_LEDS;
      }
  }
  
  if (currentMillis - previousMillis2 >= delayTime2) {
    previousMillis2 = currentMillis;
      for (int stripNumber = 0; stripNumber < STRIPS_IN_GROUP; stripNumber++) {
        for (int i=0; i<=LENGTH_OF_TAIL; i++)  {
          float attenuation = i * (256 / LENGTH_OF_TAIL);
          int scale = clamp(int(256 - attenuation), 0, 255);
          int target = (NUMBER_OF_LEDS + brightestPixels[stripNumber] - i) % NUMBER_OF_LEDS;
          strips2[stripNumber].setPixelColor(target, scale, scale, scale);
        }
     
        strips2[stripNumber].show();
        brightestPixels[stripNumber] = (brightestPixels[stripNumber] + 1) % NUMBER_OF_LEDS;
      }
  }
  
  if (currentMillis - previousMillis3 >= delayTime3) {
    previousMillis3 = currentMillis;
      for (int stripNumber = 0; stripNumber < STRIPS_IN_GROUP; stripNumber++) {
        for (int i=0; i<=LENGTH_OF_TAIL; i++)  {
          float attenuation = i * (256 / LENGTH_OF_TAIL);
          int scale = clamp(int(256 - attenuation), 0, 255);
          int target = (NUMBER_OF_LEDS + brightestPixels[stripNumber] - i) % NUMBER_OF_LEDS;
          strips3[stripNumber].setPixelColor(target, scale, scale, scale);
        }
     
        strips3[stripNumber].show();
        brightestPixels[stripNumber] = (brightestPixels[stripNumber] + 1) % NUMBER_OF_LEDS;
      }
  }

  Serial.println("hi");
}

boolean isEngaged(float delayTime) {
  return delayTime <= minDelay;
}

inline float clamp(float x, float a, float b){
    return x < a ? a : (x > b ? b : x);
}
