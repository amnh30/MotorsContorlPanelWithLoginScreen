#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/delay.h>
#define C_CPU 8000000UL

/* MCAL Layer Include */
#include "MDIO/MDIO_Interface.h"

/* HAL Layer Include */
#include "HLCD/HLCD_interface.h"
#include "HKPD_interface.h"
#include <stdlib.h>

/* Constants */
#define MAX_TRIALS 3
#define PASSWORD 1234 // Define your password as a number

/* Function Prototypes */
void SystemInit(void);
void PasswordPrompt(void);
u32 GetPasswordInput(void);
u8 ValidatePassword(u32 enteredPassword);
void SuccessAction(void);
void FailureAction(u8 trials);
void MotorMenu(void);
void RunDCMotor(void);
void RunStepperMotor(void);

/* Main function */
int main(void) {
    u8 trials = 0;

    // Initialize system components
    SystemInit();

    while (trials < MAX_TRIALS) {
        PasswordPrompt();
        u32 enteredPassword = GetPasswordInput();

        if (ValidatePassword(enteredPassword)) {
            SuccessAction();
        } else {
            trials++;
            FailureAction(trials);
        }
    }

    // After exceeding MAX_TRIALS
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Access Denied");
    MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_7, MDIO_HIGH);
    while (1); // Lock out or redirect
}

/* Function Definitions */

// Initializes the system components like LCD and keypad
void SystemInit(void) {
    MDIO_IntialPins();
    HLCD_VoidLcdIint();
    HLCD_VoidLcdClear();
}

// Prompts the user to enter a password
void PasswordPrompt(void) {
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Enter Password:");
    HLCD_VoidSetCurser(HLCD_LINE_2, 0);
}

// Collects the entered password from the keypad
u32 GetPasswordInput(void) {
    u8 keyPressed = 0;
    u32 enteredPassword = 0;
    u8 passwordDigitCount = 0;

    while (passwordDigitCount < 5) { // Assuming a 4-digit password
        if (HKPD_u8GetPressedKey(&keyPressed) == STD_TYPE_OK) {
            _delay_ms(200);
            if (keyPressed != HKPD_NO_KEY_PRESSED) {
                // Handle numeric input (0-9)
                if (keyPressed >= '0' && keyPressed <= '9') {
                    enteredPassword = enteredPassword * 10 + (keyPressed - '0');
                    HLCD_VoidLcdWriteChar('*');
                    passwordDigitCount++;
                }
                // Handle clear key ('C')
                else if (keyPressed == '%') {
                    HLCD_VoidLcdClear();
                    enteredPassword = 0;
                    passwordDigitCount = 0;
                }

                _delay_ms(10); // Small delay for debouncing
                keyPressed = 0;
            }
        }
    }

    return enteredPassword;
}

// Validates the entered password against the stored password
u8 ValidatePassword(u32 enteredPassword) {
    return enteredPassword == PASSWORD;
}

// Actions performed on successful password entry
void SuccessAction(void) {
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Password Correct");
    HLCD_VoidSetCurser(HLCD_LINE_2, 0);
    HLCD_u8WriteStr("Welcome Ahmed");
    _delay_ms(2000);

    // After login, display the motor control menu
    MotorMenu();
}

// Displays the motor control menu after successful login
void MotorMenu(void) {
    u8 keyPressed = 0;

    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("1: DC Motor");
    HLCD_VoidSetCurser(HLCD_LINE_2, 0);
    HLCD_u8WriteStr("2: Stepper Motor");

    while (1) {
        if (HKPD_u8GetPressedKey(&keyPressed) == STD_TYPE_OK) {
            _delay_ms(200);
            if (keyPressed == '1') {
                RunDCMotor();
            } else if (keyPressed == '2') {
                RunStepperMotor();
            }

            _delay_ms(10);
            keyPressed = 0;
        }
    }
}

// Runs the DC Motor (implement motor control logic here)
void RunDCMotor(void) {
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Running DC Motor");
    // Set pin for DC motor control, e.g., turn on motor
    MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_0, MDIO_HIGH); // Assume motor connected to PORTB PIN0
    _delay_ms(5000); // Run the motor for 5 seconds
    MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_0, MDIO_LOW);  // Stop the motor

    HLCD_VoidLcdClear();
    MotorMenu(); // Go back to the motor menu
}

// Runs the Stepper Motor (implement stepper motor control logic here)
void RunStepperMotor(void) {
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Running Stepper");
    // Stepper motor control logic
    for (int i = 0; i < 100; i++) {
        // Assume motor steps are controlled by multiple pins, e.g., PORTB PIN1 to PIN4
        MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_1, MDIO_HIGH);
        _delay_ms(100);
        MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_1, MDIO_LOW);

        MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_2, MDIO_HIGH);
        _delay_ms(100);
        MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_2, MDIO_LOW);

        // Repeat for other pins (PIN3, PIN4) to step the motor
    }

    HLCD_VoidLcdClear();
    MotorMenu(); // Go back to the motor menu
}

// Actions performed on failed password entry
void FailureAction(u8 trials) {
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Wrong Password");
    HLCD_VoidSetCurser(HLCD_LINE_2, 0);
    HLCD_VoidLcdWriteInt(MAX_TRIALS - trials);
    HLCD_u8WriteStr(" Trials left");
    _delay_ms(2000); // Delay to show message
}
