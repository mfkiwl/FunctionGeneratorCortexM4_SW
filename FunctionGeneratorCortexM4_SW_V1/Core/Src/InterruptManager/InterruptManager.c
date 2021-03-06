/*
 * InterruptManager.c
 *
 *  Created on: May 16, 2020
 *      Author: chris
 */

#include "main.h"
#include "InterruptManager.h"
#include "EventManager.h"
#include "SignalManager.h"
#include "FreqMenuStateHandler.h"

#include <stdio.h>

// TODO doesn't work correctly
//#define ENABLE_PWM_SWEEP

uint16_t btn1_last_interrupt_time = 0;
uint16_t btn2_last_interrupt_time = 0;
uint16_t btn3_last_interrupt_time = 0;
uint16_t btn4_last_interrupt_time = 0;
uint16_t encbtn_last_interrupt_time = 0;
uint16_t encpos_last_interrupt_time = 0;


void IM_Init()
{
	  // debounce timer
	  DEBOUNCE_TIMER->CR1 |= TIM_CR1_CEN;



}


/*
 *
 *	@brief Called from TIM5_IRQHandler
 *
 *	This function will allow the SWEEP_TIME to update the OUTPUT_TIMER frequency
 *
 *	Note that OUTPUT_TIMER->ARR is not set to the SWEEP_TIME->ARR.
 *	Instead the OUTPUT_TIMER->ARR value is incremented/decremented for every SWEEP_TIMER overflow.
 *	This allows consistent sweep speeds.
 *
 *	OUTPUT_TIMER->ARR is incremented if the SWEEP_TIMER is in "upcounter" mode.
 *	OUTPUT_TIMER->ARR is decremented if the SWEEP_TIMER is in "downcounter" mode.
 *
 *	It has a very low end range (32-bit SWEEP_TIMER).
 *
 *	@param None
 *	@retval None
 *
 */
void IM_SWEEP_UPDATE_TIM_IRQHandler()
{

	#ifdef ENABLE_PWM_SWEEP
		eOutput_mode tmpOut = SM_GetOutputChannel(AUX_CHANNEL)->func_profile->func;
	#endif	//ENABLE_PWM_SWEEP

		// upcounter (decreasing freq)
	if((SWEEP_TIMER->CR1 & TIM_CR1_DIR) == TIM_CR1_DIR)
	{
		// if we reach lower freq limit for sweep, reset to highest freq limit
		if(OUTPUT_TIMER->ARR >= sweep_upper_bounds_longest_output_arr)
		{
			OUTPUT_TIMER->ARR = sweep_lower_bounds_shortest_output_arr;

			#ifdef ENABLE_PWM_SWEEP
				if(tmpOut == PWM_FUNC_MODE)
				{
					// duty cycle of PWM require slower settings to get the
					// same frequency as normal output functions
					PWM_AUX_OUT_TIM->PSC = 256;
					PWM_AUX_OUT_TIM->ARR = sweep_lower_bounds_shortest_output_arr/2;
					PWM_AUX_OUT_TIM->CCR1 = PWM_AUX_OUT_TIM->ARR/2;

				}
			#endif	//ENABLE_PWM_SWEEP
		}
		else
		{
			// keep decreasing freq
			OUTPUT_TIMER->ARR++;

			#ifdef ENABLE_PWM_SWEEP
				if(tmpOut == PWM_FUNC_MODE)
				{
					// duty cycle of PWM require slower settings to get the
					// same frequency as normal output functions

					PWM_AUX_OUT_TIM->ARR++;
					PWM_AUX_OUT_TIM->CCR1 = PWM_AUX_OUT_TIM->ARR/2;
				}
			#endif	//ENABLE_PWM_SWEEP

		}
	}
	// downcounter (increasing freq)
	else
	{
		// stop before reaching null ARR
		if(OUTPUT_TIMER->ARR == 0x1U)
		{
			// reset to lowest freq
			OUTPUT_TIMER->ARR = MAX_OUTPUT_ARR;


			#ifdef ENABLE_PWM_SWEEP
				if(tmpOut == PWM_FUNC_MODE)
				{
					// duty cycle of PWM require slower settings to get the
					// same frequency as normal output functions

					PWM_AUX_OUT_TIM->ARR = MAX_OUTPUT_ARR/2;
					PWM_AUX_OUT_TIM->CCR1 = PWM_AUX_OUT_TIM->ARR/2;

				}
			#endif	//ENABLE_PWM_SWEEP
		}
		else
		{
			// if we reach higher freq limit for sweep, reset to lowest freq limit
			if(OUTPUT_TIMER->ARR <= sweep_lower_bounds_shortest_output_arr)
			{
				OUTPUT_TIMER->ARR = sweep_upper_bounds_longest_output_arr;



				#ifdef ENABLE_PWM_SWEEP
					if(tmpOut == PWM_FUNC_MODE)
					{
						// duty cycle of PWM require slower settings to get the
						// same frequency as normal output functions

						PWM_AUX_OUT_TIM->ARR = sweep_upper_bounds_longest_output_arr/2;
						PWM_AUX_OUT_TIM->CCR1 = PWM_AUX_OUT_TIM->ARR/2;

					}
				#endif	//ENABLE_PWM_SWEEP

			}
			// keep increasing freq
			else
			{
				OUTPUT_TIMER->ARR--;

				#ifdef ENABLE_PWM_SWEEP
					if(tmpOut == PWM_FUNC_MODE)
					{
						// duty cycle of PWM require slower settings to get the
						// same frequency as normal output functions

						PWM_AUX_OUT_TIM->ARR--;
						PWM_AUX_OUT_TIM->CCR1 = PWM_AUX_OUT_TIM->ARR/2;
					}
				#endif	//ENABLE_PWM_SWEEP
			}
		}
	}

	//SWEEP_TIMER->ARR--;
}


