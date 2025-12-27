# PL25A07 Waste Segregation System

**Project ID:** PL25A07
**Topic:** Automated Waste Segregation System
**Current Version:** v2.0 (Stepper Motor Upgrade)

## 📝 Project Overview
This is an automated system designed to classify and segregate waste into four categories: **Plastic, Glass, Paper, and Metal**.

The system accepts a waste type command via the Serial Monitor and physically rotates a selector disk to the correct bin using a high-precision **NEMA 17 Stepper Motor**. A secondary Servo motor operates the disposal lid.

## 🔄 Hardware Upgrade: Why Stepper Motor?
Initially, this project utilized a standard Servo motor for the selector disk. However, standard servos are mechanically limited to 180° rotation.
To achieve **full 360° rotation** and accommodate a circular bin layout, the selector mechanism was upgraded to a **NEMA 17 Stepper Motor** controlled by an **A4988 Driver**.
* **Microstepping:** Enabled for smoother and more precise movement.
* **Homing System:** Integrated a Limit Switch to automatically find the "Zero" position (Plastic) upon startup.

## 📂 Segregation Logic (Calibrated Steps)
The system uses calibrated step counts to align with the bins:

| Category | Step Position | Description |
| :--- | :--- | :--- |
| **Plastic** | 0 | Home Position (Reference) |
| **Glass** | 100 | ~90° Rotation |
| **Paper** | 200 | ~180° Rotation |
| **Metal** | 300 | ~270° Rotation |

## 🔌 Circuit Connections

| Component | Pin / Wiring | Function |
| :--- | :--- | :--- |
| **NEMA 17 STEP** | Arduino Pin 3 | Stepper Step Pulse |
| **NEMA 17 DIR** | Arduino Pin 2 | Stepper Direction Control |
| **Limit Switch** | Arduino Pin 7 | Homing Sensor (NO terminal) |
| **Lid Servo** | Arduino Pin 9 | Opens/Closes Bin Lid |
| **A4988 Power** | 12V DC | External Power for Motor |
| **Arduino Power** | USB / 5V | Logic Power |

## 🚀 How to Run
1.  **Power Up:** Connect the 12V power supply for the motor and the USB for the Arduino.
2.  **Auto-Homing:** The system will immediately rotate the disk backward until it hits the limit switch to find the "Zero" position.
3.  **Input:** Open Serial Monitor (Baud 9600).
4.  **Command:** Type `plastic`, `glass`, `paper`, or `metal`.
5.  **Action:** The disk rotates to the correct step count, the lid opens, waits 3 seconds, and closes.
