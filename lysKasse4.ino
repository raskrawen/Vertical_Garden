/*
   LED strip WS2818B, pin 5
   LDR + 100K resistor pin A0
   Husk at adskille LDR og LEDstrip :-)
*/

#include <FastLED.h>
#define LED_PIN 5
#define COLOR_ORDER GRB
#define NUM_LEDS_PER_STRIP 30
CRGB leds[NUM_LEDS_PER_STRIP];

int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor

void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP);
  Serial.begin(9600);
  for (int i = 0; i < 30; i++) {
    leds[i].setRGB(0, 255, 0); //green leds
    FastLED.show();
    delay(50);
  }
  for (int i = 0; i < 30; i++) {
    leds[i].setRGB(0, 0, 0); //no leds
  }
  FastLED.show();
}

void loop()
{
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  Serial.println(sensorValue); //prints the values coming from the sensor on the screen
  if (sensorValue < 500) {
    for (int i = 0; i < 30; i++) {
      leds[i].setRGB(255, 0, 0); //red leds
      if (i % 2 == 0) {
        leds[i].setRGB(255, 0, 255); // red and blue leds
      }
    }
    FastLED.show();
  }
  else {
    for (int i = 0; i < 30; i ++) {
      leds[i].setRGB(0, 0, 0); //no leds

    }
    FastLED.show();
  }
  delay(100);
}
