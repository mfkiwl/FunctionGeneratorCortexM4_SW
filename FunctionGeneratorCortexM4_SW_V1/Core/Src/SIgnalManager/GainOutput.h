/*
 * GainOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_GAINOUTPUT_H_
#define SRC_SIGNALMANAGER_GAINOUTPUT_H_

#include <stdint.h>

void GO_SetOutputToEncoder(uint8_t pGain);
void GO_SetOutputGain(uint8_t pGain, uint8_t reverse);
uint8_t GO_GetOutputGain();

#endif /* SRC_SIGNALMANAGER_GAINOUTPUT_H_ */
