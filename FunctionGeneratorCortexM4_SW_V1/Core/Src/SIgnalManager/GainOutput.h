/*
 * GainOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_GAINOUTPUT_H_
#define SRC_SIGNALMANAGER_GAINOUTPUT_H_

#include <stdint.h>
#include "pysine.h"



// signal output gain settings
typedef enum
{
	ZERO_GAIN = 0U,
	ONE_GAIN,
	TWO_GAIN,
	THREE_GAIN,
	FOUR_GAIN,
	FIVE_GAIN,
	SIX_GAIN,
	SEVEN_GAIN

} eGainSettings_t;


#define MAX_NUM_GAIN_PRESETS 8

/*
 *	object for Frequency Preset and its encoder position for freq preset menu
 */
typedef struct
{
	eGainSettings_t gain;
	int8_t decibels;
	uint8_t epos;

} GainProfile_t;

GainProfile_t theGainProfiles[MAX_NUM_GAIN_PRESETS];


void GO_MapEncoderPositionToSignalOutput(uint16_t pEncoderValue);
void GO_ApplyPresetToSignal(eGainSettings_t pPresetEnum);



GainProfile_t * GO_FindGPresetObject(eGainSettings_t pEnum);

void GO_ResetLastEncoderValue();


uint8_t GO_GetGainPresetEncoderRange();

#endif /* SRC_SIGNALMANAGER_GAINOUTPUT_H_ */
