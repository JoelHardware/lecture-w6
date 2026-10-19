// ECSE3038 - Week 6, Lecture 1: the ESP32 starts.
// Starter: blink an LED and say hello over Serial.
// Tonight you add a Wi-Fi connection (Part 2) and a first HTTP request (Part 3).
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Which Wi-Fi network to join.
// Real board: put your network in include/secrets.h (copy secrets.h.example).
// No secrets.h: the simulator's open network, Wokwi-GUEST, on channel 6.
#if __has_include("secrets.h")
#include "secrets.h"
#else
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6
#endif

const unsigned long WIFI_TIMEOUT_MS = 15000;  // 15 seconds

const int LED_PIN = 2;   // the LED on GPIO 2

// Part 2: connectWiFi() goes here.
bool connectWiFi() {
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - start > WIFI_TIMEOUT_MS) {
      Serial.println("No Wi-Fi after 15 s.");
      return false;
    }
    delay(250);
    Serial.print(".");
  }
  Serial.println(" connected");
  Serial.print("IP address:  ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  return true;
}  
// Part 3: firstGet() goes here.

void firstGet() {
  HTTPClient http;
  http.begin("http://httpbin.org/get");
  int status = http.GET();
  Serial.print("Status: ");
  Serial.println(status);
  if (status > 0) Serial.println(http.getString());
  http.end();
}

void setup() {
  Serial.begin(115200);   // must match monitor_speed in platformio.ini
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Hello from the ESP32");

  connectWiFi();
  firstGet();
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
