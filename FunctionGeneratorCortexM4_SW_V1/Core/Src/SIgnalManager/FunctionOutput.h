/*
 * FunctionOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FUNCTIONOUTPUT_H_
#define SRC_SIGNALMANAGER_FUNCTIONOUTPUT_H_

#include <stdint.h>

uint8_t FuncPresetEncoderRange;

typedef enum
{
	SINE_FUNC_MODE,
	SQUARE_FUNC_MODE,
	SAW_FUNC_MODE,
	REV_SAW_FUNC_MODE,
	TRIANGLE_FUNC_MODE,
	IMPULSE_FUNC_MODE

} eOutput_mode;


#define MAX_NUM_FUNC_PRESETS 6

/*
 *	object for Function Preset and its encoder position for func preset menu
 */
typedef struct
{
	eOutput_mode func;
	uint8_t epos;

} Func_Preset_Encoder_Pos_t;

Func_Preset_Encoder_Pos_t aFuncPresetEncoderPos[MAX_NUM_FUNC_PRESETS];

/*
 * 		The Currently Used Function Preset
 */
Func_Preset_Encoder_Pos_t *pNewFuncPresetEncoderPos;


/*
 *  Function declarations
 */
void FuncO_ModifyOutput(uint16_t pEncoderValue);


//void FuncO_ApplyPreset(eOutput_mode pPresetEnum);
void FuncO_ApplyPreset_Fast(eOutput_mode pPresetEnum);

Func_Preset_Encoder_Pos_t * FuncO_FindFPresetObject(eOutput_mode pEnum);
Func_Preset_Encoder_Pos_t * FuncO_GetFPresetObject();

void FuncO_SetNewDataTable(uint32_t * pdata_table);

uint8_t FuncO_GetFuncPresetEncoderRange();


#endif /* SRC_SIGNALMANAGER_FUNCTIONOUTPUT_H_ */
