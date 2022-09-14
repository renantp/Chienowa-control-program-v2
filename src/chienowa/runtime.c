/*
 * runtime.c
 *
 *  Created on: Aug 11, 2022
 *      Author: Renan
 */
#include "eeprom.h"
#include "raspberry_pi_communication.h"
#include "global_variable.h"
#include "pin_define.h"
#include "adc.h"
#include "water_flow_calculation.h"
#include "hand_sensor.h"
#include "individual_mode.h"
#include "delay.h"
#include "../r_cg_dac.h"

void input_flag_update(void){
	g.io.fl1 = !FL1;
	g.io.fl2 = !FL2;
	g.io.fl3 = !FL3;
	g.io.fl4 = !FL4;
	g.io.fl5 = !FL5;
	g.io.fl6 = !FL6;
	g.io.fl7 = !FL7;
	g.io.fl8 = !FL8;

	g.io.valve.sw1 = !SW1_PIN;
	g.io.valve.sw2 = !SW2_PIN;
	g.io.valve.sw3 = !SW3_PIN;

	g.io.cvcc_alarm_in = !CVCC_ALARM_IN_PIN;
	g.io.hand_sensor_on = g_hs.on;
	g.io.hand_sensor_off = g_hs.off;
}

void output_flag_update(void){
	g.io.valve.sv1 = SV1_PIN;
	g.io.valve.sv2 = SV2_PIN;
	g.io.valve.sv3 = SV3_PIN;
	g.io.valve.sv4 = SV4_PIN;
	g.io.valve.sv5 = SV5_PIN;
	g.io.valve.sv6 = SV6_PIN;
	g.io.valve.sv7 = SV7_PIN;
	g.io.pump_1 = !PUMP_1_PIN;
	g.io.pump_2 = !PUMP_2_PIN;
	g.io.salt_pump = !SP_PIN;
	g.io.cvcc_control = CVCC_CONTROL_PIN;
	g.io.cvcc_alarm_out = CVCC_ALARM_OUT_PIN;
}

void adc_value_update(void){
	g.cvcc_current = g_adc.current;
	g.cvvc_voltage = g_adc.voltage;
}
uint32_t pump_3_timer;
void runtime(void){
	individual_runtime();
	input_flag_update();
	output_flag_update();
	communication_runtime();
	adc_value_update();
	eeprom_runtime();
//	water_flow_runtime();
	hand_sensor_runtime();
	if(elapsed_time_ms(pump_3_timer) > 1000){
		PUMP_3_PIN = !PUMP_3_PIN;
		pump_3_timer = timer_start_ms();
/**
 * This block of code make it stop
 */
//		if(g_V_S.v10_V > 0.0f){
//			uint8_t radio = ((g_V_S.v10_V) / 5.0f);
//			SV1_PIN = VALVE_ON;
//			uint8_t sat = (0xff * radio);
//			SV2_PIN = VALVE_ON;
//			R_DAC1_Set_ConversionValue(sat);
//			SV3_PIN = VALVE_ON;
//		}
	}
}
