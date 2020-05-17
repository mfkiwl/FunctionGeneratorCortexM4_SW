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

#include <stdio.h>



uint16_t btn1_last_interrupt_time = 0;
uint16_t btn2_last_interrupt_time = 0;
uint16_t btn3_last_interrupt_time = 0;
uint16_t btn4_last_interrupt_time = 0;
uint16_t encbtn_last_interrupt_time = 0;

void 	IM_SWEEPINCREMENT_TIM_IRQHandler()
{
	if((SWEEP_TIMER->CR1 & TIM_CR1_DIR) == TIM_CR1_DIR)
	{
		OUTPUT_TIMER->ARR++;
	}
	else
	{
		OUTPUT_TIMER->ARR--;
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
		EM_SetNewEvent(evEncoderSet);
		printf("Encoder new direction\n");
		TIM1->SR &= ~(TIM_SR_DIRF);

	}
}

