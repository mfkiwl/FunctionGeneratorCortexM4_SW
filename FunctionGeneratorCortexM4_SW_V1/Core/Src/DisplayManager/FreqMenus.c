/*
 * FreqMenus.c
 *
 *  Created on: 11 May 2020
 *      Author: chris
 */


#include "FreqMenus.h"
#include <stdio.h>
#include "DisplayManager.h"



void FreqMenu_DrawMainMenu();
void FreqMenu_DrawPresetMenu();
void FreqMenu_DrawSyncMenu();

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FreqMenu_DrawMenu(eFreqMenu_Status pMenu)
{
	switch(pMenu)
	{
		case ENABLE_FREQ_MAIN_MENU:
			FreqMenu_DrawMainMenu();
			break;
		case ENABLE_FREQ_PRESET_MENU:
			FreqMenu_DrawPresetMenu();
			break;
		case ENABLE_FREQ_ADJUST_MENU:
			FreqMenu_DrawAdjustMenu();
			break;
		case ENABLE_FREQ_SWEEP_MENU:
			FreqMenu_DrawSweepMenu();
			break;

		default:
			break;

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
void FreqMenu_DrawMainMenu()
{
	// main
	ILI9341_Draw_Text("OUT->FREQ", 	10, 10, WHITE, 2, BLACK);
//	ILI9341_Draw_Text("Select an option below", 	30, 165, BLACK, 2, WHITE);

	DM_DisplayFormattedOutput();

	// buttons
	ILI9341_Draw_Text("PRESET", 5, 210, BLACK, 2, DARKCYAN);
	ILI9341_Draw_Text("ADJUST", 87, 210, BLACK, 2, DARKGREEN);
	ILI9341_Draw_Text("SWEEP", 174, 210, BLACK, 2, YELLOW);
	//ILI9341_Draw_Text("    ", 260, 210, BLACK, 2, RED);
}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FreqMenu_DrawPresetMenu()
{

	ILI9341_Draw_Text("OUT->FREQ->PRESET", 	10, 10, WHITE, 2, BLACK);
	uint8_t menu_pos_y1 = 50;
	uint8_t menu_pos_y2 = 70;
	uint8_t menu_pos_y3 = 90;
	uint8_t menu_pos_y4 = 110;
	uint8_t menu_pos_y5 = 130;
	uint8_t menu_pos_y6 = 150;
	uint8_t menu_pos_y7 = 170;
	FreqProfile_t *pFreqPresetTmp =  FreqO_GetFPresetObject();
	if(pFreqPresetTmp)
	{
		switch(pFreqPresetTmp->hertz)
		{
			case FPRESET_1HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_10HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_50HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_100HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_250HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_500HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_750HZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, WHITE, 2, BLACK);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_1KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_5KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_10KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_25KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
				break;
			case FPRESET_50KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
			break;
			case FPRESET_75KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, WHITE, 2, BLACK);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, BLACK, 2, WHITE);
			break;
			case FPRESET_100KHZ:
				ILI9341_Draw_Text("- 1Hz", 		10, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10Hz", 	10, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50Hz", 	10, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100Hz", 	10, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 250Hz", 	10, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 500Hz",	10, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 750Hz", 	10, menu_pos_y7, BLACK, 2, WHITE);

				ILI9341_Draw_Text("- 1KHz", 	120, menu_pos_y1, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 5KHz", 	120, menu_pos_y2, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 10KHz", 	120, menu_pos_y3, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 25KHz", 	120, menu_pos_y4, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 50KHz", 	120, menu_pos_y5, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 75KHz",	120, menu_pos_y6, BLACK, 2, WHITE);
				ILI9341_Draw_Text("- 100KHz", 	120, menu_pos_y7, WHITE, 2, BLACK);
			break;

		}
	}
	else
	{
		ILI9341_Draw_Text("FreqMenus::FreqMenu_DrawFreqPresetMenu() Error", 		10, 180, RED, 1, BLACK);
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
void FreqMenu_DrawAdjustMenu()
{
	ILI9341_Draw_Text("OUT->FREQ->ADJUST", 10, 10, WHITE, 2, BLACK);

	DM_DisplayFormattedOutput();


/*	ILI9341_Draw_Text("Output Signal Freq: ", 	10, 150, BLACK, 1, WHITE);

	char freq[6] = "";
	//snprintf(freq, sizeof(freq), "%u", (uint8_t)FreqO_GetOutputFreq());
	if(DM_AddDigitPadding((uint16_t)FreqO_GetOutputFreq(), freq, sizeof(freq)) == 0)
		ILI9341_Draw_Text(freq, 250, 150, WHITE, 1, BLACK);
*/

}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FreqMenu_DrawSweepMenu()
{
	ILI9341_Draw_Text("OUT->FREQ->SWEEP", 	10, 10, WHITE, 2, BLACK);


	// draw enabled status


	char enabled_text[20] = "";
	if((SWEEP_TIMER->CR1 & TIM_CR1_CEN) == TIM_CR1_CEN)
	{
		snprintf(enabled_text, sizeof(enabled_text), "STATUS:  RUNNING");
	}
	else
	{
		snprintf(enabled_text, sizeof(enabled_text), "STATUS:  STOPPED");
	}

	ILI9341_Draw_Text(enabled_text, 10, 40, BLACK, 2, WHITE);

	// draw output freq status
	char out_hertz[25] = "";
	snprintf(out_hertz, sizeof(out_hertz), "OUTPUT: %7.2f Hz", SM_GetOutputInHertz());
	ILI9341_Draw_Text(out_hertz, 10, 60, BLACK, 2, WHITE);


	// draw mode (direction) status
//	char mode_text[20] = "";

/*	if((SWEEP_TIMER->CR1 & TIM_CR1_CMS_0) == TIM_CR1_CMS_0)
	{
		// direction not relevant in center-alligned mode (bi-directional)
		snprintf(mode_text, sizeof(mode_text), "MODE: BOTH");
		//snprintf(dir_text, sizeof(dir_text), "DIRECTION:  N/A");
	}
	else
	{
*/
		ILI9341_Draw_Text("SWEEP MODE:", 10, 100, BLACK, 2, WHITE);

		// get direction
		if((SWEEP_TIMER->CR1 & TIM_CR1_DIR) == TIM_CR1_DIR)
		{
			ILI9341_Draw_Text("UP", 170, 100, BLACK, 2, WHITE);
			ILI9341_Draw_Text("DOWN", 200, 100, WHITE, 2, BLACK);
		}
		else
		{
			ILI9341_Draw_Text("UP", 170, 100, WHITE, 2, BLACK);
			ILI9341_Draw_Text("DOWN", 200, 100, BLACK, 2, WHITE);
		}

//	}





	// draw rate status
	if(theCurrentEncoderSweepFunction == ENCODER_SWEEP_SPEED_FUNCTION)
	{
		ILI9341_Draw_Text("SWEEP SPEED:", 10, 120, WHITE, 2, BLACK);
	}
	else
	{
		ILI9341_Draw_Text("SWEEP SPEED:", 10, 120, BLACK, 2, WHITE);
	}
	char arr_text[25] = "";
	snprintf(arr_text, sizeof(arr_text), "%8.3f Hz", calculated_sweep_in_hertz);
	ILI9341_Draw_Text(arr_text, 182, 120, BLACK, 2, WHITE);


	// draw lower sweep bounds
	if( (theCurrentEncoderSweepFunction == ENCODER_SWEEP_LIMIT_FUNCTION) && (active_sweep_mode == SWEEP_MODE_UP) )
	{
		ILI9341_Draw_Text("SWEEP UPPER:", 10, 140, WHITE, 2, BLACK);	// highlighted
		//ILI9341_Draw_Arrow(ARROW_UP, 280, 120, 10, BLACK);
	}
	else
	{
		ILI9341_Draw_Text("SWEEP UPPER:", 10, 140, BLACK, 2, WHITE);
	}
	char sweep_lower_text[20] = "";
	snprintf(sweep_lower_text, sizeof(sweep_lower_text), "%9.2f  Hz", SM_ConvertPeriodToHertz(sweep_lower_bounds_shortest_output_arr, OUTPUT_TIMER->PSC) /SM_FSAMP);
	ILI9341_Draw_Text(sweep_lower_text, 158, 140, BLACK, 2, WHITE);


	// draw upper sweep bounds
	if( (theCurrentEncoderSweepFunction == ENCODER_SWEEP_LIMIT_FUNCTION) && (active_sweep_mode == SWEEP_MODE_DOWN) )
	{
		ILI9341_Draw_Text("SWEEP LOWER:", 10, 160, WHITE, 2, BLACK); 	// highlighted
		//ILI9341_Draw_Arrow(ARROW_DOWN, 280, 130, 10, BLACK);
	}
	else
	{
		ILI9341_Draw_Text("SWEEP LOWER:", 10, 160, BLACK, 2, WHITE);
	}
	char sweep_upper_text[20] = "";
	snprintf(sweep_upper_text, sizeof(sweep_upper_text), "%7.2f Hz", SM_ConvertPeriodToHertz(sweep_upper_bounds_longest_output_arr, OUTPUT_TIMER->PSC) /SM_FSAMP );
	ILI9341_Draw_Text(sweep_upper_text, 170, 160, BLACK, 2, WHITE);


	// draw bottom menu button text
	if((SWEEP_TIMER->CR1 & TIM_CR1_CEN) == TIM_CR1_CEN)
		ILI9341_Draw_Text("PAUSE ", 6, 213, BLACK, 2, DARKCYAN);
	else
		ILI9341_Draw_Text("RESUME", 5, 213, BLACK, 2, DARKCYAN);

	ILI9341_Draw_Text("SET", 	105,	204, BLACK, 2, DARKGREEN);
	ILI9341_Draw_Text("MODE",	98, 	222, BLACK, 2, DARKGREEN);

	ILI9341_Draw_Text("SET", 	183,	204, BLACK, 2, YELLOW);
	ILI9341_Draw_Text("SPEED",	173, 	222, BLACK, 2, YELLOW);

	ILI9341_Draw_Text("SET", 	263, 	204, BLACK, 2, RED);
	ILI9341_Draw_Text("LIMIT", 	252, 	222, BLACK, 2, RED);
}

