/*******************************************************************************
 *    This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *******************************************************************************/
/*
 * canFeedback.c
 *
 *  Created on: 23 Jul 2018
 *
 *  #DeadlineFighter
 *
 *  Author: Alex Wong
 */

#include "ch.h"
#include "hal.h"
#include "bxCAN.h"
#include <string.h>
#include "canFeedback.h"
#include "pathControl.h"

static pathData_t* pathData;
canFeedback_t feedbackData;

static THD_WORKING_AREA(canFeedbackThd_wa, 1024);
static THD_FUNCTION(canFeedbackThd, p) {

  (void)p;

  static systime_t now = 0;
  static systime_t next = 0;

  CANTxFrame txmsg;
  txmsg.IDE = CAN_IDE_STD;
  txmsg.SID = CAN_FEEDBACK_ID;
  txmsg.RTR = CAN_RTR_DATA;
  txmsg.DLC = 0x08;

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(1000);

    chSysLock();

    feedbackData.Pchassis = (uint16_t) pathData->outPower;
    feedbackData.Pjudge = (uint16_t) pathData->judgePower;
    feedbackData.Vin = (uint8_t)pathData->voltage->vinMv / 1000;
    feedbackData.capEnergy = (int16_t) pathData->capEnergy;
    feedbackData.pathType = (uint8_t) pathData->path;

    memcpy(txmsg.data8, &feedbackData, sizeof(feedbackData));

    chSysUnlock();

    canTransmit(&CAND1, CAN_ANY_MAILBOX, &txmsg, MS2ST(100));

    chThdSleepUntilWindowed(now, next);

  }

}

void canFeedbackInit(void) {

  pathData = returnPathData();

  chThdCreateStatic(canFeedbackThd_wa, sizeof(canFeedbackThd_wa),
                    NORMALPRIO + 10, canFeedbackThd, NULL);

}
