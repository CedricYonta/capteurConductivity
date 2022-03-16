/*
  Titre      : alerteFuiteEau
  Auteur     : Cedric Yonta
  Date       : 16/03/2022
  Description: declanche la pompe à eau en cas de fuite d'eau
  Version    : 0.0.1
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
  //digitalWrite(ledPin,HIGH);
  counter++;
}



void setup() {
  wifiConnect();                  //Branchement au réseau WIFI
    MQTTConnect();     

  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(inputPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(inputPin), count, RISING);
  //digitalWrite(ledPin,HIGH);
  delay(10000);
}

void loop() {
int  pinValue=digitalRead(inputPin);
  if(pinValue==HIGH){
    Serial.println(counter);
    digitalWrite(ledPin,HIGH);
  } else{
    Serial.println(counter);
    digitalWrite(ledPin,LOW);
  }

/*if (counter > PreviousCounter )
    {
      Serial.println(counter);
      digitalWrite(ledPin, ledstate);
      ledstate = !ledstate;
      PreviousCounter = counter;
    }*/

    
/*int val;
  val = digitalRead(inputPin);
  if (val== 1)
{
  digitalWrite(ledPin,HIGH);
}
else
{
  digitalWrite(ledPin,LOW);
}*/
appendPayload("pompestate", pinValue);
        
            sendPayload();    }
  
}