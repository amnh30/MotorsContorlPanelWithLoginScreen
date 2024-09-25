#ifndef HSTEPM_INTERFACE_H
#define HSTEPM_INTERFACE_H




/*Driection */
#define HSTEPM_CLOCK_WISE 1
#define HSTEPM_ANTI_CLOCK_WISE 2



u8 HSTEPM_u8RunStepperMotor(u16 Copy_u8Angle, u8 Copy_u8Direction, u8 Copy_u8SpeedFm_1_To_10);

#endif
