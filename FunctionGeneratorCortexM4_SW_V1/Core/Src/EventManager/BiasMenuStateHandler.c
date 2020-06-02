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

eBiasMenu_Status eNextBiasMenuStatus =	DISABLE_BIAS_MENU;

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eBiasMenu_Status BiasMenu_getStatus()
{
	return eNextBiasMenuStatus;
}

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

	eNextBiasMenuStatus = ENABLE_BIAS_MENU;

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
eSystemState BiasMenuInputHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("BiasMenuInputHandler Event captured\n");
	#endif

	BO_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_FORWARD));

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
	eNextBiasMenuStatus = DISABLE_BIAS_MENU;

	// reset the encoder range

	//ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

	#ifdef EVENT_MENU_DEBUG
		  printf("returning to Idle State\n");
	#endif

	eNewEvent = evIdle;
	return Toplevel_Output_Menu_State;
}

