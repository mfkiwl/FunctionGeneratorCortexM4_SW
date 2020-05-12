/*
 * FreqMenus.c
 *
 *  Created on: 11 May 2020
 *      Author: chris
 */

#include "FreqMenus.h"

#include "DisplayManager.h"
#include "SignalManager.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FreqMenu_DrawFreqMainMenu()
{
	// main
	ILI9341_Draw_Text("Select an option below", 	30, 150, BLACK, 2, WHITE);

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
void FreqMenu_DrawFreqPresetMenu()
{

	uint8_t menu_pos_y1 = 50;
	uint8_t menu_pos_y2 = 70;
	uint8_t menu_pos_y3 = 90;
	uint8_t menu_pos_y4 = 110;
	uint8_t menu_pos_y5 = 130;
	uint8_t menu_pos_y6 = 150;
	uint8_t menu_pos_y7 = 170;
	Freq_Preset_Encoder_Pos_t *pFreqPresetTmp =  FreqO_GetFPresetObject();
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
void FreqMenu_DrawFreqAdjustMenu()
{

	ILI9341_Draw_Text("Output Signal Freq: ", 	10, 150, BLACK, 1, WHITE);

	char freq[6] = "";
	//snprintf(freq, sizeof(freq), "%u", (uint8_t)FreqO_GetOutputFreq());
	if(DM_AddDigitPadding((uint16_t)FreqO_GetOutputFreq(), freq, sizeof(freq)) == 0)
		ILI9341_Draw_Text(freq, 250, 150, WHITE, 1, BLACK);


}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void FreqMenu_DrawFreqSweepMenu()
{

	ILI9341_Draw_Text("TODO: Freq Sweep Menu", 	10, 120, BLACK, 2, WHITE);




}
