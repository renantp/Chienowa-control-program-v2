/*
 * p_module.c
 *
 *  Created on: Jul 27, 2022
 *      Author: Renan
 *
 */

#include "p_module.h"
#include "s_module.h"
#include "b_module.h"
#include "c_module.h"
#include "t_module.h"
#include "../runtime.h"
#include "../pin_define.h"
#include "../delay.h"
#include "../main.h"
#include "../hand_sensor.h"
//  Need to implement
int p3_individual_test(void) {
	return 0;
}
/* end things need to implement */


/**
 * Don't need this function
 * @return System mode
 */
int p01_system_main_sub_system(void) {
	return SYSTEM_MODE;
}

int p0_system_main_prpocess(void){
	bp0_system_main_start();
	p1_initial_working_mode_start_process();
	switch (SYSTEM_MODE) {
		case 0:
			p2_water_discharge_mode();
			break;
		case 1:
			p3_individual_test();
			break;
		default:
			//Not going here
			break;
	}
	return 0;
}
int p1_initial_working_mode_start_process(void) {
	bp1_initial_working_mode_start_process();
	p11_startup_draining_water();
	p12_startup_water_supply();
	c3_acid_tank_level_check();
	c5_electrolysis_CVCC_status();
	p13_startup_electrolysis_operation();
	p14_initial_2nd_draining_water();
//	p15_2nd_electrolysis_water_generation_process();
	p11_startup_draining_water(); //replace p15 by this p11
	tp1_stop_process_initial_working_mode_stop_process();
	return 0;
}

int p11_startup_draining_water(void) {
	bp11_initial_drainage_start_process();
	p111_startup_drain_tank();
	tp11_initial_draining_stop_process();
	return 0;
}

int p111_startup_drain_tank(void){
	bp111_inital_alkali_tank_drainage_start_process();
	if(s1_alkali_tank_data_set() && g_ALD > 0){
		b_sv6_start_process();
		wait(500);
		b_p2_start_process();
		g.flag.alkali_drainning = 1;
	}

	if(s2_acid_tank_data_set()){
		b_sv5_start_process();
		wait(500);
		b_p1_start_process();
		g.flag.acid_drainning = 1;
	}
	while(g_ALD > 0 || g_ACD > 0){
		if(s1_alkali_tank_data_set() && g_ALD == 0){
			if(g.flag.alkali_drainning == 1){
				g.flag.alkali_drainning = 0;
				p112_alkali_drain_stop();
			}
		}

		if(s2_acid_tank_data_set() && g_ACD == 0){
			if(g.flag.acid_drainning == 1){
				g.flag.acid_drainning = 0;
				p113_acid_drain_stop();
			}
		}
	}
	p114_alkali_drain_final_stop();
	p115_acid_drain_final_stop();
	tp111_initial_alkali_tank_drainage_stop_process();
	return 0;
}
int p112_alkali_drain_stop(void){
	t_p2_stop_process();
	t_sv6_stop_process();
	return 0;
}
int p113_acid_drain_stop(void){
	t_p1_stop_process();
	t_sv5_stop_process();
	return 0;
}
int p114_alkali_drain_final_stop(void){
	b_sv6_start_process();
	wait(500);
	b_p2_start_process();
	wait(g_T_S.t1_ms);
	t_p2_stop_process();
	t_sv6_stop_process();
	return 0;
}
int p115_acid_drain_final_stop(void){
	b_sv5_start_process();
	wait(500);
	b_p1_start_process();
	wait(g_T_S.t1_ms);
	t_p1_stop_process();
	t_sv5_stop_process();
	return 0;
}
int p12_startup_water_supply(void) {
	bp12_initial_water_supply_start_process();
	wait(500);
	b_sv2_start();
	wait(30 * 1000);
	t_sv2_stop();
	wait(g_T_S.t2_s * 1000);
	//TODO: P313

	tp12_inital_water_supply_stop_process();
	return 0;
}
int p13_startup_electrolysis_operation(void) {
	p131_electrolysis_start();
	do {
		s1_alkali_tank_data_set();
		s2_acid_tank_data_set();
		runtime();
	} while (g_ALD != 3 || g_ACD != 3);
	p132_initial_electrolysis_stop();
	return 0;
}

int neutralized_timer_on(void) {
	return start_timer(&g.timer.c1_on, C_1_ON_T3);
}
int neutralized_timer_off(void) {
	return stop_timer(C_1_ON_T3);
}

