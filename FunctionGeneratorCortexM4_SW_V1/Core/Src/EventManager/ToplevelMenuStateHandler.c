/*
 * OutputMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#include "DisplayManager.h"
//#include "SignalManager.h"
#include <stdio.h>
#include <ToplevelMenuStateHandler.h>

eTriggerInput isTriggerInputEnabled = DISABLE_TRIGGER_INPUT;
eTriggerInputMode activeInputerTriggerMode = INPUT_TRIGGER_TIM;

eToplevelMenu_Status eNextToplevelMenuStatus = 	ENABLE_TOPLEVEL_MAIN_MENU;



eToplevelMenu_Status ToplevelMenu_getStatus()
{
	return eNextToplevelMenuStatus;
}

void ToplevelMenu_setStatus(eToplevelMenu_Status pStatus)
{
	eNextToplevelMenuStatus = pStatus;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelMainMenuEntryHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelMainMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextToplevelMenuStatus = ENABLE_TOPLEVEL_MAIN_MENU;

	// stay in this state
	eNewEvent = evIdle;
	return Toplevel_Main_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelMainMenuInputHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelMainMenuInputHandler Event captured\n");
	#endif


	return Toplevel_Main_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelMainMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelMainMenuExitHandler Event captured\n");
	#endif


	// disable the menu
	eNextToplevelMenuStatus = DISABLE_TOPLEVEL_MENU;

	// reset the encoder range

	DM_RefreshScreen();

	#ifdef EVENT_MENU_DEBUG
		  printf("returning to Idle State\n");
	#endif

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
eSystemState ToplevelOutputMenuEntryHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelOutputMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextToplevelMenuStatus = ENABLE_TOPLEVEL_OUTPUT_MENU;




	// stay in this state
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
eSystemState ToplevelOutputMenuInputHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelOutputMenuInputHandler Event captured\n");
	#endif


	// stay in this state
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
eSystemState ToplevelOutputMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelOutputMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	// disable the menu
	eNextToplevelMenuStatus = ENABLE_TOPLEVEL_MAIN_MENU;

	// back to main freq menu
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
eSystemState ToplevelInputMenuEntryHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelInputMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextToplevelMenuStatus = ENABLE_TOPLEVEL_INPUT_MENU;




	// stay in this state
	eNewEvent = evIdle;
	return Toplevel_Input_Menu_State;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelInputMenuInputHandler(eSystemEvent pEvent)
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelInputMenuInputHandler Event captured\n");
	#endif


		switch(pEvent)
		{

			case evBlueBtn:

				if(isTriggerInputEnabled)
				{

					OUTPUT_TIMER->SMCR &= ~(TIM_SMCR_ECE);
					OUTPUT_TIMER->SMCR &= ~(TIM_TS_TI1FP1);
					OUTPUT_TIMER->SMCR &= ~(TIM_SMCR_SMS_2);
					isTriggerInputEnabled = DISABLE_TRIGGER_INPUT;
				}
				else
				{
					// enable external clock source
					OUTPUT_TIMER->SMCR |= (TIM_SMCR_ECE);
					// enable Filtered timer input 1 (tim_ti1fp1)
					OUTPUT_TIMER->SMCR |= (TIM_TS_TI1FP1);
					//
					OUTPUT_TIMER->SMCR |= (TIM_SMCR_SMS_2);

					isTriggerInputEnabled = ENABLE_TRIGGER_INPUT;
				}




				break;

			case evGreenBtn:
				switch(activeInputerTriggerMode)
				{
					case INPUT_TRIGGER_TIM:
						activeInputerTriggerMode = INPUT_TRIGGER_COMP;
						break;
					case INPUT_TRIGGER_COMP:
						activeInputerTriggerMode = INPUT_TRIGGER_ADC;
						break;

					case INPUT_TRIGGER_ADC:
						activeInputerTriggerMode = INPUT_TRIGGER_TIM;
						break;
				}

				break;

			default:
				break;
		}
	// stay in this state
	eNewEvent = evIdle;
	return Toplevel_Input_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState ToplevelInputMenuExitHandler()
{
	#ifdef EVENT_MENU_DEBUG
		printf("ToplevelInputMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	// disable the menu
	eNextToplevelMenuStatus = ENABLE_TOPLEVEL_MAIN_MENU;

	// back to main freq menu
	eNewEvent = evIdle;
	return Idle_State;
}
