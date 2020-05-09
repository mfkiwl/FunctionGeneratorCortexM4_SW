/*
 * EventManager.c
 *
 *  Created on: May 8, 2020
 *      Author: chris
 */


#include "EventManager.h"
#include "DisplayManager.h"
#include "FunctionOutput.h"
#include "GainOutput.h"
//#include "funcgen.h"

#include "dac.h"
#include "tim.h"

#include <stdio.h>



// public function prototypes
void EM_SetNewEvent(eSystemEvent pEvent);



// private function prototypes
eSystemState _FuncMenuHandler();
eSystemState _FuncSetHandler();
eSystemState _ExitFuncMenuHandler();

eSystemState _GainMenuHandler();
eSystemState _GainSetHandler();
eSystemState _ExitGainMenuHandler();

eSystemState _FreqMenuHandler();
eSystemState _FreqSetHandler();
eSystemState _ExitFreqMenuHandler();

eSystemState _BiasMenuHandler();
eSystemState _BiasSetHandler();
eSystemState _ExitBiasMenuHandler();

eSystemState _AdjustConfirmedHandler();



// state machine
eSystemState eNextState = Idle_State;
eSystemEvent eNewEvent = evIdle;





// dc bias constants
#define BIAS_MAG 10						// adjustment speed
#define BIAS_MAX 8092/BIAS_MAG			// The encoder max value: top=max pos bias, 0=max neg bias
#define BIAS_CENTER	4096/BIAS_MAG		// the encoder center value: zero crossing point


// rotary encoder value
uint32_t newRotEncoderValue = 0;
uint32_t oldRotEncoderValue = 0;

/*
 *
 * 	Main state machine for event process
 *
 */
void EM_ProcessEvent()
{

	switch(eNextState)
	{
		case Idle_State:
			if(eNewEvent == evFuncMenu)
			{
				eNextState = _FuncMenuHandler();
			}
			if(eNewEvent == evFreqMenu)
			{
				eNextState = _FreqMenuHandler();
			}
			if(eNewEvent == evGainMenu)
			{
				eNextState = _GainMenuHandler();
			}
			if(eNewEvent == evBiasMenu)
			{
				eNextState = _BiasMenuHandler();
			}

			break;

		case Func_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _FuncSetHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _ExitFuncMenuHandler();
			}
			break;

		case Gain_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _GainSetHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _ExitGainMenuHandler();
			}
			break;

		case Freq_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _FreqSetHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _ExitFreqMenuHandler();
			}
			break;

		case Bias_Menu_State:
			if(eNewEvent == evEncoderSet)
			{
				eNextState = _BiasSetHandler();
			}
			if(eNewEvent == evEncoderPush)
			{
				eNextState = _ExitBiasMenuHandler();
			}
			break;

		default:
			break;
	}

}

///////////////////////////////////////////////////////
//////		PRIVATE EVENTHANDLER FUNCTIONS		///////
///////////////////////////////////////////////////////

/*
 *
 *	Business logic for evFunctionMenu events
 *
 */
eSystemState _FuncMenuHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("FunctionMenu Event captured\n");
#endif

	DM_ShowFuncSelectMenu(ENABLE_FUNCMENU);

	// set the rotary encoder limits to 0-20 for this menu
	TIM1->ARR = 20;

	return Func_Menu_State;
}

/*
 *
 *	Business logic for evFunctionSet events
 *
 */
eSystemState _FuncSetHandler(void)
{
#ifdef EM_SWV_DEBUG
	printf("FunctionAdjust Event captured\n");
#endif

	FO_ModifyOutput();
	eNewEvent = evFuncMenu;
	return Func_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _ExitFuncMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitFuncMenu Event captured\n");
#endif

	// disable the menu
	DM_ShowFuncSelectMenu(DISABLE_FUNCMENU);

	// reset the encoder range
	TIM1->ARR = 1024;

	// don't let the DisplayManager interrupt the LCD refresh
	HAL_TIM_Base_Stop_IT(&htim15);
	{
		DM_RefreshBackgroundLayout();
	}
	HAL_TIM_Base_Start_IT(&htim15);

	eNewEvent = evIdle;
	return Idle_State;
}


/*
 *
 *	Business logic for AmplitudeAdjust events
 *
 */
