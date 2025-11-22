#include <Arduino.h>
#include <util/atomic.h> // For the ATOMIC_BLOCK macro

// Arduino Uno ↔ Driver BTS7960
// Motor: 12V, Stall Current: ~ 5.5 A, No-Load Current: 0.2 A
// Pololu DC Motor: 330 MAX RPM; 30:1 Reduction; 64 Encoder CPR (Full Quadrature)

// Pin definitions
#define PIN_R_PWM 10
#define  PIN_L_PWM 9
#define PIN_R_EN 7
#define PIN_L_EN 6
#define ENCA 2 // YELLOW
#define ENCB 3 // WHITE

volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/

void setMotor(int dir, int pwmVal){
  if(dir == 1 and 0 < pwmVal <= 255){
    analogWrite(PIN_R_PWM, pwmVal);
    analogWrite(PIN_L_PWM, 0);
    digitalWrite(PIN_R_EN, HIGH);
    digitalWrite(PIN_L_EN, HIGH);
  }
  else if(dir == -1 and 0 < pwmVal <= 255){
    analogWrite(PIN_R_PWM, 0);
    analogWrite(PIN_L_PWM, pwmVal);
    digitalWrite(PIN_R_EN, HIGH);
    digitalWrite(PIN_L_EN, HIGH);
  }
  else if(pwmVal == 0){
    analogWrite(PIN_R_PWM, 0);
    analogWrite(PIN_L_PWM, 0);
    digitalWrite(PIN_R_EN, LOW);
    digitalWrite(PIN_L_EN, LOW);
  }
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}

void setup() {
  Serial.begin(9600);
  
  // Setup control pins
  pinMode(PIN_R_PWM, OUTPUT);
  pinMode(PIN_L_PWM, OUTPUT);
  pinMode(PIN_R_EN, OUTPUT);
  pinMode(PIN_L_EN, OUTPUT);

  // Setup encoder pins
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
}

void loop() {
  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos = 0; 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi;
  }
  
  // Forward
  setMotor(1, 25);
  delay(500);
  Serial.println(pos);
  
  // Reverse
  setMotor(-1, 25);
  delay(500);
  Serial.println(pos);
  
  // Stop
  setMotor(1, 0);
  delay(500);
  Serial.println(pos);
}
