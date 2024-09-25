/* LIB Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/delay.h>

/*MCAL Layer Include*/
#include "../MDIO/MDIO_Interface.h"

/* HAL Layer Include*/
#include "HKPD_private.h"
#include "HKPD_config.h"
#include "HKPD_interface.h"

/* Define Globale Arrays*/
static u8 HKPD_AU8RowsPins[4] = {HKPD_R1_PIN, HKPD_R2_PIN, HKPD_R3_PIN, HKPD_R4_PIN};
static u8 HKPD_AU8ColsPins[4] = {HKPD_C1_PIN, HKPD_C2_PIN, HKPD_C3_PIN, HKPD_C4_PIN};
static u8 HKPD_Au8Keys[4][4] = HKPD_KPD;


u8 HKPD_u8GetPressedKey(u8 *Copy_u8KeyPressed)
{
    u8 Local_u8ErrorState = STD_TYPE_NOK;
    u8 Local_u8RowCounter;
    u8 Local_u8ColCounter;
    u8 Local_u8PinValue;
    if (Copy_u8KeyPressed != STD_TYPE_POINTER_NULL)
    {
        Local_u8ErrorState = STD_TYPE_OK;
        //*Copy_u8KeyPressed = HKPD_NO_KEY_PRESSED;
        for (Local_u8RowCounter = 0; Local_u8RowCounter < 4; Local_u8RowCounter++)
        {
            MDIO_u8SetPinValue(HKPD_ROWS_PORT, HKPD_AU8RowsPins[Local_u8RowCounter], MDIO_LOW);
            /* Check Cols*/
            for (Local_u8ColCounter = 0; Local_u8ColCounter < 4; Local_u8ColCounter++)
            {
                MDIO_u8GetPinValue(HKPD_COLS_PORT, HKPD_AU8ColsPins[Local_u8ColCounter], &Local_u8PinValue);
                if (Local_u8PinValue == MDIO_LOW)
                {

                    _delay_ms(20);
                    /*wait the user until switch */
                    while (Local_u8PinValue == MDIO_LOW)
                    {
                        MDIO_u8GetPinValue(HKPD_COLS_PORT, HKPD_AU8ColsPins[Local_u8ColCounter], &Local_u8PinValue);
                    }
                    *Copy_u8KeyPressed = HKPD_Au8Keys[Local_u8RowCounter][Local_u8ColCounter];
                }

            }
            /*Deactivate Current Row*/
            MDIO_u8SetPinValue(HKPD_ROWS_PORT, HKPD_AU8RowsPins[Local_u8RowCounter], MDIO_HIGH);
        }
    }

    return Local_u8ErrorState;
}
