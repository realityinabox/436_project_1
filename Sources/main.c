/* ###################################################################
 **     Filename    : main.c
 **     Project     : Lab2
 **     Processor   : MK64FN1M0VLQ12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2015-01-12, 19:05, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

#include "stdio.h"
#include <stdlib.h>
#include <math.h>
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "PDC1.h"
#include "RESpin1.h"
#include "SCEpin1.h"
#include "D_Cpin1.h"
#include "WAIT1.h"
#include "SM1.h"
#include "rLED.h"
#include "BitIoLdd1.h"
#include "bLED.h"
#include "BitIoLdd2.h"
#include "gLED.h"
#include "BitIoLdd3.h"
#include "ENC_SW_1.h"
#include "ExtIntLdd1.h"
#include "ENC_SW_2.h"
#include "ExtIntLdd2.h"
#include "ENC_PB.h"
#include "ExtIntLdd3.h"
#include "TI1_SW.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "AD1.h"
#include "AdcLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

// This variable is declared in Events.c and contains the current counter value
extern volatile int counter, pb, enc_write_flag, adc1_flag, timer_1s;
//extern const unsigned char sunny, cloudy, night;

#define NIGHT 3
#define CLOUDY 2
#define SUNNY  1
#define RES 9890 // ohms
#define LIGHT 0
#define TEMP 1

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	char *str[10], *int_str[4], *dec_str[4], *lux_str[10], *res_str[10];
	int count = 0, conv_type = 1;
	int char_col;
	int button_pressed, enc_pb_flag = 0, temp_flag = 0, lux_flag = 1, mode = 1, hold = 0;
	unsigned short Val[2], full = 0xFFFF, temp_adc, light;
	float temp_C, temp_F, temp_mV, light_mV, resistance, light_ratio;
	int temp_int, temp_dec, x_pos;


	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	enc_write_flag = 0;
	/* Write your code here */
	// Create infinite loop

	while(1){

		// ADC READS
		// if the timer_1s flag was set within TI1_SW_OnInterrupt
		if (timer_1s == 1){

			// start conversion
			if (conv_type == LIGHT){
				(void)AD1_MeasureChan(FALSE, 0);
			}
			if (conv_type == TEMP){
				(void)AD1_MeasureChan(FALSE, 1);
			}

			//(void)AD1_Measure(FALSE);
			// clear flag
			timer_1s = 0;
			// toggle LEDAD2
			//rLED_NegVal();
		}
		// if LIGHT conversion is completed
		if(adc1_flag == 1 && conv_type == LIGHT){
			// reset conversion done flag
			adc1_flag = 0;
			// read values
			(void)AD1_GetChanValue16(LIGHT, &Val[LIGHT]);
			// assign values to local variables
			light = Val[LIGHT] ;

			// convert light reading from adc to mV
			light_mV = light / 19.8591;
			light_ratio = light_mV / 3300;

			// calculate the resistance value
			resistance = (RES * light_ratio) / ( 1 - light_ratio);

			// convert light reading from adc to mV
			light_mV = light / 19.8591;
			light_ratio = light_mV / 3300;

			// set lux_flag
			lux_flag = 1;
			// set next conversion to be for temperature
			conv_type = TEMP;

		}
		// if TEMPERATURE conversion is done
		if (adc1_flag == 1 && conv_type == TEMP){
			// reset conversion done flag
			adc1_flag = 0;
			// read values
			(void)AD1_GetChanValue16(TEMP, &Val[TEMP]);
			// assign values to local variables

			temp_adc = Val[TEMP] ;

			// convert temp_adc to mV by scaling 2^16 over 3.3 volts
			temp_mV = temp_adc / 19.8591;
			temp_C = (temp_mV - 500) / 10;
			temp_F = ((9 * temp_C) / 5) + 32;

			// set the temp_flag to signal display to update
			temp_flag = 1;
			// set next conversion to light
			conv_type = LIGHT;
		}
		// END ADC READS

		// ROTARY ENCODER PUSH BUTTON DEBOUNCE
		// get the push button state
		button_pressed = ENC_PB_GetVal();
		// if button is pressed
		if (button_pressed == 0){
			// increment counter
			count++;
			// might need to guard against over-flow here, incase the button is held down and we keep incrementing
		}
		// wait for counter to count up to 30,000 (ie, debounced)
		if (count >= 15000){
			// update button status
			button_pressed = ENC_PB_GetVal();
			// if button is pressed, set the flag
			if (button_pressed == 0)
				enc_pb_flag = 1;
			// if button is released
			if (button_pressed == 1)
			{
				// clear the counter, the push button flag, and the hold flag
				count = 0;
				enc_pb_flag = 0;
				hold = 0;
			}
		}
		// if the push button flag is set and the hold flag is clear
		if (enc_pb_flag == 1 && hold == 0){
			// clear the pushbutton flag, toggle the mode, set the hold flag
			enc_pb_flag = 0;
			mode ^= 1;
			hold = 1;
			// flag the display to update temperature
			temp_flag = 1;
			lux_flag = 1;
			// invert the display
			//PDC1_SetMode(mode);
		}
		// END DEBOUNCE

		// UPDATE THE DISPLAY

		// WRITE NEW ENCODER COUNTERS DATA
		if (enc_write_flag == 1){
			// Convert the int counter value to a string for writing to display
			sprintf(str, "%0.3d", counter);
			// write the counter value to the display
			PDC1_WriteStringBigger("Count:", 0, 0);
			// clear the old value
			PDC1_ClearLine(2);
			PDC1_ClearLine(3);
			// write the count value
			PDC1_WriteStringBigger(str, 10, 2);
			// reset the write flag
			enc_write_flag = 0;
		}
		// WRITE NEW TEMPERATURE DATA and LUX DATA
		if (temp_flag == 1 && lux_flag == 1){
			// Convert the int counter value to a string for writing to display
			if (mode == 1){
				// get the whole number portion of temperature float
				temp_int = floorf(temp_F);
				// get the first two decimal places
				temp_dec = (temp_F - temp_int) * 100;
				// write the temperature type to display
				PDC1_SetPos(0,0);
				PDC1_WriteString("Temp(F):");
			}
			if (mode == 0){
				// get the whole number portion of temperature
				temp_int = floorf(temp_C);
				// get the first two decimal places of temperature
				temp_dec = (temp_C - temp_int) * 100;
				// write temperature type to display
				PDC1_SetPos(0,0);
				PDC1_WriteString("Temp(C):");
			}
			// convert the temperatures to strings
			sprintf(int_str, "% d", (int)temp_int);
			sprintf(dec_str, "%.2d", (int)temp_dec);
			// try to lop off the leading zero
			if (int_str[0] == "0"){
				int_str[0] = " ";
			}
			// clear the old value
			PDC1_ClearLine(1);
			PDC1_ClearLine(2);
			// set initial x position
			x_pos = 0;
			// write integer value
			x_pos = PDC1_WriteStringBigger(int_str, x_pos, 1);
			// write the decimal place
			x_pos = PDC1_WriteStringBigger(".", x_pos, 1);
			// write the decimals
			x_pos = PDC1_WriteStringBigger(dec_str, x_pos, 1);

			// reset the write flag
			temp_flag = 0;
		//}
		// WRITE LUMINANCE DATA
		//if (lux_flag == 1){
			PDC1_ClearLine(3);
			PDC1_ClearLine(4);
			PDC1_ClearLine(5);

			if (light > 40000){
				PDC1_weather_image(NIGHT, 60, 3);
			}
			else if (light <= 40000 && light > 8000){
				PDC1_weather_image(CLOUDY, 60, 3);
			}
			else if (light <= 8000){
				PDC1_weather_image(SUNNY, 60, 3);
			}
			sprintf(lux_str, "%d", (int)light);
			sprintf(res_str, "%d", (int)resistance);
			PDC1_SetPos(0,3);
			PDC1_WriteString("ADC:");
			PDC1_WriteString(lux_str);
			PDC1_SetPos(0,4);
			PDC1_WriteString("Res:");
			PDC1_WriteString(res_str);
			lux_flag = 0;

		}
		// END DISPLAY UPDATE


	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.4 [05.11]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
