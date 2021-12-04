#access switching interface through firebase console

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "*******************"                         // the project name address from firebase id
#define FIREBASE_AUTH "********************"            // the secret key generated from firebase
#define WIFI_SSID "*********"                                           // input your home or public wifi name 
#define WIFI_PASSWORD "***********"

String fireStatus;

void setup()
{
  Serial.begin(9600);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(500);
}

void loop()
{
  fireStatus = Firebase.getString("STATUS");                                      // get ld status input from firebase
  Serial.println(fireStatus);
  delay(2000);
}
