/**
  ******************************************************************************
  * @file    basic_gui.h
  * @author  MCD Application Team
  * @brief   This file contains the common defines and functions prototypes for
  *          the basic_gui.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#ifndef STMBASICGUI_H_
#define STMBASICGUI_H_
#include <stdio.h>
/**
  * @brief  GUI Drawing point (pixel) geometric definition
  */
typedef struct
{
  int16_t X; /*!< geometric X position of drawing */
  int16_t Y; /*!< geometric Y position of drawing */
} Point;

/**
  * @brief  Pointer on GUI Drawing point (pixel) geometric definition
  */
typedef Point * pPoint;


#define ABS(X)                 ((X) > 0 ? (X) : -(X))
#define POLY_X(Z)              ((int32_t)((Points + (Z))->X))
#define POLY_Y(Z)              ((int32_t)((Points + (Z))->Y))

void GUI_DrawLine(uint32_t Xpos1, uint32_t Ypos1, uint32_t Xpos2, uint32_t Ypos2, uint32_t Color);
void GUI_DrawPolygon(pPoint Points, uint32_t PointCount, uint32_t Color);
void GUI_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius, uint32_t Color);
void GUI_FillCircle(uint32_t Xpos, uint32_t Ypos, uint32_t Radius, uint32_t Color);
void GUI_FillPolygon(pPoint Points, uint32_t PointCount, uint32_t Color);
void GUI_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius, uint32_t Color);


#endif /* STMBASICGUI_H_ */
