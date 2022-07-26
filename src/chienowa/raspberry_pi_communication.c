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
#include "delay.h"
#include "hand_sensor.h"
#include "individual_mode.h"
#include "water_flow_calculation.h"
#include "../r_cg_dac.h"

#define UART_DATA_POP()	(uart_receive_callback_count--)
#define HAS_UART_DATA	(uart_receive_callback_count > 0)
#define SET_SEND_RESPONSE(type)		((uart_response_type) = (type))
#define SET_RECEIVE_RESPONSE(type)	((uart_receive_type) = (type))
#define UART_MAX_TIMEOUT			(1000)
#define UART_MAX_RESET_TIME			(10)


#define SHIFT(cmd, bits) (((uint32_t)(cmd)) << (bits))

#define PACK1(c1,...)          ( SHIFT(c1, 0) )
#define PACK2(c1,c2,...)       ( SHIFT(c1, 8) | SHIFT(c2, 0) )
#define PACK3(c1,c2,c3,...)    ( SHIFT(c1,16) | SHIFT(c2, 8) | SHIFT(c3,0) )
#define PACK4(c1,c2,c3,c4,...) ( SHIFT(c1,24) | SHIFT(c2,16) | SHIFT(c3,8) | SHIFT(c4,0) )

#define PACK_VARIABLE(c1,c2,c3,c4,N,...) PACK##N (c1, c2, c3, c4, __VA_ARGS__)
#define PACK(...) PACK_VARIABLE(__VA_ARGS__,4,3,2,1,0)
enum Response {
	RESPONSE_IDLE,
	RESPONSE_IO_DATA,
	RESPONSE_TIME,
	RESPONSE_NUMBER,
}uart_response_type;
enum Receive {
	RECEIVE_IDLE,
	RECEIVE_TIME = 2,
	COPY_TIME = 3,
	RECEIVE_NUMBER,
	COPY_NUMBER,
}uart_receive_type;

uint32_t uart_receive_callback_count = 0;
uint32_t uart_sended_callback_count = 0;
uint32_t uart_read_callback_count = 0;
uint32_t uart_timeout = 0;
enum Communication_Header head;
enum Communication_Command cmd;

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
		case OK_USER:
			send_reponse(pdata, OK_USER);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			g_hs.on = 1;
			break;
		case TEST_INDIVITUAL_MODE:
			send_reponse(pdata, TEST_INDIVITUAL_MODE);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			init_individual = 1;
			SYSTEM_MODE = INDIVIDUAL;
			break;
		case MACHINE_IO_DATA:
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			getIOData(pdata);
			send_reponse(pdata, 1);
			break;
		case NORMAL_MODE:
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			SYSTEM_MODE = WASHING;
			resetIO();
			send_reponse(pdata, 1);
			break;
		case WASHING_MODE:
			g.mode = (enum WASH_MODE_E)pdata[3]; //TODO: Change from pdata[5] to pdata[3]
			send_reponse(pdata, g.mode);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case TIME_SETTING:
			R_UART2_Receive((uint8_t *)&g_T_S_buffer, NUMBER_OF_TIMER_SETTING_BYTE);
			send_reponse(pdata, NUMBER_OF_TIMER_SETTING_BYTE);
			SET_RECEIVE_RESPONSE(RECEIVE_TIME);
			break;
		case NUMBER_SETTING:
			send_reponse(pdata, 1);
			SET_RECEIVE_RESPONSE(RECEIVE_NUMBER);
			R_UART2_Receive((uint8_t *)&g_V_S_buffer, NUMBER_OF_NUMBER_SETTING_BYTE);
			break;
		case CONTROL_DRAINAGE_MODE:
//			g.control_setting.drain = PACK(pdata[2], pdata[3], pdata[4], pdata[5]);
			g.control_setting.drain = pdata[2];
			send_reponse(pdata, g.control_setting.drain);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case CONTROL_BIOMETRIC:
			g.control_setting.biomectric = pdata[2];
			send_reponse(pdata, g.control_setting.biomectric);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case CONTROL_POWER_ON:
			g.control_setting.power_on = pdata[2];
			send_reponse(pdata, g.control_setting.power_on);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case CONTROL_WATER_FILTER:
			g.control_setting.filter = pdata[2];
			send_reponse(pdata, g.control_setting.filter);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case ERROR_PACKAGE:
