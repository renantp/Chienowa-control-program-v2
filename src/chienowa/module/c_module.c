/*
 * c_module.c
 *
 *  Created on: Jul 29, 2022
 *      Author: Renan
 */

#include "c_module.h"
#include "s_module.h"
#include "b_module.h"
#include "t_module.h"
#include "../pin_define.h"
#include "../global_variable.h"
#include "../delay.h"
#include "../adc.h"
#include "e_module.h"

int c1_on_off(uint8_t on_off){
	if(on_off){
		g.flag.module.c1 = 0;
		SP_PIN = PUMP_OFF; //SP_F=0?
		b_sv1_start(); //SV１（給水） ON処理
		b_sp_start(); //SP（塩ポンプ） ON処理
		if(elapsed_time_s(SP_ON_T2)/1000 >= g_T_S.t17_s){
			bc1();
		}
	}else{
		//C_1_F=1
		g.flag.module.c1 = 1;
		//SP_F=1
		SP_PIN = PUMP_ON;
		//T-SP   SP（塩ポンプ）Stop処理
		t_sp_stop();
		if(elapsed_time_ms(SP_OFF_T2)/1000 >= g_T_S.t5_s){
			t_sv1_stop();
			//TODO: tc1() flow chart is missing

			C_1_ON_T3 = timer_stop_s(C_1_ON_T3);
			return -1;
		}else{
			return -2;
		}
	}
	return 0;
}

struct C_5_3 {
	uint8_t state;
	uint8_t rsvd;
	uint32_t tick;
}c5_3;
uint8_t size = sizeof(c5_3);
int c53_over_voltage_3_check(float *voltage){
	uint8_t *state = &c5_3.state;
	uint32_t *tick = &c5_3.tick;
	switch (*state) {
		case 0:
			if(g.flag.electrolysis == 1){
				if(ns_delay_ms(tick, g_T_S.t13_s * 1000)){
					*state = 1;
				}else{
					*tick = g_systemTick;
				}
			}
			break;
		case 1:
			//TODO: Call C531

			break;
		default:
			break;
	}
	return 0;
}
struct C_5_2{
	uint8_t state;
	uint8_t rsvd;
	uint32_t tick;
}c5_2;
/**
 * Check over voltage 1 and call error module
 * @param voltage - float pointer to over voltage 1
 * @return int [-1:0]
 * -1: Error occur
 * 0: No error
 */
int c52_over_voltage_2_check(float *voltage){
	uint8_t *state = &c5_2.state;
	uint32_t *tick = &c5_2.tick;
	switch (*state) {
		case 0:
			if(g.flag.electrolysis == 1){
				if(ns_delay_ms(tick, g_T_S.t12_s * 1000))
					*state = 1;
			}else{
				*tick = g_systemTick;
			}
			break;
		case 1:
			if (g.flag.electrolysis == 1) {
				//TODO: Check for over voltage 2
				if(g_adc.voltage > *voltage){
					if(g_error_status.over_voltage_2 == 0){
						//TODO: Call E-1003
						g_error_status.over_voltage_2 = 1;
					}
					return -1;
				}

			} else {
				*state = 0;
			}
			break;
		default:
			break;
	}
	return 0;
}

struct C_5_1{
	uint8_t state;
	uint8_t rsvd;
	uint32_t tick;
}c5_1;
/**
 * Check over voltage 1 and call error module
 * @param voltage - float pointer to over voltage 1
 * @return int [-1:0]
 * -1: Error occur
 * 0: No error
 */
int c51_over_voltage_1_check(float *voltage){
	uint8_t *state = &c5_1.state;
	uint32_t *tick = &c5_1.tick;
	switch (*state) {
		case 0:
			if(g.flag.electrolysis == 1){
				if(ns_delay_ms(tick, g_T_S.t11_s * 1000))
					*state = 1;
			}else{
				*tick = g_systemTick;
			}
			break;
		case 1:
			if(g.flag.electrolysis == 1){
				//TODO: Check for over voltage 1
				if (g_adc.voltage > *voltage) {
					if(g_error_status.over_voltage_1 == 0){
						//TODO: Call E-1002
						g_error_status.over_voltage_1 = 1;
					}
					return -1;
				}
			}else{
				*state = 0;
			}
			break;
		default:
			break;
	}
	return 0;
}

