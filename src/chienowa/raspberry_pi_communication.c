/*
 * raspberry_pi_communication.c
 *
 *  Created on: Aug 25, 2022
 *      Author: Renan
 */

#include "raspberry_pi_communication.h"
#include "global_variable.h"
#include "module/e_module.h"
#include "crc8.h"
#include "../r_cg_serial.h"

#define HAS_UART_DATA	(uart_data.tail != uart_data.head)

struct {
	uint8_t data[MAX_UART_DATA_QUEUE][6];
	uint8_t head;
	uint8_t tail;
}uart_data;

uint8_t * get_pointer_uart_queue(void){
	uint8_t *const ret = uart_data.data[uart_data.head];
	go_next_uart_queue();
	return ret;
}
void go_next_uart_queue(void){
	uint8_t next = uart_data.head + 1;
	if(next >= MAX_UART_DATA_QUEUE)
		next = 0;
	if (next == uart_data.tail) {
		return;
	}
	uart_data.head = next;
}
void push_uart_queue(uint8_t *const pdata){
	uint8_t next = uart_data.head + 1;
	if(next >= MAX_UART_DATA_QUEUE)
		next = 0;
	if (next == uart_data.tail) {
		return;
	}
	for(int i=0; i<6;i++){
		uart_data.data[uart_data.head][i] = pdata[i];
	}
	uart_data.head = next;
}
uint8_t * pop_uart_queue(void){
	uint8_t next = uart_data.tail + 1;
	if (next >= MAX_UART_DATA_QUEUE)
		next =  0;
	uint8_t * const ret = uart_data.data[uart_data.tail];
	if(uart_data.tail != uart_data.head)
		uart_data.tail = next;
	return ret;
}
void send_reponse(uint8_t *const pdata, uint32_t data){
	uint8_t* write_it = pdata + 2;
	(*write_it) = data;
	R_UART2_Send(pdata, 6);
}
void header_set_callback(uint8_t *const pdata){
	const enum Communication_Header head = (enum Communication_Header)pdata[1];
	switch (head) {
		case TIMER_SETTING:
			send_reponse(pdata, 1);
			g_T_S.crc = crc8((uint8_t *)&g_T_S, sizeof(g_T_S));
			R_UART2_Send((uint8_t *)&g_T_S, sizeof(g_T_S));
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case NUMBER_SETTING:
			send_reponse(pdata, 1);
			g_V_S.crc = crc8((uint8_t *)&g_V_S, sizeof(g_V_S));
			R_UART2_Send((uint8_t *)&g_V_S, sizeof(g_V_S));
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case ERROR_PACKAGE:
			send_reponse(pdata, e_current_error);
			break;
		case INDIVITUAL_OUTPUT:

			break;
		default:
			break;
	}
}
void header_read_callback(uint8_t *const pdata){

}
void header_clear_callback(uint8_t *const pdata){

}

void communication_runtime(void){
	if(HAS_UART_DATA){
		uint8_t *const p_data = pop_uart_queue();
		const enum Communication_Command cmd = (enum Communication_Command)p_data[0];
		switch (cmd) {
			case H_SET:
				header_set_callback(p_data);
				break;
			case H_READ:
				header_read_callback(p_data);
				break;
			case H_ERROR:

				break;
			case H_CLEAR:
				header_clear_callback(p_data);
				break;
			default:
				break;
		}
	}
}

void uart_callback(void){

}
