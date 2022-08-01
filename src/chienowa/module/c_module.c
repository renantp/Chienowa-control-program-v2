/*
 * c_module.c
 *
 *  Created on: Jul 29, 2022
 *      Author: Hung
 */

#include "c_module.h"
#include "s_module.h"
#include "../pin_define.h"
#include "../global_variable.h"
#include "../delay.h"
#include "../adc.h"
#include "e_module.h"

int g_electrolysis_status;

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
			if(g_electrolysis_status == 1){
				if(ns_delay_ms(tick, g_timerSetting.t13_s * 1000)){
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
			if(g_electrolysis_status == 1){
				if(ns_delay_ms(tick, g_timerSetting.t12_s * 1000))
					*state = 1;
			}else{
				*tick = g_systemTick;
			}
			break;
		case 1:
			if (g_electrolysis_status == 1) {
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
			if(g_electrolysis_status == 1){
				if(ns_delay_ms(tick, g_timerSetting.t11_s * 1000))
					*state = 1;
			}else{
				*tick = g_systemTick;
			}
			break;
		case 1:
			if(g_electrolysis_status == 1){
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
		SP = PUMP_OFF;
		*tick = g_systemTick;
		*state = 1;
		break;
	case 1:
		if (ns_delay_ms(tick, g_timerSetting.t5_s * 1000)) {
			SV1 = VALVE_OFF;
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
		SV1 = VALVE_ON;
		SP = PUMP_ON;
		*tick = g_systemTick;
		*state = 1;
		break;
	case 1:
		if (ns_delay_ms(tick, g_timerSetting.t4_2_s * 1000)) {
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
	if (g_electrolysis_status == 1) {
		if (g_ALD != 3 && g_ACD != 3) {
			//TODO: C11 Condition?
			return 1;
		}
	}
	return 0;
}

int c1_electrolusis_status_check(void) {

	return 0;
}