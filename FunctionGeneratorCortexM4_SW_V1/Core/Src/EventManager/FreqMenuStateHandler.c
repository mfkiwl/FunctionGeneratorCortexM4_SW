/*
 * FreqMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#include "FreqMenuStateHandler.h"

#include "DisplayManager.h"
#include "SignalManager.h"
#include <stdio.h>

///////////////////////////////////////////////////////
//////    "FREQUENCY" EVENTHANDLER FUNCTIONS	///////
///////////////////////////////////////////////////////

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqMainMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqMenu Event captured\n");
#endif

	DM_RefreshScreen();

	DM_ShowFreqMenu(ENABLE_FREQ_MAIN_MENU);

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Main_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqMainMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqSet Event captured\n");
#endif


	return Freq_Main_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqMainMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Main Menu Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Idle_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqPresetMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Freq Preset Menu Entry Event captured\n");
#endif

	DM_RefreshScreen();

	DM_ShowFreqMenu(ENABLE_FREQ_PRESET_MENU);

	Freq_Preset_Encoder_Pos_t *pFreqPresetTmp =  FreqO_GetFPresetObject();
	if(pFreqPresetTmp)
	{
		ENCODER_TIMER->CNT = pFreqPresetTmp->epos;
		ENCODER_TIMER->ARR = FreqO_GetFreqPresetEncoderRange();
	}
	else
	{
		DM_SetErrorDebugMsg("_FreqPresetMenuEntryHandler: pFreqPresetTmp null pointer");
	}


	// stay in this state
	eNewEvent = evIdle;
	return Freq_Preset_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqPresetMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqSet Event captured\n");
#endif

	FreqO_ModifyOutput(SM_GetEncoderValue(ENCODER_REVERSE));

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Preset_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqPresetMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Menu Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

	// back to main freq menu
	eNewEvent = evGreenBtn;
	return Idle_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqAdjustMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Freq Adjust Menu Event captured\n");
#endif

	DM_RefreshScreen();

	DM_ShowFreqMenu(ENABLE_FREQ_ADJUST_MENU);

	// set the rotary encoder limits to 0-? for this menu
	ENCODER_TIMER->CNT = TIM8->ARR;
	ENCODER_TIMER->ARR = 65535;

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Adjust_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqAdjustMenuInputHandler()
{
#ifdef EM_SWV_DEBUG
	printf("FreqSet Event captured\n");
#endif

	FreqO_AdjustFreq();

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Adjust_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqAdjustMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Adjust Menu Exit Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

	// back to main freq menu
	eNewEvent = evGreenBtn;
	return Idle_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqSweepMenuEntryHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Freq Sweep Menu Event captured\n");
#endif

	DM_RefreshScreen();

	DM_ShowFreqMenu(ENABLE_FREQ_SWEEP_MENU);

	// set the rotary encoder limits to 0-? for this menu
	ENCODER_TIMER->CNT = 0;
	ENCODER_TIMER->ARR = 56;

	// stay in this state
	eNewEvent = evIdle;
	return Freq_Sweep_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FreqSweepMenuExitHandler()
{
#ifdef EM_SWV_DEBUG
	printf("Exit Freq Sweep Menu Exit Event captured\n");
#endif


	// disable the menu
	DM_ShowFreqMenu(DISABLE_FREQ_MENU);

	// back to main freq menu
	eNewEvent = evGreenBtn;
	return Idle_State;
}
