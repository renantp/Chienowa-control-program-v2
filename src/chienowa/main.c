/*
 * main.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 */

#include "main.h"
#include "runtime.h"
#include "../r_cg_serial.h"
struct GLOBAL g;
eeprom_config e_config = { .csi_flag = &g_csi01_flag, .csi_send_receive =
		R_CSI01_Send_Receive };
uint32_t tick;
struct Number_Setting_s g_numberSetting, clone;
struct Timer_Setting_s g_timerSetting;
const uint8_t timeSettingSize = sizeof(struct Timer_Setting_s) - 1;
uint8_t my_data[40], read_data[40];
uint8_t eeprom_count, eeprom_working;
void init(void) {
	R_UART2_Receive(circular_buffer_calloc(&g_rx_data, 1), 6);

	for (uint8_t i = 0; i < 40; i++) {
		my_data[i] = i;
	}

	if (eeprom_init(&e_config) == 0) {
		eeprom_set_block(NONE_BLOCK);
		eeprom_read((uint8_t*) &g_numberSetting, 0x0000, 41);
		eeprom_write((uint8_t*) &g_numberSetting, 0x0000, 41);
		eeprom_read((uint8_t*) &clone, 0x0000, 41);
	}
}

const uint8_t max = 39;
uint16_t sended, checked;
void loop(void) {
	if (ns_delay_ms(&tick, 10 * 1000)) {
		g_count++;
		if (g_count % 2) {
			if (sended == 0) {
				checked = 0;
			} else {

			}
//			eeprom_write((uint8_t*) my_data, 0x0800, max);
//			my_data[0]++;
//			my_data[max / 2]++;
//			my_data[max - 1]++;
		} else {
//			sended++;
//			eeprom_read((uint8_t*) read_data, 0x0800, max);
//			eeprom_read((uint8_t*) &clone, 0x0000, 41);
		}
	}
	runtime();

	if (eeprom_runtime() == 1 && eeprom_working == 0) {
		eeprom_working = 1;
	} else if (eeprom_working == 1 && eeprom_runtime() == 0) {
		if (my_data[0] == read_data[0] && my_data[max / 2] == read_data[max / 2]
				&& my_data[max - 1] == read_data[max - 1]) {
			sended = sended > 0 ? sended - 1 : sended;
		}
		eeprom_working = 0;
	}
}
