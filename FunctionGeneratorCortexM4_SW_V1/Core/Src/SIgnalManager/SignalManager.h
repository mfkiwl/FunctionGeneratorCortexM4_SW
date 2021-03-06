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
#include "InputTrigger.h"

#include "pysineicon.h"
#include "pysquareicon.h"
#include "pysawicon.h"
#include "pysawicon_rev.h"
#include "pytriangleicon.h"
#include "pyunitimpulse.h"

#include <stdio.h>

#include "tim.h"

#define ENCODER_TIMER	TIM1
#define SM_MCLK 168000000		// MCU master clock frequency
#define SM_FSAMP 120			// sampling frequency, defined in WaveTableGeneratiom scripts

#define OUTPUT_TIMER TIM8
#define SWEEP_TIMER TIM5
#define INPUT_TIMER TIM2

#define PWM_AUX_OUT_TIM	TIM3

#define DAC_TRIGGER_TRGO DAC_TRIGGER_T2_TRGO

#define eDefaultFreqPreset 	FPRESET_1KHZ
#define eDefaultFuncPreset 	SINE_FUNC_MODE
#define eDefaultGainPreset  SEVEN_GAIN
#define eDefaultVppPreset 	VPP90

// enable printf/SWV debug messages
//#define EVENT_MENU_DEBUG

uint32_t comp1_output_value[1];

uint32_t recip_counter;

// shortest output period permitted
#define MIN_OUTPUT_ARR 	13		//107KHz if SM_CLKC=168000000 and OUTPUT_TIMER->PSC=0

// longest output period permitted
#define MAX_OUTPUT_ARR 0xFFFF

// shortest sweep period permitted
//#define MIN_SWEEP_ARR = 3555		//50KHz if SM_CLKC=168000000 and SWEEP_TIMER->PSC=0
#define MIN_SWEEP_ARR 	16800		//10KHz if SM_CLKC=168000000 and SWEEP_TIMER->PSC=0
//#define MIN_SWEEP_ARR	33600		//5KHz if SM_CLKC=168000000 and SWEEP_TIMER->PSC=0
//#define MIN_SWEEP_ARR	84000		//2KHz if SM_CLKC=168000000 and SWEEP_TIMER->PSC=0
//#define MIN_SWEEP_ARR	16800		//1KHz if SM_CLKC=168000000 and SWEEP_TIMER->PSC=0

// longest sweep period permitted
#define MAX_SWEEP_ARR 0xFFFFFFF

typedef enum
{
	ENCODER_NORMAL = 0U,
	ENCODER_INVERSE

} eEncoder_Inversion;

typedef enum
{
	SIGNAL_CHANNEL = 0U,
	AUX_CHANNEL

} eOutputChannel_t;

typedef struct
{
	// the output channel type: Signal or Aux Aux
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


DMA_HandleTypeDef hdma_dac1_ch1;
TIM_HandleTypeDef htim3;


void SM_Init();
sOutputChannel_t * SM_GetOutputChannel(eOutputChannel_t pChannel);

uint16_t SM_GetEncoderValue(eEncoder_Inversion direction);
float SM_GetOutputInHertz();

float SM_ConvertPeriodToHertz(uint32_t period, uint16_t psc);
uint16_t SM_ConvertHertzToPeriod(float hertz, uint16_t psc);


/*void SM_EnablePwmToSignal();
void SM_DisablePwmToSignal();
void SM_EnableDacToSignal();
void SM_DisableDacToSignal();
*/
void SM_EnablePwmToAux();
void SM_DisablePwmToAux();
void SM_EnableDacToAux();
void SM_DisableDacToAux();

uint8_t SM_IsFuncPwmDutyMode();
void SM_ToggleFuncPwmDutyMode();
void SM_ResetFuncPwmDutyMode();


#endif /* SRC_SIGNALMANAGER_SIGNALMANAGER_H_ */
