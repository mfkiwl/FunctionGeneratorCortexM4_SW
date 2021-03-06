/*
 * BiasOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#include "BiasOutput.h"

#include "gpio.h"
#include "dac.h"

#include "SignalManager.h"
#include "EventManager.h"

eBias_Polarity eBiasPolarity = NORMALBIAS;
uint16_t dc_bias_encoder_value  = 400;


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eBias_Polarity BO_GetBiasPolarity()
{
	return eBiasPolarity;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
uint16_t BO_GetDcBiasEncoderValue()
{
	return dc_bias_encoder_value;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void BO_MapEncoderPositionToSignalOutput(uint16_t pEncoderValue)
{
	// pEncoderValue is reversed for correct rotary encoder operation.
	// However, we want to retain the forward direction value to prevent polarity flip!
	dc_bias_encoder_value = SM_GetEncoderValue(ENCODER_NORMAL);

	// apply negative dc bias
	if(pEncoderValue < BIAS_CENTER) {

		eBiasPolarity = INVERSEBIAS;

		//TIM1->CNT = pEncoderValue;


		HAL_DAC_SetValue(	&hdac1,
							DAC1_CHANNEL_2,
							DAC_ALIGN_12B_R,
							((BIAS_CENTER - pEncoderValue) * BIAS_MAG));

		HAL_GPIO_WritePin(	OFFSET_ENABLE_GPIO_Port,
							OFFSET_ENABLE_Pin,
							GPIO_PIN_SET);
	}
	// apply positive dc bias
	if(pEncoderValue >= BIAS_CENTER) {

		eBiasPolarity = NORMALBIAS;

		//TIM1->CNT = pEncoderValue;

		HAL_DAC_SetValue(	&hdac1,
							DAC1_CHANNEL_2,
							DAC_ALIGN_12B_R,
							((pEncoderValue - BIAS_CENTER) * BIAS_MAG));

		HAL_GPIO_WritePin(	OFFSET_ENABLE_GPIO_Port,
							OFFSET_ENABLE_Pin,
							GPIO_PIN_RESET);
	}
}

void BO_SetPwmSignalOffsetForGain(eGainSettings_t temp_gain)
{
	// artifically offset PWM signal above DC
	uint16_t new_bias_value;
	switch(temp_gain)
	{

		case ONE_GAIN:
			new_bias_value = 2500;
			break;
		case TWO_GAIN:
			new_bias_value = 3000;
			break;

		case THREE_GAIN:
		case FOUR_GAIN:
		case FIVE_GAIN:
		case SIX_GAIN:
		case SEVEN_GAIN:
			new_bias_value = 4095;
			break;

		default:
			break;

	}

	HAL_DAC_SetValue(	&hdac1,
						DAC1_CHANNEL_2,
						DAC_ALIGN_12B_R,
						new_bias_value);

	HAL_GPIO_WritePin(	OFFSET_ENABLE_GPIO_Port,
						OFFSET_ENABLE_Pin,
						GPIO_PIN_RESET);
}



void BO_SetPwmSignalOffsetForDuty(uint32_t value)
{
	HAL_DAC_SetValue(	&hdac1,
						DAC1_CHANNEL_2,
						DAC_ALIGN_12B_R,
						value);

	HAL_GPIO_WritePin(	OFFSET_ENABLE_GPIO_Port,
						OFFSET_ENABLE_Pin,
						GPIO_PIN_RESET);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
uint32_t BO_GetOutputBias()
{
	return HAL_DAC_GetValue(&hdac1, DAC1_CHANNEL_2);
}




