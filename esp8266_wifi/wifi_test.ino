/*  AUTHOR:         Morgan Visnesky
*   DATE:           04/17/2021
*   FILENAME:       wifi_test.ino
*   ORGANIZATION:   PITT-RAS SumoBot Spring 2021
*   DESCRIPTION:
*   Connect the ESP8266 unit to an existing WiFi access point
*   For more information see http://42bots.com
*/

#include <ESP8266WiFi.h> // Used for wifi board
#include <WiFiUdp.h> // Used for UDP client/server (to transmit sensor data from bot to computer)

// Replace these with your WiFi network settings
const char* ssid = "VV6VG"; //replace this with your WiFi network name
const char* password = "33NG8DSNNY4ZKG4Z"; //replace this with your WiFi network password
IPAddress broadcastIp;
WiFiUDP udp;

void setup()
{
  delay(1000);
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());

  // set broadcast and gateway ip
  broadcastIp = ~WiFi.subnetMask() | WiFi.gatewayIP();
}

void loop() {
  // broadcast udp package
  udp.beginPacket(broadcastIp, 5005);
  udp.write("{ \"sensor\" : \"esp8266\", \"value\": \"hello from esp8266\" }");
  Serial.println("Writing Value");
  udp.endPacket();

  // wait 10 seconds
  delay(10000);

}
