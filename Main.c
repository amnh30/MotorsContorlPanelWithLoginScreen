#include "STD_Types.h"
#include "BIT_MATH.h"
#include <avr/delay.h>
#define C_CPU 8000000UL

/* MCAL Layer Include */
#include "MDIO/MDIO_Interface.h"

/* HAL Layer Include */
#include "HLCD/HLCD_interface.h"
#include "HKPD/HKPD_interface.h"
#include "HSTEPM/HSTEPM_interface.h"
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
u8 GetKeypadInput(void);

/* Main function */
int main(void)
{
    // Initialize system components
    SystemInit();
    u8 trials = 0;
    while (trials < MAX_TRIALS)
    {
        PasswordPrompt();
        u32 enteredPassword = GetPasswordInput();

        if (ValidatePassword(enteredPassword))
        {
            SuccessAction();
        }
        else
        {
            trials++;
            FailureAction(trials);
        }
    }

    // After exceeding MAX_TRIALS
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Access Denied");
    MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_7, MDIO_HIGH);
    while (1)
        ; // Lock out or redirect
}

/* Function Definitions */

// Initializes the system components like LCD and keypad
void SystemInit(void)
{
    MDIO_IntialPins();
    HLCD_VoidLcdIint();
    HLCD_VoidLcdClear();
}

// Prompts the user to enter a password
void PasswordPrompt(void)
{
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Enter Password:");
    HLCD_VoidSetCurser(HLCD_LINE_2, 0);
}

// Collects the entered password from the keypad
u32 GetPasswordInput(void)
{
    u8 keyPressed = 0;
    u32 enteredPassword = 0;
    u8 passwordDigitCount = 0;

    while (passwordDigitCount < 5) // Assuming a 4-digit password
    {
        if (HKPD_u8GetPressedKey(&keyPressed) == STD_TYPE_OK)
        {
            _delay_ms(200);
            if (keyPressed != HKPD_NO_KEY_PRESSED)
            {
                // Handle numeric input (0-9)
                if (keyPressed >= '0' && keyPressed <= '9')
                {
                    enteredPassword = enteredPassword * 10 + (keyPressed - '0');
                    HLCD_VoidLcdWriteChar('*');
                    passwordDigitCount++;
                }
                else if (keyPressed == '=')
                {
                    return enteredPassword;
                }
                // Handle clear key ('C')
                else if (keyPressed == '%')
                {
                    HLCD_VoidLcdClear();
                    HLCD_u8WriteStr("Enter Password:");
                    HLCD_VoidSetCurser(HLCD_LINE_2, 0);
                    enteredPassword = 0;
                    passwordDigitCount = 0;
                }

                _delay_ms(10); // Small delay for debouncing
                keyPressed = 0;
            }
        }
    }
}

// Validates the entered password against the stored password
u8 ValidatePassword(u32 enteredPassword)
{
    return enteredPassword == PASSWORD;
}

// Actions performed on successful password entry
void SuccessAction(void)
{
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Password Correct");
    HLCD_VoidSetCurser(HLCD_LINE_2, 0);
    HLCD_u8WriteStr("Welcome Ahmed");
    _delay_ms(2000);

    // After login, display the motor control menu
    MotorMenu();
}

// Displays the motor control menu after successful login
void MotorMenu(void)
{
    u8 keyPressed = 0;

    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("1:DC M 2:Step M");
    HLCD_VoidSetCurser(HLCD_LINE_2, 0);
    HLCD_u8WriteStr("3:Exit");

    while (1)
    {
        if (HKPD_u8GetPressedKey(&keyPressed) == STD_TYPE_OK)
        {
            _delay_ms(200);
            if (keyPressed == '1')
            {
                RunDCMotor();
            }
            else if (keyPressed == '2')
            {
                RunStepperMotor();
            }
            else if (keyPressed == '3') // If 'Exit' is pressed, return to the password input
            {
                HLCD_VoidLcdClear();
                main(); // Exits the MotorMenu function, returning to password prompt
            }

            _delay_ms(10);
            keyPressed = 0;
        }
    }
}

// Variable to control motor state
volatile u8 motorRunning = 0;

