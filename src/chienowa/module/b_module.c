/*
 * b_module.c
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#include "b_module.h"
#include "../pin_define.h"
#include "../delay.h"
#include "../global_variable.h"

#define P_1_ON_T1

struct {
	struct{
		uint32_t p1_t1;
		uint32_t p1_t2;
	}on;
	struct{
		uint32_t p1_t1;
		uint32_t p1_t2;
	}off;
}module_timer;

int bp1_initial_working_mode_start_process(void){
	if(g.flag.module.bp1 == 0){
		module_timer.on.p1_t1 = g_systemTick;
		module_timer.on.p1_t2 = 0;
		g.flag.module.bp1 = 1;
	}
	return 0;
}
int bp0_system_main_start(void){
	return 0;
}
int bp21_alkali_discharge_start(void){
	return 0;
}
int bp22_acid_discharge_start(void){
	return 0;
}
int bp23_water_discharge_start(void){
	return 0;
}
int bp24_hand_wash_start(void){
	return 0;
}
int bp241(void){
	return 0;
}
int bp242(void){
	return 0;
}
int bp243(void){
	return 0;
}
int bp314(void){

	return 0;
}
int bp3_individual_start(void){
	return 0;
}


int bp2_water_discharge_start_process(void){

	return 0;
}

int b_inital_acid_tank_drainage_start_process(void){

	return 0;
}

int bp111_inital_alkali_tank_drainage_start_process(void){
	if( g.flag.module.p111 == 0 ){
		g.flag.module.p111 = 1;
		return 1;
	}
	return 0;
}
int bp112_inital_acid_tank_drainage_start_process(void){
	if( g.flag.module.p112 == 0 ){
		g.flag.module.p112 = 1;
		return 1;
	}
	return 0;
}
int bp13_initial_electrolysis_start_process(void){
	CVCC_CONTROL_PIN = 1U;
	return 0;
}
int bp112_p1_start_process(void){
	return 0;
}
int bp141_2nd_alkali_tank_drain_startup_process(void){
	return 0;
}
int bp142_2nd_acid_tank_drain_startup_process(void){
	return 0;
}
int bp15_electrolysis_start_process(void){
	return 0;
}
int bp11_initial_drainage_start_process(void){
	return 0;
}
int bp12_initial_water_supply_start_process(void){
	return 0;
}
int bp14_initial_2nd_draining_start_process(void){
	return 0;
}

int b_p1_start(void){
	if ( g.io.pump_1 == 0){
		g.io.pump_1 = 1;
		return 1;
	}
	return 0;
}
int b_p2_start(void){
	if( g.io.pump_2 == 0 ){
		PUMP_2_PIN = PUMP_ON;
		g.io.pump_2 = 1;
	}
	return 0;
}
int b_sp_start(void){
	if( g.io.salt_pump == 0 ){
		PUMP_2_PIN = PUMP_ON;
		g.io.salt_pump = 1;
	}
	return 0;
}
int b_sv1_start(void){
	if ( g.io.valve.sv1 == 0){
		SV1_PIN = VALVE_ON;
		g.io.valve.sv1 = 1;
		return 1;
	}
	return 0;
}
int b_sv2_start(void){
	if( g.io.valve.sv2 == 0){
		SV2_PIN = VALVE_ON;
		g.io.valve.sv2 = 1;
		return 1;
	}
	return 0;
}
int b_sv3_start(void){
	if(g.io.valve.sv3 == 0){
		SV3_PIN = VALVE_ON;
		g.io.valve.sv3 = 1;
		return 0;
	}
	return 0;
}
int b_sv4_start(void){
	if(g.io.valve.sv4 == 0){
		SV4_PIN = VALVE_ON;
		g.io.valve.sv4 = 1;
		return 0;
	}
	return 0;
}
int b_sv5_start(void){
	if ( g.io.valve.sv5 == 0){
		SV5_PIN = VALVE_ON;
		g.io.valve.sv5 = 1;
		return 1;
	}
	return 0;
}
int b_sv6_start(void){
	if( g.io.valve.sv6 == 0 ){
		SV6_PIN = VALVE_ON;
		g.io.valve.sv6 = 1;
	}
	return SV6_PIN;
}
int b_sv7_start(void){
	if( g.io.valve.sv7 == 0 ){
		SV7_PIN = VALVE_ON;
		g.io.valve.sv7 = 1;
	}
	return SV7_PIN;
}
