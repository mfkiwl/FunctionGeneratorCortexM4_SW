/*
 * SignalManager.c
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */


#include "SignalManager.h"
#include <math.h>
#include "dac.h"

sOutputChannel_t SignalChannel;
sOutputChannel_t SyncChannel;
void _InitOutputChannels();
void _InitNegGainCoefficients();
void _InitGainInDecibels();

void SM_Init()
{

	_InitOutputChannels();
	_InitNegGainCoefficients();
	_InitGainInDecibels();

}

void _InitGainInDecibels()
{

	// =20*LOG10(TARGETVPP/0.001)
	for(int i = 0; i < MAX_VPP_PRESETS; i++)
	{
		float decibel_mvolt_ref = 0.001;
		float this_amp_value = theAmpProfiles[i].amp_value;
		float new_gain_decibels = 20 * log10( this_amp_value / decibel_mvolt_ref );
		theAmpProfiles[i].gain_decibels = new_gain_decibels;

	}
}

void _InitNegGainCoefficients()
{

	// =(TARGETVPP/LUTVPP)/GAIN
	for(int i = 0; i < MAX_VPP_PRESETS; i++)
	{
		float this_amp_value = theAmpProfiles[i].amp_value;
		float this_lut_vpp = LUT_VPP;
		float this_gain_preset = (float)theAmpProfiles[i].gain_preset;
		float new_ngc = ( (this_amp_value / this_lut_vpp) / this_gain_preset);
		theAmpProfiles[i].neg_gain_coeff = new_ngc;
	}
}

void _InitOutputChannels()
{
	// initialise the SIGNAL output channel
	SignalChannel.channel = SIGNAL_CHANNEL;
	SignalChannel.ref_lut_data = theFuncProfiles[SINE_FUNC_MODE].lookup_table_data;
	SignalChannel.func_profile = &theFuncProfiles[eDefaultFuncPreset];

	for(int i = 0; i < SINE_DATA_SIZE; i++)
		SignalChannel.dsp_lut_data[i] = sine_data_table_3600[i];

	SignalChannel.amp_profile = &theAmpProfiles[eDefaultVppPreset];
	SignalChannel.gain_profile = &theGainProfiles[eDefaultGainPreset];

	// initialise the SYNC output channel
	SyncChannel.channel = SYNC_CHANNEL;
	SyncChannel.ref_lut_data = theFuncProfiles[SINE_FUNC_MODE].lookup_table_data;
	SyncChannel.func_profile = &theFuncProfiles[eDefaultFuncPreset];

	for(int i = 0; i < SINE_DATA_SIZE; i++)
		SyncChannel.dsp_lut_data[i] = sine_data_table_3600[i];

	SyncChannel.amp_profile = &theAmpProfiles[eDefaultVppPreset];
	SyncChannel.gain_profile = &theGainProfiles[eDefaultGainPreset];
}

sOutputChannel_t * SM_GetOutputChannel(eOutputChannel_t pChannel)
{
	if(!pChannel)
		return &SignalChannel;
	else
		return &SyncChannel;
}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void SM_EnablePwmToSignal()
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	GPIO_InitTypeDef GPIO_InitStruct = {0};


	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 0;
	htim3.Init.CounterMode = TIM_COUNTERMODE_DOWN;
	htim3.Init.Period = 1;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}


	// Timer Post Initialization

	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**TIM3 GPIO Configuration
	PA4     ------> TIM3_CH2
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	// TIM3_MspInit 0

	/* TIM3 clock enable */
	__HAL_RCC_TIM3_CLK_ENABLE();

	/* TIM3 interrupt Init */
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	/* USER CODE BEGIN TIM3_MspInit 1 */

	/* USER CODE END TIM3_MspInit 1 */

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	GO_ApplyPresetToSignal(eDefaultGainPreset);
	// 50% duty cycle
	TIM3->CCR2 = 32768;
	TIM3->ARR = 65535;
}