// Run the DC Motor (implement motor control logic here)
void RunDCMotor(void)
{
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("DC Motor Control");

    // Initial state: Stopped
    MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_0, MDIO_LOW); // Ensure motor is stopped initially

    // Display options for user
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("1:CW 2:CCW");

    u8 keyPressed = 0xff;
    while (0xff == keyPressed)
    {
        HKPD_u8GetPressedKey(&keyPressed);
    }
    // Read user input for direction or stop
    if (HKPD_u8GetPressedKey(&keyPressed) == STD_TYPE_OK)
    {
        if (keyPressed == '1') // Clockwise
        {
            motorRunning = 1;
            MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_0, MDIO_HIGH); // Turn on motor (CW)
            HLCD_VoidLcdClear();
            HLCD_u8WriteStr("Running CW");
            HLCD_VoidSetCurser(HLCD_LINE_2, 0);
            HLCD_u8WriteStr("1: Stop");
            keyPressed = 0;
            while ('1' != keyPressed)
            {
                HKPD_u8GetPressedKey(&keyPressed);
            }
            MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_0, MDIO_LOW); // Turn off motor (CW)
            HLCD_VoidLcdClear();
        }
        else if (keyPressed == '2') // Anti-clockwise
        {
            motorRunning = 1;
            MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_1, MDIO_HIGH); // Turn on motor (CCW)
            // Implement the control logic to reverse polarity if needed for CCW
            HLCD_VoidLcdClear();
            HLCD_u8WriteStr("Running CCW");
            HLCD_VoidSetCurser(HLCD_LINE_2, 0);
            HLCD_u8WriteStr("1: Stop");
            keyPressed = 0;
            while ('1' != keyPressed)
            {
                HKPD_u8GetPressedKey(&keyPressed);
            }
            MDIO_u8SetPinValue(MDIO_PORTB, MDIO_PIN_1, MDIO_LOW); // Turn off motor (CW)
            HLCD_VoidLcdClear();
        }
    }

    keyPressed = 0;

    _delay_ms(200); // Delay for stability

    MotorMenu(); // Go back to the motor menu
}

// Runs the Stepper Motor (implement stepper motor control logic here)
void RunStepperMotor(void)
{
    u8 angle = 0;
    u8 direction = 0;
    u8 speed = 0;
    u8 keyPressed = 0;

    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Set Angle 0-360:");
    HLCD_VoidSetCurser(HLCD_LINE_2,0);
    // Get angle from keypad (assume two digits for simplicity)
    angle = GetKeypadInput();

    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("1:CW 2:CCW");

    // Get direction from keypad
    while (1)
    {
        if (HKPD_u8GetPressedKey(&keyPressed) == STD_TYPE_OK)
        {
            if (keyPressed == '1') // Clockwise
            {
                direction = HSTEPM_CLOCK_WISE;
                break;
            }
            else if (keyPressed == '2') // Anti-clockwise
            {
                direction = HSTEPM_ANTI_CLOCK_WISE;
                break;
            }
        }
    }

    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Set Speed 2-10:");

    // Get speed from keypad
    speed = GetKeypadInput(); // Assume user will enter valid speed
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Stepper Running");
    // Run the stepper motor with the input parameters
    HSTEPM_u8RunStepperMotor(angle, direction, speed);

    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Stepper Finished");
    _delay_ms(2000);

    MotorMenu(); // Return to motor menu
}

// Helper function to get keypad input as a number
u8 GetKeypadInput(void)
{
    u8 input = 0;
    u8 keyPressed = 0;
    u8 digitCount = 0;
    u8 Local_u8flag = 0;

    while (digitCount < 3) // Allow up to 3 digits for input
    {
        Local_u8flag = HKPD_u8GetPressedKey(&keyPressed);
        if (Local_u8flag)
        {
            if (keyPressed >= '0' && keyPressed <= '9')
            {
                input = input * 10 + (keyPressed - '0');
                HLCD_VoidLcdWriteChar(keyPressed); // Show the entered digit
                digitCount++;
            }
            else if (keyPressed == '=') // Confirm input
            {
                return input;
            }
        }
        keyPressed = 0;
    }
    return input;
}

// Actions performed on failed password entry
void FailureAction(u8 trials)
{
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Wrong Password");
    HLCD_VoidSetCurser(HLCD_LINE_2, 0);
    HLCD_u8WriteStr("Trials Left:");
    HLCD_VoidSetCurser(HLCD_LINE_2, 12);
    HLCD_VoidLcdWriteInt(MAX_TRIALS - trials);
    _delay_ms(2000);
}
