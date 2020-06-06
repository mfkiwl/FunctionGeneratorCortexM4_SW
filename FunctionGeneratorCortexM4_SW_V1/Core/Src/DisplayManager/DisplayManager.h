/*
 * DisplayManager.h
 *
 *  Created on: 3 May 2020
 *      Author: chris
 */

#ifndef INC_DISPLAYMANAGER_DISPLAYMANAGER_H_
#define INC_DISPLAYMANAGER_DISPLAYMANAGER_H_



#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

#include "SignalManager.h"
#include "EventManager.h"
#include "ToplevelMenuStateHandler.h"
#include "GainMenuStateHandler.h"
#include "FuncMenuStateHandler.h"
#include "FreqMenuStateHandler.h"
#include "BiasMenuStateHandler.h"

#include <stdint.h>

// colour presets
#define SCREEN_BGCOLOUR				BLACK

#define BREADTRAIL_FGCOLOUR			BLACK
#define BREADTRAIL_BGCOLOUR			WHITE

#define NORMAL_TEXT_FGCOLOUR		GREY
#define	NORMAL_TEXT_BGCOLOUR		BLACK
#define HIGHLIGHT_TEXT_FGCOLOUR		BLACK
#define HIGHLIGHT_TEXT_BGCOLOUR		LBLUE

#define ERR_FGCOLOUR				BLACK
#define ERR_BGCOLOUR				RED

#define BTN1_BORDER_WEIGHT			2
#define BTN1_BORDER_COLOUR			BLACK
#define BTN1_FILL_COLOUR			BLUE
#define BTN1_TEXT_FGCOLOUR			BLACK
#define BTN1_TEXT_BGCOLOUR			BTN1_FILL_COLOUR

#define BTN2_BORDER_WEIGHT			2
#define BTN2_BORDER_COLOUR			BLACK
#define BTN2_FILL_COLOUR			GREEN
#define BTN2_TEXT_FGCOLOUR			BLACK
#define BTN2_TEXT_BGCOLOUR			BTN2_FILL_COLOUR

#define BTN3_BORDER_WEIGHT			2
#define BTN3_BORDER_COLOUR			BLACK
#define BTN3_FILL_COLOUR			YELLOW
#define BTN3_TEXT_FGCOLOUR			BLACK
#define BTN3_TEXT_BGCOLOUR			BTN3_FILL_COLOUR

#define BTN4_BORDER_WEIGHT			2
#define BTN4_BORDER_COLOUR			BLACK
#define BTN4_FILL_COLOUR			RED
#define BTN4_TEXT_FGCOLOUR			BLACK
#define BTN4_TEXT_BGCOLOUR			BTN4_FILL_COLOUR

#define SIGNAL_OUTPUT_ICON			BLUE
#define Aux_OUTPUT_ICON			RED


void DM_Init();
void DM_PostInit();
void DM_UpdateDisplay();

void DM_RefreshScreen();
void DM_DisplayFormattedOutput();

void DM_DisplayInputTriggerStatus();

void DM_SetErrorDebugMsg(char* msg);
int DM_AddDigitPadding(uint16_t num, char *buffer, uint16_t buflen);


// unused
//int DM_DigitCount(int num);
//void DM_TestScreen();


#endif /* INC_DISPLAYMANAGER_DISPLAYMANAGER_H_ */
