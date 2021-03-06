/*
 * FreqSweep.h
 *
 *  Created on: May 23, 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FREQSWEEP_H_
#define SRC_SIGNALMANAGER_FREQSWEEP_H_

typedef enum
{
	SWEEP_MODE_UP = 0U,
	SWEEP_MODE_DOWN,
	SWEEP_MODE_BIDIR

} eFreqSweepModes;

typedef enum
{
	ENCODER_SWEEP_SPEED_FUNCTION = 0U,
	ENCODER_SWEEP_LIMIT_FUNCTION
} eEncoderSweepFunctions;

eFreqSweepModes active_sweep_mode;
eEncoderSweepFunctions theCurrentEncoderSweepFunction;

void FS_SetSweepModeDown();
void FS_SetSweepModeUp();
void FS_SetEncoderControlMode(eEncoderSweepFunctions pFunction);
void FS_SetSweepTimerAutoReloadForEncoderControl(eEncoderSweepFunctions pFunction);
float FS_GetCalculatedSweepFrequencyInHertz();


#endif /* SRC_SIGNALMANAGER_FREQSWEEP_H_ */
