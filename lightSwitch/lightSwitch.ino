#include <Servo.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include "FirebaseESP32.h"


FirebaseData firebaseData;
WiFiMulti WiFiMulti;
#define led 2

Servo onServo;
Servo offServo;

const char* ssid     = "MySSID";
const char* password = "MyPass";
#define FIREBASE_HOST "https://everythingwand-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "MyAuth"
static bool hasWifi = false;



void streamCallback(StreamData data)
{
  digitalWrite(led, HIGH);
  Serial.println("Stream Data1 available...");
  Serial.println("STREAM PATH: " + data.streamPath());
  Serial.println("EVENT PATH: " + data.dataPath());
  Serial.println("DATA TYPE: " + data.dataType());
  Serial.println("EVENT TYPE: " + data.eventType());
  Serial.print("VALUE: ");
  Serial.println(data.intData()); //see addons/RTDBHelper.h
  Serial.println();

  if (data.intData() == 1) {
    onServo.write(180);
    delay(1000);
    onServo.write(0);
  } else if (data.intData() == 0) {
    offServo.write(180);
    delay(1000);
    offServo.write(0);
  }
  digitalWrite(led, LOW);
}

void streamTimeoutCallback(bool timeout)
{
  if (timeout)
  {
    Serial.println();
    Serial.println("Stream timeout, resume streaming...");
    Serial.println();
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  onServo.attach(13);
  offServo.attach(12);
  Serial.begin(9600);
  Serial.println("Connecting to WiFi...");
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

  if (!Firebase.beginStream(firebaseData, "/GateVal"))
  {
    Serial.println("------------------------------------");
    Serial.println("Can't begin stream connection...");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  Firebase.setStreamCallback(firebaseData, streamCallback, streamTimeoutCallback);


}

void loop() {
  Serial.println("All good to go");
  // put your main code here, to run repeatedly:
  //  if (Firebase.getInt(firebaseData, "/Command")) {
  //
  //    if (firebaseData.dataType() == "int") {
  //      Serial.println(firebaseData.intData());
  //      myservo.write(firebaseData.intData());
  //    }
  //
  //  } else {
  //    Serial.println(firebaseData.errorReason());
  //  }

  while (1) {
    delay(1000);
  }

}