void SM_DisablePwmToSignal()
{
	/* USER CODE BEGIN TIM3_MspDeInit 0 */

	/* USER CODE END TIM3_MspDeInit 0 */
	/* Peripheral clock disable */
	__HAL_RCC_TIM3_CLK_DISABLE();

	/* TIM3 interrupt Deinit */
	HAL_NVIC_DisableIRQ(TIM3_IRQn);
	/* USER CODE BEGIN TIM3_MspDeInit 1 */

	/* USER CODE END TIM3_MspDeInit 1 */
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void SM_EnableDacToSignal()
{
	DAC_ChannelConfTypeDef sConfig = {0};
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/** DAC Initialization
	*/
	hdac1.Instance = DAC1;
	if (HAL_DAC_Init(&hdac1) != HAL_OK)
	{
		Error_Handler();
	}
	/** DAC channel OUT1 config
	*/
	sConfig.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_ABOVE_80MHZ;
	sConfig.DAC_DMADoubleDataMode = DISABLE;
	sConfig.DAC_SignedFormat = DISABLE;
	sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
	sConfig.DAC_Trigger = DAC_TRIGGER_T8_TRGO;
	sConfig.DAC_Trigger2 = DAC_TRIGGER_NONE;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
	sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
	if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	/** DAC channel OUT2 config
	*/
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
	sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
	if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}

    /* DAC1 clock enable */
    __HAL_RCC_DAC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**DAC1 GPIO Configuration
    PA4     ------> DAC1_OUT1
    PA5     ------> DAC1_OUT2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* DAC1 DMA Init */
    /* DAC1_CH1 Init */
    hdma_dac1_ch1.Instance = DMA1_Channel2;
    hdma_dac1_ch1.Init.Request = DMA_REQUEST_DAC1_CHANNEL1;
    hdma_dac1_ch1.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_dac1_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_dac1_ch1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_dac1_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_dac1_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_dac1_ch1.Init.Mode = DMA_CIRCULAR;
    hdma_dac1_ch1.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_dac1_ch1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(&hdac1,DMA_Handle1,hdma_dac1_ch1);

    GO_ApplyPresetToSignal(eDefaultGainPreset);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void SM_DisableDacToSignal()
{

	  /* USER CODE BEGIN DAC1_MspDeInit 0 */

	  /* USER CODE END DAC1_MspDeInit 0 */
	    /* Peripheral clock disable */
	    //__HAL_RCC_DAC1_CLK_DISABLE();

	    /**DAC1 GPIO Configuration
	    PA4     ------> DAC1_OUT1
	    PA5     ------> DAC1_OUT2
	    */
	    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

	    /* DAC1 DMA DeInit */
	   //HAL_DMA_DeInit(hdac1.DMA_Handle1);
	  /* USER CODE BEGIN DAC1_MspDeInit 1 */

	  /* USER CODE END DAC1_MspDeInit 1 */
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void SM_EnablePwmToSync()
{
	SM_GetOutputChannel(SYNC_CHANNEL)->func_profile = &theFuncProfiles[PWM_FUNC_MODE];
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void SM_DisablePwmToSync()
{

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void SM_EnableDacToSync()
{
	SM_GetOutputChannel(SYNC_CHANNEL)->func_profile = &theFuncProfiles[PWM_FUNC_MODE];
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void SM_DisableDacToSync()
{

}


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
uint16_t SM_GetEncoderValue(eEncoder_Direction direction)
{
	if(direction)
	{
		return ENCODER_TIMER->ARR - ENCODER_TIMER->CNT;
	}
	else
	{
		return ENCODER_TIMER->CNT;
	}
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
float SM_GetOutputInHertz()
{
	volatile float output_tm_psc;
	volatile float output_tm_arr;

	// safe-guard against divide by zero
	(OUTPUT_TIMER->PSC == 0) ? (output_tm_psc = 1) : (output_tm_psc = OUTPUT_TIMER->PSC);
	(OUTPUT_TIMER->ARR == 0) ? (output_tm_arr = 1) : (output_tm_arr = OUTPUT_TIMER->ARR);

	float output_tm_freq = SM_MCLK / (output_tm_psc * output_tm_arr);


	return output_tm_freq / SM_FSAMP;
}


float SM_ConvertPeriodToHertz(uint32_t period, uint16_t psc)
{
	(psc == 0) ? (psc = 1) : psc;

	return (float)SM_MCLK / ( (float)psc * (float)period );
}


uint16_t SM_ConvertHertzToPeriod(float hertz, uint16_t psc)
{
	(psc == 0) ? (psc = 1) : psc;

	return (SM_MCLK / hertz) / psc;
}



