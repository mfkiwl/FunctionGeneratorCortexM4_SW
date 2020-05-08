/*
 * ILI9341_TextManager.c
 *
 *  Created on: 6 May 2020
 *      Author: chris
 */

#include "ILI9341_TextManager.h"

#include <stdio.h>
#include <string.h>

StringRegister STRINGREG[MAX_REG_INDEX] = {
/*
 * 	char text[MAX_TEXT_LENGTH];
	int16_t x;
	int16_t y;
	int16_t size;
 */
		{"", -1, -1, -1},
		{"", -1, -1, -1},
		{"", -1, -1, -1},
		{"", -1, -1, -1}
};


/*
 * 	@Brief search registry for empty registry entry. Internal use only.
 *
 * 	@Returns index of next empty entry, -1 if no empty registry entries are available
 */
int _GetEmptyRegEntry()
{
	for(int i = 0; i < MAX_REG_INDEX; i++)
	{
		if(	(strcmp(STRINGREG[i].text, "") == 0)	&&
			(STRINGREG[i].x 	== -1) 	&&
			(STRINGREG[i].y 	== -1) 	&&
			(STRINGREG[i].size == -1)
		)
		{
			return i;
		}
	}
	return -1;	// no space left!
}


/*
 * 	@Brief searches registry for matching text value
 *
 * 	@Returns index of found entry, -1 if no matching registry entries are found
 */
int TM_FindStringRegister(char* pSearch)
{
	for(int i=0; i<MAX_REG_INDEX; i++)
	{
		if(strcmp(pSearch, STRINGREG[i].text) == 0)
		{
			return i;
		}

	}
	return -1;
}


/*
 * 	@Brief allocates new data in registry
 *
 * 	@Returns index of new entry, -1 if no empty registry entries are available
 */
int TM_RegisterString(char* pText, int16_t pX, int16_t pY, int16_t pSize)
{
	int res = _GetEmptyRegEntry();
	if(res < 0)
	{
		return -1;
	}
	else
	{
		snprintf(STRINGREG[res].text, sizeof(STRINGREG[res].text), "%s", pText);
		STRINGREG[res].x = pX;
		STRINGREG[res].y = pY;
		STRINGREG[res].size = pSize;
	}
	return res;
}

/*
 * 	@Brief marks registry entry as empty
 *
 * 	@Returns none
 */
void TM_DeRegisterString(uint8_t pIndex)
{
	snprintf(STRINGREG[pIndex].text, sizeof(STRINGREG[pIndex].text), "%s", "");
	STRINGREG[pIndex].x = -1;
	STRINGREG[pIndex].y = -1;
	STRINGREG[pIndex].size = -1;
}

