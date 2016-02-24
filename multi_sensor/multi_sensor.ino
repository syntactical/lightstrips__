#include <Adafruit_NeoPixel.h>

#define PIN 11
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

Adafruit_NeoPixel strips1[3] = {strip8, strip9, strip10};
Adafruit_NeoPixel strips2[3] = {strip5, strip4, strip7};
Adafruit_NeoPixel strips3[3] = {strip2, strip3, strip6};

int brightestPixels1[3];
int brightestPixels2[3];
int brightestPixels3[3];

#define STRIPS_IN_GROUP (sizeof(strips1)/sizeof(strips1[0]))

float minDelay;
float maxDelay;
float maxSensorValue;
float minSensorValue;
float threshold;

int sensor1Pin = A0;
int sensor2Pin = A1;
int sensor3Pin = A2;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(3));

  pinMode(PIN, OUTPUT);
  
  minDelay = 30;
  maxDelay = 900;

  maxSensorValue = 200;
  minSensorValue = 60;

  for (int stripNumber = 0; stripNumber < STRIPS_IN_GROUP; stripNumber++) {
    brightestPixels1[stripNumber] = random(0, NUMBER_OF_LEDS);
    brightestPixels2[stripNumber] = random(0, NUMBER_OF_LEDS);
    brightestPixels3[stripNumber] = random(0, NUMBER_OF_LEDS);
    strips1[stripNumber].begin();
    strips1[stripNumber].show();
    strips2[stripNumber].begin();
    strips2[stripNumber].show();
    strips3[stripNumber].begin();
    strips3[stripNumber].show();
  }
}

