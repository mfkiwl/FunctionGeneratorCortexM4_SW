/*
 * FunctionOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FUNCTIONOUTPUT_H_
#define SRC_SIGNALMANAGER_FUNCTIONOUTPUT_H_

#include <stdint.h>
#include "pysine.h"
#include "pysquare.h"
#include "pyunitimpulse.h"
#include "pysaw.h"
#include "pysaw_rev.h"
#include "pytriangle.h"

uint8_t FuncPresetEncoderRange;

typedef enum
{
	SINE_FUNC_MODE = 0U,
	SQUARE_FUNC_MODE,
	SAW_FUNC_MODE,
	REV_SAW_FUNC_MODE,
	TRIANGLE_FUNC_MODE,
	IMPULSE_FUNC_MODE,
	PWM_FUNC_MODE

} eOutput_mode;


#define MAX_NUM_FUNC_PRESETS 7

/*
 *	object for Function Preset and its encoder position for func preset menu
 */
typedef struct
{
	eOutput_mode func;
	uint32_t *lookup_table_data;


} FunctionProfile_t;

FunctionProfile_t theFuncProfiles[MAX_NUM_FUNC_PRESETS];


void 				FuncO_Init();

void 				FuncO_EnablePWMToSignal();
void 				FuncO_DisablePWMToSignal();
void 				FuncO_EnableDacToSignal();
void 				FuncO_DisableDacToSignal();

void 				FuncO_MapEncoderPositionToSignalOutput(uint16_t pEncoderValue);
void 				FuncO_ApplyProfileToSignal(eOutput_mode pPresetEnum);

void 				FuncO_MapEncoderPositionToAuxOutput(uint16_t pEncoderValue);
void 				FuncO_ApplyProfileToAux(eOutput_mode pPresetEnum);

FunctionProfile_t * FuncO_FindFPresetObject(eOutput_mode pEnum);
FunctionProfile_t * FuncO_GetSignalFPresetObject();
FunctionProfile_t * FuncO_GetAuxFPresetObject();
void 				FuncO_ResetLastEncoderValue();


#endif /* SRC_SIGNALMANAGER_FUNCTIONOUTPUT_H_ */
