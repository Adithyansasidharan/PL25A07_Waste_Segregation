/*
 * Project ID: PL25A07
 * Project Name: Waste Segregation
 * Description: Automated system for segregating Plastic, Glass, Paper, and Metal.
 * Hardware: Arduino Uno, 2x SG90 Servos.
 */

#include <Servo.h>

Servo diskServo; 
Servo lidServo;

// --- CONFIGURATION ---
const int diskPin = 9;   // Selector Disk
const int lidPin = 10;   // Dustbin Lid

// --- ANGLES (Calibrated for SG90) ---
// Sequence: Plastic -> Glass -> Paper -> Metal
const int posPlastic = 0;
const int posGlass = 60;
const int posPaper = 120;
const int posMetal = 175; 

const int lidClosed = 0; 
const int lidOpen = 90; 

void setup() {
  Serial.begin(9600);
  
  diskServo.attach(diskPin);
  lidServo.attach(lidPin);

  // Initialize System
  diskServo.write(posPlastic);
  lidServo.write(lidClosed);
  
  Serial.println("PL25A07 Waste Segregation System Initialized.");
  Serial.println("Ready for input: plastic, glass, paper, metal");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();        
    command.toLowerCase(); 

    int targetAngle = -1;

    if (command == "plastic") targetAngle = posPlastic;
    else if (command == "glass") targetAngle = posGlass;
    else if (command == "paper") targetAngle = posPaper;
    else if (command == "metal") targetAngle = posMetal;

    if (targetAngle != -1) {
      // 1. Align Selector Disk
      diskServo.write(targetAngle);
      delay(800); 

      // 2. Open Lid
      lidServo.write(lidOpen);
      delay(3000); 

      // 3. Close Lid
      lidServo.write(lidClosed);
    }
  }
}
