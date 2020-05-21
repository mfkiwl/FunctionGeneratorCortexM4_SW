/*
 * FreqOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FREQOUTPUT_H_
#define SRC_SIGNALMANAGER_FREQOUTPUT_H_

#include <stdint.h>

uint8_t FreqPresetEncoderRange;

/*
 *	Frequency Preset value enumerations
 */
typedef enum
{
	FPRESET_1HZ 	= 1U,
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

} eFreqSettings_t;

#define MAX_NUM_FREQ_PRESETS 14

/*
 *	object for Frequency Preset and its encoder position for freq preset menu
 */
typedef struct
{
	eFreqSettings_t hertz;
	uint8_t epos;
	uint16_t index;

} FreqProfile_t;

FreqProfile_t theFreqProfiles[MAX_NUM_FREQ_PRESETS];

/*
 * 		The Currently Used Frequency Preset
 */
FreqProfile_t *freq_profile;

/*
 *
 */
#define FREQ_ENCODER_HIFREQ_MAG 1						// adjustment speed
#define FREQ_ENCODER_MIDFREQ_MAG 5						// adjustment speed
#define FREQ_ENCODER_LOFREQ_MAG 10						// adjustment speed
#define FREQ_ENCODER_MAX 65535

/*
 *  Function definitions
 */
void FreqO_ModifyOutput(uint16_t pEncValue);
uint32_t FreqO_GetOutputFreq();

void FreqO_ApplyPreset(eFreqSettings_t pPresetEnum);
void FreqO_ApplyPreset_Fast(eFreqSettings_t pPresetEnum);


FreqProfile_t * FreqO_FindFPresetObject(eFreqSettings_t pEnum);
FreqProfile_t * FreqO_GetFPresetObject();

void FreqO_AdjustFreq();

void FreqO_ResetLastEncoderValue();

uint8_t FreqO_GetPresetEncoderPos();
uint8_t FreqO_GetFreqPresetEncoderRange();


#endif /* SRC_SIGNALMANAGER_FREQOUTPUT_H_ */
