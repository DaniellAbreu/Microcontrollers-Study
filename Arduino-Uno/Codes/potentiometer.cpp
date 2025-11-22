#include <Arduino.h>

// Code: Testing Potentiometer with a LED;

// put function declarations here:
int potPin = A0;
int potValue = 0;
int brightness = 0;
int ledPin = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  potValue = analogRead(potPin);
  Serial.println(potValue);

  brightness = (255.0/1023.0) * potValue;
  analogWrite(ledPin, brightness);
}

// put function definitions here:
