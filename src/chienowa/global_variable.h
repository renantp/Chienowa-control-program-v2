/*
 * global_variable.h
 *
 *  Created on: Jul 25, 2022
 *      Author: Hung
 */

#ifndef CHIENOWA_GLOBAL_VARIABLE_H_
#define CHIENOWA_GLOBAL_VARIABLE_H_

#include "../r_cg_macrodriver.h"
#include "circular_buffer.h"

#define UART_MAX_LEN (6)
#define TIMER_SETTING_MAX (40)

extern uint8_t g_uart2_rx_data[UART_MAX_LEN], g_uart2_tx_data[UART_MAX_LEN];
extern circular_buffer g_rx_data;
extern volatile int8_t g_uart2_recieve_end, g_uart2_send_end;
extern volatile int8_t g_csi01_flag;
extern uint32_t g_count;

#endif /* CHIENOWA_GLOBAL_VARIABLE_H_ */
