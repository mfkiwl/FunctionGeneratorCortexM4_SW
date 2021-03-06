/*
 * EventManager.h
 *
 *  Created on: May 8, 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_EVENTMANAGER_H_
#define SRC_EVENTMANAGER_EVENTMANAGER_H_

#include <stdint.h>





typedef enum
{


	Toplevel_Main_Menu_State,				// main display
	Toplevel_Output_Menu_State,
	Toplevel_Input_Menu_State,

	Func_Main_Menu_State,
	Func_Signal_Menu_State,
	Func_Aux_Menu_State,

	Gain_Main_Menu_State,
	Gain_Signal_Menu_State,
	Gain_Aux_Menu_State,

	Vpp_Menu_State,			// deprecated

	Freq_Main_Menu_State,
	Freq_Preset_Menu_State,
	Freq_Adjust_Menu_State,
	Freq_Sweep_Menu_State,
	Freq_Prescaler_Menu_State,

	Bias_Menu_State,

	Idle_State = Toplevel_Main_Menu_State

} eSystemState;

typedef enum
{
	evIdle,						// default

	evBlueBtn,					// user presses blue "function" menu button
	evGreenBtn,					// user presses green "freq" menu button
	evYellowBtn,					// user presses yellow "Ampl" menu button
	evRedBtn,					// user presses red "bias" menu button

	evEncoderSet,				// user turns rotary encoder
	evEncoderPush,				// user presses button. return to main screen. All menus closed.

	evSweepEnableBtn,
	evSweepModeBtn,				// direction
	evSweepSpeedBtn,
	evSweepLimitBtn,

	evEncoderSweep,

	evAdjustConfirmed			// user presses rotary encoder confirmation button

} eSystemEvent;




// state machine context
eSystemState eNextState;
eSystemEvent eNewEvent;

void EM_ProcessEvent();
void EM_SetNewEvent(eSystemEvent pEvent);
eSystemState EM_GetSystemState();
uint8_t EM_IsDutyAdjustMode();


#endif /* SRC_EVENTMANAGER_EVENTMANAGER_H_ */
