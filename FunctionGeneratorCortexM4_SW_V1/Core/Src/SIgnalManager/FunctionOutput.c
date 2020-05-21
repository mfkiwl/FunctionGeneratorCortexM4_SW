/*
 * FunctionOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */


#include "FunctionOutput.h"

#include "EventManager.h"
#include "DisplayManager.h"
#include "SignalManager.h"

#include "dac.h"
#include "tim.h"



void FuncO_EnablePWMToSignal();
void FuncO_DisablePWMToSignal();
void FuncO_EnableDacToSignal();
void FuncO_DisableDacToSignal();

void FuncO_EnablePWMToSync();
void FuncO_DisablePWMToSync();
void FuncO_EnableDacToSync();
void FuncO_DisableDacToSync();

// dummy lookup table for PWM_FUNC_MODE
uint32_t empty_table[10] = {};


/*
 *	Array of objects for Function Presets, their encoder positions for func preset menu and LUT data for the function
 */
FunctionProfile_t theFuncProfiles[MAX_NUM_FUNC_PRESETS] =
{
	{ SINE_FUNC_MODE,		24, sine_data_table_3600 		},
	{ SQUARE_FUNC_MODE,		20, square_data_table_3600 		},
	{ SAW_FUNC_MODE,		16, saw_data_table_3600 		},
	{ REV_SAW_FUNC_MODE,	12, saw_rev_data_table_3600 	},
	{ TRIANGLE_FUNC_MODE, 	8, 	triangle_data_table_3600 	},
	{ IMPULSE_FUNC_MODE, 	4, 	unitimpulse_data_table_3600 },
	{ PWM_FUNC_MODE,		0,	empty_table					}			// no lookup table used

};



uint8_t FuncPresetEncoderRange = 24;

uint16_t func_last_encoder_value = 0;

void FuncO_ResetLastEncoderValue()
{
	func_last_encoder_value = 0;
}

/*
 *
 *	@brief	Initialise the
 *
 *	@param pEncoderValue rotary encoder value
 *	@retval None
 *
 */
void FuncO_Init()
{
	/*
	for(int i = 0; i < SINE_DATA_SIZE; i++)
		aProcessedSignalDataTable[i] = sine_data_table_3600[i];

	for(int i = 0; i < SINE_DATA_SIZE; i++)
		aProcessedSyncDataTable[i] = sine_data_table_3600[i];
		*/
}


/*
 *
 *	@brief	multiplex encoder input -> preset function
 *
 *	@param pEncoderValue rotary encoder value
 *	@retval None
 *
 */
void FuncO_ModifySignalOutput(uint16_t pEncoderValue)
{
	eOutput_mode tmpFunc = SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile->func;
	if(pEncoderValue > func_last_encoder_value)
	{
		tmpFunc++;
		if(tmpFunc > MAX_NUM_FUNC_PRESETS-1) tmpFunc = PWM_FUNC_MODE;
		FuncO_ApplyPresetToSignal(tmpFunc);
	}
	else if (pEncoderValue < func_last_encoder_value)
	{
		tmpFunc--;
		if(tmpFunc > MAX_NUM_FUNC_PRESETS-1) tmpFunc = SINE_FUNC_MODE;
		FuncO_ApplyPresetToSignal(tmpFunc);
	}
	func_last_encoder_value = pEncoderValue;
}

/*
 *
 *	@brief multiplex encoder input -> preset function
 *
 *	@param pEncoderValue rotary encoder value
 *	@retval None
 *
 */
void FuncO_ModifySyncOutput(uint16_t pEncoderValue)
{
	eOutput_mode tmpFunc = SM_GetOutputChannel(SYNC_CHANNEL)->func_profile->func;
	if(pEncoderValue > func_last_encoder_value)
	{
		tmpFunc++;
		if(tmpFunc > MAX_NUM_FUNC_PRESETS-1) tmpFunc = PWM_FUNC_MODE;
		FuncO_ApplyPresetToSync(tmpFunc);
	}
	else if (pEncoderValue < func_last_encoder_value)
	{
		tmpFunc--;
		if(tmpFunc > MAX_NUM_FUNC_PRESETS-1) tmpFunc = SINE_FUNC_MODE;
		FuncO_ApplyPresetToSync(tmpFunc);
	}
	func_last_encoder_value = pEncoderValue;
}


void FuncO_EnablePWMToSignal()
{
	SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile = &theFuncProfiles[PWM_FUNC_MODE];
}

void FuncO_DisablePWMToSignal()
{

}

void FuncO_EnableDacToSignal()
{
	SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile = &theFuncProfiles[PWM_FUNC_MODE];
}

void FuncO_DisableDacToSignal()
{

}

void FuncO_EnablePWMToSync()
{
	SM_GetOutputChannel(SYNC_CHANNEL)->func_profile = &theFuncProfiles[PWM_FUNC_MODE];
}

void FuncO_DisablePWMToSync()
{

}

void FuncO_EnableDacToSync()
{
	SM_GetOutputChannel(SYNC_CHANNEL)->func_profile = &theFuncProfiles[PWM_FUNC_MODE];
}

void FuncO_DisableDacToSync()
{

}

/*
 *
 *	@brief	Modify the function and gain of the main Signal output (DAC1/CH1)
 *
 *	@param pPresetEnum the enum literal for the preset. Should be one of the following:
 *
 *	SINE_FUNC_MODE,
	SQUARE_FUNC_MODE,
	SAW_FUNC_MODE,
	REV_SAW_FUNC_MODE,
	TRIANGLE_FUNC_MODE,
	IMPULSE_FUNC_MODE

 *	@retval None
 *
 */
