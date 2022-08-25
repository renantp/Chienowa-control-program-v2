/*
 * raspberry_pi_communication.h
 *
 *  Created on: Aug 25, 2022
 *      Author: Hung
 */

#ifndef CHIENOWA_RASPBERRY_PI_COMMUNICATION_H_
#define CHIENOWA_RASPBERRY_PI_COMMUNICATION_H_

#include "../r_cg_macrodriver.h"

#define MAX_UART_DATA_QUEUE	(10)

enum Communication_Command{
	H_READ = 82, //0x52, R
	H_SET = 83,  //0x53, W
	H_ALARM = 65,
	H_ERROR = 69,
	H_CLEAR = 67
};

enum Communication_Header{
	TIMER_SETTING,
	NUMBER_SETTING,
	ERROR_PACKAGE,
	INDIVITUAL_OUTPUT,
};


void uart_callback(uint8_t *const pdata);
#endif /* CHIENOWA_RASPBERRY_PI_COMMUNICATION_H_ */
