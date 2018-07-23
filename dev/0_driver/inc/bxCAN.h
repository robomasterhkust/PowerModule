/*
 * bxCAN.h
 *
 *  Created on: 16 Jul 2018
 *      Author: Alex Wong
 */

#ifndef BXCAN_H_
#define BXCAN_H_

#define CAN_FEEDBACK_ID				0x050
#define CAN_CONTROL_ID				0x055

typedef enum {

	notUpdated = 0,
	updated = 1

} msgUpdatedEnum;

typedef struct userCommand_t{

	msgUpdatedEnum msgUpdated;
	uint8_t pathType;			//1 = judge power, 2 = cap power
	uint8_t robotType;		//1 = 80W limit, 2 = 120W limit

} userCommand_t;

typedef struct canFeedback_t{

	uint8_t Vin;					//V
	uint8_t pathType;			//0 = diode, 1 = judge power, 2 = cap power
	int16_t capEnergy;		//J, 0.5 * C * (Vcap^2 - Vmin^2)
	uint16_t Pjudge;			//W
	uint16_t Pchassis;		//W

}__attribute__((packed)) canFeedback_t;

userCommand_t* returnCommand(void);
void can_processInit(void);

#endif /* 0_DRIVER_INC_BXCAN_H_ */
