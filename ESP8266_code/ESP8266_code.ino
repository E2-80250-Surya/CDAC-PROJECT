#include <ESP8266WiFi.h>

const char* ssid = "Redmi 8";
const char* password = "9970641609";
const char* server = "api.thingspeak.com";
unsigned long channelID = 2436418;
String writeAPIKey = "XB2XYMN0LMZ0QOSY";

#define SENSOR A0
char str_sensor[10];

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(SENSOR, INPUT);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  
  int receivedChar;
  float myecg = analogRead(SENSOR);
  dtostrf(myecg, 4, 2, str_sensor);

  char str1[100];
  if (Serial.available()){
    Serial.readBytesUntil('\n',str1,50);
      String str = str1+String("&field3=")+String(str_sensor);
  // Send the data to ThingSpeak
      if (client.connect(server, 80)) {
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(str.length());
        client.print("\n\n");
        client.print(str);    
        Serial.println(str);
        Serial.println("Data sent to ThingSpeak");
      }
      client.stop();
}
}