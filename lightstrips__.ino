#include <Adafruit_NeoPixel.h>
#define PIN 6
#define LENGTH_OF_TAIL 8
#define NUMBER_OF_LEDS 30
#define MAX_8_BIT_VALUE 255

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int brightestPixel;
int pixelNumber;
int colorValue;

void setup() {
  brightestPixel = 0;
  strip.begin();
  strip.show(); // initialize all pixels to 'off'
}

void loop() {
  for (int i=0; i<=LENGTH_OF_TAIL; i++)
  {
    float attenuation = i * (256 / LENGTH_OF_TAIL);
    int scale =  clamp(256 - attenuation, 0, 255);
    int target = (NUMBER_OF_LEDS + brightestPixel - i) % NUMBER_OF_LEDS;
    strip.setPixelColor(target, scale, scale, scale);
  }
  
  strip.show();

  brightestPixel = (brightestPixel+1) % NUMBER_OF_LEDS;
  delay(100);
}


inline int clamp(int x, int a, int b){
    return x < a ? a : (x > b ? b : x);
}

