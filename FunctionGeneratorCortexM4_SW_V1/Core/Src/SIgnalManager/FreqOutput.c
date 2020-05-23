/*
 * FreqOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FREQOUTPUT_C_
#define SRC_SIGNALMANAGER_FREQOUTPUT_C_

#include "FreqOutput.h"
#include "SignalManager.h"
#include "DisplayManager.h"

#include "tim.h"
#include "dac.h"

/*
 *	Array of objects for Frequency Presets and their encoder positions for freq preset menu
 */
FreqProfile_t theFreqProfiles[MAX_NUM_FREQ_PRESETS] =
{
	{ FPRESET_1HZ,		53, 0 },
	{ FPRESET_10HZ,		49, 1 },
	{ FPRESET_50HZ,		45, 2 },
	{ FPRESET_100HZ,	41, 3 },
	{ FPRESET_250HZ, 	37, 4 },
	{ FPRESET_500HZ, 	33, 5 },
	{ FPRESET_750HZ,	29, 6 },
	{ FPRESET_1KHZ, 	25, 7 },
	{ FPRESET_5KHZ, 	21, 8 },
	{ FPRESET_10KHZ,	17, 9 },
	{ FPRESET_25KHZ, 	13, 10},
	{ FPRESET_50KHZ, 	9, 	11},
	{ FPRESET_75KHZ, 	5, 	12},
	{ FPRESET_100KHZ, 	1, 	13}

};

/*
 * 		eDefaultFreqPreset set by SignalManager
 */
FreqProfile_t *freq_profile = &theFreqProfiles[eDefaultFreqPreset];


uint8_t FreqPresetEncoderRange = 56;

uint16_t freq_last_encoder_value = 0;

void FreqO_ResetLastEncoderValue()
{
	freq_last_encoder_value = 0;
}

/*
 * 	Function protochannels
 */
FreqProfile_t * FreqO_GetFPresetObject();
eFreqSettings_t _FindFPresetObjectByIndex(uint32_t pIndex);


/*
 *
 *	@brief	Increment/Decrement output frequency value
 *
 *	@param None
 *	@retval None
 *
 */
void FreqO_AdjustFreq()
{

		OUTPUT_TIMER->ARR = SM_GetEncoderValue(ENCODER_FORWARD); //* FREQ_ENCODER_MIDFREQ_MAG;

		eOutput_mode tmpOut = SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile->func;
		if(tmpOut == PWM_FUNC_MODE)
		{
			// duty cycle of PWM require slower settings to get the
			// same frequency as normal output functions
			TIM3->PSC = 256;
			TIM3->ARR = SM_GetEncoderValue(ENCODER_FORWARD)/2;
			TIM3->CCR2 = TIM3->ARR/2;

		}
}


/*
 *
 *	@brief	select frequency output preset from rot enc value
 *
 *	@param None
 *	@retval None
 *
 */
void FreqO_MapEncoderPositionToBothOutput(uint16_t pEncValue)
{

	switch(pEncValue)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			FreqO_ApplyPreset(FPRESET_1HZ);
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			FreqO_ApplyPreset(FPRESET_10HZ);
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			FreqO_ApplyPreset(FPRESET_50HZ);
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			FreqO_ApplyPreset(FPRESET_100HZ);
			break;
		case 16:
		case 17:
		case 18:
		case 19:
			FreqO_ApplyPreset(FPRESET_250HZ);
			break;
		case 20:
		case 21:
		case 22:
		case 23:
			FreqO_ApplyPreset(FPRESET_500HZ);
			break;
		case 24:
		case 25:
		case 26:
		case 27:
			FreqO_ApplyPreset(FPRESET_750HZ);
			break;
		case 28:
		case 29:
		case 30:
		case 32:
			FreqO_ApplyPreset(FPRESET_1KHZ);
			break;
		case 33:
		case 34:
		case 35:
		case 36:
			FreqO_ApplyPreset(FPRESET_5KHZ);
			break;
		case 37:
		case 38:
		case 39:
		case 40:
			FreqO_ApplyPreset(FPRESET_10KHZ);
			break;
		case 41:
		case 42:
		case 43:
		case 44:
			FreqO_ApplyPreset(FPRESET_25KHZ);
			break;
		case 45:
		case 46:
		case 47:
		case 48:
			FreqO_ApplyPreset(FPRESET_50KHZ);
			break;
		case 49:
		case 50:
		case 51:
		case 52:
			FreqO_ApplyPreset(FPRESET_75KHZ);
			break;
		case 53:
		case 54:
		case 55:
		case 56:
			FreqO_ApplyPreset(FPRESET_100KHZ);
			break;
	}