void loop() {
  digitalWrite(PIN, HIGH);
  delay(10);
  digitalWrite(PIN, LOW);
//  delay(10);
  
  int sensorValue1 = analogRead(sensor1Pin);
  int sensorValue2 = analogRead(sensor2Pin);
  int sensorValue3 = analogRead(sensor3Pin);
//
//  float slope = ((minDelay-maxDelay)/(maxSensorValue-minSensorValue));
//  float intercept = maxDelay - (slope * minSensorValue);
//  
//  long delayTime1 = clamp(sensorValue1, minSensorValue, maxSensorValue) * slope + intercept;
//  long delayTime3 = clamp(sensorValue2, minSensorValue, maxSensorValue) * slope + intercept;
  
  long delayTime1 = clamp((50000 / ((clamp(sensorValue1, minSensorValue, maxSensorValue)) - minSensorValue + 1)) - 200,minDelay,maxDelay) - 130;
  long delayTime2 = clamp((50000 / ((clamp(sensorValue2, minSensorValue, maxSensorValue)) - minSensorValue + 1)) - 200,minDelay,maxDelay) - 130;
  long delayTime3 = clamp((50000 / ((clamp(sensorValue3, minSensorValue, maxSensorValue)) - minSensorValue + 1)) - 200,minDelay,maxDelay) - 130;
  
//  long delayTime1 = long(clamp((4000/clamp(sensor1Value-50,50,300))-60, minDelay, maxDelay));
//  long delayTime2 = long(clamp((4000/clamp(sensor2Value-50,1,1023))-60, minDelay, maxDelay));
//  long delayTime3 = long(clamp((4000/clamp(sensor3Value-50,1,1023))-60, minDelay, maxDelay));
  
//  Serial.print("sensor = ");
//  Serial.print(sensorValue2);
//  Serial.print("\t");
//  Serial.print("clamped sensor = ");
//  Serial.print(clamp(sensorValue2, minSensorValue, maxSensorValue));
//  Serial.print("\t");
  Serial.print("delay time 1 = ");
  Serial.print(delayTime1);
  Serial.print("\t");
  Serial.print("delay time 2 = ");
  Serial.print(delayTime2);
  Serial.print("\t");
  Serial.print("delay time 3 = ");
  Serial.print(delayTime3);
  Serial.println("\t");
  
//  Serial.print("\t");
//  Serial.print("clamped delay time = ");
//  Serial.println(delayTime2);

//  Serial.print("sensor 2 = ");
//  Serial.print(sensorValue2);
//  Serial.print(" ");
//  Serial.print("sensor 3 = ");
//  Serial.println(sensorValue3);
  
//  if (!isEngaged(sensorValue1) && isEngaged(sensorValue2) && isEngaged(sensorValue3)){
//    delayTime1 = delayTime2;
//  } else if (isEngaged(sensorValue1) && !isEngaged(sensorValue2) && isEngaged(sensorValue3)){
////    TODO: What happens here?
//    delayTime2 = delayTime3;
//  } else if (isEngaged(sensorValue1) && isEngaged(sensorValue2) && !isEngaged(sensorValue3)){
//    delayTime3 = delayTime2;
//  } else if (isEngaged(sensorValue1) && !isEngaged(sensorValue2) && !isEngaged(sensorValue3)){
//    delayTime2 = delayTime1;
//    delayTime3 = delayTime1;
//  } else if (!isEngaged(sensorValue1) && isEngaged(sensorValue2) && !isEngaged(sensorValue3)){
//    delayTime1 = delayTime2;
//    delayTime3 = delayTime2;
//  } else if (!isEngaged(sensorValue1) && !isEngaged(sensorValue2) && isEngaged(sensorValue3)){
//    delayTime1 = delayTime3;
//    delayTime2 = delayTime3;
//  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= delayTime1) {
    previousMillis1 = currentMillis;
      for (int stripNumber = 0; stripNumber < STRIPS_IN_GROUP; stripNumber++) {
        for (int i=0; i<=LENGTH_OF_TAIL; i++)  {
          float attenuation = i * (256 / LENGTH_OF_TAIL);
          int scale = clamp(int(256 - attenuation), 0, 255);
          int target = (NUMBER_OF_LEDS + brightestPixels1[stripNumber] - i) % NUMBER_OF_LEDS;
          strips1[stripNumber].setPixelColor(target, scale, scale, scale);
        }
 
        strips1[stripNumber].show();
        brightestPixels1[stripNumber] = (brightestPixels1[stripNumber] + 1) % NUMBER_OF_LEDS;
      }
  }
  
  if (currentMillis - previousMillis2 >= delayTime2) {
    previousMillis2 = currentMillis;
      for (int stripNumber = 0; stripNumber < STRIPS_IN_GROUP; stripNumber++) {
        for (int i=0; i<=LENGTH_OF_TAIL; i++)  {
          float attenuation = i * (256 / LENGTH_OF_TAIL);
          int scale = clamp(int(256 - attenuation), 0, 255);
          int target = (NUMBER_OF_LEDS + brightestPixels2[stripNumber] - i) % NUMBER_OF_LEDS;
          strips2[stripNumber].setPixelColor(target, scale, scale, scale);
        }
     
        strips2[stripNumber].show();
        brightestPixels2[stripNumber] = (brightestPixels2[stripNumber] + 1) % NUMBER_OF_LEDS;
      }
  }
  
  if (currentMillis - previousMillis3 >= delayTime3) {
    previousMillis3 = currentMillis;
      for (int stripNumber = 0; stripNumber < STRIPS_IN_GROUP; stripNumber++) {
        for (int i=0; i<=LENGTH_OF_TAIL; i++)  {
          float attenuation = i * (256 / LENGTH_OF_TAIL);
          int scale = clamp(int(256 - attenuation), 0, 255);
          int target = (NUMBER_OF_LEDS + brightestPixels3[stripNumber] - i) % NUMBER_OF_LEDS;
          strips3[stripNumber].setPixelColor(target, scale, scale, scale);
        }
     
        strips3[stripNumber].show();
        brightestPixels3[stripNumber] = (brightestPixels3[stripNumber] + 1) % NUMBER_OF_LEDS;
      }
  }
}

boolean isEngaged(float sensorValue) {
  return sensorValue <= maxSensorValue;
}

inline float clamp(float x, float a, float b){
    return x < a ? a : (x > b ? b : x);
}

inline float clamp(int x, float a, float b){
    return x < a ? a : (x > b ? b : x);
}
