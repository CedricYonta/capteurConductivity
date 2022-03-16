/*
  Titre      : alerteFuiteEau
  Auteur     : Cedric Yonta
  Date       : 16/03/2022
  Description: declanche la pompe à eau en cas de fuite d'eau
  Version    : 0.0.1
  Sources : https://wiki.dfrobot.com/Conductivity_Switch_Sensor_SKU__SEN0223
*/


#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"

int ledPin = 2;
int inputPin = 4;
volatile int counter = 0;
int PreviousCounter = 0;
bool ledstate  = false;


void count() {
  counter++;
}





void setup() {
  wifiConnect();                  //Branchement au réseau WIFI
    MQTTConnect();     

  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(inputPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(inputPin), count, HIGH );
  
}

void loop() {


int  pinValue=digitalRead(inputPin);
  if (counter > PreviousCounter )
    {
      Serial.println(counter);
      digitalWrite(ledPin, pinValue);
      
    }

appendPayload("pompestate", pinValue);
sendPayload();    
  
}
