/*
 * main.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 */

#include "main.h"
#include "runtime.h"
#include "raspberry_pi_communication.h"
#include "../r_cg_serial.h"
#include "module/p_module.h"

struct GLOBAL g;
eeprom_config e_config = { .csi_flag = &g_csi01_flag, .csi_send_receive =
		R_CSI01_Send_Receive };
struct Number_Setting_s g_V_S, clone;
struct Timer_Setting_s g_T_S;
void set_timer_setting_default(void){
	g_T_S.t2_s = 15;
}
void init(void) {
	R_UART2_Receive(get_pointer_uart_queue(), 6);

	// EEPROM initialize
	if (eeprom_init(&e_config) == 0) {
		eeprom_set_block(NONE_BLOCK);
	}
	set_timer_setting_default();
}

const uint8_t max = 39;
uint16_t sended, checked;
void loop(void) {
	p0_system_main_prpocess();
	runtime();
}
