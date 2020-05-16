/*
 * SignalManager.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_SIGNALMANAGER_H_
#define SRC_SIGNALMANAGER_SIGNALMANAGER_H_

#include "FunctionOutput.h"
#include "GainOutput.h"
#include "VoltPeakPeakOutput.h"
#include "BiasOutput.h"
#include "FreqOutput.h"
#include "DacTimerRegistry.h"

#include "tim.h"

#define ENCODER_TIMER	TIM1
#define SM_MCLK 168000000		// MCU master clock frequency
#define SM_FSAMP 120			// sampling frequency, defined in WaveTableGeneratiom scripts

#define OUTPUT_TIMER TIM8

#define eDefaultFreqPreset 	FPRESET_1KHZ
#define eDefaultFuncPreset 	SINE_FUNC_MODE
#define eDefaultGainPreset 	ONE_GAIN
#define eDefaultVppPreset 	VPP90

typedef enum
{
	ENCODER_FORWARD = 0U,
	ENCODER_REVERSE

} eEncoder_Direction;

typedef enum
{
	SIGNAL_CHANNEL = 0U,
	SYNC_CHANNEL

} eOutputChannel_t;

typedef struct
{
	// the output channel type: Signal or Aux sync
	eOutputChannel_t channel;

	// Waveform lookup table data, used to restore the waveform to its default
	uint32_t *ref_lut_data;

	// Modified version of 'ref_lut_data'. Passed to the DAC periph via DMA.
	uint32_t dsp_lut_data[SINE_DATA_SIZE];

	// object of associated function data
	FunctionProfile_t *func_profile;

	// object of associated DSP data
	AmplitudeProfile_t* amp_profile;

	// object of associated PGA
	GainProfile_t *gain_profile;


} sOutputChannel_t;

void SM_Init();
sOutputChannel_t * SM_GetOutputChannel(eOutputChannel_t pChannel);

uint16_t SM_GetEncoderValue(eEncoder_Direction direction);
float SM_GetOutputInHertz();


#endif /* SRC_SIGNALMANAGER_SIGNALMANAGER_H_ */