//			send_reponse(pdata, e_occur_error);
			break;
		case SALT_PUMP_VOLTAGE:
			R_DAC1_Set_ConversionValue(pdata[2]);
			send_reponse(pdata, pdata[2]);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		default:
			break;
	}
}
uint8_t size_of_time_setting = NUMBER_OF_TIMER_SETTING_BYTE;
void header_read_callback(uint8_t *const pdata){
	uart_read_callback_count++;
	switch (head) {
		case WASHING_MODE:
			send_reponse(pdata, g.mode);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case TIME_SETTING:
			send_reponse(pdata, NUMBER_OF_TIMER_SETTING_BYTE);
			g_T_S.crc = crc8((uint8_t *)&g_T_S, NUMBER_OF_TIMER_SETTING_BYTE - 2);
			SET_SEND_RESPONSE(RESPONSE_TIME);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case NUMBER_SETTING:
			send_reponse(pdata, NUMBER_OF_NUMBER_SETTING_BYTE);
			g_V_S.crc = crc8((uint8_t *)&g_V_S, NUMBER_OF_NUMBER_SETTING_BYTE - 4);
			SET_SEND_RESPONSE(RESPONSE_NUMBER);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case CONTROL_SETTING:
			send_reponse(pdata, g.control_setting.raw);
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			break;
		case MACHINE_IO_DATA:
			send_reponse(pdata, NUMBER_OF_IO_BYTE);
			SET_SEND_RESPONSE(RESPONSE_IO_DATA);
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
uint8_t uart_counter;
uint8_t timer_setting_receive_correct;
uint8_t wait_for_reset = 0;
void communication_runtime(void){
	if(HAS_UART_DATA){
		if(uart_receive_type == COPY_NUMBER){
			if(g_V_S_buffer.crc == crc8((uint8_t *)&g_V_S_buffer, NUMBER_OF_NUMBER_SETTING_BYTE - 4)){
				g_V_S = g_V_S_buffer;
			}else{
				// Handle data lost.
			}
			uart_receive_type = RECEIVE_IDLE;
		}else if(uart_receive_type == COPY_TIME){
			if(g_T_S_buffer.crc == crc8((uint8_t *)&g_T_S_buffer, NUMBER_OF_TIMER_SETTING_BYTE - 2)){
				g_T_S = g_T_S_buffer;
				timer_setting_receive_correct++;
			}else{
				//TODO Handle data lost.
			}
			uart_receive_type = RECEIVE_IDLE;
		}else{
			uart_counter++;
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
		}
		UART_DATA_POP();
	}


}
void uart_receive_callback(void){
	uart_receive_callback_count++;
	switch (uart_receive_type) {
		case RECEIVE_TIME:
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			uart_receive_type = COPY_TIME;
			break;
		case RECEIVE_NUMBER:
			R_UART2_Receive(get_pointer_uart_queue(), 6);
			uart_receive_type = COPY_NUMBER;
			break;
		default:
			break;
	}
}
uint32_t send_hand_sensor_on;
uint32_t count_false;
void uart_sended_callback(void){
	uart_sended_callback_count++;
	switch (uart_response_type) {
		case RESPONSE_TIME:
			R_UART2_Send((uint8_t *)&g_T_S, NUMBER_OF_TIMER_SETTING_BYTE);
			uart_response_type = RESPONSE_IDLE;
			break;
		case RESPONSE_NUMBER:
			R_UART2_Send((uint8_t *)&g_V_S, NUMBER_OF_NUMBER_SETTING_BYTE);
			uart_response_type = RESPONSE_IDLE;
			break;
		case RESPONSE_IO_DATA:
			R_UART2_Send((uint8_t *)&g.io, NUMBER_OF_IO_BYTE);
//			if(g.io.hand_sensor_on) ++send_hand_sensor_on;
			uart_response_type = RESPONSE_IDLE;
			break;
		case RESPONSE_IDLE:
		default:
			break;
	}
}
float get_2_5(void){
	return 2.5f;
}
