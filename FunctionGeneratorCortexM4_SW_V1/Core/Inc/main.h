/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_rng.h"
#include "stm32g4xx.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_exti.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_cortex.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_pwr.h"
#include "stm32g4xx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */



char control_pressed[10];
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */



/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN1_EXTI14_Pin LL_GPIO_PIN_14
#define BTN1_EXTI14_GPIO_Port GPIOC
#define BTN1_EXTI14_EXTI_IRQn EXTI15_10_IRQn
#define BTN2_EXTI15_Pin LL_GPIO_PIN_15
#define BTN2_EXTI15_GPIO_Port GPIOC
#define BTN2_EXTI15_EXTI_IRQn EXTI15_10_IRQn
#define BTN3_EXTI0_Pin LL_GPIO_PIN_0
#define BTN3_EXTI0_GPIO_Port GPIOF
#define BTN3_EXTI0_EXTI_IRQn EXTI0_IRQn
#define BTN4_EXTI1_Pin LL_GPIO_PIN_1
#define BTN4_EXTI1_GPIO_Port GPIOF
#define BTN4_EXTI1_EXTI_IRQn EXTI1_IRQn
#define ENC_A_Pin LL_GPIO_PIN_0
#define ENC_A_GPIO_Port GPIOC
#define ENC_B_Pin LL_GPIO_PIN_1
#define ENC_B_GPIO_Port GPIOC
#define ENC_SW_Pin LL_GPIO_PIN_2
#define ENC_SW_GPIO_Port GPIOC
#define ENC_SW_EXTI_IRQn EXTI2_IRQn
#define TRIGMODE_Pin LL_GPIO_PIN_3
#define TRIGMODE_GPIO_Port GPIOC
#define OFFSET_ENABLE_Pin LL_GPIO_PIN_3
#define OFFSET_ENABLE_GPIO_Port GPIOA
#define CH1_GAIN_C_Pin LL_GPIO_PIN_4
#define CH1_GAIN_C_GPIO_Port GPIOC
#define CH1_GAIN_B_Pin LL_GPIO_PIN_5
#define CH1_GAIN_B_GPIO_Port GPIOC
#define CH1_GAIN_A_Pin LL_GPIO_PIN_0
#define CH1_GAIN_A_GPIO_Port GPIOB
#define TRIGMUX1_Pin LL_GPIO_PIN_8
#define TRIGMUX1_GPIO_Port GPIOC
#define TRIGMUX2_Pin LL_GPIO_PIN_9
#define TRIGMUX2_GPIO_Port GPIOC
#define DC_Pin LL_GPIO_PIN_6
#define DC_GPIO_Port GPIOB
#define CS_Pin LL_GPIO_PIN_7
#define CS_GPIO_Port GPIOB
#define RST_Pin LL_GPIO_PIN_9
#define RST_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
