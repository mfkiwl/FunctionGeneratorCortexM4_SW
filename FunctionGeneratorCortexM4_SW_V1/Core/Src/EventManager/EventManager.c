/*
 * EventManager.c
 *
 *  Created on: May 8, 2020
 *      Author: chris
 */


#include "EventManager.h"
#include <stdio.h>

eSystemState eNextState = Idle_State;
eSystemEvent eNewEvent;

/*
 *
 * 		Set by NVIC interrupt handlers
 */
void EM_SetNewEvent(eSystemEvent pEvent)
{
	eNewEvent = pEvent;
}

void _ClearEvent()
{
	eNewEvent = Idle_Event;
}

eSystemState _FuncAdjustHandler(void)
{
	printf("FunctionAdjust Event captured\n");
	_ClearEvent();
	return Idle_State;
}

eSystemState _FreqAdjustHandler(void)
{
	printf("FreqAdjust Event captured\n");
	_ClearEvent();
	return Idle_State;
}

eSystemState _AmplAdjustHandler(void)
{
	printf("AmplitudeAdjust Event captured\n");
	_ClearEvent();
	return Idle_State;
}

eSystemState _BiasAdjustHandler(void)
{
	printf("BiasAdjust Event captured\n");
	_ClearEvent();
	return Idle_State;
}

eSystemState _AdjustConfirmedHandler(void)
{
	printf("AdjustConfirmed Event captured\n");
	_ClearEvent();
	return Idle_State;
}



void EM_ProcessEvent()
{

	switch(eNextState)
	{
		case Idle_State:
			if(eNewEvent == Func_Select_Event)
			{
				eNextState = _FuncAdjustHandler();
			}
			if(eNewEvent == Freq_Select_Event)
			{
				eNextState = _FreqAdjustHandler();
			}
			if(eNewEvent == Ampl_Select_Event)
			{
				eNextState = _AmplAdjustHandler();
			}
			if(eNewEvent == Bias_Select_Event)
			{
				eNextState = _BiasAdjustHandler();
			}
			if(eNewEvent == Adjust_Confirmed_Event)
			{
				eNextState = _AdjustConfirmedHandler();
			}
			break;

/*		case Func_Select_state:

			break;

		case Freq_Select_state:

			break;

		case Ampl_Select_state:

			break;

		case Bias_Select_state:

			break;
*/
		default:
			break;
	}

}
