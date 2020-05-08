/*
 * DisplayManager.h
 *
 *  Created on: 3 May 2020
 *      Author: chris
 */

#ifndef INC_DISPLAYMANAGER_DISPLAYMANAGER_H_
#define INC_DISPLAYMANAGER_DISPLAYMANAGER_H_


typedef enum
{
	Func_Adjust_mode,				// edit output function
	Freq_Adjust_mode,				// edit output frequency
	Ampl_Adjust_mode,				// edit output amplitude
	Bias_Adjust_mode				// edit output DC bias

} eDisplay_Mode;


void DM_Init();
void DM_UpdateDisplay();
void DM_TestScreen();
void DM_RegisterStrings();
int DM_DigitCount(int num);
void DM_SetDisplayMode(eDisplay_Mode pMode);
#endif /* INC_DISPLAYMANAGER_DISPLAYMANAGER_H_ */
