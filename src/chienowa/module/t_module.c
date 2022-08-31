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

int tp_0(void){
	if(g_P_0_F){
		g_P_0_F = 0;
		g_P_0_ON_T1 = timer_stop_s(g.timer.module.on.p0[0]);
		g_P_0_ON_T2 = timer_stop_ms(g.timer.module.on.p0[1]);
	}
	return 0;
}
int tp_1(void) {
	if(g_P_1_F){
		//g.timer.module.work.p1[1] is last working time
		g_P_1_ON_T1 = timer_stop_s(g.timer.module.on.p1[0]);
		g_P_1_ON_T2 = timer_stop_ms(g.timer.module.on.p1[1]);
		g_P_1_F = 0;
	}
	return 0;
}
int tp_1_1(void) {
	if(g_P_1_1_F){
		g_P_1_1_ON_T1 = timer_stop_s(g.timer.module.on.p11[0]);
		g_P_1_1_ON_T2 = timer_stop_ms(g.timer.module.on.p11[1]);
		g_P_1_1_F = 0;
	}
	return 0;
}
int tp_1_1_1(void) {
	if (g_P_1_1_1_F) {
		g_P_1_1_1_ON_T1 = timer_stop_s(g.timer.module.on.p111[0]);
		g_P_1_1_1_ON_T2 = timer_stop_ms(g.timer.module.on.p111[1]);
		g_P_1_1_1_F = 0;
	}
	return 0;
}
int tp_1_1_2(void) {
	if (g_P_1_1_2_F) {
		g_P_1_1_2_ON_T1 = timer_stop_s(g.timer.module.on.p112[0]);
		g_P_1_1_2_ON_T2 = timer_stop_ms(g.timer.module.on.p112[1]);
		g_P_1_1_2_F = 0;
	}
	return 0;
}
int tp_1_2(void) {
	if(g_P_1_2_F){
		g_P_1_2_ON_T1 = timer_stop_s(g.timer.module.on.p12[0]);
		g_P_1_2_ON_T2 = timer_stop_ms(g.timer.module.on.p12[1]);
		g_P_1_2_F = 0;
	}
	return 0;
}
int tp_1_3(void) {
	if(g_P_1_3_F){
		g_P_1_3_ON_T1 = timer_stop_s(g.timer.module.on.p13[0]);
		g_P_1_3_ON_T2 = timer_stop_ms(g.timer.module.on.p13[1]);
		CVCC_CONTROL_PIN = 0U;
		//C_1_OFF_T2 START
		g.timer.module.off.c1[1] = timer_start_s();
		g_P_1_3_F = 0;
	}
	return 0;
}

int tp_1_4(void) {
	if(g_P_1_4_F){
		g_P_1_4_ON_T1 = timer_stop_s(g.timer.module.on.p14[0]);
		g_P_1_4_ON_T2 = timer_stop_ms(g.timer.module.on.p14[1]);
		g_P_1_4_F = 0;
	}
	return 0;
}
int tp_1_4_1(void) {
	if(g_P_1_4_1_F){
		g_P_1_4_1_ON_T1 = timer_stop_s(g.timer.module.on.p141[0]);
		g_P_1_4_1_ON_T2 = timer_stop_ms(g.timer.module.on.p141[1]);
		g.flag.module.bp141 = 0;
	}
	return 0;
}
int tp_1_4_2(void) {
	if(g_P_1_4_2_F){
		g_P_1_4_2_ON_T1 = timer_stop_s(g.timer.module.on.p142[0]);
		g_P_1_4_2_ON_T2 = timer_stop_ms(g.timer.module.on.p142[1]);
		g_P_1_4_2_F = 0;
	}
	return 0;
}

