/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include "RestClient.h"
#include <DallasTemperature.h>

const char* ssid     = "MyWifi";
const char* password = "passwifi";

RestClient client = RestClient("insty.io", 8080);
OneWire oneWire(D6);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  delay(100);
  //client.setFingerprint("14 D1 51 FA 47 76 91 05 F4 D2 D2 A1 A6 5F D5 7A 8F B7 82 2A");
  client.setContentType("application/json");
  client.begin(ssid, password);
  sensors.begin();
}


void loop() {
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));
  String temp = String(sensors.getTempCByIndex(0));
  String body = "{\"researchId\":\"5a7057389d71464f6f843006\",\"invitationKey\":\"\",\"fillType\":\"ANONYMOUS\",\"anonymousHash\":\"MzAwMDAzMDA2\",\"socketHost\":\"https://insty.io\",\"NUMBER_5a70576d9d71464f6f84301e\":\"" + temp + "\",\"TEXT_5a7057789d71464f6f843027\":\"Gdańsk\"}";
  int body_len = body.length() + 1;
  
  char char_body[body_len];
  body.toCharArray(char_body, body_len);
  
  String response = "";
  int statusCode = client.post("/research-fill-add", char_body, &response);
  Serial.println(response);
  Serial.println(statusCode);
  delay(900000);
}



