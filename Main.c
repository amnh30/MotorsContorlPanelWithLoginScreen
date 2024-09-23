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
/* Include your previous headers here */

/* Constants */
#define MAX_TRIALS 3
#define PASSWORD 1234 // Define your password as a number

int main(void) {
    u8 keyPressed = 0;
    u32 enteredPassword = 0; // Buffer for entered password
    u8 passwordDigitCount = 0; // Count of digits entered
    u8 trials = 0; // Count of login attempts

    // Initialize the LCD and Keypad
    MDIO_IntialPins();
    HLCD_VoidLcdIint();
    HLCD_VoidLcdClear();

    while (trials < MAX_TRIALS) {
        HLCD_VoidLcdClear();
        HLCD_u8WriteStr("Enter Password:");
HLCD_VoidSetCurser(HLCD_LINE_2,0);
        enteredPassword = 0; // Reset for each attempt
        passwordDigitCount = 0;

        while (passwordDigitCount < 5) { // Assuming a 4-digit password
            // Check if a key is pressed
            if (HKPD_u8GetPressedKey(&keyPressed) == STD_TYPE_OK) {
                _delay_ms(200);
                if (keyPressed != HKPD_NO_KEY_PRESSED) {
                    // Handle numeric input (0-9)
                    if (keyPressed >= '0' && keyPressed <= '9') {
                        enteredPassword = enteredPassword * 10 + (keyPressed - '0'); // Build the number
                        HLCD_VoidLcdWriteChar('*'); // Display * for security
                        passwordDigitCount++;
                    }
                    // Handle enter key
                    else if (keyPressed == '=') {
                        // Check password
                        if (enteredPassword == PASSWORD) {
                            HLCD_VoidLcdClear();
                            HLCD_u8WriteStr("Password Correct");
                            HLCD_VoidSetCurser(HLCD_LINE_2,0);
                            HLCD_u8WriteStr("Welcome Ahmed");
                            MDIO_u8SetPinValue(MDIO_PORTB,MDIO_PIN_5,MDIO_HIGH);
                            while (1); // Infinite loop or redirect to main system
                        } else {
                            trials++;
                            HLCD_VoidLcdClear();
                            HLCD_u8WriteStr("Wrong Password");
                            HLCD_VoidSetCurser(HLCD_LINE_2,0);
                            HLCD_VoidLcdWriteInt(MAX_TRIALS - trials);
                            HLCD_u8WriteStr(" Trials left");
                            _delay_ms(2000); // Delay to show message
                            keyPressed=0;
                            break; // Break to reset for the next trial
                        }
                    }
                    // Handle clear key ('C')
                    else if (keyPressed == '%') {
                        HLCD_VoidLcdClear();
                        enteredPassword = 0; // Reset entered password
                        passwordDigitCount = 0; // Reset digit count
                    }

                    _delay_ms(10); // Small delay for debouncing
                    keyPressed = 0;
                }
            }
        }
    }

    // After MAX_TRIALS
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("Access Denied");
    MDIO_u8SetPinValue(MDIO_PORTB,MDIO_PIN_7,MDIO_HIGH);
    while (1); // Lock out or redirect
}
