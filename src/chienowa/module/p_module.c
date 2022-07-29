/*
 * p_module.c
 *
 *  Created on: Jul 27, 2022
 *      Author: Renan
 *
 */

#include "p_module.h"
#include "../pin_define.h"
#include "../delay.h"

struct P_1_5_1{
	uint16_t state;
	uint32_t tick;
}g_p1_5_1;
struct P_1_5_2{
	uint16_t state;
	uint32_t tick;
}g_p1_5_2;
struct P_1_5{
	uint16_t state;
	uint32_t tick;
}g_p1_5;
int p151_electrolysis_start_process(void){
	uint16_t *v = &g_p1_5_1.state;
	uint32_t *tick = &g_p1_5_1.tick;
	switch (*v) {
		case 0:
			SV1 = VALVE_ON;
			SP = PUMP_ON;
			*tick = g_systemTick;
			*v = 1;
			break;
		case 1:
			if(ns_delay_ms(tick, 2*1000)){
				*v = 2;
			}
			break;
		case 2:
			//TODO: Call BP-1-5, will return 1 when done
			break;
		case 3:
			//TODO: Neutralized timer ON
			*v = 0;
			return 1;
	}
	return 0;
}

int p152_electrolysis_stop_process(void){
	uint16_t *v = &g_p1_5_2.state;
	uint32_t *tick = &g_p1_5_2.tick;
	switch (*v) {
		case 0:
			//TODO: TP-1-5, turn off CVCC
			SP = PUMP_OFF;
			*v = 1;
			break;
		case 1:
			if(ns_delay_ms(tick, 5*1000)){
				*v = 2;
			}
			break;
		case 2:
			SV1 = VALVE_OFF;
			//TODO: Neutralized timer OFF
			*v = 0;
			return 1;
	}
	return 0;
}

int p15_electrolysis_water_generation(void){
	uint16_t *v = &g_p1_5.state;
	uint32_t *tick = &g_p1_5.tick;
	switch (*v) {
		case 0:
			//TODO: Check ALD != 3 or ACD != 3 go to case 1
			break;
		case 1:
			if(p151_electrolysis_start_process()){
				*v = 2;
			}
			break;
		case 2:
			//TODO: Check ALD == 3 and ACD == 3 go to case 3
			break;
		case 3:
			if(p152_electrolysis_stop_process()){
				*v = 0;
			}
			break;
		default:
			break;
	}
	return 0;
}
