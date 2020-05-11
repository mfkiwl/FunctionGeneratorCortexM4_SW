/*
 * FreqOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FREQOUTPUT_C_
#define SRC_SIGNALMANAGER_FREQOUTPUT_C_

#include "FreqOutput.h"

#include "tim.h"

#include "SignalManager.h"

eFreq_Preset eNewFreqPreset = FPRESET_100HZ;

/*
 *
 *
 *
 */
void FreqO_ModifyOutput()
{

	switch(SM_GetEncoderValue(ENCODER_REVERSE))
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
	/*
	if( (eNewFreqPreset == FPRESET_100KHZ) || (eNewFreqPreset == FPRESET_1KHZ))
		TIM8->ARR = SM_GetEncoderValue(ENCODER_FORWARD) * FREQ_ENCODER_HIFREQ_MAG;
	else if (eNewFreqPreset == FPRESET_100HZ)
		TIM8->ARR = SM_GetEncoderValue(ENCODER_FORWARD) * FREQ_ENCODER_MIDFREQ_MAG;
	else if (eNewFreqPreset == FPRESET_1HZ)
		TIM8->ARR = SM_GetEncoderValue(ENCODER_FORWARD) * FREQ_ENCODER_LOFREQ_MAG;
	*/
}

/*
 *
 *
 *
 */
uint32_t FreqO_GetOutputFreq()
{
	return TIM8->ARR;
}

/*
 *
 *
 *
 */
void FreqO_ApplyPreset(eFreq_Preset pPreset)
{
	switch(pPreset)
	{
		case FPRESET_1HZ:
			TIM8->PSC = 0x0014;
			TIM8->ARR = 0xFFFF;

			eNewFreqPreset = FPRESET_1HZ;
			break;
		case FPRESET_10HZ:
			TIM8->PSC = 0x0003;
			TIM8->ARR = 0x87FF;

			eNewFreqPreset = FPRESET_10HZ;
			break;
		case FPRESET_50HZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x6D00;

			eNewFreqPreset = FPRESET_50HZ;
			break;
		case FPRESET_100HZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x37FF;

			eNewFreqPreset = FPRESET_100HZ;
			break;
		case FPRESET_250HZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x163F;

			eNewFreqPreset = FPRESET_250HZ;
			break;
		case FPRESET_500HZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x0AFF;

			eNewFreqPreset = FPRESET_500HZ;
			break;
		case FPRESET_750HZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x07BF;

			eNewFreqPreset = FPRESET_750HZ;
			break;
		case FPRESET_1KHZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x0577;

			eNewFreqPreset = FPRESET_1KHZ;
			break;
		case FPRESET_5KHZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x0118;

			eNewFreqPreset = FPRESET_5KHZ;
			break;
		case FPRESET_10KHZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x008B;

			eNewFreqPreset = FPRESET_10KHZ;
			break;
		case FPRESET_25KHZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x0037;

			eNewFreqPreset = FPRESET_25KHZ;
			break;
		case FPRESET_50KHZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x001B;

			eNewFreqPreset = FPRESET_50KHZ;
			break;
		case FPRESET_75KHZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x0012;

			eNewFreqPreset = FPRESET_75KHZ;
			break;
		case FPRESET_100KHZ:
			TIM8->PSC = 0x0000;
			TIM8->ARR = 0x0006;

			eNewFreqPreset = FPRESET_100KHZ;
			break;
	}
}

eFreq_Preset FreqO_GetFPreset()
{
	return eNewFreqPreset;
}

#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_C_ */