eSystemState _GainMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainMenu Event captured\n");
#endif
	DM_ShowGainSelectMenu(ENABLE_GAINMENU);

	// set the rotary encoder limits to 0-20 for this menu
	TIM1->ARR = 32;

	return Gain_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _GainSetHandler()
{
#ifdef EM_SWV_DEBUG
	printf("GainSet Event captured\n");
#endif

	GO_ModifyOutput();

	eNewEvent = evGainMenu;
	return Gain_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _ExitGainMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitGainMenu Event captured\n");
#endif


	// disable the menu
	DM_ShowGainSelectMenu(DISABLE_GAINMENU);

	// reset the encoder range
	TIM1->ARR = 1024;

	// don't let the DisplayManager interrupt the LCD refresh
	HAL_TIM_Base_Stop_IT(&htim15);
	{
		DM_RefreshBackgroundLayout();
	}
	HAL_TIM_Base_Start_IT(&htim15);

	eNewEvent = evIdle;
	return Idle_State;
}

/*
 *
 *	Business logic for BiasMenu events
 *
 */
eSystemState _BiasMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("BiasMenu Event captured\n");
#endif
	DM_ShowBiasSelectMenu(ENABLE_BIASMENU);

	// set the rotary encoder limits to 0-20 for this menu


	TIM1->ARR = BIAS_MAX;
	TIM1->CNT = BIAS_CENTER;

	return Bias_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _BiasSetHandler()
{
#ifdef EM_SWV_DEBUG
	printf("BiasSet Event captured\n");
#endif

	// apply negative dc bias
	if(TIM1->CNT < 400) {
		HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_2, DAC_ALIGN_12B_R, (BIAS_CENTER-TIM1->CNT)*BIAS_MAG);
	  HAL_GPIO_WritePin(DCBIAS_INVERT_GPIO_Port, DCBIAS_INVERT_Pin, GPIO_PIN_SET);
	}
	// apply positive dc bias
	if(TIM1->CNT >= 400) {
		HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_2, DAC_ALIGN_12B_R, (TIM1->CNT-BIAS_CENTER)*BIAS_MAG);
		HAL_GPIO_WritePin(DCBIAS_INVERT_GPIO_Port, DCBIAS_INVERT_Pin, GPIO_PIN_RESET);
	}

	eNewEvent = evBiasMenu;
	return Bias_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _ExitBiasMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitBiasMenu Event captured\n");
#endif


	// disable the menu
	DM_ShowBiasSelectMenu(DISABLE_BIASMENU);

	// reset the encoder range
	TIM1->ARR = 1024;

	// don't let the DisplayManager interrupt the LCD refresh
	HAL_TIM_Base_Stop_IT(&htim15);
	{
		DM_RefreshBackgroundLayout();
	}
	HAL_TIM_Base_Start_IT(&htim15);

	eNewEvent = evIdle;
	return Idle_State;
}

/*
 *
 *	Business logic for FREQ MENU events
 *
 */
eSystemState _FreqMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqMenu Event captured\n");
#endif
	DM_ShowFreqSelectMenu(ENABLE_FREQMENU);

	// set the rotary encoder limits to 0-20 for this menu
	TIM1->ARR = 1024;

	return Freq_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _FreqSetHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqSet Event captured\n");
#endif

	TIM8->ARR = TIM1->CNT;
	eNewEvent = evFreqMenu;
	return Freq_Menu_State;
}

/*
 *
 *
 *
 */
eSystemState _ExitFreqMenuHandler()
{
#ifdef EM_SWV_DEBUG
	printf("ExitFreqMenu Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqSelectMenu(DISABLE_FREQMENU);

	// reset the encoder range
	TIM1->ARR = 1024;

	// don't let the DisplayManager interrupt the LCD refresh
	HAL_TIM_Base_Stop_IT(&htim15);
	{
		DM_RefreshBackgroundLayout();
	}
	HAL_TIM_Base_Start_IT(&htim15);

	eNewEvent = evIdle;
	return Idle_State;
}





/*
 *
 * 	Set by NVIC interrupt handlers
 *
 */
void EM_SetNewEvent(eSystemEvent pEvent)
{
	eNewEvent = pEvent;
}




/*
 *
 *
 *
 */
uint32_t EM_GetOutputFreq()
{
	return TIM8->ARR;
}


/*
 *
 *
 *
 */
uint32_t EM_GetOutputBias()
{
	return HAL_DAC_GetValue(&hdac1, DAC1_CHANNEL_2);
}

/*
 *
 *
 *
 */
eSystemState EM_GetSystemState()
{
	return eNextState;
}

/*
 *
 *
 *
 */
void EM_SetEncoderValue(uint32_t pValue)
{
	newRotEncoderValue = pValue;


}






