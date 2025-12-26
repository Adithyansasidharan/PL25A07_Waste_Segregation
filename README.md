# PL25A07 Waste Segregation

**Project ID:** PL25A07
**Topic:** Waste Segregation System

## 📝 About the Project
This is an automated system that sorts waste into 4 categories: **Plastic, Glass, Paper, and Metal**.
It uses an Arduino and two servo motors. When you type the waste type in the computer, one motor selects the category and the other motor opens the bin lid.

## 📂 Waste Categories
1.  **Plastic**
2.  **Glass**
3.  **Paper**
4.  **Metal**

## 🔌 Circuit Connections

| Component | Pin | Function |
| :--- | :--- | :--- |
| **Servo 1 (Disk)** | Pin 9 | Rotates to point to the waste type |
| **Servo 2 (Lid)** | Pin 10 | Opens and closes the dustbin |
| **Power** | 5V | Powers both motors |
| **Ground** | GND | Common ground connection |

## 🚀 How to Use
1.  Connect the Arduino to your laptop.
2.  Upload the `PL25A07_Waste_Segregation.ino` code.
3.  Open the **Serial Monitor** in Arduino IDE.
4.  Type `plastic`, `glass`, `paper`, or `metal`.
5.  The motors will move to sort the waste automatically.