/*	uint32_t tmpFreqIndex = freq_profile->index;
	if(pEncValue > freq_last_encoder_value)
	{
		tmpFreqIndex++;
		if(tmpFreqIndex > MAX_NUM_FREQ_PRESETS-1) tmpFreqIndex = FPRESET_100KHZ;
		FreqO_ApplyPreset_Fast(_FindFPresetObjectByIndex(tmpFreqIndex));
	}
	else if (pEncValue < freq_last_encoder_value)
	{
		tmpFreqIndex--;
		if(tmpFreqIndex > MAX_NUM_FREQ_PRESETS-1) tmpFreqIndex = FPRESET_100KHZ;
		FreqO_ApplyPreset_Fast(_FindFPresetObjectByIndex(tmpFreqIndex));
	}
	freq_last_encoder_value = pEncValue;
	*/
}



/*
 *
 *	@brief	Set frequency output preset by index
 *
 *	@param pPresetEnum the enum literal for the preset. Should be one of the following:
 *
 *	FPRESET_1HZ 	= 1U,
	FPRESET_10HZ	= 10U,
	FPRESET_50HZ	= 50U,
	FPRESET_100HZ	= 100U,
	FPRESET_250HZ	= 250U,
	FPRESET_500HZ	= 500U,
	FPRESET_750HZ	= 750U,
	FPRESET_1KHZ	= 1000U,
	FPRESET_5KHZ	= 5000U,
	FPRESET_10KHZ	= 10000U,
	FPRESET_25KHZ	= 25000U,
	FPRESET_50KHZ	= 50000U,
	FPRESET_75KHZ	= 75000U,
	FPRESET_100KHZ	= 100000U

 *	@retval None
 *
 */
void FreqO_ApplyPreset_Fast(eFreqSettings_t pPresetEnum)
{
	switch(pPresetEnum)
	{
		case FPRESET_1HZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(0)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(0)->arr;

			freq_profile = &theFreqProfiles[0];
			break;
		case FPRESET_10HZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(1)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(1)->arr;

			freq_profile = &theFreqProfiles[1];
			break;
		case FPRESET_50HZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(2)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(2)->arr;

			freq_profile = &theFreqProfiles[2];
			break;
		case FPRESET_100HZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(3)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(3)->arr;

			freq_profile = &theFreqProfiles[3];
			break;
		case FPRESET_250HZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(4)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(4)->arr;

			freq_profile = &theFreqProfiles[4];
			break;
		case FPRESET_500HZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(5)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(5)->arr;

			freq_profile = &theFreqProfiles[5];
			break;
		case FPRESET_750HZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(6)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(6)->arr;

			freq_profile = &theFreqProfiles[6];
			break;
		case FPRESET_1KHZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(7)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(7)->arr;

			freq_profile = &theFreqProfiles[7];
			break;
		case FPRESET_5KHZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(8)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(8)->arr;

			freq_profile = &theFreqProfiles[8];
			break;
		case FPRESET_10KHZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(9)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(9)->arr;

			freq_profile = &theFreqProfiles[9];
			break;
		case FPRESET_25KHZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(10)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(10)->arr;

			freq_profile = &theFreqProfiles[10];
			break;
		case FPRESET_50KHZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(11)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(11)->arr;

			freq_profile = &theFreqProfiles[11];
			break;
		case FPRESET_75KHZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(12)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(12)->arr;

			freq_profile = &theFreqProfiles[12];
			break;
		case FPRESET_100KHZ:
			OUTPUT_TIMER->PSC = DT_GetRegisterByIndex(13)->psc;
			OUTPUT_TIMER->ARR = DT_GetRegisterByIndex(13)->arr;

			freq_profile = &theFreqProfiles[13];
			break;
	}
}

