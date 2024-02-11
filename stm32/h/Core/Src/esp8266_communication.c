/*
 * esp8266_communication.c
 *
 *  Created on: Feb 6, 2024
 *      Author: surya
 */


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Replace with your Wi-Fi credentials
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// Replace with your ThingSpeak MQTT broker details
const char* mqttServer = "mqtt.thingspeak.com";
const int mqttPort = 1883;
const char* mqttUser = "YourMQTTUser";
const char* mqttPassword = "YourMQTTPassword";

WiFiClient espClient;
PubSubClient client(espClient);

const int LM35_PIN = A0;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected");

  // Set MQTT server and port
  client.setServer(mqttServer, mqttPort);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read temperature from LM35 sensor
  float temperature = readTemperature();

  // Publish temperature data to ThingSpeak
  publishToThingSpeak(temperature);

  delay(60000); // Publish temperature every minute
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

float readTemperature() {
  int sensorValue = analogRead(LM35_PIN);
  float millivolts = sensorValue * (3300.0 / 4095.0);
  float temperatureC = millivolts / 10.0;
  return temperatureC;
}

void publishToThingSpeak(float temperature) {
  char payload[50];
  sprintf(payload, "field1=%.2f", temperature);

  if (client.publish("channels/your_channel_id/publish/fields/field1/api_key", payload)) {
    Serial.println("Publish successful");
  } else {
    Serial.println("Publish failed");
  }
}
