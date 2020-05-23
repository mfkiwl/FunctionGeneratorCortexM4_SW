/*
 * FuncMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */


#include "FuncMenuStateHandler.h"

#include "DisplayManager.h"
#include "SignalManager.h"

#include <stdio.h>
#include <math.h>

eFuncMenu_Status eNextFuncMenuStatus = 	DISABLE_FUNC_MENU;



eFuncMenu_Status FuncMenu_getStatus()
{
	return eNextFuncMenuStatus;
}

/*
 *
 *	@brief	_FuncMenuEntryHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncMainMenuEntryHandler(void)
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FuncMainMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextFuncMenuStatus = 	ENABLE_FUNC_MAIN_MENU;

	eNewEvent = evIdle;
	return Func_Main_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuInputHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncMainMenuInputHandler(void)
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FuncMainMenuInputHandler Event captured\n");
	#endif

	eNewEvent = evBlueBtn;
	return Func_Main_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuExitHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncMainMenuExitHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FuncMainMenuExitHandler Event captured\n");
	#endif

	eNextFuncMenuStatus = 	DISABLE_FUNC_MENU;

	// reset the encoder range
	ToplevelMenu_setStatus(ENABLE_TOPLEVEL_OUTPUT_MENU);

	DM_RefreshScreen();

	#ifdef SWV_DEBUG_ENABLED
		  printf("returning to Idle State\n");
	#endif

	eNewEvent = evIdle;
	return Toplevel_Output_Menu_State;
}


/*
 *
 *	@brief	_FuncMenuEntryHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncSignalMenuEntryHandler(void)
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FuncSignalMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();
	FuncO_ResetLastEncoderValue();

	eNextFuncMenuStatus = 	ENABLE_FUNC_SIGNAL_MENU;
/*
	FunctionProfile_t *func_profileTmp = SM_GetOutputChannel(SIGNAL_CHANNEL)->func_profile;
	if(func_profileTmp)
	{
		ENCODER_TIMER->CNT = func_profileTmp->epos;
		ENCODER_TIMER->ARR = FuncO_GetFuncPresetEncoderRange();
	}
	else
	{
		DM_SetErrorDebugMsg("_FuncMenuEntryHandler: func_profileTmp null pointer");
	}
*/

	ENCODER_TIMER->CNT = 32768;
	ENCODER_TIMER->ARR = 65535;

	eNewEvent = evIdle;
	return Func_Signal_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuInputHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncSignalMenuInputHandler(void)
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FuncSignalMenuInputHandler Event captured\n");
	#endif


	FuncO_MapEncoderPositionToSignalOutput(SM_GetEncoderValue(ENCODER_REVERSE));


	eNewEvent = evIdle;
	return Func_Signal_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FuncSignalToggleDutyMode()
{
	SM_ToggleFuncPwmDutyMode();
	ENCODER_TIMER->ARR = 16384;
	eNewEvent = evIdle;
	return Func_Signal_Menu_State;
}


/*
 *
 *	@brief	_FuncMenuExitHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncSignalMenuExitHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FuncSignalMenuExitHandler Event captured\n");
	#endif

	// disable the menu

	eNextFuncMenuStatus = 	ENABLE_FUNC_MAIN_MENU;

	// reset the encoder range

//	ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();
	SM_ResetFuncPwmDutyMode();
	eNewEvent = evIdle;
	return Func_Main_Menu_State;
}


/*
 *
 *	@brief	_FuncMenuEntryHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncAuxMenuEntryHandler(void)
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FuncAuxMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();
	FuncO_ResetLastEncoderValue();

	eNextFuncMenuStatus = 	ENABLE_FUNC_Aux_MENU;

	//FunctionProfile_t *func_profileTmp =  FuncO_GetAuxFPresetObject();
/*	FunctionProfile_t *func_profileTmp = SM_GetOutputChannel(Aux_CHANNEL)->func_profile;
	if(func_profileTmp)
	{
		ENCODER_TIMER->CNT = func_profileTmp->epos;
		ENCODER_TIMER->ARR = FuncO_GetFuncPresetEncoderRange();
	}
	else
	{
		DM_SetErrorDebugMsg("_FuncMenuEntryHandler: func_profileTmp null pointer");
	}
	*/
	ENCODER_TIMER->CNT = 32768;
	ENCODER_TIMER->ARR = 65535;

	eNewEvent = evIdle;
	return Func_Aux_Menu_State;
}

/*
 *
 *	@brief	_FuncMenuInputHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncAuxMenuInputHandler(void)
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FuncAuxMenuInputHandler Event captured\n");
	#endif

	// PWM ADJUST
	if(SM_IsFuncPwmDutyMode())
	{
		uint16_t enc_value = SM_GetEncoderValue(ENCODER_FORWARD);
		TIM3->CCR1 = (pow(enc_value, 2));
		//BO_SetPwmSignalOffsetForDuty(BO_GetOutputBias() + SM_GetEncoderValue(ENCODER_FORWARD));

	}
	else
	{
		FuncO_MapEncoderPositionToAuxOutput(SM_GetEncoderValue(ENCODER_REVERSE));
	}

	eNewEvent = evIdle;
	return Func_Aux_Menu_State;
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
eSystemState FuncAuxToggleDutyMode()
{
	SM_ToggleFuncPwmDutyMode();
	ENCODER_TIMER->ARR = 16384;
	eNewEvent = evIdle;
	return Func_Aux_Menu_State;
}


/*
 *
 *	@brief	_FuncMenuExitHandler
 *
 *	@param None
 *	@retval eSystemState enum for next system state
 *
 */
eSystemState FuncAuxMenuExitHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FuncAuxMenuExitHandler Event captured\n");
	#endif

	// disable the menu

	eNextFuncMenuStatus = 	ENABLE_FUNC_MAIN_MENU;

	// reset the encoder range

	//ENCODER_TIMER->ARR = 1024;
	SM_ResetFuncPwmDutyMode();
	DM_RefreshScreen();

	eNewEvent = evIdle;
	return Func_Main_Menu_State;
}
