#include <WiFi.h>
#include "time.h"

// Configuration
const char* ssid     = "Debabrata1";
const char* password = "Password@123";

#define pirPin 12
#define ledPin 14
#define ldrPin 32

// PWM settings
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

// NTP Settings
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800; // For India (GMT+5:30)
const int   daylightOffset_sec = 0;

// Variables
int ldrValue = 0;
int brightness = 0;

// Timer Variables for 30-minute logging
unsigned long lastLogTime = 0;
const unsigned long logInterval = 1800000; // 30 minutes in milliseconds

void setup() {
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  // Pin Setups
  pinMode(pirPin, INPUT);
  pinMode(ldrPin, INPUT);
  ledcAttachChannel(ledPin, freq, resolution, ledChannel);
  
  Serial.println("System Online. Status will print every 30 minutes.");
}

void loop() {
  unsigned long currentMillis = millis();
  ldrValue = analogRead(ldrPin);
  int pirValue = digitalRead(pirPin); // Read the PIR sensor
  
  // BASE LOGIC: Ambient Light Level (LDR)
  if (ldrValue < 2000) {
    brightness = 0; 
  } 
  else if(ldrValue < 3000) {
    brightness = map(ldrValue, 2000, 3000, 40, 150); 
  } 
  else {
    brightness = map(ldrValue, 3000, 4095, 150, 255); 
  }

  // TIME-BASED OVERRIDE LOGIC (10:30 PM to 5:30 AM)
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    int hour = timeinfo.tm_hour; // 0-23
    int min = timeinfo.tm_min;   // 0-59

    // Check if the current time falls inside the late-night window
    bool isLateNight = ((hour == 22 && min >= 30) || (hour >= 23) || (hour <= 4) || (hour == 5 && min <= 30));

    //  60% power-saving mode 
    if (isLateNight && ldrValue >= 2000) {
      brightness = 153; // Force to 60% brightness (153 out of 255)
      
      // PIR SENSOR BOOST
      if (pirValue == HIGH) {
        brightness = 255; // Boost to 100% if motion is detected
      }
    }
  }

  // Apply the final calculated brightness to the LED
  ledcWrite(ledPin, brightness);

  // INTERVAL LOGGING: Check if 30 minutes have passed
  if (currentMillis - lastLogTime >= logInterval) {
    lastLogTime = currentMillis; // Reset timer

    Serial.println("\n--- [30 MIN STATUS] ---");
    printLocalTime();
    Serial.print("LDR Value: ");
    Serial.println(ldrValue);
    Serial.print("PIR Status: ");
    Serial.println(pirValue == HIGH ? "MOTION DETECTED" : "CLEAR");
    Serial.print("Current Brightness: ");
    Serial.println(brightness);
    Serial.println("-----------------------\n");
  }

  delay(500); // Small stability delay
}

// Function to print current time from NTP
void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}