/*
 * raspberry_pi_communication.c
 *
 *  Created on: Aug 25, 2022
 *      Author: Renan
 */

#include "raspberry_pi_communication.h"

#define HAS_UART_DATA	(uart_data.tail != uart_data.head)

struct {
	uint8_t data[MAX_UART_DATA_QUEUE][6];
	uint8_t head;
	uint8_t tail;
}uart_data;

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
void header_set_callback(const enum Communication_Header *const head){
	switch (*head) {
		case TIMER_SETTING:

			break;
		case NUMBER_SETTING:

			break;
		case ERROR_PACKAGE:

			break;
		case INDIVITUAL_OUTPUT:

			break;
		default:
			break;
	}
}
void header_read_callback(const enum Communication_Header *const head){

}
void header_clear_callback(const enum Communication_Header *const head){

}

void communication_runtime(void){
	if(HAS_UART_DATA){
		uint8_t *p_data = pop_uart_queue();
		const enum Communication_Command cmd = (enum Communication_Command)p_data[0];
		const enum Communication_Header head = (enum Communication_Header)p_data[1];

		switch (cmd) {
			case H_SET:
				header_set_callback(&head);
				break;
			case H_READ:
				header_read_callback();
				break;
			case H_ERROR:

				break;
			case H_CLEAR:
				header_clear_callback();
				break;
			default:
				break;
		}

	}
}

void uart_callback(uint8_t *const pdata){
	push_uart_queue(pdata);
}
