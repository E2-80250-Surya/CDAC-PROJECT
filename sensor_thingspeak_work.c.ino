#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>

#define RX_PIN D2  // Define the RX pin
#define TX_PIN D1  // Define the TX pin

DHT dht(D5, DHT11);
SoftwareSerial uart(RX_PIN, TX_PIN);  // Create a SoftwareSerial object

WiFiClient client;

const char *ssid = "Ronit";
const char *password = "ronitp2001";
long myChannelNumber = 2425307;
const char myWriteAPIKey[] = "G1P0W3ZTL1MHZEZR";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  uart.begin(9600);  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println("WiFi is connected!");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  int receivedChar
  if (uart.available()) {  // Check if data is available to read from UART
    int receivedChar = uart.read();  // Read the incoming byte
    //Serial.print("Received: ");
    Serial.print(receivedChar);  // Print the received character to the serial monitor
    //Serial.println();
  
  }

  // if (Serial.available()) {  // Check if data is available to read from serial monitor
  //   char sendData = Serial.read();  // Read the incoming byte from serial monitor
  //   uart.write(sendData);  // Send the data over UART
  // }
  ThingSpeak.writeField(myChannelNumber, 1, receivedChar, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, receivedChar, myWriteAPIKey);
  delay(2000);
}