int p131_electrolysis_start(void) {
	b_sv1_start();
	b_sp_start();
	wait(g_T_S.t16_s * 1000);
	bp13_initial_electrolysis_start_process();
	neutralized_timer_on();
	start_timer(&g.timer.faucet_off, FAUCET_OFF_T);
	return 0;
}

int p132_initial_electrolysis_stop(void) {
	tp13_initial_electrolysis_stop_process();
	t_sp_stop();
	wait(g_T_S.t5_s * 1000);
	t_sv1_stop();
	neutralized_timer_off();
	return 0;
}

int p14_initial_2nd_draining_water(void) {
	bp14_initial_2nd_draining_start_process();
	p111_startup_drain_tank();
	tp14_initial_2nd_draining_stop_process();
	return 0;
}
int p15_2nd_electrolysis_water_generation_process(void) {
	do {
		s1_alkali_tank_data_set();
		s2_acid_tank_data_set();
		runtime();
	} while (g_ALD != 3 || g_ACD != 3);
	p151_2nd_electrolysis_start_process();
	do {
		s1_alkali_tank_data_set();
		s2_acid_tank_data_set();
		runtime();
	} while (g_ALD != 3 || g_ACD != 3);
	p152_2nd_initial_electrolysis_stop_process();
	return 0;
}
int p151_2nd_electrolysis_start_process(void) {
	b_sv1_start();
	b_sp_start();
	wait(g_T_S.t17_s * 1000);
	bp15_electrolysis_start_process();
	neutralized_timer_on();
	return 0;
}
int p152_2nd_initial_electrolysis_stop_process(void) {
	t_sp_stop();
	wait(g_T_S.t5_s * 1000);
	t_sv1_stop();
	neutralized_timer_off();
	return 0;
}
int p2_water_discharge_mode(void){
	bp2_water_discharge_start_process();
	do{
		c1_on_off(C1_ON);				//電解業務開始処理
		switch ((enum WASH_MODE_E) WASH_MODE) {
			case HAND_WASHING_MODE:
				p24_hand_wash_mode();
				break;
			case WATER_MODE:
				p23_water_discharge_mode();
				break;
			case ACID_MODE:
				p22_acid_water_discharge_mode();
				break;
			case ALKALI_MODE:
				p21_alkali_water_discharge_mode();
				break;
			default:
				//Crash
				break;
		}
	}while(SYSTEM_MODE != 2);
	c1_on_off(C1_OFF);
	tp2_wash_mode_stop_process();
	return 0;
}
int p21_alkali_water_discharge_mode(void){
	bp21_alkali_discharge_start();
	// Large loop
	do {
		c1_on_off(C1_ON);
		if(check_hand_sensor() || SYSTEM_MODE == NORMAL){
			b_sv4_start();
			b_p2_start_process();
			//TODO: Blink led on Hand sensor

			g.timer.water_discharge = 0;
			start_timer(&g.timer.water_discharge, ALKALI_DISCHARGE_T);

			// Small loop
			do {
				if(check_hand_sensor() || calculate_timer_eslapse(ALKALI_DISCHARGE_T) >= g_T_S.t35_s * 1000){
					SYSTEM_MODE = NORMAL;
				}else{
					c1_on_off(C1_OFF);
				}
			}while(SYSTEM_MODE == WASHING);
			t_p2_stop_process();
			t_sv4_stop();
			stop_timer(ALKALI_DISCHARGE_T);
			//TODO: Turn off blinking LED on hand sensor

		}
		runtime();
	}while(SYSTEM_MODE != INDIVIDUAL);
	tp21_alkali_discharge_stop();
	return 0;
}

int p22_acid_water_discharge_mode(void){
	bp22_acid_discharge_start();
	//Large loop
	do{
		c1_on_off(C1_ON);
		if(check_hand_sensor() && SYSTEM_MODE == NORMAL){
			SYSTEM_MODE = WASHING;
			b_sv3_start();
			b_p1_start_process();
			//TODO: Blink LED on hand sensor

			g.timer.water_discharge = g_systemTick;
			start_timer(&g.timer.water_discharge, ACID_DISCHARGE_T);
			//Small loop
			do{
				if (check_hand_sensor() || calculate_timer_eslapse(ACID_DISCHARGE_T) >= g_T_S.t34_s * 1000 ){
					SYSTEM_MODE = NORMAL;
				}else{
					c1_on_off(C1_ON);
				}
				runtime();
			}while(SYSTEM_MODE == WASHING);
			t_p1_stop_process();
			t_sv3_stop();
			stop_timer(ACID_DISCHARGE_T);
			//TODO: Turn off blinking LED on hand sensor

		}
		runtime();
	}while(SYSTEM_MODE != INDIVIDUAL);
	tp22_acid_discharge_stop();
	return 0;
}

