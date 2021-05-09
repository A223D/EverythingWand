#include <WiFi.h>
#include <WiFiMulti.h>
#include "FirebaseESP32.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>


FirebaseData firebaseData;
WiFiMulti WiFiMulti;

#define led 2
#define button1 27
#define button2 23
#define button3 19
#define THRESH 17.00
float oldX = 0, oldY = 0, oldZ = 0;
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

int gateVal = 0;

const char* ssid     = "TestArduino";
const char* password = "abcdefghi";
#define FIREBASE_HOST "https://everythingwand-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "CV2k6Amuz1QdnclSfl06yGWc3IlA4Q35AV4soEuV"
static bool hasWifi = false;


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  Serial.begin(9600);
  Serial.println("Connecting to WiFi...");
  if (!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  hasWifi = true;
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t event;
  accel.getEvent(&event);
  if (digitalRead(button1)) {
    //pizza order
    Serial.println("Button 1 was pressed");
    digitalWrite(led, HIGH);
    bool secondButtonPressed = false;
    delay(500);
    while (!secondButtonPressed) {
      if (digitalRead(button1)) {
        secondButtonPressed = true;
        Serial.println("Button 1 was pressed again");
        Firebase.setInt(firebaseData, "/Attribute", 1);
      } else if (digitalRead(button2)) {
        secondButtonPressed = true;
        Serial.println("Button 2 was pressed again");
        Firebase.setInt(firebaseData, "/Attribute", 2);
      } else if (digitalRead(button3)) {
        secondButtonPressed = true;
        Serial.println("Button 3 was pressed again");
        Firebase.setInt(firebaseData, "/Attribute", 3);
      }
    }

    Firebase.setInt(firebaseData, "/Command", 1);
    digitalWrite(led, LOW);

  } else if (digitalRead(button2)) {
    //sonos
    Serial.println("Button 2 was pressed");
    digitalWrite(led, HIGH);
    Firebase.setInt(firebaseData, "/Command", 2);
    digitalWrite(led, LOW);
  } else if (digitalRead(button3)) {
    //netflix
    Serial.println("Button 3 was pressed");
    digitalWrite(led, HIGH);
    bool secondButtonPressed = false;
    delay(500);
    while (!secondButtonPressed) {
      if (digitalRead(button1)) {
        secondButtonPressed = true;
        Serial.println("Button 1 was pressed again");
        Firebase.setInt(firebaseData, "/Attribute", 1);
      } else if (digitalRead(button2)) {
        secondButtonPressed = true;
        Serial.println("Button 2 was pressed again");
        Firebase.setInt(firebaseData, "/Attribute", 2);
      } else if (digitalRead(button3)) {
        secondButtonPressed = true;
        Serial.println("Button 3 was pressed again");
        Firebase.setInt(firebaseData, "/Attribute", 3);
      }
    }
    Firebase.setInt(firebaseData, "/Command", 3);
    digitalWrite(led, LOW);
  } else if (abs(event.acceleration.x - oldX) > THRESH || abs(event.acceleration.y - oldY) > THRESH || abs(event.acceleration.z - oldZ) > THRESH) {
    //text boss
    digitalWrite(led, HIGH);
    Firebase.setInt(firebaseData, "/Command", 0);
    digitalWrite(led, LOW);
  }
  oldX = event.acceleration.x;
  oldY = event.acceleration.y;
  oldZ = event.acceleration.z;
  delay(10);

}
