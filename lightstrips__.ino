#include <Adafruit_NeoPixel.h>
#define PIN 6
#define LENGTH_OF_TAIL 8
#define NUMBER_OF_LEDS 30
#define MAX_8_BIT_VALUE 255

using namespace std;

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

int* brightnessArray = new int[LENGTH_OF_TAIL];

void setup() {
  brightestPixel = 0;
  strip.begin();
  strip.show(); // initialize all pixels to 'off'

  initializeBrightnessArray();

//  cout << brightnessArray;
}

void loop() {
  Serial.begin(9600);
  
  for (int i=0; i<=LENGTH_OF_TAIL; i++)
  {
    float v = 256 / LENGTH_OF_TAIL * i;
    int scale =  clamp(256 - v, 0, 255);
    int target = (NUMBER_OF_LEDS + brightestPixel - i) % NUMBER_OF_LEDS;
    strip.setPixelColor(target, scale, scale, scale);
  }
  
  strip.show();

  brightestPixel = (brightestPixel+1) % NUMBER_OF_LEDS;
  delay(100);
}


inline int clamp(int x, int a, int b)

{

    return x < a ? a : (x > b ? b : x);

}

void initializeBrightnessArray() {
  for(int i = 0; i < LENGTH_OF_TAIL; i++) {
    Serial.print (MAX_8_BIT_VALUE * ( i / LENGTH_OF_TAIL ));
    brightnessArray[i] = MAX_8_BIT_VALUE * i / LENGTH_OF_TAIL;
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

