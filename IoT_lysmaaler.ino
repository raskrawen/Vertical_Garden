#include <ESP8266WiFi.h>

/*
Wemos D1 -- LDR
5V -- LDR + 100K resistor
GND -- GND
A0 -- Analog output between LDR and resistor
*/

String apiKey = "3X23XXMCGT3V0QJ1";
const char* ssid = "camilla-PC-Wireless";
const char* password = "n33gvsn33gvs";
const char* server = "api.thingspeak.com";
WiFiClient client;

int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor


void setup()
{
Serial.begin(9600);
Serial.println("begyndelse");
delay(10);
Serial.println("WIFI begin");
delay(100); 
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
delay(1000); 
while (WiFi.status() != WL_CONNECTED) 
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
 }


void loop()
{
  sensorValue = analogRead(sensorPin); 
  
  Serial.print("LightLevel: ");
  Serial.println(sensorValue);
 
if (client.connect(server,80)) {
String postStr = apiKey;
postStr +="&field1=";
postStr += String(sensorValue);
postStr += "\r\n\r\n";

client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);
Serial.println("sender til web");
digitalWrite(D4, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(500);              // wait for half a second
digitalWrite(D4, LOW);    // turn the LED off by making the voltage LOW
 }
client.stop();
 
Serial.println("Waiting 30 secs");
// thingspeak needs at least a 15 sec delay between updates
// 20 seconds to be safe
delay(30000);
//delay(300*1000); //300 sekunder = 5 minutters pause
}
