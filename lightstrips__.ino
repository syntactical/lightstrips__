#include <Adafruit_NeoPixel.h>
#define PIN 6
#define LENGTH_OF_TAIL 2
#define NUMBER_OF_LEDS 30
#define MAX_8_BIT_VALUE 255

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

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

int analogPin = A0;

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(1));

  for (int stripNumber = 0; stripNumber < NUMSTRIPS; stripNumber++) {
    brightestPixels[stripNumber] = random(0, NUMBER_OF_LEDS);
    strips[stripNumber].begin();
    strips[stripNumber].show();
  }
}

void loop() {
  int sensorValue = analogRead(A0);
  int delayTime = int(clamp(4000/(clamp(sensorValue-15,1,1023))-45,200,2000));

//  Serial.println("delay time:");
//  Serial.println(delayTime);
//  Serial.println("sensor value:");
//  Serial.println(sensorValue);

  if(counter == delayTime) {
    counter = 0;
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
    
//  delay(delayTime);
}

inline int clamp(int x, int a, int b){
    return x < a ? a : (x > b ? b : x);
}

inline float clamp(float x, float a, float b){
    return x < a ? a : (x > b ? b : x);
}

