#access switching interface using apds9960 gesture module
#interfacing arduino uno with apds9960

#include <SoftwareSerial.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin

SoftwareSerial mySerial(3, 4);
const int  rel1 = 8;
const int  rel2 = 9;
// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
int val123;
String serval;
void setup() {

  // Initialize Serial port
  Serial.begin(9600);
  delay(100);
  mySerial.begin(9600);
  delay(100);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));

  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
  pinMode(rel1, OUTPUT);
  pinMode(rel2, OUTPUT);
  delay(500);
}

void loop() {
  //Serial.println("Hello");
  if ( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }

  if (mySerial.available() > 0) {
    serval = mySerial.readString();
    Serial.println(serval);
    val123 = serval.toInt();
    if  (val123 == 1)
    {

      Serial.println("Relay 1 ON");
      digitalWrite(rel1, HIGH);
      delay(2000);

    }

    if  (val123 == 2)
    {

      Serial.println("Relay 1 OFF");
      digitalWrite(rel1, LOW);
      delay(2000);
    }

    if  (val123 == 3)
    {

      Serial.println("Relay 2 ON");
      digitalWrite(rel2, HIGH);
      delay(2000);

    }
    if  (val123 == 4)
    {

      Serial.println("Relay 2 OFF");
      digitalWrite(rel2, LOW);
      delay(2000);
    }
  }
}

void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture() {
  if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        digitalWrite(rel1, HIGH);
        delay(2000);
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        digitalWrite(rel1, LOW);
        delay(2000);
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        digitalWrite(rel2, HIGH);
        delay(2000);
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        digitalWrite(rel2, LOW);
        delay(2000);
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}
