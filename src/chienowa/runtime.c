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
}

void output_flag_update(void){
	g.io.valve.sv1 = SV1_PIN;
	g.io.valve.sv2 = SV2_PIN;
	g.io.valve.sv3 = SV3_PIN;
	g.io.valve.sv4 = SV4_PIN;
	g.io.valve.sv5 = SV5_PIN;
	g.io.valve.sv6 = SV6_PIN;
	g.io.valve.sv7 = SV7_PIN;
	g.io.cvcc_control = CVCC_CONTROL_PIN;
	g.io.cvcc_alarm_out = CVCC_ALARM_OUT_PIN;
}

void adc_value_update(void){
	g.cvcc_current = g_adc.current;
	g.cvvc_voltage = g_adc.voltage;
}

void runtime(void){
	input_flag_update();
	output_flag_update();
	adc_value_update();
	eeprom_runtime();
	communication_runtime();
	water_flow_runtime();
}
