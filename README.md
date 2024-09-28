# Password-Protected Motor Control System

## Description
This project implements a password-protected system for controlling motors using a microcontroller (AVR). The user is required to input a correct 4-digit password to gain access to motor control functionalities. Once logged in, the user can control a DC motor or a stepper motor through a simple menu displayed on an LCD.

### Features:
- **Password Authentication**: Users are required to enter a correct password to access motor controls.
- **Motor Control**: Options to run a DC motor in clockwise (CW) or counterclockwise (CCW) directions.
- **Stepper Motor Control**: Allows setting angle, direction (CW/CCW), and speed of the stepper motor.
- **LCD Display**: Provides real-time feedback and prompts for user inputs.
- **Keypad Input**: Users input passwords and motor commands via a keypad.
- **Trial Limit**: The user has up to 3 trials to input the correct password before access is denied.

## Components:
- **Microcontroller**: AVR (e.g., ATmega32)
- **Keypad**: 4x4 matrix keypad for input
- **LCD**: 16x2 LCD to display information
- **DC Motor and Stepper Motor**: For motor control demonstration
- **H-Bridge or Stepper Motor Driver**: To control motor directions and speed

## File Structure:
- `main.c`: The main code that handles password authentication and motor control logic.
- `MDIO_Interface.h`: Microcontroller's Digital Input/Output (DIO) interface for handling input/output pins.
- `HLCD_interface.h`: LCD interface for controlling the display.
- `HKPD_interface.h`: Keypad interface to handle user input.
- `HSTEPM_interface.h`: Stepper motor driver interface to control the stepper motor.

## Functionality Overview:

1. **Password Input**:  
   The system prompts the user to enter a 4-digit password via the keypad. Each digit is masked on the LCD display for security.
   
2. **Password Validation**:  
   If the password is correct, the system grants access to the motor control menu. The user has up to 3 attempts to enter the correct password.

3. **Motor Control Menu**:  
   - **DC Motor Control**: The user can choose to run the DC motor in either CW or CCW direction.
   - **Stepper Motor Control**: The user can set the angle, direction (CW/CCW), and speed of the stepper motor.

4. **Failure Action**:  
   If the user fails to enter the correct password after 3 attempts, the system will lock the user out and display an "Access Denied" message.

## Usage:

### Hardware Setup:
- Connect the keypad to the designated microcontroller pins.
- Connect the LCD to the microcontroller for display.
- Wire the DC motor or stepper motor with the necessary motor drivers.
- Ensure the microcontroller is powered and the motor drivers are connected to the motors.

### Software Instructions:
1. Clone the repository or download the project files.
2. Open the project in your preferred IDE for AVR programming (e.g., Atmel Studio).
3. Compile the code and upload it to the microcontroller.
4. After successful upload, the system will prompt for a password on the LCD.
5. Follow the on-screen instructions to control the motors.

### Keypad Operations:
- **Enter Password**: Input 4-digit password using the keypad.
- **Motor Menu**: Select motor control options using keys '1', '2', or '3'.
  - '1' - Run DC Motor (CW/CCW)
  - '2' - Run Stepper Motor
  - '3' - Exit to re-enter password

## Customization:
- **Password**: The default password is `1234`. You can change the password in the code by modifying the `#define PASSWORD` line.
- **Trial Limit**: The maximum number of trials is set to 3. You can change this by modifying `#define MAX_TRIALS`.
- **Stepper Motor Settings**: You can customize the angle, direction, and speed input handling for the stepper motor in the `RunStepperMotor` function.

## Future Improvements:
- Add functionality to store passwords in EEPROM for persistence.
- Implement a user-friendly configuration interface for changing passwords.
- Add more motor control features, such as speed control for the DC motor.

## Author
Developed by Ahmed Mohamed Nageeb

## License
All rights reserved. © 2024
