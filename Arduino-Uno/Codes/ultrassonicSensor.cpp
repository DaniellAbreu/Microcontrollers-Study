#include <Arduino.h>

// Code to configure HC-RS04 Ultrassonic Sensor

long readUltrassonicDistance(int trigPin, int echoPin){
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);

  return (pulseIn(echoPin, HIGH) * 0.017);
}

const int trigPin = 7;
const int echoPin = 8;
const int ledPin = 10;

void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop(){
  long distance = readUltrassonicDistance(trigPin, echoPin);
    
  Serial.print("Distance: ");
  Serial.println(distance);
    
  if(distance < 20){
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }

  delay(60);
}