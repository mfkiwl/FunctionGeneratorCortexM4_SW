/*
 * InputTrigger.h
 *
 *  Created on: 3 Jun 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_INPUTTRIGGER_H_
#define SRC_SIGNALMANAGER_INPUTTRIGGER_H_

#include <stdint.h>

// Enumerations

typedef enum
{
	DISABLE_TRIGGER 	= 	0U,
	ENABLE_TRIGGER	= 	1U,
} eTriggerInput;

typedef enum
{
	//INPUT_TIMER_DISABLED = 0U,
	INPUT_TIMER_TIM,
	INPUT_TIMER_COMP,
	INPUT_TIMER_ADC
} eTriggerInputMode;

typedef struct
{
		char note_string[4];
		float volts;
		float hertz;
		uint16_t period;

} VoltsPerOctave_t;

#define MAX_VOLTS_PER_OCTAVE_INDEX 40
VoltsPerOctave_t theVoltsPerOctaveTable[MAX_VOLTS_PER_OCTAVE_INDEX];

// Public functions

void 				IT_CycleInputTriggerMode();
void 				IT_ArbitrateInputTrigger();

eTriggerInput 		IT_GetTriggerStatus();
void 				IT_SetTriggerStatus(eTriggerInput newTriggerStatus);
eTriggerInputMode 	IT_GetActiveTriggerMode();
void 				IT_SetActiveTriggerMode(eTriggerInputMode newTriggerMode);

float 				IT_GetAvgAdcVoltage();

float IT_GetAverageFreqCountPeriod();
float IT_GetAverageFreqCountHertz();

#endif /* SRC_SIGNALMANAGER_INPUTTRIGGER_H_ */
