/*
 * Project ID: PL25A07
 * Project Title: Waste Segregation System
 * Hardware: Arduino Uno, NEMA 17 Stepper (A4988), SG90 Servo, Limit Switch
 *
 * --- WIRING MAP ---
 * NEMA 17 STEP Pin  -> Arduino Pin 3
 * NEMA 17 DIR Pin   -> Arduino Pin 2
 * Limit Switch (NO) -> Arduino Pin 7  (Common goes to GND)
 * Lid Servo Signal  -> Arduino Pin 9
 */

#include <Servo.h>

// --- PIN DEFINITIONS ---
const int stepPin = 3;        
const int dirPin = 2;         
const int limitSwitchPin = 7; 
const int servoPin = 9;       

Servo lidServo;

// --- CALIBRATED STEP COUNTS ---
// Updated based on user calibration
const int stepsPlastic = 0;   // Home
const int stepsGlass = 100;   
const int stepsPaper = 200;   
const int stepsMetal = 300;   

// Variable to track current position
int currentStepPosition = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("--- PL25A07 SYSTEM BOOT ---");

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(limitSwitchPin, INPUT_PULLUP); 

  lidServo.attach(servoPin);
  lidServo.write(0); // Close lid
  delay(500);

  // --- HOMING SEQUENCE ---
  Serial.println("Status: Homing...");
  digitalWrite(dirPin, HIGH); // Rotate Backward

  long startTime = millis();
  while (digitalRead(limitSwitchPin) == HIGH) {
    stepMotor(1); 
    delay(5);     
    
    if (millis() - startTime > 5000) { 
      Serial.println("ERROR: Homing Timeout!");
      break; 
    }
  }

  currentStepPosition = 0;
  Serial.println("Status: Homing Complete (Position 0).");
  Serial.println("READY. Type: plastic, glass, paper, metal");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();        
    command.toLowerCase(); 

    int targetSteps = -1;

    // Match command to your calibrated steps
    if (command == "plastic") targetSteps = stepsPlastic;
    else if (command == "glass") targetSteps = stepsGlass;
    else if (command == "paper") targetSteps = stepsPaper;
    else if (command == "metal") targetSteps = stepsMetal;

    if (targetSteps != -1) {
      Serial.print("Processing: ");
      Serial.println(command);

      // 1. Move Stepper
      moveToPosition(targetSteps);
      delay(500); 

      // 2. Open Lid
      Serial.println("Opening Lid...");
      lidServo.write(90); 
      delay(3000);        

      // 3. Close Lid
      Serial.println("Closing Lid...");
      lidServo.write(10);  
      
      Serial.println("--- Ready ---");
    } 
  }
}

// Moves motor to specific target step
void moveToPosition(int target) {
  int stepsToMove = target - currentStepPosition;

  if (stepsToMove > 0) {
    digitalWrite(dirPin, LOW); // Forward
  } else {
    digitalWrite(dirPin, HIGH); // Backward
    stepsToMove = -stepsToMove;
  }

  for (int i = 0; i < stepsToMove; i++) {
    stepMotor(1);
    delay(5); // Speed Control (Lower is faster)
  }

  currentStepPosition = target;
}

// Single step pulse
void stepMotor(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000); 
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000); 
  }
}
