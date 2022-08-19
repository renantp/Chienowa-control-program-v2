/*
 * t_module.c
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#include "t_module.h"
#include "../pin_define.h"
#include "../global_variable.h"
#include "../delay.h"
#include "../hand_sensor.h"

int tp0(void){
	if(g.flag.module.bp0){
		g.flag.module.bp0 = 0;
		g.timer.module.work.p0[0] = timer_stop_s(g.timer.module.on.p0[0]);
		g.timer.module.work.p0[1] = timer_stop_ms(g.timer.module.on.p0[1]);
	}
	return 0;
}
int tp1_stop_process_initial_working_mode_stop_process(void) {
	if(g.flag.module.bp1){
		//g.timer.module.work.p1[1] is last working time
		g.timer.module.work.p1[0] = timer_stop_s(g.timer.module.on.p1[0]);
		g.timer.module.work.p1[1] = timer_stop_ms(g.timer.module.on.p1[1]);
		g.flag.module.bp1 = 0;
	}
	return 0;
}
int tp11_initial_draining_stop_process(void) {
	if(g.flag.module.bp11){
		//P_1_1_ON_T1 STOP
		g.timer.module.work.p11[0] = timer_stop_s(g.timer.module.on.p11[0]);
		//P_1_1_ON_T2 STOP
		g.timer.module.work.p11[1] = timer_stop_ms(g.timer.module.on.p11[1]);
		//P_1_1_F = 0
		g.flag.module.bp11 = 0;
	}
	return 0;
}
int tp111_initial_alkali_tank_drainage_stop_process(void) {
	if (g.flag.module.bp111) {
		//P_1_1_1_ON_T1 STOP
		g.timer.module.work.p111[0] = timer_stop_s(g.timer.module.on.p111[0]);
		//P_1_1_1_ON_T2 STOP
		g.timer.module.work.p111[1] = timer_stop_ms(g.timer.module.on.p111[1]);
		//P_1_1_1_F = 0
		g.flag.module.bp111 = 0;
	}
	return 0;
}
int tp112_inital_acid_tank_drainage_stop_process(void) {
	if (g.flag.module.bp112) {
		//P_1_1_2_ON_T1 STOP
		g.timer.module.work.p112[0] = timer_stop_s(g.timer.module.on.p112[0]);
		//P_1_1_2_ON_T2 STOP
		g.timer.module.work.p112[1] = timer_stop_ms(g.timer.module.on.p112[1]);
		//P_1_1_2_F
		g.flag.module.bp112 = 0;
	}
	return 0;
}
int tp12_inital_water_supply_stop_process(void) {
	if(g.flag.module.bp12){
		//P_1_2_ON_T1 STOP
		g.timer.module.work.p12[0] = timer_stop_s(g.timer.module.on.p12[0]);
		//P_1_2_ON_T2 STOP
		g.timer.module.work.p12[1] = timer_stop_ms(g.timer.module.on.p12[1]);
		//P_1_2_F = 0
		g.flag.module.bp12 = 0;
	}
	return 0;
}
int tp13_initial_electrolysis_stop_process(void) {
	if(g.flag.module.bp13){
		//P_1_3_ON_T1 STOP
		g.timer.module.work.p13[0] = timer_stop_s(g.timer.module.on.p13[0]);
		//P_1_3_ON_T2 STOP
		g.timer.module.work.p13[1] = timer_stop_ms(g.timer.module.on.p13[1]);
		CVCC_CONTROL_PIN = 0U;
		//C_1_OFF _T2 START
		g.timer.module.off.c1[1] = timer_start_s();
		//P_1_3_F = 0
		g.flag.module.bp13 = 0;
	}
	return 0;
}

int tp14_initial_2nd_draining_stop_process(void) {
	if(g.flag.module.bp14){
		//P_1_4_ON_T1 STOP
		g.timer.module.work.p14[0] = timer_stop_s(g.timer.module.on.p14[0]);
		//P_1_4_ON_T2 STOP
		g.timer.module.work.p14[1] = timer_stop_ms(g.timer.module.on.p14[1]);
		//P_1_4_F
		g.flag.module.bp14 = 0;
	}
	return 0;
}
int tp141_2nd_alkali_tank_drain_stop_process(void) {
	if(g.flag.module.bp141){
		//P_1_4_1_ON_T1 STOP
		g.timer.module.work.p141[0] = timer_stop_s(g.timer.module.on.p141[0]);
		//P_1_4_1_ON_T2 STOP
		g.timer.module.work.p141[1] = timer_stop_ms(g.timer.module.on.p141[1]);
		//P_1_4_1_F
		g.flag.module.bp141 = 0;
	}
	return 0;
}
int tp142_2nd_acid_tank_drain_stop_process(void) {
	if(g.flag.module.bp142){
		//P_1_4_2_ON_T1 STOP
		g.timer.module.work.p142[0] = timer_stop_s(g.timer.module.on.p142[0]);
		//P_1_4_2_ON_T2 STOP
		g.timer.module.work.p142[1] = timer_stop_ms(g.timer.module.on.p142[1]);
		//P_1_4_2_F
		g.flag.module.bp142 = 0;
	}
	return 0;
}

int tp15_electrolysis_stop_process(void) {
	if(P_1_5_F){
		//P_1_5_ON_T1 STOP
		P_1_5_ON_T1 = timer_stop_s(g.timer.module.on.p15[0]);
		//P_1_5_ON_T2 STOP
		P_1_5_ON_T2 = timer_stop_ms(g.timer.module.on.p15[1]);
		CVCC_CONTROL_PIN = 0U;
		//C_1_OFF _T2 START
		C_1_OFF_T2 = timer_start_s();
		//P_1_5_F
		P_1_5_F = 0;
	}
	return 0;
}
int tp2_wash_mode_stop_process(void) {
	if(g.flag.module.bp2){
		//P_2_ON_T1 STOP
		g.timer.module.work.p2[0] = timer_stop_s(g.timer.module.on.p2[0]);
		//P_2_ON_T2 STOP
		g.timer.module.work.p2[1] = timer_stop_ms(g.timer.module.on.p2[1]);
		//P_2_F
		g.flag.module.bp2 = 0;
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp21_alkali_discharge_stop(void){
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp22_acid_discharge_stop(void){
	return 0;
}
int tp23_water_discharge_stop(void){
	if(g.flag.module.bp23){
		//P_2_3_ON_T1 STOP
		g.timer.module.work.p23[0] = timer_stop_s(g.timer.module.on.p23[0]);
		//P_2_3_ON_T2 STOP
		g.timer.module.work.p23[1] = timer_stop_ms(g.timer.module.on.p23[1]);
		//P_2_3_F
		g.flag.module.bp23 = 0;
	}
	return 0;
}
int tp24_hand_wash_stop(void){
	if(g.flag.module.bp24){
		//P_2_4_ON_T1 STOP
		g.timer.module.work.p24[0] = timer_stop_s(g.timer.module.on.p24[0]);
		//P_2_4_ON_T2 STOP
		g.timer.module.work.p24[1] = timer_stop_ms(g.timer.module.on.p24[1]);
		//P_2_4_F
		g.flag.module.bp24 = 0;
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp241(void){
	if(g.flag.module.bp241){
		//P_2_4_1_ON_T1 STOP
		g.timer.module.work.p241[0] = timer_stop_s(g.timer.module.on.p241[0]);
		//P_2_4_1_ON_T2 STOP
		g.timer.module.work.p241[1] = timer_stop_ms(g.timer.module.on.p241[1]);
		//P_2_4_1_F
		g.flag.module.bp241 = 0;
		//P_2_4_1_OFF_T1 RESTART
		g.timer.module.off.p241[0] = timer_restart_s(g.timer.module.work.p241[0]);
		//P_2_4_1_OFF_T2 START
		g.timer.module.off.p241[1] = timer_start_ms();
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp242(void){
	if(g.flag.module.bp242){
		//P_2_4_2_ON_T1 STOP
		g.timer.module.work.p242[0] = timer_stop_s(g.timer.module.on.p242[0]);
		//P_2_4_2_ON_T2 STOP
		g.timer.module.work.p242[1] = timer_stop_ms(g.timer.module.on.p242[1]);
		//P_2_4_2_F
		g.flag.module.bp242 = 0;
		//P_2_4_2_OFF_T1 RESTART
		g.timer.module.off.p242[0] = timer_restart_s(g.timer.module.work.p242[0]);
		//P_2_4_2_OFF_T2 START
		g.timer.module.off.p242[1] = timer_start_ms();
	}
	return 0;
}
int tp243(void){
	if(g.flag.module.bp243){
		//P_2_4_3_ON_T1 STOP
		g.timer.module.work.p243[0] = timer_stop_s(g.timer.module.on.p243[0]);
		//P_2_4_3_ON_T2 STOP
		g.timer.module.work.p243[1] = timer_stop_ms(g.timer.module.on.p243[1]);
		//P_2_4_3_F
		g.flag.module.bp243 = 0;
	}
	return 0;
}
int tp3_individual_stop(void){
	if(g.flag.module.bp3){
		//P_3_ON_T1 STOP
		g.timer.module.work.p3[0] = timer_stop_s(g.timer.module.on.p3[0]);
		//P_3_ON_T2 STOP
		g.timer.module.work.p3[1] = timer_stop_ms(g.timer.module.on.p3[1]);
		//P_3_F
		g.flag.module.bp3 = 0;
	}
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
//I can change to t_pump_1_stop(); for better understand
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

int tp314(void){
	if(g.flag.module.bp314){
		//P_3_1_4_ON_T1 STOP
		g.timer.module.work.p314[0] = timer_stop_s(g.timer.module.on.p314[0]);
		//P_3_1_4_ON_T2 STOP
		g.timer.module.work.p314[1] = timer_stop_ms(g.timer.module.on.p314[1]);
		//P_3_1_4_F
		g.flag.module.bp314 = 0;
	}
	return 0;
}
int tp8(void){
	if(g.flag.module.bp8){
		//P_8_ON_T1 STOP
		g.timer.module.work.p8[0] = timer_stop_s(g.timer.module.on.p8[0]);
		//P_8_ON_T2 STOP
		g.timer.module.work.p8[1] = timer_stop_ms(g.timer.module.on.p8[1]);
		//P_8_F
		g.flag.module.bp8 = 0;
	}
	return 0;
}
int tc1(void){
	if(g.flag.module.bc1){
		//C_1_ON_T1 STOP
		g.timer.module.work.c1[0] = timer_stop_s(g.timer.module.on.c1[0]);
		//C_1_ON_T2 STOP
		g.timer.module.work.c1[1] = timer_stop_ms(g.timer.module.on.c1[1]);
		//CVCC（ER＝電解装置） OFF
		CVCC_CONTROL_PIN = 0U;
		//C_1_OFF _T2 START
		C_1_OFF_T2 = timer_start_ms();
		//C_1_F
		g.flag.module.bc1 = 0;
	}
	return 0;
}
int tc2(void){
	if(g.flag.module.bc2){
		//C_2_ON_T1 STOP
		g.timer.module.work.c2[0] = timer_stop_s(g.timer.module.on.c2[0]);
		//C_2_ON_T2 STOP
		g.timer.module.work.c2[1] = timer_stop_ms(g.timer.module.on.c2[1]);
		//C_2_F
		g.flag.module.bc2 = 0;
	}
	return 0;
}
int tc3(void){
	if(g.flag.module.bc3){
		//C_3_ON_T1 STOP
		g.timer.module.work.c3[0] = timer_stop_s(g.timer.module.on.c3[0]);
		//C_3_ON_T2 STOP
		g.timer.module.work.c3[1] = timer_stop_ms(g.timer.module.on.c3[1]);
		//C_3_F
		g.flag.module.bc3 = 0;
	}
	return 0;
}
int tc4(void){
	if(g.flag.module.bc4){
		//C_4_ON_T1 STOP
		g.timer.module.work.c4[0] = timer_stop_s(g.timer.module.on.c4[0]);
		//C_4_ON_T2 STOP
		g.timer.module.work.c4[1] = timer_stop_ms(g.timer.module.on.c4[1]);
		//C_4_F
		g.flag.module.bc4 = 0;
	}
	return 0;
}
int tc5(void){
	if(g.flag.module.bc5){
		//C_5_ON_T1 STOP
		g.timer.module.work.c5[0] = timer_stop_s(g.timer.module.on.c5[0]);
		//C_5_ON_T2 STOP
		g.timer.module.work.c5[1] = timer_stop_ms(g.timer.module.on.c5[1]);
		//C_5_F
		g.flag.module.bc5 = 0;
	}
	return 0;
}
int tc51(void){
	if(g.flag.module.bc51){
		//C_5_1_ON_T1 STOP
		g.timer.module.work.c51[0] = timer_stop_s(g.timer.module.on.c51[0]);
		//C_5_1_ON_T2 STOP
		g.timer.module.work.c51[1] = timer_stop_ms(g.timer.module.on.c51[1]);
		//C_5_1_F
		g.flag.module.bc51 = 0;
	}
	return 0;
}
int tc52(void){
	if(g.flag.module.bc52){
		//C_5_2_ON_T1 STOP
		g.timer.module.work.c52[0] = timer_stop_s(g.timer.module.on.c52[0]);
		//C_5_2_ON_T2 STOP
		g.timer.module.work.c52[1] = timer_stop_ms(g.timer.module.on.c52[1]);
		//C_5_2_F
		g.flag.module.bc52 = 0;
	}
	return 0;
}
int tc53(void){
	if(g.flag.module.bc53){
		//C_5_3_ON_T1 STOP
		g.timer.module.work.c53[0] = timer_stop_s(g.timer.module.on.c53[0]);
		//C_5_3_ON_T2 STOP
		g.timer.module.work.c53[1] = timer_stop_ms(g.timer.module.on.c53[1]);
		//C_5_3_F
		g.flag.module.bc53 = 0;
	}
	return 0;
}
int tc531(void){
	if(g.flag.module.bc531){
		//C_5_3_1_ON_T1 STOP
		g.timer.module.work.c531[0] = timer_stop_s(g.timer.module.on.c531[0]);
		//C_5_3_1_ON_T2 STOP
		g.timer.module.work.c531[1] = timer_stop_ms(g.timer.module.on.c531[1]);
		//C_5_3_1_F
		g.flag.module.bc531 = 0;
	}
	return 0;
}
int tc54(void){
	if(g.flag.module.bc54){
		//C_5_4_ON_T1 STOP
		g.timer.module.work.c54[0] = timer_stop_s(g.timer.module.on.c54[0]);
		//C_5_4_ON_T2 STOP
		g.timer.module.work.c54[1] = timer_stop_ms(g.timer.module.on.c54[1]);
		//C_5_4_F
		g.flag.module.bc54 = 0;
	}
	return 0;
}
int tc55(void){
	if(g.flag.module.bc55){
		//C_5_5_ON_T1 STOP
		g.timer.module.work.c55[0] = timer_stop_s(g.timer.module.on.c55[0]);
		//C_5_5_ON_T2 STOP
		g.timer.module.work.c55[1] = timer_stop_ms(g.timer.module.on.c55[1]);
		//C_5_5_F
		g.flag.module.bc55 = 0;
	}
	return 0;
}
int tc56(void){
	if(g.flag.module.bc56){
		//C_5_6_ON_T1 STOP
		g.timer.module.work.c56[0] = timer_stop_s(g.timer.module.on.c56[0]);
		//C_5_6_ON_T2 STOP
		g.timer.module.work.c56[1] = timer_stop_ms(g.timer.module.on.c56[1]);
		//C_5_6_F
		g.flag.module.bc56 = 0;
	}
	return 0;
}
int tc6(void){
	if(g.flag.module.bc6){
		//C_6_ON_T1 STOP
		g.timer.module.work.c6[0] = timer_stop_s(g.timer.module.on.c6[0]);
		//C_6_ON_T2 STOP
		g.timer.module.work.c6[1] = timer_stop_ms(g.timer.module.on.c6[1]);
		//C_6_F
		g.flag.module.bc6 = 0;
	}
	return 0;
}
int tc7(void){
	if(g.flag.module.bc7){
		//C_7_ON_T1 STOP
		g.timer.module.work.c7[0] = timer_stop_s(g.timer.module.on.c7[0]);
		//C_7_ON_T2 STOP
		g.timer.module.work.c7[1] = timer_stop_ms(g.timer.module.on.c7[1]);
		//C_7_F
		g.flag.module.bc7 = 0;
	}
	return 0;
}
int tc8(void){
	if(g.flag.module.bc8){
		//C_8_ON_T1 STOP
		g.timer.module.work.c8[0] = timer_stop_s(g.timer.module.on.c8[0]);
		//C_8_ON_T2 STOP
		g.timer.module.work.c8[1] = timer_stop_ms(g.timer.module.on.c8[1]);
		//C_8_F
		g.flag.module.bc8 = 0;
	}
	return 0;
}
int tc9(void){
	if(g.flag.module.bc9){
		//C_9_ON_T1 STOP
		g.timer.module.work.c9[0] = timer_stop_s(g.timer.module.on.c9[0]);
		//C_9_ON_T2 STOP
		g.timer.module.work.c9[1] = timer_stop_ms(g.timer.module.on.c9[1]);
		//C_9_F
		g.flag.module.bc9 = 0;
	}
	return 0;
}
int tc10(void){
	if(g.flag.module.bc10){
		//C_10_ON_T1 STOP
		g.timer.module.work.c10[0] = timer_stop_s(g.timer.module.on.c10[0]);
		//C_10_ON_T2 STOP
		g.timer.module.work.c10[1] = timer_stop_ms(g.timer.module.on.c10[1]);
		//C_10_F
		g.flag.module.bc10 = 0;
	}
	return 0;
}
int tc11(void){
	if(g.flag.module.bc11){
		//C_11_ON_T1 STOP
		g.timer.module.work.c11[0] = timer_stop_s(g.timer.module.on.c11[0]);
		//C_11_ON_T2 STOP
		g.timer.module.work.c11[1] = timer_stop_ms(g.timer.module.on.c11[1]);
		//C_11_F
		g.flag.module.bc11 = 0;
	}
	return 0;
}
int tc12(void){
	if(g.flag.module.bc12){
		//C_12_ON_T1 STOP
		g.timer.module.work.c12[0] = timer_stop_s(g.timer.module.on.c12[0]);
		//C_12_ON_T2 STOP
		g.timer.module.work.c12[1] = timer_stop_ms(g.timer.module.on.c12[1]);
		//C_12_F
		g.flag.module.bc12 = 0;
	}
	return 0;
}
int tc13(void){
	if(g.flag.module.bc13){
		//C_13_ON_T1 STOP
		g.timer.module.work.c13[0] = timer_stop_s(g.timer.module.on.c13[0]);
		//C_13_ON_T2 STOP
		g.timer.module.work.c13[1] = timer_stop_ms(g.timer.module.on.c13[1]);
		//C_13_F
		g.flag.module.bc13 = 0;
	}
	return 0;
}
int tc14(void){
	if(g.flag.module.bc14){
		//C_14_ON_T1 STOP
		g.timer.module.work.c14[0] = timer_stop_s(g.timer.module.on.c14[0]);
		//C_14_ON_T2 STOP
		g.timer.module.work.c14[1] = timer_stop_ms(g.timer.module.on.c14[1]);
		//C_14_F
		g.flag.module.bc14 = 0;
	}
	return 0;
}
int tc15(void){
	if(g.flag.module.bc15){
		//C_15_ON_T1 STOP
		g.timer.module.work.c15[0] = timer_stop_s(g.timer.module.on.c15[0]);
		//C_15_ON_T2 STOP
		g.timer.module.work.c15[1] = timer_stop_ms(g.timer.module.on.c15[1]);
		//C_15_F
		g.flag.module.bc15 = 0;
	}
	return 0;
}
int tc16(void){
	if(g.flag.module.bc16){
		//C_16_ON_T1 STOP
		g.timer.module.work.c16[0] = timer_stop_s(g.timer.module.on.c16[0]);
		//C_16_ON_T2 STOP
		g.timer.module.work.c16[1] = timer_stop_ms(g.timer.module.on.c16[1]);
		//C_16_F
		g.flag.module.bc16 = 0;
	}
	return 0;
}
int tc17(void){
	if(g.flag.module.bc17){
		//C_17_ON_T1 STOP
		g.timer.module.work.c17[0] = timer_stop_s(g.timer.module.on.c17[0]);
		//C_17_ON_T2 STOP
		g.timer.module.work.c17[1] = timer_stop_ms(g.timer.module.on.c17[1]);
		//C_17_F
		g.flag.module.bc17 = 0;
	}
	return 0;
}
int tc18(void){
	if(g.flag.module.bc18){
		//C_18_ON_T1 STOP
		g.timer.module.work.c18[0] = timer_stop_s(g.timer.module.on.c18[0]);
		//C_18_ON_T2 STOP
		g.timer.module.work.c18[1] = timer_stop_ms(g.timer.module.on.c18[1]);
		//C_18_F
		g.flag.module.bc18 = 0;
	}
	return 0;
}
int tc19(void){
	if(g.flag.module.bc19){
		//C_19_ON_T1 STOP
		g.timer.module.work.c19[0] = timer_stop_s(g.timer.module.on.c19[0]);
		//C_19_ON_T2 STOP
		g.timer.module.work.c19[1] = timer_stop_ms(g.timer.module.on.c19[1]);
		//C_19_F
		g.flag.module.bc19 = 0;
	}
	return 0;
}
int te1(void){
	if(g.flag.module.e1){
		//E_1_ON_T1 STOP
		g.timer.module.work.e1[0] = timer_stop_s(g.timer.module.on.e1[0]);
		//E_1_ON_T2 STOP
		g.timer.module.work.e1[1] = timer_stop_ms(g.timer.module.on.e1[1]);
		//E_1_F = 0
		g.flag.module.e1 = 0;
	}
	return 0;
}
/**
 * Blue LED light
 * @return
 */
int t_b_led_l(void){
	if(g.flag.module.b_b_led_l){
		//B_LED_B_ON_T1 STOP
		g.timer.module.work.b_led_l[0] = timer_stop_s(g.timer.module.on.b_led_l[0]);
		//B_LED_B_ON_T2 STOP
		g.timer.module.work.b_led_l[1] = timer_stop_ms(g.timer.module.on.b_led_l[1]);
		hand_sensor_light(HS_OFF);
		//B_LED_B_F = 0
		g.flag.module.b_b_led_l = 0;
	}
	return 0;
}
/**
 * Blue LED blink
 * @return
 */
int t_b_led_b(void){
	if(g.flag.module.b_b_led_b){
		//E_1_ON_T1 STOP
		g.timer.module.work.b_led_b[0] = timer_stop_s(g.timer.module.on.b_led_b[0]);
		//E_1_ON_T2 STOP
		g.timer.module.work.b_led_b[1] = timer_stop_ms(g.timer.module.on.b_led_b[1]);
		hand_sensor_blink(HS_OFF, 300);
		//B_LED_B_F = 0
		g.flag.module.b_b_led_b = 0;
	}
	return 0;
}