int tp_1_5(void) {
	if(g_P_1_5_F){
		g_P_1_5_ON_T1 = timer_stop_s(g.timer.module.on.p15[0]);
		g_P_1_5_ON_T2 = timer_stop_ms(g.timer.module.on.p15[1]);
		CVCC_CONTROL_PIN = 0U;
		//C_1_OFF_T2 START
		g.timer.module.off.c1[1] = timer_start_s();
		g_P_1_5_F = 0;
	}
	return 0;
}
int tp_2(void) {
	if(g_P_2_F){
		g_P_2_ON_T1 = timer_stop_s(g.timer.module.on.p2[0]);
		g_P_2_ON_T2 = timer_stop_ms(g.timer.module.on.p2[1]);
		g_P_2_F = 0;
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp21_alkali_discharge_stop(void){
	if(g_P_2_1_F){
		g_P_2_1_ON_T1 = timer_stop_s(g.timer.module.on.p23[0]);
		g_P_2_1_ON_T2 = timer_stop_ms(g.timer.module.on.p23[1]);
		g_P_2_1_F = 0;
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp22_acid_discharge_stop(void){
	if(g_P_2_2_F){
		g_P_2_2_ON_T1 = timer_stop_s(g.timer.module.on.p23[0]);
		g_P_2_2_ON_T2 = timer_stop_ms(g.timer.module.on.p23[1]);
		g_P_2_2_F = 0;
	}
	return 0;
}
int tp_2_3(void){
	if(g_P_2_3_F){
		g_P_2_3_ON_T1 = timer_stop_s(g.timer.module.on.p23[0]);
		g_P_2_3_ON_T2 = timer_stop_ms(g.timer.module.on.p23[1]);
		g_P_2_3_F = 0;
	}
	return 0;
}
int tp_2_4(void){
	if(g_P_2_4_F){
		g_P_2_4_ON_T1 = timer_stop_s(g.timer.module.on.p24[0]);
		g_P_2_4_ON_T2 = timer_stop_ms(g.timer.module.on.p24[1]);
		g_P_2_4_F = 0;
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp_2_4_1(void){
	if(g.flag.module.bp241){
		g_P_2_4_1_ON_T1 = timer_stop_s(g.timer.module.on.p241[0]);
		g_P_2_4_1_ON_T2 = timer_stop_ms(g.timer.module.on.p241[1]);
		g_P_2_4_1_F = 0;
		g.timer.module.off.p241[0] = timer_restart_s(g_P_2_4_1_OFF_T1);
		g.timer.module.off.p241[1] = timer_start_ms();
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp_2_4_2(void){
	if(g.flag.module.bp242){
		g_P_2_4_2_ON_T1 = timer_stop_s(g.timer.module.on.p242[0]);
		g_P_2_4_2_ON_T2 = timer_stop_ms(g.timer.module.on.p242[1]);
		g_P_2_4_2_F = 0;
		g.timer.module.off.p242[0] = timer_restart_s(g_P_2_4_2_OFF_T1);
		g.timer.module.off.p242[1] = timer_start_ms();
	}
	return 0;
}
int tp_2_4_3(void){
	if(g_P_2_4_3_F){
		g_P_2_4_3_ON_T1 = timer_stop_s(g.timer.module.on.p243[0]);
		g_P_2_4_3_ON_T2 = timer_stop_ms(g.timer.module.on.p243[1]);
		g_P_2_4_3_F = 0;
	}
	return 0;
}
int tp_3(void){
	if(g_P_3_F){
		g_P_3_ON_T1 = timer_stop_s(g.timer.module.on.p3[0]);
		g_P_3_ON_T2 = timer_stop_ms(g.timer.module.on.p3[1]);
		g_P_3_F = 0;
	}
	return 0;
}

int t_sv1_stop(void) {
	if (g.io.valve.sv1 == 1) {
		g_SV1_ON_T1 = timer_stop_s(g.timer.module.on.io.sv1[0]);
		g_SV1_ON_T2 = timer_stop_s(g.timer.module.on.io.sv1[1]);
		g_SV1_ON_T3 = timer_stop_s(g.timer.module.on.io.sv1[2]);
		SV1_PIN = VALVE_OFF;
		g.io.valve.sv1 = 0;
		return 1;
	}
	return 0;
}
int t_sv2_stop(void) {
	if (g.io.valve.sv2 == 1) {
		g_SV2_ON_T1 = timer_stop_s(g.timer.module.on.io.sv2[0]);
		g_SV2_ON_T2 = timer_stop_s(g.timer.module.on.io.sv2[1]);
		g_SV2_ON_T3 = timer_stop_s(g.timer.module.on.io.sv2[2]);
		SV2_PIN = VALVE_OFF;
		g.io.valve.sv2 = 0;
		return 1;
	}
	return 0;
}
int t_sv3_stop(void) {
	if (g.io.valve.sv3 == 1) {
		g_SV3_ON_T1 = timer_stop_s(g.timer.module.on.io.sv3[0]);
		g_SV3_ON_T2 = timer_stop_s(g.timer.module.on.io.sv3[1]);
		g_SV3_ON_T3 = timer_stop_s(g.timer.module.on.io.sv3[2]);
		SV3_PIN = VALVE_OFF;
		g.io.valve.sv3 = 0;
		return 1;
	}
	return 0;
}
int t_sv4_stop(void) {
	if (g.io.valve.sv4 == 1) {
		g_SV4_ON_T1 = timer_stop_s(g.timer.module.on.io.sv4[0]);
		g_SV4_ON_T2 = timer_stop_s(g.timer.module.on.io.sv4[1]);
		g_SV4_ON_T3 = timer_stop_s(g.timer.module.on.io.sv4[2]);
		SV4_PIN = VALVE_OFF;
		g.io.valve.sv4 = 0;
		return 1;
	}
	return 0;
}
int t_sv5_stop(void) {
	if (g.io.valve.sv5 == 1) {
		g_SV5_ON_T1 = timer_stop_s(g.timer.module.on.io.sv5[0]);
		g_SV5_ON_T2 = timer_stop_s(g.timer.module.on.io.sv5[1]);
		g_SV5_ON_T3 = timer_stop_s(g.timer.module.on.io.sv5[2]);
		SV5_PIN = VALVE_OFF;
		g.io.valve.sv5 = 0;
		return 1;
	}
	return 0;
}
int t_sv6_stop(void) {
	if (g.io.valve.sv6 == 1) {
		g_SV6_ON_T1 = timer_stop_s(g.timer.module.on.io.sv6[0]);
		g_SV6_ON_T2 = timer_stop_s(g.timer.module.on.io.sv6[1]);
		g_SV6_ON_T3 = timer_stop_s(g.timer.module.on.io.sv6[2]);
		SV6_PIN = VALVE_OFF;
		g.io.valve.sv6 = 0;
	}
	return 0;
}
int t_sv7_stop(void){
	if (g.io.valve.sv7 == 1){
		g_SV7_ON_T1 = timer_stop_s(g.timer.module.on.io.sv7[0]);
		g_SV7_ON_T2 = timer_stop_s(g.timer.module.on.io.sv7[1]);
		g_SV7_ON_T3 = timer_stop_s(g.timer.module.on.io.sv7[2]);
		SV7_PIN = VALVE_OFF;
		g.io.valve.sv7 = 0;
	}
	return 0;
}
int t_p1_stop(void) {
	if (g_P1_F == 1) {
		PUMP_1_PIN = PUMP_OFF;
		g_P1_ON_T1 = timer_stop_s(g.timer.module.on.io.p1[0]);
		g_P1_ON_T2 = timer_stop_s(g.timer.module.on.io.p1[1]);
		g_P1_ON_T3 = timer_stop_s(g.timer.module.on.io.p1[2]);
		g_P1_F = 0;
		return 1;
	}
	return 0;
}

int t_p2_stop(void) {
	if (g_P2_F == 1) {
		PUMP_2_PIN = PUMP_OFF;
		g_P2_ON_T1 = timer_stop_s(g.timer.module.on.io.p2[0]);
		g_P2_ON_T2 = timer_stop_s(g.timer.module.on.io.p2[1]);
		g_P2_ON_T3 = timer_stop_s(g.timer.module.on.io.p2[2]);
		PUMP_2_PIN = PUMP_OFF;
		g_P2_F = 0;
	}
	return 0;
}
int t_sp_stop(void) {
	if (g_SP_F == 1) {
		SP_PIN = PUMP_OFF;
		g_SP_ON_T1 = timer_stop_s(g.timer.module.on.io.sp[0]);
		g_SP_ON_T2 = timer_stop_s(g.timer.module.on.io.sp[1]);
		g_SP_ON_T3 = timer_stop_s(g.timer.module.on.io.sp[2]);
		g_SP_F = 0;
		return 1;
	}
	return 0;
}

int tp_3_1_4(void){
	if(g_P_3_1_4_F){
		g_P_3_1_4_ON_T1 = timer_stop_s(g.timer.module.on.p314[0]);
		g_P_3_1_4_ON_T2 = timer_stop_ms(g.timer.module.on.p314[1]);
		g_P_3_1_4_F = 0;
	}
	return 0;
}
int tp_8(void){
	if(g_P_3_F){
		g_P_8_ON_T1 = timer_stop_s(g.timer.module.on.p8[0]);
		g_P_8_ON_T2 = timer_stop_ms(g.timer.module.on.p8[1]);
		g_P_3_F = 0;
	}
	return 0;
}
int tc_1(void){
	if(g_C_1_F){
		g_C_1_ON_T1 = timer_stop_s(g.timer.module.on.c1[0]);
		g_C_1_ON_T2 = timer_stop_ms(g.timer.module.on.c1[1]);
		CVCC_CONTROL_PIN = 0U;
		//C_1_OFF_T2 START
		g.timer.module.off.c1[1] = timer_start_ms();
		g_C_1_F = 0;
	}
	return 0;
}
int tc_2(void){
	if(g_C_2_F){
		g_C_2_ON_T1 = timer_stop_s(g.timer.module.on.c2[0]);
		g_C_2_ON_T2 = timer_stop_ms(g.timer.module.on.c2[1]);
		g_C_2_F = 0;
	}
	return 0;
}
/**
 * Do not have information yet
 * @return
 */
int tc_2_3(void){
	return 0;
}
int tc_3(void){
	if(g_C_3_F){
		g_C_3_ON_T1 = timer_stop_s(g.timer.module.on.c3[0]);
		g_C_3_ON_T2 = timer_stop_ms(g.timer.module.on.c3[1]);
		g_C_3_F = 0;
	}
	return 0;
}
int tc_4(void){
	if(g_C_4_F){
		g_C_4_ON_T1 = timer_stop_s(g.timer.module.on.c4[0]);
		g_C_4_ON_T1 = timer_stop_ms(g.timer.module.on.c4[1]);
		g_C_4_F = 0;
	}
	return 0;
}
int tc_5(void){
	if(g_C_5_F){
		g_C_5_ON_T1 = timer_stop_s(g.timer.module.on.c5[0]);
		g_C_5_ON_T2 = timer_stop_ms(g.timer.module.on.c5[1]);
		g_C_5_F = 0;
	}
	return 0;
}
int tc_5_1(void){
	if(g_C_5_1_F){
		g_C_5_1_ON_T1 = timer_stop_s(g.timer.module.on.c51[0]);
		g_C_5_1_ON_T2 = timer_stop_ms(g.timer.module.on.c51[1]);
		g_C_5_1_F = 0;
	}
	return 0;
}
int tc_5_2(void){
	if(g_C_5_2_F){
		g_C_5_2_ON_T1 = timer_stop_s(g.timer.module.on.c52[0]);
		g_C_5_2_ON_T1 = timer_stop_ms(g.timer.module.on.c52[1]);
		g_C_5_2_F = 0;
	}
	return 0;
}
int tc_5_3(void){
	if(g_C_5_3_F){
		g_C_5_3_ON_T1 = timer_stop_s(g.timer.module.on.c53[0]);
		g_C_5_3_ON_T1 = timer_stop_ms(g.timer.module.on.c53[1]);
		g_C_5_3_F = 0;
	}
	return 0;
}
int tc_5_3_1(void){
	if(g_C_5_3_1_F){
		g_C_5_3_1_ON_T1 = timer_stop_s(g.timer.module.on.c531[0]);
		g_C_5_3_1_ON_T2 = timer_stop_ms(g.timer.module.on.c531[1]);
		g_C_5_3_1_F = 0;
	}
	return 0;
}
int tc_5_4(void){
	if(g_C_5_4_F){
		g_C_5_4_ON_T1 = timer_stop_s(g.timer.module.on.c54[0]);
		g_C_5_4_ON_T2 = timer_stop_ms(g.timer.module.on.c54[1]);
		g_C_5_4_F = 0;
	}
	return 0;
}
int tc_5_5(void){
	if(g_C_5_5_F){
		g_C_5_5_ON_T1 = timer_stop_s(g.timer.module.on.c55[0]);
		g_C_5_5_ON_T2 = timer_stop_ms(g.timer.module.on.c55[1]);
		g_C_5_5_F = 0;
	}
	return 0;
}
int tc_5_6(void){
	if(g_C_5_6_F){
		g_C_5_6_ON_T1 = timer_stop_s(g.timer.module.on.c56[0]);
		g_C_5_6_ON_T2 = timer_stop_ms(g.timer.module.on.c56[1]);
		g_C_5_6_F = 0;
	}
	return 0;
}
int tc_6(void){
	if(g_C_6_F){
		g_C_6_ON_T1 = timer_stop_s(g.timer.module.on.c6[0]);
		g_C_6_ON_T2 = timer_stop_ms(g.timer.module.on.c6[1]);
		g_C_6_F = 0;
	}
	return 0;
}
int tc_7(void){
	if(g_C_7_F){
		g_C_7_ON_T1 = timer_stop_s(g.timer.module.on.c7[0]);
		g_C_7_ON_T2 = timer_stop_ms(g.timer.module.on.c7[1]);
		g_C_7_F = 0;
	}
	return 0;
}
int tc_8(void){
	if(g_C_8_F){
		g_C_8_ON_T1 = timer_stop_s(g.timer.module.on.c8[0]);
		g_C_8_ON_T2 = timer_stop_ms(g.timer.module.on.c8[1]);
		g_C_8_F = 0;
	}
	return 0;
}
int tc_9(void){
	if(g_C_9_F){
		g_C_9_ON_T1 = timer_stop_s(g.timer.module.on.c9[0]);
		g_C_9_ON_T2 = timer_stop_ms(g.timer.module.on.c9[1]);
		g_C_9_F = 0;
	}
	return 0;
}
int tc_10(void){
	if(g_C_10_F){
		g_C_10_ON_T1 = timer_stop_s(g.timer.module.on.c10[0]);
		g_C_10_ON_T2 = timer_stop_ms(g.timer.module.on.c10[1]);
		g_C_10_F = 0;
	}
	return 0;
}
int tc_11(void){
	if(g_C_11_F){
		g_C_11_ON_T1 = timer_stop_s(g.timer.module.on.c11[0]);
		g_C_11_ON_T2 = timer_stop_ms(g.timer.module.on.c11[1]);
		g_C_11_F = 0;
	}
	return 0;
}
int tc_12(void){
	if(g_C_12_F){
		g_C_12_ON_T1 = timer_stop_s(g.timer.module.on.c12[0]);
		g_C_12_ON_T2 = timer_stop_ms(g.timer.module.on.c12[1]);
		g_C_12_F = 0;
	}
	return 0;
}
int tc_13(void){
	if(g_C_13_F){
		g_C_13_ON_T1 = timer_stop_s(g.timer.module.on.c13[0]);
		g_C_13_ON_T2 = timer_stop_ms(g.timer.module.on.c13[1]);
		g_C_13_F = 0;
	}
	return 0;
}
int tc_14(void){
	if(g_C_14_F){
		g_C_14_ON_T1 = timer_stop_s(g.timer.module.on.c14[0]);
		g_C_14_ON_T2 = timer_stop_ms(g.timer.module.on.c14[1]);
		g_C_14_F = 0;
	}
	return 0;
}
int tc_15(void){
	if(g_C_15_F){
		g_C_15_ON_T1 = timer_stop_s(g.timer.module.on.c15[0]);
		g_C_15_ON_T2 = timer_stop_ms(g.timer.module.on.c15[1]);
		g_C_15_F = 0;
	}
	return 0;
}
int tc_16(void){
	if(g_C_16_F){
		g_C_16_ON_T1 = timer_stop_s(g.timer.module.on.c16[0]);
		g_C_16_ON_T1 = timer_stop_ms(g.timer.module.on.c16[1]);
		g_C_16_F = 0;
	}
	return 0;
}
int tc_17(void){
	if(g_C_17_F){
		g_C_17_ON_T1 = timer_stop_s(g.timer.module.on.c17[0]);
		g_C_17_ON_T2 = timer_stop_ms(g.timer.module.on.c17[1]);
		g_C_17_F = 0;
	}
	return 0;
}
int tc_18(void){
	if(g_C_18_F){
		g_C_18_ON_T1 = timer_stop_s(g.timer.module.on.c18[0]);
		g_C_18_ON_T2 = timer_stop_ms(g.timer.module.on.c18[1]);
		g_C_18_F = 0;
	}
	return 0;
}
int tc_19(void){
	if(g_C_19_F){
		g_C_19_ON_T1 = timer_stop_s(g.timer.module.on.c19[0]);
		g_C_19_ON_T2 = timer_stop_ms(g.timer.module.on.c19[1]);
		g_C_19_F = 0;
	}
	return 0;
}
int te_1(void){
	if(g_E_1_F){
		g_E_1_ON_T1 = timer_stop_s(g.timer.module.on.e1[0]);
		g_E_1_ON_T2 = timer_stop_ms(g.timer.module.on.e1[1]);
		g_E_1_F = 0;
	}
	return 0;
}
/**
 * Blue LED light
 * @return
 */
int t_b_led_l(void){
	if(g.flag.module.b_b_led_l){
		//B_LED_L_ON_T1 STOP
		g.timer.module.work.b_led_l[0] = timer_stop_s(g.timer.module.on.b_led_l[0]);
		//B_LED_L_ON_T2 STOP
		g.timer.module.work.b_led_l[1] = timer_stop_ms(g.timer.module.on.b_led_l[1]);
		hand_sensor_light(HS_OFF);
		//B_LED_L_F = 0
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
		//B_LED_B_ON_T1 STOP
		g.timer.module.work.b_led_b[0] = timer_stop_s(g.timer.module.on.b_led_b[0]);
		//B_LED_B_ON_T2 STOP
		g.timer.module.work.b_led_b[1] = timer_stop_ms(g.timer.module.on.b_led_b[1]);
		hand_sensor_blink(HS_OFF, 300);
		//B_LED_B_F = 0
		g.flag.module.b_b_led_b = 0;
	}
	return 0;
}
/**
 * Red LED light
 * @return
 */
int t_r_led_l(void){
	if(g.flag.module.b_r_led_l){
		//R_LED_L_ON_T1 STOP
		g.timer.module.work.r_led_l[0] = timer_stop_s(g.timer.module.on.r_led_l[0]);
		//R_LED_L_ON_T2 STOP
		g.timer.module.work.r_led_l[1] = timer_stop_ms(g.timer.module.on.r_led_l[1]);
		hand_sensor_light(HS_OFF);
		//R_LED_L_F = 0
		g.flag.module.b_r_led_l = 0;
	}
	return 0;
}
/**
 * Red LED blink
 * @return
 */
int t_r_led_b(void){
	if(g.flag.module.b_r_led_b){
		//R_LED_B_ON_T1 STOP
		g.timer.module.work.r_led_b[0] = timer_stop_s(g.timer.module.on.r_led_b[0]);
		//R_LED_B_ON_T2 STOP
		g.timer.module.work.r_led_b[1] = timer_stop_ms(g.timer.module.on.r_led_b[1]);
		hand_sensor_blink(HS_OFF, 300);
		//R_LED_B_F = 0
		g.flag.module.b_r_led_b = 0;
	}
	return 0;
}
/**
 * White LED light
 * @return
 */
int t_w_led_l(void){
	if(g.flag.module.b_w_led_l){
		//W_LED_L_ON_T1 STOP
		g.timer.module.work.r_led_l[0] = timer_stop_s(g.timer.module.on.r_led_l[0]);
		//W_LED_L_ON_T2 STOP
		g.timer.module.work.r_led_l[1] = timer_stop_ms(g.timer.module.on.r_led_l[1]);
		hand_sensor_light(HS_OFF);
		//W_LED_L_F = 0
		g.flag.module.b_w_led_l = 0;
	}
	return 0;
}
/**
 * White LED blink
 * @return
 */
int t_w_led_b(void){
	if(g.flag.module.b_w_led_b){
		//W_LED_B_ON_T1 STOP
		g.timer.module.work.w_led_b[0] = timer_stop_s(g.timer.module.on.w_led_b[0]);
		//W_LED_B_ON_T2 STOP
		g.timer.module.work.w_led_b[1] = timer_stop_ms(g.timer.module.on.w_led_b[1]);
		hand_sensor_blink(HS_OFF, 300);
		//W_LED_B_F = 0
		g.flag.module.b_w_led_b = 0;
	}
	return 0;
}
/**
 * TODO: Not have flow chart yet
 * @return
 */
int te11(void){
	return 0;
}
