#include <Arduino.h>

// Code to use push button

const int buttonPin = 8;
const int ledPin = 13;

void setup(){
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop(){
  Serial.print("Nível: ");
  Serial.println(digitalRead(buttonPin));
  delay(10);

  if(digitalRead(buttonPin) == LOW){
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }
}
