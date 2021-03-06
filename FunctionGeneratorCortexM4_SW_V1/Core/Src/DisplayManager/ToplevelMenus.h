/*
 * ToplevelMenus.h
 *
 *	Declares draw functions for TopLevel menu and its sub menus: Output and Input
 *
 *  Created on: 15 May 2020
 *      Author: chris
 */

#ifndef SRC_DISPLAYMANAGER_TOPLEVELMENUS_H_
#define SRC_DISPLAYMANAGER_TOPLEVELMENUS_H_

#include "ToplevelMenuStateHandler.h"

void ToplevelMenu_DrawMenu(eSystemState pMenu);

void ToplevelMenu_DrawMainMenu();
void ToplevelMenu_DrawOutputMenu();
void ToplevelMenu_DrawInputMenu();



#endif /* SRC_DISPLAYMANAGER_TOPLEVELMENUS_H_ */
