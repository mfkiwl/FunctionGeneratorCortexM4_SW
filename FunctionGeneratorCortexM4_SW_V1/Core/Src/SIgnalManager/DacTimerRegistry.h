/*
 * DacTimer.h
 *
 *  Created on: 12 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_DACTIMERREGISTRY_H_
#define SRC_SIGNALMANAGER_DACTIMERREGISTRY_H_

#include "SignalManager.h"

#include <stdint.h>

#define MAX_DAC_TIMER_SETTINGS 14



typedef struct
{
	uint8_t 		id;				// index
	eFreq_Preset 	hertz;			// freq enum
	uint32_t		psc;			// MCU timer prescaler. Default 0. Set higher for freq < 20Hz.
	uint32_t		arr;			// MCU timer auto-reload (top). Set by DT_InitRegister()
	float			error;			// coefficient for error correction, set to 1.0 if not required
									// 0 < error < 1	- correction for under freq (increase)
									// 1 < error		- correction for over freq (decrease)

} DacTimeReg_t;

DacTimeReg_t DacTimerReg[MAX_DAC_TIMER_SETTINGS];

void DT_InitRegister();
DacTimeReg_t* DT_GetRegisterByIndex(uint8_t pIndex);
DacTimeReg_t* DT_GetRegisterByEnum(eFreq_Preset pEnum);

#endif /* SRC_SIGNALMANAGER_DACTIMERREGISTRY_H_ */