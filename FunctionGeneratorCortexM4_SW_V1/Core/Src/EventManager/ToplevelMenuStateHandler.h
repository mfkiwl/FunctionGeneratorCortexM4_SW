/*
 * ToplevelMenuStateHandler.h
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_EVENTMANAGER_TOPLEVELMENUSTATEHANDLER_H_
#define SRC_EVENTMANAGER_TOPLEVELMENUSTATEHANDLER_H_

#include "EventManager.h"

/*
 * 	Sub menus should have their ExitHandlers set eXXXXMenu_Status to ENABLE_xxxx_MAIN_MENU
 */
typedef enum
{
	DISABLE_TOPLEVEL_MENU = 0x00U,
	ENABLE_TOPLEVEL_MAIN_MENU,
	ENABLE_TOPLEVEL_OUTPUT_MENU,
	ENABLE_TOPLEVEL_INPUT_MENU

} eToplevelMenu_Status;


eToplevelMenu_Status ToplevelMenu_getStatus();
void ToplevelMenu_setStatus(eToplevelMenu_Status pStatus);

eSystemState ToplevelMainMenuEntryHandler();
eSystemState ToplevelMainMenuInputHandler();
eSystemState ToplevelMainMenuExitHandler();

eSystemState ToplevelOutputMenuEntryHandler();
eSystemState ToplevelOutputMenuInputHandler();
eSystemState ToplevelOutputMenuExitHandler();

eSystemState ToplevelInputMenuEntryHandler();
eSystemState ToplevelInputMenuInputHandler();
eSystemState ToplevelInputMenuExitHandler();


#endif /* SRC_EVENTMANAGER_TOPLEVELMENUSTATEHANDLER_H_ */