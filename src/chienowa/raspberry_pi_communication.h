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
	COMMAND_INIT = 0,
	H_READ = 82, //0x52, R
	H_SET = 83,  //0x53, W
	H_ALARM = 65,
	H_ERROR = 69,
	H_CLEAR = 67
};

enum Communication_Header{
	HEADER_INIT,
	TIMER_SETTING,
	NUMBER_SETTING,
	ERROR_PACKAGE,
	INDIVITUAL_OUTPUT,
	MACHINE_IO_DATA = 23U,
	WASHING_MODE = 24U,
	CONTROL_SETTING = 44U,
};

uint8_t * get_pointer_uart_queue(void);
void go_next_uart_queue(void);
void uart_receive_callback(void);
void uart_sended_callback(void);
void communication_runtime(void);
#endif /* CHIENOWA_RASPBERRY_PI_COMMUNICATION_H_ */
