/*
 * DisplayManager.c
 *
 *  Created on: 3 May 2020
 *      Author: chris
 */

#include "DisplayManager.h"
#include "EventManager.h"

#include <stdint.h>
#include <stdio.h>
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "rng.h"
#include <string.h>
#include <stdlib.h>

eDisplay_Mode eCurrentMode = Func_Adjust_mode;
eFuncMenu_Status eNextFuncMenuStatus = DISABLE_FUNCMENU;
eGainMenu_Status eNextGainMenuStatus = DISABLE_GAINMENU;

 extern uint16_t BURST_MAX_SIZE;



#define BTN_WIDTH 				(ILI9341_SCREEN_WIDTH)/4
#define BTN_HEIGHT				50
#define BTN_Y_POS 				(ILI9341_SCREEN_HEIGHT)-40
#define BORDER_SIZE				2
#define BTN_TXT_X_POS 			(ILI9341_SCREEN_WIDTH)/8
#define BTN_TXT_Y_POS 			(ILI9341_SCREEN_HEIGHT)-25

uint16_t btn_x_pos[4] = { 0, (BTN_WIDTH)+1, (BTN_WIDTH*2)+2, (BTN_WIDTH*3)+2 };
//#define BUTTON_Y_POSITION 50
//uint16_t button_x_positions[1] = { (BUTTON_WIDTH) };

// public function prototypes
void DM_RefreshBackgroundLayout();

// private function prototypes
void _DrawFuncSelectMenu();
void _DrawGainSelectMenu();

/*
 *
 *
 *
 */
void DM_Init()
{
	  ILI9341_Init();
	  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
	  ILI9341_Fill_Screen(WHITE);

}

/*
 *
 *
 *
 */
void DM_PostInit()
{

	  ILI9341_Draw_Text("Initialising", 10, 10, BLACK, 1, WHITE);
	  HAL_Delay(500);

	  DM_RefreshBackgroundLayout();
	  printf("Init Completed\n");
}


/*
 *
 *
 *
 */

void DM_UpdateDisplay()
{

	ILI9341_Draw_Text("FUNC", 10, 210, BLACK, 2, DARKCYAN);
	ILI9341_Draw_Text("FREQ", 100, 210, BLACK, 2, DARKGREEN);
	ILI9341_Draw_Text("AMPL", 175, 210, BLACK, 2, YELLOW);
	ILI9341_Draw_Text("BIAS", 260, 210, BLACK, 2, RED);

	if(eNextFuncMenuStatus)		//  == ENABLE_FUNCMENU
		_DrawFuncSelectMenu();

	if(eNextGainMenuStatus)		//  == ENABLE_GAINMENU
		_DrawGainSelectMenu();

#ifdef ENCODER_DEBUG
	char tim1tmp[11] = "";
	snprintf(tim1tmp, sizeof(tim1tmp), "%lu", TIM1->CNT);
	ILI9341_Draw_Text(tim1tmp, 260, 50, BLACK, 2, RED);
#endif //ENCODER_DEBUG
/*
	if((TIM1->SR & TIM_SR_IDXF) == TIM_SR_IDXF)
	{
		TIM1->SR &= ~(TIM_SR_IDXF);
	}*/
}

/*
 *
 *
 *
 */
void DM_ShowFuncSelectMenu(eFuncMenu_Status pValue)
{
	eNextFuncMenuStatus = pValue;
}

/*
 *
 *
 *
 */
