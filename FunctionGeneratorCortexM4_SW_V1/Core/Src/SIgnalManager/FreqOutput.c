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


/*
 *
 *
 *
 */
void FreqO_ModifyOutput()
{
	TIM8->ARR = TIM1->CNT;
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

#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_C_ */
