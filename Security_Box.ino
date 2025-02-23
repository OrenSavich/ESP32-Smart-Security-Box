/*
 * 
 * Aquiring and Manifesting Sensoric Data
 * 
  Security Box

This sketch is designed to monitor a smart home environment using an ESP32.
It reads data from a DHT22 sensor for temperature and humidity,
a microphone for noise levels, and controls a LED strip and speaker based on the sensor readings.
The system can be remotely controlled via the Blynk app.

  The circuit:
  * DHT22 sensor attached to pin 16
  * Microphone module attached to pin 34 (analog input)
  * LED strip (Neopixel) attached to pin 18
  * Speaker attached to pin 26

  Video link: https://www.youtube.com/watch?v=JnvoE2-8a28
  Created By:
  Oren Savich 207610668
  Rotem Peled 206463572
*/

#define BLYNK_TEMPLATE_ID           "TMPL6dYY_ps9I"
#define BLYNK_TEMPLATE_NAME         "Smart Home Monitor"
#define BLYNK_AUTH_TOKEN            "e7ksGpMNFkDH76EaV94XtTOZec7w7Zvi"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h> // Include the Adafruit Unified Sensor library

char ssid[] = "RUNI-Wireless"; // Replace with your WiFi SSID
char pass[] = ""; // Replace with your WiFi Password

//char ssid[] = "Savich"; // Replace with your WiFi SSID
//char pass[] = "0509112343"; // Replace with your WiFi Password

#define DHTPIN 16
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define SPEAKER_PIN 26  // Define the pin for the speaker
#define LED_PIN 18      // Define the pin for the LED strip
#define NUM_LEDS 12     // Number of LEDs in the strip
#define MIC_PIN 34      // Define the pin for the microphone module

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

BlynkTimer timer;

int currentMode = 0;
bool modeChanged = false;

void sendSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int noiseLevel = analogRead(MIC_PIN); // Read the analog value from the microphone
  
  // Debugging: Print sensor values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Noise Level: ");
  Serial.println(noiseLevel);
  
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V3, noiseLevel);
}

void playSound(int frequency, int duration) {
  tone(SPEAKER_PIN, frequency, duration);
  delay(duration);
  noTone(SPEAKER_PIN);
}

void setLEDColor(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

BLYNK_WRITE(V4) {
  int mode = param.asInt();
  if (mode != currentMode) {
    currentMode = mode;
    modeChanged = true;
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  timer.setInterval(1000L, sendSensorData); // Call sendSensorData every 1 second
}

void loop() {
  Blynk.run();
  timer.run();

  if (modeChanged) {
    modeChanged = false;
    switch (currentMode) {
      case 0:
        // Do Nothing
        Serial.println("Mode: Do Nothing");
        setLEDColor(strip.Color(0, 0, 0)); // Turn off the lights
        noTone(SPEAKER_PIN); // Ensure the speaker is off
        break;
      case 1:
        // Something Suspicious - Let's Check
        Serial.println("Mode: Something Suspicious - Let's Check");
        setLEDColor(strip.Color(255, 255, 255)); // White light 
        break;
      case 2:
        // Something is Definitely Happening - Let's Do Something
        Serial.println("Mode: Something is Definitely Happening - Let's Do Something");
        setLEDColor(strip.Color(255, 0, 0)); // Red light
        break;
      case 3:
        // This is an Emergency - Call Help
        Serial.println("Mode: This is an Emergency - Call Help");
        break;
    }
  }

  switch (currentMode) {
    case 2:
      // Something is Definitely Happening - Let's Do Something
      for (int i = 0; i < 3; i++) {
        playSound(2000, 500); // Alarm sound
        delay(500);
      }
      break;
    case 3:
      // This is an Emergency - Call Help
      for (int i = 0; i < 5; i++) {
        playSound(3000, 200); // Crazy alarm sound
        if(i % 2 == 0) {
          setLEDColor(strip.Color(255, 0, 0)); // Red light
        } else {
          setLEDColor(strip.Color(0, 0, 255)); // Blue light
        }
        delay(200);
      }
      break;
  }
}
