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

#include "tim.h"

/*
 *	Array of objects for Frequency Presets and their encoder positions for freq preset menu
 */
Freq_Preset_Encoder_Pos_t aFreqPresetEncoderPos[MAX_NUM_FPRESETS] =
{
	{ FPRESET_1HZ,		53 },
	{ FPRESET_10HZ,		49 },
	{ FPRESET_50HZ,		45 },
	{ FPRESET_100HZ,	41 },
	{ FPRESET_250HZ, 	37 },
	{ FPRESET_500HZ, 	33 },
	{ FPRESET_750HZ,	29 },
	{ FPRESET_1KHZ, 	25 },
	{ FPRESET_5KHZ, 	21 },
	{ FPRESET_10KHZ,	17 },
	{ FPRESET_25KHZ, 	13 },
	{ FPRESET_50KHZ, 	9  },
	{ FPRESET_75KHZ, 	5  },
	{ FPRESET_100KHZ, 	1  }

};

/*
 * 		eDefaultFreqPreset set by SignalManager
 */
Freq_Preset_Encoder_Pos_t *pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[eDefaultFreqPreset];


uint8_t FreqPresetEncoderRange = 56;



/*
 * 	Function prototypes
 */
Freq_Preset_Encoder_Pos_t * FreqO_GetFPresetObject();



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
		//TIM8->ARR = SM_GetEncoderValue(ENCODER_FORWARD) * FREQ_ENCODER_HIFREQ_MAG;
		TIM8->ARR = SM_GetEncoderValue(ENCODER_FORWARD); //* FREQ_ENCODER_MIDFREQ_MAG;
		//TIM8->ARR = SM_GetEncoderValue(ENCODER_FORWARD) * FREQ_ENCODER_LOFREQ_MAG;
}


/*
 *
 *	@brief	select frequency output preset from rot enc value
 *
 *	@param None
 *	@retval None
 *
 */
void FreqO_ModifyOutput(uint16_t pEncValue)
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
void FreqO_ApplyPreset_Fast(eFreq_Preset pPresetEnum)
{
	switch(pPresetEnum)
	{
		case FPRESET_1HZ:
			TIM8->PSC = DT_GetRegisterByIndex(0)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(0)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[0];
			break;
		case FPRESET_10HZ:
			TIM8->PSC = DT_GetRegisterByIndex(1)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(1)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[1];
			break;
		case FPRESET_50HZ:
			TIM8->PSC = DT_GetRegisterByIndex(2)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(2)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[2];
			break;
		case FPRESET_100HZ:
			TIM8->PSC = DT_GetRegisterByIndex(3)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(3)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[3];
			break;
		case FPRESET_250HZ:
			TIM8->PSC = DT_GetRegisterByIndex(4)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(4)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[4];
			break;
		case FPRESET_500HZ:
			TIM8->PSC = DT_GetRegisterByIndex(5)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(5)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[5];
			break;
		case FPRESET_750HZ:
			TIM8->PSC = DT_GetRegisterByIndex(6)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(6)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[6];
			break;
		case FPRESET_1KHZ:
			TIM8->PSC = DT_GetRegisterByIndex(7)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(7)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[7];
			break;
		case FPRESET_5KHZ:
			TIM8->PSC = DT_GetRegisterByIndex(8)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(8)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[8];
			break;
		case FPRESET_10KHZ:
			TIM8->PSC = DT_GetRegisterByIndex(9)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(9)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[9];
			break;
		case FPRESET_25KHZ:
			TIM8->PSC = DT_GetRegisterByIndex(10)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(10)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[10];
			break;
		case FPRESET_50KHZ:
			TIM8->PSC = DT_GetRegisterByIndex(11)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(11)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[11];
			break;
		case FPRESET_75KHZ:
			TIM8->PSC = DT_GetRegisterByIndex(12)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(12)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[12];
			break;
		case FPRESET_100KHZ:
			TIM8->PSC = DT_GetRegisterByIndex(13)->psc;
			TIM8->ARR = DT_GetRegisterByIndex(13)->arr;

			pNewFreqPresetEncoderPos = &aFreqPresetEncoderPos[13];
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
void FreqO_ApplyPreset(eFreq_Preset pPresetEnum)
{
	DacTimeReg_t* tmp = DT_GetRegisterByEnum(pPresetEnum);
	if(tmp)
	{
		TIM8->PSC = tmp->psc;
		TIM8->ARR = tmp->arr;
		//eNewFreqPreset = pPresetEnum;
		Freq_Preset_Encoder_Pos_t * tmp = FreqO_FindFPresetObject(pPresetEnum);
		if(tmp)
		{
			pNewFreqPresetEncoderPos = tmp;
		}

	}
}

/*
 *
 *	@brief Get currently set freq output preset
 *
 *	@param None
 *	@retval pointer to Freq_Preset_Encoder_Pos_t struct
 *
 */
Freq_Preset_Encoder_Pos_t * FreqO_GetFPresetObject()
{
	return pNewFreqPresetEncoderPos;
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

 *	@retval pointer to Freq_Preset_Encoder_Pos_t struct
 *
 */
Freq_Preset_Encoder_Pos_t * FreqO_FindFPresetObject(eFreq_Preset pEnum)
{
	for(int i = 0; i < MAX_NUM_FPRESETS; i++ )
	{
		if(aFreqPresetEncoderPos[i].hertz == pEnum)
		{
			return &aFreqPresetEncoderPos[i];
		}
	}
	// error!
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
	return TIM8->ARR;
}


#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_C_ */
