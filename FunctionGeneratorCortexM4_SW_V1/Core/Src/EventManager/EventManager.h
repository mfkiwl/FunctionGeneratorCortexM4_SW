/*
 * EventManager.h
 *
 *  Created on: May 8, 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_EVENTMANAGER_H_
#define SRC_EVENTMANAGER_EVENTMANAGER_H_

typedef enum
{
	Idle_State = 0x00U,		// idle
	Func_Select_State,		// select edit output function
	Freq_Select_State,		// select edit output frequency
	Ampl_Select_State,		// select edit output amplitude
	Bias_Select_State		// select edit output DC bias

} eSystemState;

typedef enum
{
	Idle_Event,
	Func_Select_Event,
	Freq_Select_Event,
	Ampl_Select_Event,
	Bias_Select_Event,
	Adjust_Confirmed_Event

} eSystemEvent;

void EM_SetNewEvent(eSystemEvent pEvent);
void EM_ProcessEvent();

#endif /* SRC_EVENTMANAGER_EVENTMANAGER_H_ */
