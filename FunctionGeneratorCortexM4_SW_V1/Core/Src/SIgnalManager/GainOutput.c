/*
 * GainOutput.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#include "GainOutput.h"
#include "DisplayManager.h"


/*
 *	Array of objects for Gain Presets and their encoder positions for gain preset menu
 */
GainProfile_t theGainProfiles[MAX_NUM_GAIN_PRESETS] =
{
	{ ZERO_GAIN,	-1, 28 },
	{ ONE_GAIN,		0,  24 },
	{ TWO_GAIN,		6,  20 },
	{ THREE_GAIN,	9,  16 },
	{ FOUR_GAIN, 	12, 12 },
	{ FIVE_GAIN, 	14, 8  },
	{ SIX_GAIN,		16, 4  },
	{ SEVEN_GAIN, 	18, 0  }

};

uint8_t GainPresetEncoderRange = 28;



// signal output gain
//eGainSettings_t eNewOutGain = ONE_GAIN;


void GO_MapEncoderPositionToSyncOutput(uint16_t pEncoderValue)
{
	switch(pEncoderValue)
	{
		case 0: case 1: case 2:
			GO_ApplyPresetToSync(ZERO_GAIN);
			break;

		case 3: case 4: case 5: case 6:
			GO_ApplyPresetToSync(ONE_GAIN);
			break;

		case 7: case 8: case 9: case 10:
			GO_ApplyPresetToSync(TWO_GAIN);
			break;

		case 11: case 12: case 13: case 14:
			GO_ApplyPresetToSync(THREE_GAIN);
			break;

		case 15: case 16: case 17: case 18:
			GO_ApplyPresetToSync(FOUR_GAIN);
			break;

		case 19: case 20: case 21: case 22:
			GO_ApplyPresetToSync(FIVE_GAIN);
			break;

		case 23: case 24: case 25: case 26:
			GO_ApplyPresetToSync(SIX_GAIN);
			break;

		case 27: case 28: case 29: case 30:
			GO_ApplyPresetToSync(SEVEN_GAIN);
			break;
	}


}

void GO_MapEncoderPositionToSignalOutput(uint16_t pEncoderValue)
{
	switch(pEncoderValue)
	{
		case 0: case 1: case 2:
			GO_ApplyPresetToSignal(ZERO_GAIN);
			break;

		case 3: case 4: case 5: case 6:
			GO_ApplyPresetToSignal(ONE_GAIN);
			break;

		case 7: case 8: case 9: case 10:
			GO_ApplyPresetToSignal(TWO_GAIN);
			break;

		case 11: case 12: case 13: case 14:
			GO_ApplyPresetToSignal(THREE_GAIN);
			break;

		case 15: case 16: case 17: case 18:
			GO_ApplyPresetToSignal(FOUR_GAIN);
			break;

		case 19: case 20: case 21: case 22:
			GO_ApplyPresetToSignal(FIVE_GAIN);
			break;

		case 23: case 24: case 25: case 26:
			GO_ApplyPresetToSignal(SIX_GAIN);
			break;

		case 27: case 28: case 29: case 30:
			GO_ApplyPresetToSignal(SEVEN_GAIN);
			break;
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void GO_ApplyPresetToSignal(eGainSettings_t pPresetEnum)
{
	SM_GetOutputChannel(SIGNAL_CHANNEL)->gain_profile = &theGainProfiles[pPresetEnum];

	switch(pPresetEnum)
	{
		case ZERO_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			break;

		case ONE_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			break;

		case TWO_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			break;

		case THREE_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			break;

		case FOUR_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			break;

		case FIVE_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			break;

		case SIX_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			break;

		case SEVEN_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			break;
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void GO_ApplyPresetToSync(eGainSettings_t pPresetEnum)
{
	SM_GetOutputChannel(SYNC_CHANNEL)->gain_profile = &theGainProfiles[pPresetEnum];

	switch(pPresetEnum)
	{
		case ZERO_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			break;

		case ONE_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			break;

		case TWO_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			break;

		case THREE_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_RESET);
			break;

		case FOUR_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			break;

		case FIVE_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			break;

		case SIX_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			break;

		case SEVEN_GAIN:
			HAL_GPIO_WritePin(SG0_GPIO_Port, SG0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG1_GPIO_Port, SG1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SG2_GPIO_Port, SG2_Pin, GPIO_PIN_SET);
			break;
	}
}



/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
GainProfile_t * GO_FindGPresetObject(eGainSettings_t pEnum)
{

	for(int i = 0; i < MAX_NUM_GAIN_PRESETS; i++ )
	{
		if(theGainProfiles[i].gain == pEnum)
		{
			return &theGainProfiles[i];
		}
	}
	// error!
	DM_SetErrorDebugMsg("GO_FindGPresetObject(): no GPreset obj found");
	return 0;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
uint8_t GO_GetGainPresetEncoderRange()
{
	return GainPresetEncoderRange;
}