int c5_electrolysis_check_process(void){
	int errors = 0;
	if(c51_over_voltage_1_check(&g_numberSetting.upperVoltage1))
		errors++;
	if(c52_over_voltage_2_check(&g_numberSetting.upperVoltage2))
		errors++;
	return errors;
}

/**
 * TODO: C4 - inital start flag? when call salt tank full error E-1020
 * Check acid level data (SAD) and call error module
 * @return int [-2:0]
 * 0: SAD not changed
 * 1: SAD go back to normal (from error state)
 * -1, -2: SAD have error
 */
int c4_salt_tank_sensor_value_check_process(void){
	if (s3_salt_tank_data_set()) {
		if (g_SAD < 0){
			//TODO: Call E-1023
			return -2;
		}else if (g_SAD == 0){
			//TODO: Call E-1021
			return -1;
		}else{
			return 1;
		}
	}
	return 0;
}

/**
 * Check acid level data (ACD) and call error module
 * @return int [-2:0]
 * 0: ACD not changed
 * 1: ACD go back to normal (from error state)
 * -1, -2: ACD have error
 */
int c3_acid_tank_level_check(void){
	if (s2_acid_tank_data_set()){
		if(g_ACD < 0){
			//TODO: Call E-1024
			return -2;
		}else if(g_ACD == 0){
			//TODO: call E-1028
			return -1;
		}else{
			return 1;
		}
	}
	return 0;
}

/**
 * Check alkali level data (ALD) and call error module
 * @return int [-2:0]
 * 0: ALD not change
 * 1: ALD go back to normal (from error state)
 * -1, -2: ALD have error
 */
int c2_alkali_tank_level_check(void) {
	if (s1_alkali_tank_data_set()) {
		if (g_ALD < 0) {
			//TODO: Call E-1025
			return -2;
		} else if (g_ALD == 0) {
			//TODO: Call E-1029
			return -1;
		} else {
			return 1;
		}
	}
	return 0;
}

struct C_1_3 {
	uint8_t state;
	uint8_t rsvd;
	uint32_t tick;
} c1_3;
//TODO: C13 - Electrolysis stop process
int c13_electrolysis_stop_process(void) {
	uint8_t *state = &c1_3.state;
	uint32_t *tick = &c1_3.tick;
	switch (*state) {
	case 0:
		//TODO: TC1 - CVCC（ER＝電解装置）OFF
		SP_PIN = PUMP_OFF;
		*tick = g_systemTick;
		*state = 1;
		break;
	case 1:
		if (ns_delay_ms(tick, g_T_S.t5_s * 1000)) {
			SV1_PIN = VALVE_OFF;
			//TODO: Neutralized timer stop
			*state = 0;
		}
		break;
	default:
		break;
	}
	if (*state != 0)
		return 1;
	return 0;
}

struct C_1_2 {
	uint8_t state;
	uint8_t rsvd;
	uint32_t tick;
} c1_2;
//TODO: C12 - Electrolysis start
int c12_electrolysis_start(void) {
	uint8_t *state = &c1_2.state;
	uint32_t *tick = &c1_2.tick;
	switch (*state) {
	case 0:
		SV1_PIN = VALVE_ON;
		SP_PIN = PUMP_ON;
		*tick = g_systemTick;
		*state = 1;
		break;
	case 1:
		if (ns_delay_ms(tick, g_T_S.t4_2_s * 1000)) {
			//TODO: C1 - Insert BC1 here?? CVCC（ER＝電解装置）ON
			*state = 0;
		}
		break;
	default:
		break;
	}
	if (*state == 0)
		return 1;
	return 0;
}

//TODO: C11 - Electrolysis status
int c11_electrolysis_status(void) {
	if (g.flag.electrolysis == 1) {
		if (g_ALD != 3 && g_ACD != 3) {
			//TODO: C11 Condition?
			return 1;
		}
	}
	return 0;
}

int c1_electrolysis_service_start(void) {

	return 0;
}

int c19_salt_tank_drain_check(void){

	return 0;
}

int c5_electrolysis_CVCC_status(void) { return 0; }
