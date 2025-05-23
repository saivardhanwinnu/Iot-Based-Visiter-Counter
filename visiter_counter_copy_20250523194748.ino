#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>
#include<ThingSpeak.h>
// Pin configuration for the LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(D5, D6, D7, D8, D1, D2);

#define sensorPin1 D0
#define sensorPin2 D3
#define ledpin D4
int sensorState1 = 0;
int sensorState2 = 0;
int count = 0;
int ready_entrer = 0;
int ready_sortir = 0;
const char *ssid = "OPPO A12";
const char *password = "sanjaychandra";
const char *thingSpeakApiKey = "B0ZBRU96IXP68CNO";
const char *thingSpeakURL = "api.thingspeak.com";
const String postUrl = "/update?api_key=" + String(thingSpeakApiKey) + "&field1=";

WiFiClient client;
void setup() {
  pinMode(sensorPin1, INPUT_PULLUP);
  pinMode(sensorPin2, INPUT_PULLUP);
  pinMode(ledpin, OUTPUT);

  lcd.begin(16, 2);  // initialize the LCD
  lcd.setCursor(4, 0);
  lcd.print("COUNTER");
  lcd.setCursor(0, 1);
  lcd.print("No Visitors     ");
  Serial.begin(115200);
  delay(1000);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  sensorState1 = digitalRead(sensorPin1);
  sensorState2 = digitalRead(sensorPin2);

  if (sensorState1 == LOW) {
    ready_entrer = 1;
  } else if (sensorState2 == LOW) {
    ready_sortir = 1;
  }
  if (ready_entrer == 1 && sensorState2 == LOW) {
    count++;
    ready_entrer = 0;
    ready_sortir = 0;
    delay(3000);
  } else if (ready_sortir == 1 && sensorState1 == LOW && count > 0)  {
    count--;
    ready_sortir = 0;
    ready_entrer = 0;
    delay(3000);
  }

  if (count > 0){
    digitalWrite(ledpin,HIGH);
  }
  else{
    digitalWrite(ledpin,LOW);
  }
  if (count <= 0) {
    lcd.setCursor(0, 1);
    lcd.print("No visitors    ");
     sendDataToThingSpeak(count, ledpin);
  } 
  else if (count > 0 && count < 10) {
    lcd.setCursor(0, 1);
    lcd.print("Visitors:   ");
    lcd.setCursor(12, 1);
    lcd.print(count);
    lcd.setCursor(13, 1);
    lcd.print("  ");
    sendDataToThingSpeak(count, ledpin);
  } 
  else {
    lcd.setCursor(0, 1);
    lcd.print("Visitors:   ");
    lcd.setCursor(12, 1);
    lcd.print(count);
  }
}
void sendDataToThingSpeak(int data, int ledPin) {
  if (client.connect(thingSpeakURL, 80)) {
    String postString = postUrl + String(data) + "&field2=" + String(digitalRead(ledPin));
    client.print(String("GET ") + postString + " HTTP/1.1\r\n" +
                 "Host: " + thingSpeakURL + "\r\n" +
                 "Connection: close\r\n\r\n");
    Serial.println("Sending data to ThingSpeak...");
    client.stop();
  } else {
    Serial.println("Failed to connect to ThingSpeak");
  }
}
