# car-follower
I like to follow u around

This project is an Arduino-based autonomous robot that detects obstacles and moves in the direction where it senses the most open space. The robot uses an ultrasonic sensor mounted on a servo to scan left, center, and right, then moves well where the sensor detects it.

 Features:
- uses ultrasonic sensor and moves towards direction
- drives where senses
- 

 Hardware Requirements

List of Materials:
- Arduino Uno - Main microcontroller $7
- HC-SR04 Ultrasonic Sensor $6
- SG90 Micro Servo $8
- DC Motors (x2) $10
- Motor Driver(L298N or similar) $8
- Motor Battery - 7.4V-12V $6
- USB Cable $3

I bought this originally from this kit but then I replaced the esp32 it came with for an Arduino because the esp32 came with software preloaded on it that I could not quit figure out

Wiring List

 Left Motor A-  D8  controls: Motor direction control
 Left Motor B-  D9 controls: Motor direction control 
 Right Motor A- D10 : Motor direction control 
Right Motor B-  D11 : Motor direction control 
Left Motor PWM-  D5 : Speed control 
Right Motor PWM-  D6 : Speed control 
Ultrasonic TRIG-  D12 : Trigger pulse for sensor :
Ultrasonic ECHO- D13 : Echo pulse from sensor :
 Servo Signal-  D4 : Servo control  :


Motor Driver wirings;
Battery + (red): Motor Driver VCC / VM
Battery - (black): → Motor Driver GND
Arduino GND:  → Motor Driver GND (shared ground)
Arduino D8-D11:  → Motor Driver IN1-IN4
Arduino D5, D6: → Motor Driver ENA, ENB
Left Motor: → Motor Driver Output A
Right Motor: → Motor Driver Output B

Ultrasonic Sensor wiring: 
Sensor G (GND): Arduino GND
Sensor V (VCC):  Arduino 5V
Sensor T (TRIG):  Arduino D12
Sensor E (ECHO): Arduino D13


Servo Motor wiring:

Brown (GND): Arduino GND
Red (VCC):  Arduino 5V
Orange (PWM): Arduino D4


Software used: 
-vscode
-platformio
-json


Problems:
- Wheels don't move so I checked the motor battery connection and polarity.
- When the servo didn't rotate I verified the orange wire on D4, and checked 5V power 
- Ultrasonic shows 0cm I Checked TRIG (D12) and ECHO (D13) connections 
- When Arduino wonuldnt  upload I Checked USB cable and then verified the board with in Arduino uno and used platformio.ini 
- when the Sensor reads garbage I Move sensor away from electrical noise and then proceeded to check the wiring 

  Future work:

-  Add multiple ultrasonic sensors for 360° detection
-  Implement true "follow" behavior
  - Add line-following capability with IR sensors
-  Bluetooth remote control and wireless


Pictures: 
<img width="3072" height="4096" alt="robot" src="https://github.com/user-attachments/assets/a3971674-5f2b-4eda-b70b-e3899233f9d5" />

<img width="4284" height="5712" alt="IMG_8546 copy" src="https://github.com/user-attachments/assets/4c5c4db0-0d2f-4521-ad9b-de504b686561" />
<img width="4284" height="5712" alt="IMG_8538 copy" src="https://github.com/user-attachments/assets/3193552c-cdab-4c60-bb51-012738e2fb69" />

AI Usage: 
Used to debug and edit my code



