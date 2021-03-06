/*
 * BiasMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include "BiasMenuStateHandler.h"

#include "DisplayManager.h"
#include "SignalManager.h"
#include <stdio.h>

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState BiasMenuEntryHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("BiasMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	//_setBiasMenuStatus(ENABLE_BIAS_MENU);

	ENCODER_TIMER->ARR = BIAS_MAX;
	ENCODER_TIMER->CNT = BO_GetDcBiasEncoderValue();

	eNewEvent = evIdle;
	return Bias_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState BiasMenuInputHandler(eSystemEvent pEvent)
{
	#ifdef EVENT_MENU_DEBUG
		printf("BiasMenuInputHandler Event captured\n");
	#endif


	switch(pEvent)
	{
		case evEncoderSet:
			BO_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_NORMAL));
			break;
		case evBlueBtn:
			BO_MapEncoderPositionToSignalOutput(BIAS_MAX);
			ENCODER_TIMER->CNT = BIAS_MAX;
			break;
		case evGreenBtn:
			BO_MapEncoderPositionToSignalOutput(10);
			ENCODER_TIMER->CNT = 10;
			break;
		case evYellowBtn:
			// jump to zero crossing point
			BO_MapEncoderPositionToSignalOutput(BIAS_CENTER);
			ENCODER_TIMER->CNT = BIAS_CENTER;
			break;

		default:
			break;
	}


	eNewEvent = evIdle;
	return Bias_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState BiasMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("BiasMenuExitHandler Event captured\n");
	#endif

	// disable the menu
	//_setBiasMenuStatus(DISABLE_BIAS_MENU);

	DM_RefreshScreen();

	#ifdef EVENT_MENU_DEBUG
		  printf("returning to Idle State\n");
	#endif

	eNewEvent = evIdle;
	return Toplevel_Output_Menu_State;
}