int p23_water_discharge_mode(void){
	bp23_water_discharge_start();
	// Large loop
	do{
		c1_on_off(C1_ON);
		if(check_hand_sensor() || SYSTEM_MODE == NORMAL){
			b_sv2_start();
			//TODO: Blink LED on hand sensor

			g.timer.water_discharge = g_systemTick;
			start_timer(&g.timer.water_discharge, WATER_DISCHARGE_T);
			// Small loop
			do {
				if (check_hand_sensor() || calculate_timer_eslapse(WATER_DISCHARGE_T) >= g_T_S.t34_s * 1000 ){
					SYSTEM_MODE = NORMAL;
				}else{
					c1_on_off(C1_ON);
				}
				runtime();
			}while(SYSTEM_MODE == WASHING);
			t_sv2_stop();
			stop_timer(WATER_DISCHARGE_T);
			//TODO: Turn off blinking LED on hand sensor

		}
		runtime();
	}while(SYSTEM_MODE != INDIVIDUAL);

	tp23_water_discharge_stop();
	return 0;
}

int p24_hand_wash_mode(void){
	bp24_hand_wash_start();
	do{
		c1_on_off(C1_ON);
		if (check_hand_sensor() || SYSTEM_MODE == NORMAL){
			SYSTEM_MODE = WASHING;
			p2411();
			p2412();
			p2421();
			p2413();
			p2422();
			p2431();
			p2423();
			p2432();
			p2433();
		}

	}while(SYSTEM_MODE == NORMAL);

	tp24_hand_wash_stop();
	return 0;
}

void p2411(void){
	bp241();
	b_sv4_start();
	b_p2_start_process();
	start_timer(&g.timer.water_discharge, ALKALI_DISCHARGE_T);
}

void p2412(void){
	//TODO: Turn ON hand sensor LED (Blue)
	while (g_T_S.t29_s * 1000 - calculate_timer_eslapse(ALKALI_DISCHARGE_T) > 2 * 1000 ){
		c1_on_off(C1_ON);
		runtime();
	}
	//TODO: Blink hand sensor LED (Blue)

	while (calculate_timer_eslapse(ALKALI_DISCHARGE_T) <= g_T_S.t29_s * 1000 &&
			g_T_S.t29_s * 1000 - calculate_timer_eslapse(ALKALI_DISCHARGE_T) <= g_T_S.t32_ms){
		runtime();
		c1_on_off(C1_ON);
	}
}
void p2413(void){
	while (calculate_timer_eslapse(ALKALI_DISCHARGE_T) <= g_T_S.t29_s * 1000){
		c1_on_off(C1_ON);
		runtime();
	}
	stop_timer(ALKALI_DISCHARGE_T);
	//TODO: Turn off hand sensor LED

	t_p2_stop_process();
	t_sv4_stop();
	//TODO: アルカリ未吐水タイマ＝0

	tp241();
}
void p2421(void){
	bp242();
	b_sv3_start();
	b_p1_start_process();
	start_timer(&g.timer.water_discharge, ACID_DISCHARGE_T);
}
void p2422(void){
	//TODO: Turn ON hand sensor LED (Red)

	//酸吐水減算タイマが２秒か?
	while(g_T_S.t30_s * 1000 - calculate_timer_eslapse(ACID_DISCHARGE_T) > 2 * 1000 ){
		c1_on_off(C1_ON);
		runtime();
	}
	//TODO: Blink hand sensor LED (Red)

	while (calculate_timer_eslapse(ACID_DISCHARGE_T) <= g_T_S.t30_s * 1000 &&
			g_T_S.t30_s * 1000 - calculate_timer_eslapse(ACID_DISCHARGE_T) <= g_T_S.t32_ms){
		runtime();
		c1_on_off(C1_ON);
	}
}

void p2423(void){
	while (calculate_timer_eslapse(ACID_DISCHARGE_T) <= g_T_S.t30_s * 1000){
		c1_on_off(C1_ON);
		runtime();
	}
	//TODO: Turn off hand sensor LED

	stop_timer(ACID_DISCHARGE_T);
	t_p1_stop_process();
	t_sv3_stop();
	//TODO: 酸未吐水タイマ＝0

	tp242();
}

void p2431(void){
	bp243();
	b_sv2_start();
	start_timer(&g.timer.water_discharge, WATER_DISCHARGE_T);
}
void p2432(void){
	//TODO: Turn ON hand sensor (WHITE)

}
void p2433(void){
	while (calculate_timer_eslapse(WATER_DISCHARGE_T) <= g_T_S.t31_s * 1000){
		c1_on_off(C1_ON);
		runtime();
	}
	//TODO: Turn off hand sensor LED

	stop_timer(WATER_DISCHARGE_T);
	t_sv2_stop();
	//TODO: 水未吐水タイマ＝0

	tp243();
}