void _DrawFuncSelectMenu()
{

	switch(EM_GetOutputMode())
	{
		case Sine_Out_Mode:
			ILI9341_Draw_Text("- SINE", 	10, 30, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- SQUARE", 	10, 50, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- SAW", 		10, 70, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- REV SAW", 	10, 90, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- TRIANGLE",	10, 110, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- UNIT", 	10, 130, BLACK, 2, WHITE);
			break;
		case Square_Out_Mode:
			ILI9341_Draw_Text("- SINE", 	10, 30, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- SQUARE", 	10, 50, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- SAW", 		10, 70, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- REV SAW", 	10, 90, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- TRIANGLE",	10, 110, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- UNIT", 	10, 130, BLACK, 2, WHITE);
			break;
		case Saw_Out_Mode:
			ILI9341_Draw_Text("- SINE", 	10, 30, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- SQUARE", 	10, 50, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- SAW", 		10, 70, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- REV SAW", 	10, 90, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- TRIANGLE",	10, 110, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- UNIT", 	10, 130, BLACK, 2, WHITE);
			break;
		case RevSaw_Out_Mode:
			ILI9341_Draw_Text("- SINE", 	10, 30, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- SQUARE", 	10, 50, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- SAW", 		10, 70, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- REV SAW", 	10, 90, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- TRIANGLE",	10, 110, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- UNIT", 	10, 130, BLACK, 2, WHITE);
			break;
		case Triangle_Out_Mode:
			ILI9341_Draw_Text("- SINE", 	10, 30, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- SQUARE", 	10, 50, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- SAW", 		10, 70, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- REV SAW", 	10, 90, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- TRIANGLE",	10, 110, WHITE, 2, BLACK);
			ILI9341_Draw_Text("- UNIT", 	10, 130, BLACK, 2, WHITE);
			break;
		case Impulse_Out_Mode:
			ILI9341_Draw_Text("- SINE", 	10, 30, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- SQUARE", 	10, 50, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- SAW", 		10, 70, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- REV SAW", 	10, 90, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- TRIANGLE",	10, 110, BLACK, 2, WHITE);
			ILI9341_Draw_Text("- UNIT", 	10, 130, WHITE, 2, BLACK);
			break;

	}

}

/*
 *
 *
 *
 */
void DM_ShowGainSelectMenu(eGainMenu_Status pValue)
{
	eNextGainMenuStatus = pValue;
}

/*
 *
 *
 *
 */
void _DrawGainSelectMenu()
{

	ILI9341_Draw_Text("Output Signal Gain: ", 	10, 120, BLACK, 2, WHITE);

	char gain[11] = "";
	snprintf(gain, sizeof(gain), "%u", (uint8_t)EM_GetOutputGain());
	ILI9341_Draw_Text(gain, 250, 120, WHITE, 2, BLACK);

}

/*
 *
 *
 *
 */
int DM_DigitCount(int num)
{
	if(num < 10)
		return 1;
	if(num < 100)
		return 2;
	if(num < 1000)
		return 3;
	if(num < 10000)
		return 4;
	if(num < 100000)
		return 5;
	else
		return 0;
}

/*
 *
 * Call this only once during init.
 *
 *
 */
void DM_RefreshBackgroundLayout()
{


	ILI9341_Fill_Screen(WHITE);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[0],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													DARKCYAN,
													BORDER_SIZE,
													BLACK);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[1],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													DARKGREEN,
													BORDER_SIZE,
													BLACK);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[2],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													YELLOW,
													BORDER_SIZE,
													BLACK);

	ILI9341_Draw_Bordered_Filled_Rectangle_Coord(	btn_x_pos[3],
													BTN_Y_POS,
													BTN_WIDTH,
													BTN_HEIGHT,
													RED,
													BORDER_SIZE,
													BLACK);
}





/*
 *
 *
 *
 */
void DM_RegisterStrings()
{
	int res = 0;
	res = TM_RegisterString("ONE", 10, 220, 2);
	res = TM_RegisterString("TWO", 100, 220, 2);
	res = TM_RegisterString("THREE", 175, 220, 2);
	res = TM_RegisterString("FOUR", 260, 220, 2);
	if(res < 0)
	{
		ILI9341_Draw_Text("Exceeded String Buffer Bounds!", 10, 20, BLACK, 1, WHITE);
	}
}

/*
 *
 *	adds num to buffer with empty char padding
 *
 *	used so that smaller number can erase previously
 *	larger number when displayed on TFT
 *
 *	buflen should include terminating null zero
 *
 *	returns 	0 when OK
 *				1 if buflen is invalid size
 *				2 unknown error
 *
 */
int DM_AddDigitPadding(uint16_t num, char *buffer, uint16_t buflen)
{
	if((buflen < 1) || (buflen > 6))
		return 1;

	//char* tmpbuf = malloc(sizeof(buffer) * buflen);

	uint16_t tmpcnt = num;
	switch(DM_DigitCount(tmpcnt))
	{

		case 0:
			snprintf(buffer,buflen, "     ");
			return 0;
		case 1:
			snprintf(buffer, buflen, "%u    ", tmpcnt);
			return 0;
		case 2:
			snprintf(buffer, buflen, "%u   ", tmpcnt);
			return 0;
		case 3:
			snprintf(buffer, buflen, "%u  ", tmpcnt);
			return 0;
		case 4:
			snprintf(buffer, buflen, "%u ", tmpcnt);
			return 0;
		case 5:
			snprintf(buffer, buflen, "%u", tmpcnt);
			return 0;

	}

	return 2;


}

/*
 *
 *
 *
 */
void DM_SetDisplayMode(eDisplay_Mode pMode)
{

}


/*
 *
 *
 *
 */
void DM_TestScreen()
{
	  //----------------------------------------------------------FILLED CIRCLES EXAMPLE

	  			uint16_t xr = 0;
	  			uint16_t yr = 0;
	  			uint16_t radiusr = 0;
	  			uint16_t colourr = 0;
	  			xr = LL_RNG_ReadRandData32(RNG);
	  			yr = LL_RNG_ReadRandData32(RNG);
	  			radiusr = LL_RNG_ReadRandData32(RNG);
	  			colourr = LL_RNG_ReadRandData32(RNG);

	  			xr &= 0x01FF;
	  			yr &= 0x01FF;
	  			radiusr &= 0x001F;

	  			ILI9341_Draw_Filled_Circle(xr, yr, radiusr/2, colourr);

	  			char enc_buff[13] = "";
	  			snprintf(enc_buff, sizeof(enc_buff), "%d\n", new_enc_value);
	  			ILI9341_Draw_Text(enc_buff, 10, 20, BLACK, 5, WHITE);

	  			ILI9341_Draw_Text(control_pressed, 10, 60, BLACK, 5, WHITE);
	  		//HAL_Delay(1);
}
