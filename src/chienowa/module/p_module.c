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

int g_ALTank_drain_flag;
int p111_startup_drain_alkali_tank_water(void) {
	s1_alkali_tank_data_set();
	if (g_ALD > 0) {
		bp111_inital_alkali_tank_drainage_start_process(); //Initial Alkali Tank Drainage start processing
		b_sv6_start_process();	//Turn SV6 (Alkali drain) ON
		wait(500);
		b_p2_start_process();		//Turn P2 (Alkali pump) ON
		do {
			s1_alkali_tank_data_set();
			runtime();
		} while (g_ALD != 0);
		wait(g_timerSetting.t1_ms);
		t_sv6_stop_process();	//Turn SV6 (Alkali drain) OFF
		t_p2_stop_process();	//Turn P2 (Alkali pump) OFF
		tp111_initial_alkali_tank_drainage_stop_process();//Initial Alkali Tank Drainage Stop process
		return 1;
	}
	return 0;
}

int g_ACTank_drain_flag;
int p112_startup_drain_acid_tank_water(void) {
	ENTRY: if (g_ACD == 0) {
		wait(g_timerSetting.t1_ms);
		t_sv5_stop_process();
		t_p1_stop_process();
		tp112_inital_acid_tank_drainage_stop_process();
		return 1;
	} else if (g_ACTank_drain_flag == 0) {
		b_inital_acid_tank_drainage_start_process();
		b_sv5_start_process();
		wait(500);
		bp112_p1_start_process();
		goto ENTRY;
	} else {
		goto ENTRY;
	}
}

int neutralized_timer_on(void) {
	return 0;
}
int faucet_not_using_term_timer(void) {
	return 0;
}
int p131_initial_electrolysis_start(void) {
	b_sv1_start();
	b_sp_start();
	wait(g_timerSetting.t16_s * 1000);
	bp13_initial_electrolysis_start_process();
	neutralized_timer_on();
	faucet_not_using_term_timer();
	return 0;
}

int neutralized_timer_off(void) {
	return 0;
}
int p132_initial_electrolysis_stop(void) {
	tp13_initial_electrolysis_stop_process();
	t_sp_stop();
	wait(g_timerSetting.t5_s * 1000);
	t_sv1_stop();
	neutralized_timer_off();
	return 0;
}

inline int alkali_drain_timer_on(void) {
	return 0;
}
int p141_2nd_drain_alkali_tank_drain(void) {
	bp141_2nd_alkali_tank_drain_startup_process();
	if (g_ALD > 0) {
		b_sv6_start_process();
		wait(500);
		b_p2_start_process();
		alkali_drain_timer_on();

		do {
			s1_alkali_tank_data_set();
		} while (g_ALD > 0);

		wait(g_timerSetting.t1_ms);
		t_p2_stop_process();
		t_sv6_stop_process();
		tp141_2nd_alkali_tank_drain_stop_process();
	}
	return 0;
}

inline int acid_drain_timer_on(void) {
	return 0;
}
int p142_2nd_drain_acid_tank_drain_process(void) {
	bp142_2nd_acid_tank_drain_startup_process();
	if (g_ACD > 0) {
		b_sv5_start_process();
		wait(500);
		b_p1_start_process();
		acid_drain_timer_on();

		while (g_ACD != 0) {
			s2_acid_tank_data_set();
		}

		wait(g_timerSetting.t1_ms);
		t_p1_stop_process();
		t_sv5_stop_process();
		tp142_2nd_acid_tank_drain_stop_process();
	}
	return 0;
}

int neutralized_timer_on(void);
int p151_2nd_electrolysis_start_process(void) {
	b_sv1_start();
	b_sp_start();
	wait(g_timerSetting.t17_s * 1000);
	bp15_electrolysis_start_process();
	neutralized_timer_on();
	return 0;
}

int neutralized_timer_off(void);
int p152_2nd_initial_electrolysis_stop_process(void) {
	t_sp_stop();
	wait(g_timerSetting.t5_s * 1000);
	t_sv1_stop();
	neutralized_timer_off();
	return 0;
}

int p01_system_main_sub_system(void) {
	return 0;
}

int p11_startup_draining_water(void) {
	bp11_initial_drainage_start_process();
	p111_startup_drain_alkali_tank_water();
	p112_startup_drain_acid_tank_water();
	tp11_initial_draining_stop_process();
	return 0;
}

int p313_flow_rate_adjustment(void) {
	return 0;
}
int p12_startup_water_supply(void) {
	bp12_initial_water_supply_start_process();
	wait(500);
	b_sv2_start();
	wait(30 * 1000);
	t_sv2_stop();
	wait(g_timerSetting.t2_s * 1000);
	p313_flow_rate_adjustment();
	tp12_inital_water_supply_stop_process();
	return 0;
}