void FuncO_ApplyPresetToSignal(eOutput_mode pPresetEnum)
{

	// set the next function output
	SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile = &theFuncProfiles[pPresetEnum];

	// copy the lookup table for the next output function in to SignalChannel object
	SM_GetOutputChannel(SIGNAL_CHANNEL)->ref_lut_data = theFuncProfiles[pPresetEnum].lookup_table_data;

	// set preset for PGA gain and dsp amplitude adjustment
	eAmpSettings_t eTmpVppPreset = SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile->amp_setting;
	VPP_ApplyPresetToSignal(eTmpVppPreset);

	// pause timer to resync both outputs
	//OUTPUT_TIMER->CR1 &= ~(TIM_CR1_CEN);
	HAL_TIM_Base_Stop(&htim8);

	// restart the DAC with the new data
	HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
	HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)SM_GetOutputChannel(SIGNAL_CHANNEL)->dsp_lut_data, SINE_DATA_SIZE, DAC_ALIGN_12B_R);

	// restart the the other DAC
	HAL_DAC_Stop_DMA(&hdac2, DAC1_CHANNEL_1);
	HAL_DAC_Start_DMA(&hdac2, DAC1_CHANNEL_1, (uint32_t*)SM_GetOutputChannel(SYNC_CHANNEL)->dsp_lut_data, SINE_DATA_SIZE, DAC_ALIGN_12B_R);

	// resume timer to resync both outputs
	HAL_TIM_Base_Start(&htim8);
	//OUTPUT_TIMER->CR1 |= (TIM_CR1_CEN);
}

/*
 *
 *	@brief	Modify the function and gain of the aux Sync output (DAC2/CH1)
 *
 *	@param pPresetEnum the enum literal for the preset. Should be one of the following:
 *
 *	SINE_FUNC_MODE,
	SQUARE_FUNC_MODE,
	SAW_FUNC_MODE,
	REV_SAW_FUNC_MODE,
	TRIANGLE_FUNC_MODE,
	IMPULSE_FUNC_MODE

 *	@retval None
 *
 */
void FuncO_ApplyPresetToSync(eOutput_mode pPresetEnum)
{
	// set the next output function
	SM_GetOutputChannel(SYNC_CHANNEL)->func_profile = &theFuncProfiles[pPresetEnum];


	// copy the lookup table for the next output function in to SyncChannel object
	SM_GetOutputChannel(SYNC_CHANNEL)->ref_lut_data = theFuncProfiles[pPresetEnum].lookup_table_data;

	// set preset PGA gain and dsp amplitude adjustment
	eAmpSettings_t eTmpVppPreset = SM_GetOutputChannel(SYNC_CHANNEL)->amp_profile->amp_setting;
	VPP_ApplyPresetToSync(eTmpVppPreset);

	// pause timer to resync both outputs
	//HAL_TIM_Base_Stop(&htim8);
	OUTPUT_TIMER->CR1 &= ~(TIM_CR1_CEN);

	// restart the DAC with the new data
	HAL_DAC_Stop_DMA(&hdac2, DAC1_CHANNEL_1);
	HAL_DAC_Start_DMA(&hdac2, DAC1_CHANNEL_1, (uint32_t*)SM_GetOutputChannel(SYNC_CHANNEL)->dsp_lut_data, SINE_DATA_SIZE, DAC_ALIGN_12B_R);

	// restart the the other DAC
	HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
	HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t*)SM_GetOutputChannel(SIGNAL_CHANNEL)->dsp_lut_data, SINE_DATA_SIZE, DAC_ALIGN_12B_R);

	// resume timer to resync both outputs
	//HAL_TIM_Base_Start(&htim8);
	OUTPUT_TIMER->CR1 |= (TIM_CR1_CEN);
}


/*
 *
 *	@brief Search array of structs for preset
 *
 *	@param Search criteria. Should be one of the following:
 *
 *	SINE_FUNC_MODE,
	SQUARE_FUNC_MODE,
	SAW_FUNC_MODE,
	REV_SAW_FUNC_MODE,
	TRIANGLE_FUNC_MODE,
	IMPULSE_FUNC_MODE

 *	@retval pointer to FunctionProfile_t struct
 *
 */
FunctionProfile_t * FuncO_FindFPresetObject(eOutput_mode pEnum)
{
	for(int i = 0; i < MAX_NUM_FUNC_PRESETS; i++ )
	{
		if(theFuncProfiles[i].func == pEnum)
		{
			return &theFuncProfiles[i];
		}
	}
	// error!
	DM_SetErrorDebugMsg("FuncO_FindFPresetObject(): no FPreset obj found");
	return 0;
}


/*
 *
 *	@brief Get currently set function output preset
 *
 *	@param None
 *	@retval pointer to FunctionProfile_t struct
 *
 */
/*
FunctionProfile_t * FuncO_GetSignalFPresetObject()
{
	return pSignalFuncPresetEncoderPos;
}
*/

/*
 *
 *	@brief Get currently set function output preset
 *
 *	@param None
 *	@retval pointer to FunctionProfile_t struct
 *
 */
/*
FunctionProfile_t * FuncO_GetSyncFPresetObject()
{
	return pSyncFuncPresetEncoderPos;
}
*/

/*
 *
 *	@brief	Get range value for rotary encoder
 *
 *	@param None
 *	@retval uint8_t
 *
 */
uint8_t FuncO_GetFuncPresetEncoderRange()
{
	return FuncPresetEncoderRange;
}



