/*
 * t_module.c
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#include "t_module.h"
#include "../pin_define.h"
#include "../global_variable.h"
int tp1_stop_process_initial_working_mode_stop_process(void) {

	return 0;
}
int tp2_wash_mode_stop_process(void) {
	return 0;
}

int tp111_initial_alkali_tank_drainage_stop_process(void) {
	if (g.flag.module.p111 == 1) {
		g.flag.module.p111 = 0;
		return 1;
	}
	return 0;
}
int tp112_inital_acid_tank_drainage_stop_process(void) {
	if (g.flag.module.p112 == 1) {
		g.flag.module.p112 = 0;
		return 1;
	}
	return 0;
}
int tp13_initial_electrolysis_stop_process(void) {
	CVCC_CONTROL_PIN = 0U;
	return 0;
}
int tp141_2nd_alkali_tank_drain_stop_process(void) {
	return 0;
}
int tp142_2nd_acid_tank_drain_stop_process(void) {
	return 0;
}
int tp15_electrolysis_stop_process(void) {
	return 0;
}
int tp11_initial_draining_stop_process(void) {
	return 0;
}
int tp12_inital_water_supply_stop_process(void) {
	return 0;
}
int tp14_initial_2nd_draining_stop_process(void) {
	return 0;
}

int tp21_alkali_discharge_stop(void){
	return 0;
}
int tp22_acid_discharge_stop(void){
	return 0;
}
int tp23_water_discharge_stop(void){
	return 0;
}
int tp24_hand_wash_stop(void){
	return 0;
}
int tp241(void){
	return 0;
}
int tp242(void){
	return 0;
}
int tp243(void){
	return 0;
}
int tp314(void){
	return 0;
}
int tp3_individual_stop(void){
	return 0;
}

int t_sv1_stop(void) {
	if (g.io.valve.sv1 == 1) {
		SV1_PIN = VALVE_OFF;
		g.io.valve.sv1 = 0;
		return 1;
	}
	return 0;
}
int t_sv2_stop(void) {
	if (g.io.valve.sv2 == 1) {
		SV2_PIN = VALVE_OFF;
		g.io.valve.sv2 = 0;
		return 1;
	}
	return 0;
}
int t_sv3_stop(void) {
	if (g.io.valve.sv3 == 1) {
		SV3_PIN = VALVE_OFF;
		g.io.valve.sv3 = 0;
		return 1;
	}
	return 0;
}
int t_sv4_stop(void) {
	if (g.io.valve.sv4 == 1) {
		SV4_PIN = VALVE_OFF;
		g.io.valve.sv4 = 0;
		return 1;
	}
	return 0;
}
int t_sv5_stop(void) {
	if (g.io.valve.sv5 == 1) {
		SV5_PIN = VALVE_OFF;
		g.io.valve.sv5 = 0;
		return 1;
	}
	return 0;
}
int t_sv6_stop(void) {
	if (g.io.valve.sv6 == 1) {
		SV6_PIN = VALVE_OFF;
		g.io.valve.sv6 = 0;
	}
	return 0;
}
int t_sv7_stop(void){
	if (g.io.valve.sv7 == 1){
		SV7_PIN = VALVE_OFF;
		g.io.valve.sv7 = 0;
	}
	return 0;
}
int t_p1_stop(void) {
	if (g.io.pump_1 == 1) {
		g.io.pump_1 = 0;
		return 1;
	}
	return 0;
}

int t_p2_stop(void) {
	if (g.io.pump_2 == 1) {
		PUMP_2_PIN = PUMP_OFF;
		g.io.pump_2 = 0;
	}
	return 0;
}
int t_sp_stop(void) {
	if (g.io.salt_pump == 1) {
		SP_PIN = PUMP_OFF;
		g.io.salt_pump = 0;
		return 1;
	}
	return 0;
}
