#include <Adafruit_NeoPixel.h>

#define PIN 2

int analogPin1 = A0;
int analogPin2 = A1;
int analogPin3 = A2;

void setup() {
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, HIGH);
  delay(100);
  
  Serial.begin(9600);
}

void loop() {
  Serial.print("sensor 1 = ");
  Serial.print(analogRead(analogPin1));
  Serial.print(" ");
  Serial.print("sensor 2 = ");
  Serial.print(analogRead(analogPin2));
  Serial.print(" ");
  Serial.print("sensor 3 = ");
  Serial.println(analogRead(analogPin3));
}