int p3_individual_mode(void) {

	p8();
	bp3_individual_start();
	while (SYSTEM_MODE == INDIVIDUAL) {
		if (g.flag.individual) {
		//個別処理実施 (Individual processing)
//			p31_sv1_individual_process();
//			p32_sv2_individual_process();
//			p33_sv3_individual_process();
//			p34_sv4_individual_process();
//			p35_sv5_individual_process();
//			p36_sv6_individual_process();
//			p37_sv7_individual_process();
//			p38_p1_individual_process();
//			p39_p2_individual_process();
//			p310_sp_individual_process();
//			p311_electrolysis_equipment_process();
		}
	}
	p8_stop_all_processing();
	tp3_individual_stop();
	return 0;
}
int p31_sv1_individual_process(void){
//	const uint8_t state = g.flag.io.valve.sv1 == 1U ? VALVE_ON : VALVE_OFF;
//	if(g.flag.io.valve.sv1 != SV1_PIN){
//		SV1_PIN = state;
//		return 1;
//	}
//	return 0;
	if(g.flag.io.valve.sv1){
		b_sv1_start();
	}else{
		t_sv2_stop();
	}
	return g.flag.io.valve.sv1;
}
int p32_sv2_individual_process(void){
	const uint8_t state = g.flag.io.valve.sv2 == 1U ? VALVE_ON : VALVE_OFF;
	if(g.flag.io.valve.sv2 != SV2_PIN){
		SV2_PIN = state;
		return 1;
	}
	return 0;
}
int p33_sv3_individual_process(void){
	const uint8_t state = g.flag.io.valve.sv3 == 1U ? VALVE_ON : VALVE_OFF;
	if(g.flag.io.valve.sv3 != SV3_PIN){
		SV3_PIN = state;
		return 1;
	}
	return 0;
}
int p34_sv4_individual_process(void){
	const uint8_t state = g.flag.io.valve.sv4 == 1U ? VALVE_ON : VALVE_OFF;
	if(g.flag.io.valve.sv4 != SV4_PIN){
		SV4_PIN = state;
		return 1;
	}
	return 0;
}
int p35_sv5_individual_process(void){
	const uint8_t state = g.flag.io.valve.sv5 == 1U ? VALVE_ON : VALVE_OFF;
	if(g.flag.io.valve.sv5 != SV5_PIN){
		SV5_PIN = state;
		return 1;
	}
	return 0;
}
int p36_sv6_individual_process(void){
	const uint8_t state = g.flag.io.valve.sv6 == 1U ? VALVE_ON : VALVE_OFF;
	if(g.flag.io.valve.sv6 != SV6_PIN){
		SV6_PIN = state;
		return 1;
	}
	return 0;
}
int p37_sv7_individual_process(void){
	const uint8_t state = g.flag.io.valve.sv7 == 1U ? VALVE_ON : VALVE_OFF;
	if(g.flag.io.valve.sv7 != SV7_PIN){
		SV7_PIN = state;
		return 1;
	}
	return 0;
}
int p38_p1_individual_process(void){
	const uint8_t state = g.flag.io.pump_1 == 1U ? PUMP_ON : PUMP_OFF;
	if(state != PUMP_1_PIN){
		PUMP_1_PIN = state;
		return 1;
	}
	return 0;
}
int p39_p2_individual_process(void){
	const uint8_t state = g.flag.io.pump_2 == 1U ? PUMP_ON : PUMP_OFF;
	if(state != PUMP_2_PIN){
		PUMP_2_PIN = state;
		return 1;
	}
	return 0;
}
int p310_sp_individual_process(void){
	const uint8_t state = g.flag.io.salt_pump == 1U ? PUMP_ON : PUMP_OFF;
	if(state != SP_PIN){
		SP_PIN = state;
		return 1;
	}
	return 0;
}
int p311_electrolysis_equipment_process(void){
	//TODO: ???
	return 0;
}
int p8_stop_all_processing(void){
	//TODO: C11 Electrolytic service emergency stop processing

	t_p1_stop_process();
	t_p2_stop_process();
	t_sp_stop();
	t_sv1_stop();
	t_sv2_stop();
	t_sv3_stop();
	t_sv4_stop();
	t_sv5_stop_process();
	t_sv6_stop_process();
	t_sv7_stop();
	return 0;
}