int p131_electrolysis_start(void) {
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

int p14_initial_2nd_draining_water(void) {
	bp14_initial_2nd_draining_start_process();
	p141_2nd_drain_alkali_tank_drain();
	p142_2nd_drain_acid_tank_drain_process();
	tp14_initial_2nd_draining_stop_process();
	return 0;
}
int p15_2nd_electrolysis_water_generation_process(void) {
	do {
		s1_alkali_tank_data_set();
		s2_acid_tank_data_set();
	} while (g_ALD != 3 || g_ACD != 3);
	p151_2nd_electrolysis_start_process();
	do {
		s1_alkali_tank_data_set();
		s2_acid_tank_data_set();
	} while (g_ALD != 3 || g_ACD != 3);
	p152_2nd_initial_electrolysis_stop_process();
	return 0;
}

int p151_electrolysis_start_process(void) {
	b_sv1_start();
	b_sp_start();
	wait(g_timerSetting.t22_s * 1000);
	bp15_electrolysis_start_process();
	neutralized_timer_on();
	return 0;
}
int p152_initial_electrolysis_stop_process(void) {
	tp15_electrolysis_stop_process();
	t_sp_stop();
	wait(g_timerSetting.t5_s * 1000);
	t_sv1_stop();
	neutralized_timer_off();
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
	p15_2nd_electrolysis_water_generation_process();
	tp1_stop_process_initial_working_mode_stop_process();
	return 0;
}
int p210_wash_mode_2nd_process(void){
	return 0;
}
int p211_alkali_mode(void){
	return 0;
}
int p212_acid_mode(void){
	return 0;
}
int p213_water_mode(void){
	return 0;
}
int p214_hand_wash_mode(void){
	return 0;
}

int p21_alkali_mode(void){
	bp211_alkali_mode_start_process();
	do{
	//TODO: Check mode(Normal/Individual)
		check_hand_sensor();
	}while(g.flag.hand_sensor == 0);

	return 0;
}
int p22_acid_mode(void){
	return 0;
}
int p23_water_mode(void){
	return 0;
}
int p24_hand_wash_mode(void){
	return 0;
}
int p2_select_wash_mode(void){
	bp2_wash_mode_start_process();
	g.flag.cvcc_run = 1;
	do{
		g.flag.electrolysis = 1;
		g.flag.c22_start = 1;
		switch (g.mode) {
			case HAND_WASHING_MODE:
				p24_hand_wash_mode();
				break;
			case WATER_MODE:
				p23_water_mode();
				break;
			case ACID_MODE:
				p22_acid_mode();
				break;
			case ALKALI_MODE:
				p21_alkali_mode();
				break;
			default:
				//Crash
				break;
		}
		g.flag.c22_start = 0;
	}while(SYSTEM_MODE != 2);
	g.flag.cvcc_run = 0;
	tp2_wash_mode_stop_process();
	return 0;
}
//Timer interrupt function
void timer_interrupt(void) {
	g_systemTick++;
}
//struct P_1_5_1
//{
//  uint16_t state;
//  uint32_t tick;
//} g_p1_5_1;
//struct P_1_5_2
//{
//  uint16_t state;
//  uint32_t tick;
//} g_p1_5_2;
//struct P_1_5
//{
//  uint16_t state;
//  uint32_t tick;
//} g_p1_5;
//int p151_electrolysis_start_process(void)
//{
//  uint16_t *v = &g_p1_5_1.state;
//  uint32_t *tick = &g_p1_5_1.tick;
//  switch (*v)
//  {
//  case 0:
//    SV1 = VALVE_ON;
//    SP = PUMP_ON;
//    *tick = g_systemTick;
//    *v = 1;
//    break;
//  case 1:
//    if (ns_delay_ms(tick, 2 * 1000))
//    {
//      *v = 2;
//    }
//    break;
//  case 2:
//    //TODO: Call BP-1-5, will return 1 when done
//    break;
//  case 3:
//    //TODO: Neutralized timer ON
//    *v = 0;
//    return 1;
//  }
//  return 0;
//}
//
//int p152_electrolysis_stop_process(void)
//{
//  uint16_t *v = &g_p1_5_2.state;
//  uint32_t *tick = &g_p1_5_2.tick;
//  switch (*v)
//  {
//  case 0:
//    //TODO: TP-1-5, turn off CVCC
//    SP = PUMP_OFF;
//    *v = 1;
//    break;
//  case 1:
//    if (ns_delay_ms(tick, 5 * 1000))
//    {
//      *v = 2;
//    }
//    break;
//  case 2:
//    SV1 = VALVE_OFF;
//    //TODO: Neutralized timer OFF
//    *v = 0;
//    return 1;
//  }
//  return 0;
//}

//int p15_2nd_electrolysis_water_generation_process(void)
//{
//  uint16_t *v = &g_p1_5.state;
//  uint32_t *tick = &g_p1_5.tick;
//  switch (*v)
//  {
//  case 0:
//    //TODO: Check ALD != 3 or ACD != 3 go to case 1
//    if (g_ALD != 3 || g_ACD != 3)
//      *v = 1;
//    break;
//  case 1:
//    if (p151_electrolysis_start_process())
//    {
//      *v = 2;
//    }
//    break;
//  case 2:
//    //TODO: Check ALD == 3 and ACD == 3 go to case 3
//    break;
//  case 3:
//    if (p152_electrolysis_stop_process())
//    {
//      *v = 0;
//    }
//    break;
//  default:
//    break;
//  }
//  return 0;
//}
