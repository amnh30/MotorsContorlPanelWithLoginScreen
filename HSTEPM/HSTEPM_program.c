/* LIB Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "avr/delay.h"
#define C_CPU 8000000Ul

/*MCAL Layer Include*/
#include "../MDIO/MDIO_Interface.h"

/* HAL Layer Include*/
#include "HSTEPM_private.h"
#include "HSTEPM_config.h"
#include "HSTEPM_interface.h"

u8 HSTEPM_u8RunStepperMotor(u16 Copy_u8Angle, u8 Copy_u8Direction, u8 Copy_u8SpeedFm_2_To_10)
{
    u8 Local_u8ErrorState = STD_TYPE_OK;

    //if (HSTEPM_ANTI_CLOCK_WISE <= Copy_u8Direction && 10 <= Copy_u8SpeedFm_2_To_10)
    //{
        u32 Local_u32Counter;
        u32 Local_u32steps = (Copy_u8Angle * HSTEPM_PER_REV) ; // Calculate number of steps


        for (Local_u32Counter = 0; Local_u32Counter < Local_u32steps; Local_u32Counter++)
        {
            if (HSTEPM_CLOCK_WISE == Copy_u8Direction)
            {
                // Step sequence for Clockwise rotation
                // Step 1
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_BLUE_1, MDIO_LOW);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_PINK_2, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_YELLOW_3, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_ORANGE_4, MDIO_HIGH);

                _delay_ms(Copy_u8SpeedFm_2_To_10);

                // Step 2
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_BLUE_1, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_PINK_2, MDIO_LOW);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_YELLOW_3, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_ORANGE_4, MDIO_HIGH);
                _delay_ms(Copy_u8SpeedFm_2_To_10);

                // Step 3
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_PINK_2, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_YELLOW_3, MDIO_LOW);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_BLUE_1, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_ORANGE_4, MDIO_HIGH);
                _delay_ms(Copy_u8SpeedFm_2_To_10);

                // Step 4
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_YELLOW_3, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_ORANGE_4, MDIO_LOW);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_PINK_2, MDIO_HIGH);
                _delay_ms(Copy_u8SpeedFm_2_To_10);
            }
            else
            {
                // Step sequence for Anti-clockwise rotation (reverse order)
                // Step 4
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_YELLOW_3, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_ORANGE_4, MDIO_LOW);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_PINK_2, MDIO_HIGH);
                _delay_ms(Copy_u8SpeedFm_2_To_10);

                // Step 3
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_PINK_2, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_YELLOW_3, MDIO_LOW);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_BLUE_1, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_ORANGE_4, MDIO_HIGH);
                _delay_ms(Copy_u8SpeedFm_2_To_10);

                // Step 2
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_BLUE_1, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_PINK_2, MDIO_LOW);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_YELLOW_3, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_ORANGE_4, MDIO_HIGH);
                _delay_ms(Copy_u8SpeedFm_2_To_10);

                // Step 1
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_BLUE_1, MDIO_LOW);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_PINK_2, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_YELLOW_3, MDIO_HIGH);
                MDIO_u8SetPinValue(HSTEP_COILS_PORT, HSTEP_COIL_ORANGE_4, MDIO_HIGH);
                _delay_ms(Copy_u8SpeedFm_2_To_10);
            }
        }
    //}
    /*else
    {
        u8 Local_u8ErrorState = STD_TYPE_NOK;
    }*/

    return Local_u8ErrorState;
}
