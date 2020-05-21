/*
 * GainMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include "GainMenuStateHandler.h"
#include "DisplayManager.h"
#include "SignalManager.h"
#include <stdio.h>

eGainMenu_Status eNextGainMenuStatus = 	DISABLE_GAIN_MENU;

eGainMenu_Status GainMenu_getStatus()
{
	return eNextGainMenuStatus;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainMainMenuEntryHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("GainMainMenuEntryHandler Event captured\n");
#endif

	DM_RefreshScreen();

	eNextGainMenuStatus = ENABLE_GAIN_MAIN_MENU;

	eNewEvent = evIdle;
	return Gain_Main_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainMainMenuInputHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("GainMainMenuInputHandler Event captured\n");
#endif

	//GO_ModifyOutput(SMGetEncoderValue(ENCODER_REVERSE));
	//VPP_MapEncoderPositionToSignalOutput(SMGetEncoderValue(ENCODER_REVERSE));

	eNewEvent = evYellowBtn;
	return Gain_Main_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainMainMenuExitHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("GainMainMenuExitHandler Event captured\n");
#endif

	eNextGainMenuStatus = DISABLE_GAIN_MENU;

	DM_RefreshScreen();

#ifdef SWV_DEBUG_ENABLED
	  printf("returning to Idle State\n");
#endif

	eNewEvent = evIdle;
	return Toplevel_Output_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainSignalMenuEntryHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("GainSignalMenuEntryHandler Event captured\n");
#endif

	DM_RefreshScreen();
	VPP_ResetLastEncoderValue();

	eNextGainMenuStatus = ENABLE_GAIN_SIGNAL_MENU;

	AmplitudeProfile_t* pTmpVppPreset = SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile;

	if(pTmpVppPreset)
	{
		ENCODER_TIMER->CNT = pTmpVppPreset->epos;
		ENCODER_TIMER->ARR = MAX_VPP_ENCODER_RANGE;
	}
	else
	{
		DM_SetErrorDebugMsg("GainMainMenuEntryHandler: pVppPresetTmp null pointer");
	}

	eNewEvent = evIdle;
	return Gain_Signal_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainSignalMenuInputHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("GainSignalMenuInputHandler Event captured\n");
#endif

	//GO_ModifyOutput(SMGetEncoderValue(ENCODER_REVERSE));
	VPP_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_REVERSE));

	eNewEvent = evYellowBtn;
	return Gain_Signal_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainSignalMenuExitHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("GainSignalMenuExitHandler Event captured\n");
#endif

	eNextGainMenuStatus = ENABLE_GAIN_MAIN_MENU;

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Gain_Main_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainSyncMenuEntryHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("GainSyncMenuEntryHandler Event captured\n");
#endif

	DM_RefreshScreen();
	VPP_ResetLastEncoderValue();

	eNextGainMenuStatus = ENABLE_GAIN_SYNC_MENU;

	AmplitudeProfile_t* pTmpVppPreset = SM_GetOutputChannel(SYNC_CHANNEL)->amp_profile;

	if(pTmpVppPreset)
	{
		ENCODER_TIMER->CNT = pTmpVppPreset->epos;
		ENCODER_TIMER->ARR = MAX_VPP_ENCODER_RANGE;
	}
	else
	{
		DM_SetErrorDebugMsg("GainMainMenuEntryHandler: pVppPresetTmp null pointer");
	}

	eNewEvent = evIdle;
	return Gain_Sync_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainSyncMenuInputHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("GainSyncMenuInputHandler Event captured\n");
#endif

	//GO_ModifyOutput(SMGetEncoderValue(ENCODER_REVERSE));
	VPP_MapEncoderPositionToSyncOutput(SM_GetEncoderValue(ENCODER_REVERSE));

	eNewEvent = evYellowBtn;
	return Gain_Sync_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState GainSyncMenuExitHandler()
{
#ifdef SWV_DEBUG_ENABLED
	printf("GainSyncMenuExitHandler Event captured\n");
#endif

	eNextGainMenuStatus = ENABLE_GAIN_MAIN_MENU;

	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Gain_Main_Menu_State;
}

