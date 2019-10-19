/*
  ReadField

  Description: Demonstates reading from a public channel which requires no API key and reading from a private channel which requires a read API key.
               The value read from the public channel is the current outside temperature at MathWorks headquaters in Natick, MA.  The value from the
               private channel is an example counter that increments every 10 seconds.

  Hardware: ESP32 based boards

  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!

  Note:
  - Requires installation of EPS32 core. See https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md for details.
  - Select the target hardware from the Tools->Board menu
  - This example is written for a network using WPA encryption. For WEP or WPA, change the WiFi.begin() call accordingly.

  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.

  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.

  For licensing information, see the accompanying license file.

  Copyright 2018, The MathWorks, Inc.

  ESP32 Wemos D1 mini
*/

#include "ThingSpeak.h"
//#include "secrets.h"
#include <WiFi.h>

#include <Adafruit_NeoPixel.h>
#define NUM_PIXELS 30
#define LED_PIN D8
Adafruit_NeoPixel pixels(NUM_PIXELS, LED_PIN, NEO_GRB | NEO_KHZ800);


char ssid[] = "camilla-PC-Wireless";   // your network SSID (name)
char pass[] = "n33gvsn33gvs";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

// Weather station channel details
//unsigned long weatherStationChannelNumber = SECRET_CH_ID_WEATHER_STATION;
unsigned int temperatureFieldNumber = 1;

// Counting channel details
unsigned long counterChannelNumber = 207686;
const char * myCounterReadAPIKey = "O6TR4DJ56135BADQ";
unsigned int counterFieldNumber = 1;

void setup() {
  pixels.begin();
  Serial.begin(9600);
  for (int i = 0; i < 30; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.show();
    delay(100);
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
  }
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  int statusCode = 0;

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected");
  }


  /*
    // Read in field 4 of the public channel recording the temperature
    float temperatureInF = ThingSpeak.readFloatField(weatherStationChannelNumber, temperatureFieldNumber);

    // Check the status of the read operation to see if it was successful
    statusCode = ThingSpeak.getLastReadStatus();
    if(statusCode == 200){
      Serial.println("Temperature at MathWorks HQ: " + String(temperatureInF) + " deg F");
    }
    else{
      Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
    }

    delay(15000); // No need to read the temperature too often.
  */

  // Read in field 1 of the private channel
  long count = ThingSpeak.readLongField(counterChannelNumber, counterFieldNumber, myCounterReadAPIKey);

  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200) {
    Serial.println("Temerature " + String(count));
  }
  else {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }

  if (count > 500) {
    for (int i = 0; i < 30; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      if (i % 2) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 255));
      }
      pixels.show();
    }
  }
  else {
    for (int i = 0; i < 30; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
    }
  }
  delay(1000); // No need to read the counter too often.
}