/*
 *
 *	@brief Set frequency output preset by search
 *
 *	@param pPresetEnum search criteria. Should be one of the following:
 *
 *	FPRESET_1HZ 	= 1U,
	FPRESET_10HZ	= 10U,
	FPRESET_50HZ	= 50U,
	FPRESET_100HZ	= 100U,
	FPRESET_250HZ	= 250U,
	FPRESET_500HZ	= 500U,
	FPRESET_750HZ	= 750U,
	FPRESET_1KHZ	= 1000U,
	FPRESET_5KHZ	= 5000U,
	FPRESET_10KHZ	= 10000U,
	FPRESET_25KHZ	= 25000U,
	FPRESET_50KHZ	= 50000U,
	FPRESET_75KHZ	= 75000U,
	FPRESET_100KHZ	= 100000U

 *	@retval None
 *
 */
void FreqO_ApplyPreset(eFreqSettings_t pPresetEnum)
{
	DacTimeReg_t* tmpDT = DT_GetRegisterByEnum(pPresetEnum);
	if(tmpDT)
	{
		OUTPUT_TIMER->PSC = tmpDT->psc;
		OUTPUT_TIMER->ARR = tmpDT->arr;

		eOutput_mode tmpOut = SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile->func;
		if(tmpOut == PWM_FUNC_MODE)
		{
			// duty cycle of PWM require slower settings to get the
			// same frequency as normal output functions
			TIM3->PSC = 256;
			TIM3->ARR = tmpDT->arr/2;
			TIM3->CCR2 = TIM3->ARR/2;
		}

		//eNewFreqPreset = pPresetEnum;
		FreqProfile_t * tmpFreq = FreqO_FindFPresetObject(pPresetEnum);
		if(tmpFreq)
		{
			freq_profile = tmpFreq;
		}
		else
		{
			DM_SetErrorDebugMsg("FreqO_ApplyPreset() null pointer error");
		}



	}
}

/*
 *
 *	@brief Get currently set freq output preset
 *
 *	@param None
 *	@retval pointer to FreqProfile_t struct
 *
 */
FreqProfile_t * FreqO_GetFPresetObject()
{
	return freq_profile;
}


/*
 *
 *	@brief Search array of preset structs
 *
 *	@param Search criteria. Should be one of the following:
 *
 *	FPRESET_1HZ 	= 1U,
	FPRESET_10HZ	= 10U,
	FPRESET_50HZ	= 50U,
	FPRESET_100HZ	= 100U,
	FPRESET_250HZ	= 250U,
	FPRESET_500HZ	= 500U,
	FPRESET_750HZ	= 750U,
	FPRESET_1KHZ	= 1000U,
	FPRESET_5KHZ	= 5000U,
	FPRESET_10KHZ	= 10000U,
	FPRESET_25KHZ	= 25000U,
	FPRESET_50KHZ	= 50000U,
	FPRESET_75KHZ	= 75000U,
	FPRESET_100KHZ	= 100000U

 *	@retval pointer to FreqProfile_t struct
 *
 */
FreqProfile_t * FreqO_FindFPresetObject(eFreqSettings_t pEnum)
{
	for(int i = 0; i < MAX_NUM_FREQ_PRESETS; i++ )
	{
		if(theFreqProfiles[i].hertz == pEnum)
		{
			return &theFreqProfiles[i];
		}
	}
	// error!
	DM_SetErrorDebugMsg("FreqO_FindFPresetObject(): no FPreset obj found");
	return 0;
}

eFreqSettings_t _FindFPresetObjectByIndex(uint32_t pIndex)
{
	for(int i = 0; i < pIndex; i++ )
	{
		return theFreqProfiles[i].hertz;

	}
	// error!
	DM_SetErrorDebugMsg("FreqO_FindFPresetObject(): no FPreset obj found");
	return 0;
}


/*
 *
 *	@brief	Get range value for rotary encoder
 *
 *	@param None
 *	@retval uint8_t
 *
 */
uint8_t FreqO_GetFreqPresetEncoderRange()
{
	return FreqPresetEncoderRange;
}

/*
 *
 *	@brief	Get frequency of output signal
 *
 *	@param None
 *	@retval uint32_t
 *
 */
uint32_t FreqO_GetOutputFreq()
{
	return OUTPUT_TIMER->ARR;
}


#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_C_ */