/*
 *
 *	@brief Called from EXTI15_10_IRQHandler
 *
 *	@param None
 *	@retval None
 *
 */
void IM_BTN1_EXTI14_Handler()
{
	uint16_t interrupt_time = DEBOUNCE_TIMER->CNT;
	if ((interrupt_time - btn1_last_interrupt_time) > MAX_DEBOUNCE_DELAY)
	{
		if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_14))
		{

			EM_SetNewEvent(evBlueBtn);
			printf("'Blue' BTN1_EXTI14_Pin\n");
		}
	}
	btn1_last_interrupt_time = interrupt_time;


}

/*
 *
 *	@brief Called from EXTI15_10_IRQHandler
 *
 *	@param None
 *	@retval None
 *
 */
void IM_BTN2_EXTI15_Handler()
{
	uint16_t interrupt_time = DEBOUNCE_TIMER->CNT;
	if ((interrupt_time - btn2_last_interrupt_time) > MAX_DEBOUNCE_DELAY)
	{
		if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_15))
		{
			EM_SetNewEvent(evYellowBtn);
			printf("'Yellow' BTN2_EXTI15_Pin\n");
		}
	}
	btn2_last_interrupt_time = interrupt_time;


}

/*
 *
 *	@brief Called from EXTI0_IRQHandler
 *
 *	@param None
 *	@retval None
 *
 */
void IM_BTN3_EXTI0_Handler()
{
	uint16_t interrupt_time = DEBOUNCE_TIMER->CNT;
	if ((interrupt_time - btn3_last_interrupt_time) > MAX_DEBOUNCE_DELAY)
	{
		if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0))
		{
			EM_SetNewEvent(evRedBtn);
			printf("'Red' BTN3_EXTI0_Pin\n");
		}
	}
	btn3_last_interrupt_time = interrupt_time;


}

/*
 *
 *	@brief Called from EXTI1_IRQHandler
 *
 *	@param None
 *	@retval None
 *
 */
void IM_BTN4_EXTI1_Handler()
{
	uint16_t interrupt_time = DEBOUNCE_TIMER->CNT;
	if ((interrupt_time - btn4_last_interrupt_time) > MAX_DEBOUNCE_DELAY)
	{
		if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1))
		{
			EM_SetNewEvent(evGreenBtn);
			printf("'Green' BTN4_EXTI1_Pin\n");
		}
	}
	btn4_last_interrupt_time = interrupt_time;


}

/*
 *
 *	@brief Called from EXTI2_IRQHandler
 *
 *	@param None
 *	@retval None
 *
 */
void IM_ENC_EXTI2_Handler()
{
	uint16_t interrupt_time = DEBOUNCE_TIMER->CNT;
	if ((interrupt_time - encbtn_last_interrupt_time) > MAX_DEBOUNCE_DELAY)
	{
		if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_2))
		{
			EM_SetNewEvent(evEncoderPush);
			printf("'EncoderPush' ENC_EXTI2_Pin\n");
		}
	}
	encbtn_last_interrupt_time = interrupt_time;


}

/*
 *
 *	@brief Called from TIM1_BRK_TIM15_IRQHandler
 *
 *	@param None
 *	@retval None
 *
 */
void IM_ENC_DIRF_Handler()
{

	if((TIM1->SR & TIM_SR_DIRF) == TIM_SR_DIRF)
	{
		uint16_t interrupt_time = DEBOUNCE_TIMER->CNT;
		if ((interrupt_time - encpos_last_interrupt_time) > 0)
		{
			EM_SetNewEvent(evEncoderSet);
			printf("Encoder new direction\n");
			TIM1->SR &= ~(TIM_SR_DIRF);
		}
		encpos_last_interrupt_time = interrupt_time;


	}


}
/*
void IM_RECIP_COUNT_Handler()
{
	freq_count_value++;
}

void IM_RECIP_STORE_Handler()
{
	// get mean average from store
	uint32_t avg_freq_count = 0;
	for(int x = 0; x < MAX_FREQ_COUNT_STORE; x++)
	{
		avg_freq_count += freq_count_store[x];
	}

	avg_freq_count /= MAX_FREQ_COUNT_STORE;

	printf("%lu\n", avg_freq_count);

	// reset the index to zero
	if(freq_count_index > MAX_FREQ_COUNT_STORE)
		freq_count_index = 0;

	// store the current freq count
	freq_count_store[freq_count_index] = freq_count_value;

	// reset the value
	freq_count_value = 0;

	// increment the store index
	freq_count_index++;
}
*/
