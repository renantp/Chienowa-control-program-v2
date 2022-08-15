/*
 * t_module.c
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#include "t_module.h"
#include "../pin_define.h"
#include "../global_variable.h"

union FLAG_U flag;

int tp2_wash_mode_stop_process(void){
	return 0;
}

int tp111_initial_alkali_tank_drainage_stop_process(void){
	if( flag.p111 == 1 ){
		flag.p111 = 0;
		return 1;
	}
	return 0;
}
int tp112_inital_acid_tank_drainage_stop_process(void){
	if( flag.p112 == 1 ){
		flag.p112 = 0;
		return 1;
	}
	return 0;
}
int tp13_initial_electrolysis_stop_process(void){
	return 0;
}
int tp141_2nd_alkali_tank_drain_stop_process(void){
	return 0;
}
int tp142_2nd_acid_tank_drain_stop_process(void){
	return 0;
}
int tp15_electrolysis_stop_process(void){
	return 0;
}
int tp11_initial_draining_stop_process(void){
	return 0;
}
int tp12_inital_water_supply_stop_process(void){
	return 0;
}
int tp14_initial_2nd_draining_stop_process(void){
	return 0;
}
int tp1_stop_process_initial_working_mode_stop_process(void){
	return 0;
}

int t_sv1_stop(void){
	if ( flag.sv1 == 1){
		flag.sv1 = 0;
		return 1;
	}
	return 0;
}
int t_sv2_stop(void){
	if ( flag.sv2 == 1){
		flag.sv2 = 0;
		return 1;
	}
	return 0;
}
int t_sv5_stop_process(void){
	if ( flag.sv5 == 1){
		flag.sv5 = 0;
		return 1;
	}
	return 0;
}
int t_sv6_stop_process(void){
	if( flag.sv6 == 1){
		SV6 = VALVE_OFF;
		flag.sv6 = 0;
	}
	return 0;
}
int t_p1_stop_process(void){
	if ( flag.pump_1 == 1){
		flag.pump_1 = 0;
		return 1;
	}
	return 0;
}

int t_p2_stop_process(void){
	if( flag.pump_2 == 1){
		PUMP_2 = PUMP_OFF;
		flag.pump_2 = 0;
	}
	return 0;
}
int t_sp_stop(void){
	if( flag.salt_pump == 1){
		flag.salt_pump = 0;
		return 1;
	}
	return 0;
}
