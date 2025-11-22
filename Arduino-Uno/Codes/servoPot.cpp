#include <Arduino.h>
#include <Servo.h>

const int pinServo = 7;
const int pinPotenciometro = A0;

Servo servo1;


void setup() {
  servo1.attach(pinServo);
  pinMode(pinPotenciometro, INPUT);
  Serial.begin(9600);
}

void loop() {
  int lido = analogRead(pinPotenciometro);
  byte angle = map(lido, 0, 1023, 0, 179);

  servo1.write(angle);

  Serial.print("Pino: ");
  Serial.print(lido);
  Serial.print(" Ângulo: ");
  Serial.println(angle);

  delay(15);
  
}