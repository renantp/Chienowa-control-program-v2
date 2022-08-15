/*
 * b_module.c
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#include "b_module.h"
#include "../pin_define.h"

int bp211_alkali_mode_start_process(void){
	return 0;
}

int bp2_wash_mode_start_process(void){

	return 0;
}

int b_inital_acid_tank_drainage_start_process(void){

	return 0;
}

int bp111_inital_alkali_tank_drainage_start_process(void){
	if( flag.p111 == 0 ){
		flag.p111 = 1;
		return 1;
	}
	return 0;
}
int bp112_inital_acid_tank_drainage_start_process(void){
	if( flag.p112 == 0 ){
		flag.p112 = 1;
		return 1;
	}
	return 0;
}
int bp13_initial_electrolysis_start_process(void){

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
int bp1_initial_working_mode_start_process(void){
	return 0;
}

int b_p1_start_process(void){
	if ( flag.pump_1 == 0){
		flag.pump_1 = 1;
		return 1;
	}
	return 0;
}
int b_p2_start_process(void){
	if( flag.pump_2 == 0 ){
		PUMP_2 = PUMP_ON;
		flag.pump_2 = 1;
	}
	return 0;
}
int b_sp_start(void){
	if( flag.salt_pump == 0 ){
		PUMP_2 = PUMP_ON;
		flag.salt_pump = 1;
	}
	return 0;
}
int b_sv1_start(void){
	if ( flag.sv1 == 0){
		flag.sv1 = 1;
		return 1;
	}
	return 0;
}
int b_sv2_start(void){
	if( flag.sv2 == 0){
		flag.sv2 = 1;
		return 1;
	}
	return 0;
}
int b_sv5_start_process(void){
	if ( flag.sv5 == 0){
		flag.sv5 = 1;
		return 1;
	}
	return 0;
}
int b_sv6_start_process(void){
	if( flag.sv6 == 0 ){
		SV6 = VALVE_ON;
		flag.sv6 = 1;
	}
	return SV6;
}
