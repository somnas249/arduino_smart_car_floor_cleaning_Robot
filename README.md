# Arduino Smart Car Floor‑Cleaning Robot

A compact Arduino‑powered floor‑cleaning robot chassis with Bluetooth manual‑drive and ultrasonic‑servo autonomous obstacle‑avoidance, ready to carry a brush or mop attachment for automated home cleaning.

---

## 🔧 Hardware

- **Controller:** Arduino Uno (or compatible)  
- **Motor Driver:** Adafruit Motor Shield V1 (AFMotor library)  
- **Motors & Chassis:** 4× DC motors + wheel chassis  
- **Obstacle Sensor:** HC‑SR04 ultrasonic sensor on SG90 servo “head”  
- **Bluetooth:** HC‑05/HC‑06 module for remote commands  
- **Power:** Separate battery pack for motors + USB power for Arduino

---

## 💾 Software

- **IDE:** Arduino IDE (C/C++)  
- **Libraries:**  
  - `AFMotor` for DC motor control  
  - `NewPing` for ultrasonic distance readings  
  - `Servo` for servo positioning  

- **Main Sketch:** `arduino-smart-car-obstacle-avoidance.ino`

---

## 🚀 Features

1. **Manual Mode (Bluetooth):**  
   - `1` → Forward  
   - `2` → Backward  
   - `3` → Turn right  
   - `4` → Turn left  
   - `S` or `A` → Stop  

2. **Autonomous Obstacle Avoidance:**  
   - Continuous pinging; stops and “looks” left/right when an object is within 20 cm  
   - Chooses the direction with more clearance  

3. **Cleaning Ready:**  
   - Chassis designed to mount a brush, mop or lightweight vacuum module  

---

## ⚙️ Setup & Usage

1. **Clone the repo**  
   ```bash
   git clone https://github.com/somnas249/arduino_smart_car_floor_cleaning_Robot.git
   cd arduino_smart_car_floor_cleaning_Robot
