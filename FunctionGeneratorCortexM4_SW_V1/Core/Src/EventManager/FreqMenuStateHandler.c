/*
 * FreqMenuStateHandler.c
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#include "FreqMenuStateHandler.h"

#include "DisplayManager.h"
//#include "SignalManager.h"
#include <stdio.h>



eFreqMenu_Status eNextFreqMenuStatus = 	DISABLE_FREQ_MENU;
eFreqSweepModes active_sweep_mode = SWEEP_MODE_UP;

uint16_t min_arr = 128;
uint32_t max_arr = 65535;

#define RATE_COEF	32	// how much the encoder increments/decrements per pulse
#define RATE_DELTA	1.1	// how much we increment/decrement by

eFreqMenu_Status FreqMenu_getStatus()
{
	return eNextFreqMenuStatus;
}

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
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqMainMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextFreqMenuStatus = ENABLE_FREQ_MAIN_MENU;

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
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqMainMenuInputHandler Event captured\n");
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
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqMainMenuExitHandler Event captured\n");
	#endif


	// disable the menu
	eNextFreqMenuStatus = DISABLE_FREQ_MENU;

	// reset the encoder range

	ENCODER_TIMER->ARR = 1024;

	DM_RefreshScreen();

	#ifdef SWV_DEBUG_ENABLED
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
eSystemState FreqPresetMenuEntryHandler()
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqPresetMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextFreqMenuStatus = ENABLE_FREQ_PRESET_MENU;

	FreqProfile_t *pFreqPresetTmp =  FreqO_GetFPresetObject();
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
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqPresetMenuInputHandler Event captured\n");
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
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqPresetMenuExitHandler Event captured\n");
	#endif


	// disable the menu
	eNextFreqMenuStatus = ENABLE_FREQ_MAIN_MENU;

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
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqAdjustMenuEntryHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	eNextFreqMenuStatus = ENABLE_FREQ_ADJUST_MENU;

	// set the rotary encoder limits to 0-? for this menu
	ENCODER_TIMER->CNT = OUTPUT_TIMER->ARR;
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
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqAdjustMenuInputHandler Event captured\n");
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
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqAdjustMenuExitHandler Event captured\n");
	#endif


	// disable the menu
	eNextFreqMenuStatus = ENABLE_FREQ_MAIN_MENU;

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
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqSweepMenuEntryHandler captured\n");
	#endif

	DM_RefreshScreen();

	// enable the sweep timer
	//HAL_TIM_Base_Start_IT(&htim3);
	//SWEEP_TIMER->DIER 	|= (TIM_DIER_UIE);
	//SWEEP_TIMER->CR1 	|= (TIM_CR1_CEN);

	// pause sweep, wait for user input (evSweepEnable) to restart
	//SWEEP_TIMER->CR1 ^= TIM_CR1_CEN;

	// encoder start value
	ENCODER_TIMER->CNT = 1;
	// encoder limit
	ENCODER_TIMER->ARR = 65535;

	// reset sweep start value
	SWEEP_TIMER->CNT = 0;

	// sweep start speed
	SWEEP_TIMER->ARR = min_arr;
	SWEEP_TIMER->PSC = 0;

	// do stuff
	FreqSweepMenuInputHandler(evSweepSpeed);

	// get ready to load menu
	eNextFreqMenuStatus = ENABLE_FREQ_SWEEP_MENU;


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
eSystemState FreqSweepMenuInputHandler(eSystemEvent pEvent)
{
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqAdjustMenuInputHandler Event captured\n");
	#endif



	switch(pEvent)
	{
		case evSweepEnable:

			#ifdef SWV_DEBUG_ENABLED
				printf("evSweepEnable captured\n");
			#endif

			// toggle enable/disable
			SWEEP_TIMER->DIER 	^= TIM_DIER_UIE;
			SWEEP_TIMER->CR1	^= TIM_CR1_CEN;
			break;

		case evSweepMode:

			#ifdef SWV_DEBUG_ENABLED
				printf("evSweepMode captured\n");
			#endif

			active_sweep_mode++;
			if(active_sweep_mode > 3)
				active_sweep_mode = 0;

			switch(active_sweep_mode)
			{
				case SWEEP_MODE_UP:
					SWEEP_TIMER->CR1 |= (TIM_CR1_DIR);
					SWEEP_TIMER->CR1 &= ~((TIM_CR1_CMS_0) | (TIM_CR1_CMS_1));
					break;

				case SWEEP_MODE_DOWN:
					SWEEP_TIMER->CR1 &= ~(TIM_CR1_DIR);
					SWEEP_TIMER->CR1 &= ~((TIM_CR1_CMS_0) | (TIM_CR1_CMS_1));
					break;

				case SWEEP_MODE_BIDIR:
//					SWEEP_TIMER->CR1 |= (TIM_CR1_CMS_0);
					break;
			}
			// toggle bi-directional (center-alligned)

			break;



		case evSweepSpeed:

			#ifdef SWV_DEBUG_ENABLED
				printf("evSweepSpeed captured\n");
			#endif

			// adjust speed to rotary encoder position
			// clamp SWEEP_TIMER->ARR to:  4095 < SWEEP_TIMER speed < 65535

/*			if(SWEEP_TIMER->ARR >= min_arr)
			{
				uint32_t next_SWEEP_TIMER_value = min_arr + (ENCODER_TIMER->CNT * rate_coeff);
				if((next_SWEEP_TIMER_value) > max_arr)
				{
					SWEEP_TIMER->ARR = max_arr;
				}
				else
				{
					SWEEP_TIMER->ARR = next_SWEEP_TIMER_value;
				}
			}
			else
			{
				SWEEP_TIMER->ARR = min_arr;
			}
*/

			SWEEP_TIMER->PSC = min_arr + ((ENCODER_TIMER->CNT*ENCODER_TIMER->CNT*ENCODER_TIMER->CNT));


			if(SWEEP_TIMER->PSC == 0)
				calculated_sweep_in_hertz = (float)SM_MCLK / ((float)1 * (float)SWEEP_TIMER->ARR);
			else
				calculated_sweep_in_hertz = (float)SM_MCLK / ((float)SWEEP_TIMER->PSC * (float)SWEEP_TIMER->ARR);


			break;

		default:
			// don't care about other eSystemEvent
			break;
	}

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
	#ifdef SWV_DEBUG_ENABLED
		printf("FreqSweepMenuExitHandler Event captured\n");
	#endif

	DM_RefreshScreen();

	// disable sweep timer and interrupts
	SWEEP_TIMER->DIER 	&= ~(TIM_DIER_UIE);
	SWEEP_TIMER->CR1 	&= ~(TIM_CR1_CEN);



	// disable the menu
	eNextFreqMenuStatus = ENABLE_FREQ_MAIN_MENU;

	// back to main freq menu
	eNewEvent = evIdle;
	return Freq_Main_Menu_State;
}

