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

#define UART_DATA_POP()	(uart_receive_callback_count--)
#define HAS_UART_DATA	(uart_receive_callback_count > 0)
#define SET_RESPONSE(type)	(uart_response_type) = (type)

#define SHIFT(cmd, bits) (((uint32_t)(cmd)) << (bits))

#define PACK1(c1,...)          ( SHIFT(c1, 0) )
#define PACK2(c1,c2,...)       ( SHIFT(c1, 8) | SHIFT(c2, 0) )
#define PACK3(c1,c2,c3,...)    ( SHIFT(c1,16) | SHIFT(c2, 8) | SHIFT(c3,0) )
#define PACK4(c1,c2,c3,c4,...) ( SHIFT(c1,24) | SHIFT(c2,16) | SHIFT(c3,8) | SHIFT(c4,0) )

enum Response {
	RESPONSE_INIT,
	RESPONSE_IO_DATA
}uart_response_type;

uint32_t uart_receive_callback_count = 0;
uint32_t uart_sended_callback_count = 0;

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
		case WASHING_MODE:
			break;
		default:
			break;
	}
}
uint32_t uart_read_callback_count = 0;
enum Communication_Header head;
enum Communication_Command cmd;
void header_read_callback(uint8_t *const pdata){
	switch (head) {
		case WASHING_MODE:
			send_reponse(pdata, 1);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case CONTROL_SETTING:
			send_reponse(pdata, g.control_setting.raw);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case MACHINE_IO_DATA:
			uart_read_callback_count++;
			send_reponse(pdata, NUMBER_OF_IO_BYTE);
			SET_RESPONSE(RESPONSE_IO_DATA);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		default:
			send_reponse(pdata, 0);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
	}

}
void header_clear_callback(uint8_t *const pdata){

}
void communication_runtime(void){
	if(HAS_UART_DATA){
		uint8_t *const pointer_data = pop_uart_queue();
		cmd = (enum Communication_Command)pointer_data[0];
		head = (enum Communication_Header)pointer_data[1];

		switch (cmd) {
			case H_SET:
				header_set_callback(pointer_data);
				break;
			case H_READ:
				header_read_callback(pointer_data);
				break;
			case H_ERROR:
				break;
			case H_CLEAR:
				header_clear_callback(pointer_data);
				break;
			default:
				R_UART2_Receive(get_pointer_uart_queue(), 6);
				break;
		}
		UART_DATA_POP();
	}
}
void uart_receive_callback(void){
	uart_receive_callback_count++;
}
void uart_sended_callback(void){
	uart_sended_callback_count++;
	switch (uart_response_type) {
		case RESPONSE_IO_DATA:
			R_UART2_Send((uint8_t *)&g.io, NUMBER_OF_IO_BYTE);
			uart_response_type = RESPONSE_INIT;
			break;
		default:
			break;
	}
}
