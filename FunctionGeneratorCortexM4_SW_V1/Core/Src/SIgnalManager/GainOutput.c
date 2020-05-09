/*
 * GainOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#include "GainOutput.h"

#include "gpio.h"
#include "tim.h"


// signal output gain settings
typedef enum
{
	Zero_Gain = 0U,
	One_Gain,
	Two_Gain,
	Three_Gain,
	Four_Gain,
	Five_Gain,
	Six_Gain,
	Seven_Gain

} eOutput_gain;

// signal output gain
eOutput_gain eNewOutGain = One_Gain;

/*
 *
 *
 *
 */
void GO_ModifyOutput()
{

	// PGA Truth table for LTC6910:
	// https://www.analog.com/media/en/technical-documentation/data-sheets/6910fb.pdf
	switch(TIM1->CNT)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			eNewOutGain = Zero_Gain;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			eNewOutGain = One_Gain;
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			eNewOutGain = Two_Gain;
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			eNewOutGain = Three_Gain;
			break;
		case 16:
		case 17:
		case 18:
		case 19:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			eNewOutGain = Four_Gain;
			break;
		case 20:
		case 21:
		case 22:
		case 23:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			eNewOutGain = Five_Gain;
			break;
		case 24:
		case 25:
		case 26:
		case 27:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			eNewOutGain = Six_Gain;
			break;
		case 28:
		case 29:
		case 30:
		case 31:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			eNewOutGain = Seven_Gain;
			break;
	}

}

/*
 *
 *
 *
 */
uint8_t GO_GetOutputGain()
{
	return (uint8_t)eNewOutGain;
}
