# 🚀 Password-Protected Motor Control System

## 📋 Overview
This project implements a **password-protected system** for controlling motors using an AVR microcontroller. It enhances security with password authentication, followed by user-friendly control options for both **DC motors** and **stepper motors**.

### 🌟 Key Features:
- 🔒 **Password Authentication**: Secure the system with a 4-digit password.
- ⚙️ **Motor Control**: Options to run a DC motor in Clockwise (CW) or Counterclockwise (CCW) directions.
- 🌀 **Stepper Motor Control**: Set angle, direction, and speed for stepper motor operation.
- 🖥️ **LCD Display**: Real-time feedback and user prompts on a 16x2 LCD.
- 🎛️ **Keypad Input**: Seamless interaction using a 4x4 keypad for password and command inputs.
- 🚫 **Access Limit**: 3 attempts to input the correct password before the system locks out.

---

## 🧰 Components

| Component                | Description                      |
| ------------------------ | --------------------------------- |
| **Microcontroller**       | AVR (e.g., ATmega32)              |
| **Keypad**                | 4x4 matrix for user input         |
| **LCD**                   | 16x2 display for system messages  |
| **DC Motor**              | Controlled through H-Bridge       |
| **Stepper Motor**         | Stepper driver to manage movement |
| **Motor Drivers**         | H-Bridge or stepper motor driver  |

---

## 🛠️ Functionality

### 🔑 Password Input
- The user is prompted to enter a 4-digit password, with each digit masked for security.
- A correct password grants access to the motor control menu, while a wrong password triggers retry prompts.
  
### 🔄 Motor Control Menu
- **DC Motor Control**: Select between CW and CCW options using the keypad.
- **Stepper Motor Control**: Input angle (0°-360°), direction (CW/CCW), and speed (2-10 units).
  
### ❌ Failure Actions
- Users get **3 trials** to input the correct password. Upon failure, the system locks out and displays an "Access Denied" message.

---

## 🚀 Getting Started

### ⚙️ Hardware Setup
1. **Microcontroller**: AVR (ATmega32 or similar).
2. **Connections**: Wire the keypad, LCD, and motor driver circuits to the microcontroller.
3. **Power Supply**: Ensure both the microcontroller and motor drivers are powered correctly.

### 💻 Software Instructions
1. **Clone the repository** and open the project in an AVR-compatible IDE (e.g., Atmel Studio).
2. **Compile the code** and upload it to the microcontroller using a programmer.
3. Once powered on, the system will prompt the user to enter a password on the LCD.
4. Follow on-screen instructions to control the motors.

### 🧑‍💻 Keypad Controls:
- **Password Input**: Enter a 4-digit password using numeric keys.
- **Motor Menu**: Select motor control options:
  - Press `1` to run the **DC Motor** (CW/CCW).
  - Press `2` to run the **Stepper Motor**.
  - Press `3` to **Exit** and return to the password prompt.

---

## 🔧 Customization

### 🎨 **Password**: 
The default password is set to `1234`. To change it, simply modify the line in `main.c`:
```c
#define PASSWORD 1234
🔢 Trial Limit:
You can modify the number of allowed password attempts by changing the following line:

c
Copy code
#define MAX_TRIALS 3
⚙️ Stepper Motor Settings:
The angle, direction, and speed input for the stepper motor can be customized within the RunStepperMotor function.

🔮 Future Enhancements
Here are some ideas for improving the system:

Password Persistence: Store the password in EEPROM for non-volatile storage.
User-Friendly Configuration: Implement a menu for changing the password via the keypad.
Advanced Motor Control: Add speed control features for the DC motor.
👨‍💻 Author
Developed by Ahmed Mohamed Nageeb 💡
Feel free to reach out for collaboration or feedback! 😄

🛡️ License
All rights reserved. © 2024

markdown
Copy code

### Key Changes:
- **Visual Enhancements**: Added emojis and icons to make the document more engaging.
- **Professional Language**: Made the tone a bit more polished and concise.
- **Color-Coded Section Headers**: Not directly possible in markdown, but you can add this in rendered markdown viewers or platforms that support styled markdown (like GitHub, Notion, etc.).


















