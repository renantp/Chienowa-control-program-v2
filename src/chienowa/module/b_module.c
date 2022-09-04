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
#include "../hand_sensor.h"

int bp_0(void){
	if(!g_P_0_F){
		g.flag.module.bp0 = 1;
		g.timer.module.on.p0[0] = timer_restart_s(g_P_0_ON_T1);
		g.timer.module.on.p0[1] = timer_start_ms();
	}
	return 0;
}
int bp_1(void){
	if(!g_P_1_F){
		g.flag.module.bp1 = 1;
		g.timer.module.on.p1[0] = timer_restart_s(g_P_1_ON_T1);
		g.timer.module.on.p1[1] = timer_start_ms();
	}
	return 0;
}
int bp_1_1(void){
	if(!g_P_1_1_F){
		g.flag.module.bp11 = 1;
		g.timer.module.on.p11[0] = timer_restart_s(g_P_1_1_ON_T1);
		g.timer.module.on.p11[1] = timer_start_ms();
	}
	return 0;
}
int bp_1_1_1(void){
	if( !g_P_1_1_1_F){
		g.flag.module.bp111 = 1;
		g.timer.module.on.p111[0] = timer_restart_s(g_P_1_1_1_ON_T1);
		g.timer.module.on.p111[1] = timer_start_ms();
	}
	return 0;
}
int bp_1_1_2(void){
	if( !g_P_1_1_2_F ){
		g.flag.module.bp112 = 1;
		g.timer.module.on.p112[0] = timer_restart_s(g_P_1_1_2_ON_T1);
		g.timer.module.on.p112[1] = timer_start_ms();
	}
	return 0;
}
int bp_1_2(void){
	if(g_P_1_2_F){
		g.flag.module.bp12 = 1;
		g.timer.module.on.p12[0] = timer_restart_s(g_P_1_2_ON_T1);
		g.timer.module.on.p12[1] = timer_start_ms();
	}
	return 0;
}
int bp_1_3(void){
	if(!g_P_1_3_F){
		g.flag.module.bp13 = 1;
		g.timer.module.on.p13[0] = timer_restart_s(g_P_1_3_ON_T1);
		g.timer.module.on.p13[1] = timer_start_ms();
		CVCC_CONTROL_PIN = 1U;
	}
	return 0;
}
int bp_1_4(void){
	if(!g_P_1_4_F){
		g.flag.module.bp14 = 1;
		g.timer.module.on.p14[0] = timer_restart_s(g_P_1_4_ON_T1);
		g.timer.module.on.p14[1] = timer_start_ms();
		CVCC_CONTROL_PIN = 0;
	}
	return 0;
}
int bp_1_4_1(void){
	if(!g_P_1_4_1_F){
		g.flag.module.bp141 = 1;
		g.timer.module.on.p141[0] = timer_restart_s(g_P_1_4_1_ON_T1);
		g.timer.module.on.p141[1] = timer_start_ms();
	}
	return 0;
}
int bp_1_4_2(void){
	if(!g_P_1_4_2_F){
		g.flag.module.bp142 = 1;
		g.timer.module.on.p142[0] = timer_restart_s(g_P_1_4_2_ON_T1);
		g.timer.module.on.p142[1] = timer_start_ms();
	}
	return 0;
}
int bp_1_5(void){
	if(!g_P_1_5_F){
		g.flag.module.bp15 = 1;
		g.timer.module.on.p15[0] = timer_restart_s(g_P_1_5_ON_T1);
		g.timer.module.on.p15[1] = timer_start_ms();
		CVCC_CONTROL_PIN = 1;
		g_C_1_OFF_T2 = 0;

	}
	return 0;
}
int bp_2(void){
	if(!g_P_2_F){
		g.flag.module.bp2 = 1;
		g.timer.module.on.p2[0] = timer_restart_s(g_P_2_ON_T1);
		g.timer.module.on.p2[1] = timer_start_ms();
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int bp_2_1(void){
	if(!g_P_2_1_F){
		g.flag.module.bp21 = 1;
		g.timer.module.on.p21[0] = timer_restart_s(g_P_2_1_ON_T1);
		g.timer.module.on.p21[1] = timer_start_ms();
		//TODO: P_2_1_OFF_T1 stop
		//TODO: P_2_1_OFF_T2 stop
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int bp_2_2(void){
	if(!g_P_2_2_F){
		g.flag.module.bp22 = 1;
		g.timer.module.on.p22[0] = timer_restart_s(g_P_2_2_ON_T1);
		g.timer.module.on.p22[1] = timer_start_ms();
	}
	return 0;
}
int bp_2_3(void){
	if(!g_P_2_3_F){
		g.flag.module.bp23 = 1;
		g.timer.module.on.p23[0] = timer_restart_s(g_P_2_3_ON_T1);
		g.timer.module.on.p23[1] = timer_start_ms();
	}
	return 0;
}
int bp_2_4(void){
	if(!g_P_2_4_F){
		g.flag.module.bp24 = 1;
		g.timer.module.on.p24[0] = timer_restart_s(g_P_2_4_ON_T1);
		g.timer.module.on.p24[1] = timer_start_ms();
	}
	return 0;
}
/**
 * Under changing
 * @return
 */
int bp_2_4_1(void){
	if(!g_P_2_4_1_F){
		g.flag.module.bp241 = 1;
		g.timer.module.on.p241[0] = timer_restart_s(g_P_2_4_1_ON_T1);
		g.timer.module.on.p241[1] = timer_start_ms();
		g_P_2_4_1_OFF_T1 = timer_stop_s(g.timer.module.off.p241[0]);
		g_P_2_4_1_OFF_T2 = timer_stop_ms(g.timer.module.off.p241[1]);
	}
	return 0;
}
/**
 * Under changing
 * @return
 */
int bp_2_4_2(void){
	if(!g_P_2_4_2_F){
		g.flag.module.bp242 = 1;
		g.timer.module.on.p242[0] = timer_restart_s(g_P_2_4_2_ON_T1);
		g.timer.module.on.p242[1] = timer_start_ms();
		g_P_2_4_2_OFF_T1 = timer_stop_s(g.timer.module.off.p242[0]);
		g_P_2_4_2_OFF_T2 = timer_stop_ms(g.timer.module.off.p242[1]);
	}
	return 0;
}
int bp_2_4_3(void){
	if(!g_P_2_4_3_F){
		g.flag.module.bp243 = 1;
		g.timer.module.on.p243[0] = timer_restart_s(g_P_2_4_3_ON_T1);
		g.timer.module.on.p243[1] = timer_start_ms();
	}
	return 0;
}
int bp_3(void){
	if(!g_P_3_F){
		g.flag.module.bp3 = 1;
		g.timer.module.on.p3[0] = timer_restart_s(g_P_3_ON_T1);
		g.timer.module.on.p3[1] = timer_start_ms();
	}
	return 0;
}
int bp_3_1_4(void){
	if(!g_P_3_1_4_F){
		g.flag.module.bp314 = 1;
		g.timer.module.on.p314[0] = timer_restart_s(g_P_3_1_4_ON_T1);
		g.timer.module.on.p314[1] = timer_start_ms();
	}
	return 0;
}

int bp_8(void){
	if(!g_P_8_F){
		g.flag.module.bp8 = 1;
		g.timer.module.on.p8[0] = timer_restart_s(g_P_8_ON_T1);
		g.timer.module.on.p8[1] = timer_start_ms();
	}
	return 0;
}


int b_p1(void){
	if ( g_P1_F == 0){
		PUMP_1_PIN = PUMP_ON;
		g_P1_F = 1;
		g.timer.module.on.io.p1[0] = timer_restart_s(g_P1_ON_T1);
		g.timer.module.on.io.p1[2] = timer_restart_s(g_P1_ON_T3);
		g.timer.module.on.io.p1[1] = timer_start_ms();
		return 1;
	}
	return 0;
}
int b_p2(void){
	if( g_P2_F == 0 ){
		PUMP_2_PIN = PUMP_ON;
		g_P2_F = 1;
		g.timer.module.on.io.p2[0] = timer_restart_s(g_P2_ON_T1);
		g.timer.module.on.io.p2[0] = timer_restart_s(g_P2_ON_T1);
		g.timer.module.on.io.p2[1] = timer_start_ms();
	}
	return 0;
}
int b_sp_start(void){
	if( g_SP_F == 0 ){
		SP_PIN = PUMP_ON;
		g.io.salt_pump = 1;
		g.timer.module.on.io.sp[0] = timer_restart_s(g_SP_ON_T1);
		g.timer.module.on.io.sp[2] = timer_restart_s(g_SP_ON_T1);
		g.timer.module.on.io.sp[1] = timer_start_ms();
	}
	return 0;
}
int b_sv1(void){
	if ( g.io.valve.sv1 == 0){
		SV1_PIN = VALVE_ON;
		g.io.valve.sv1 = 1;
		g.timer.module.on.io.sv1[0] = timer_restart_s(g_SV1_ON_T1);
		g.timer.module.on.io.sv1[2] = timer_restart_s(g_SV1_ON_T3);
		g.timer.module.on.io.sv1[1] = timer_start_ms();
		return 1;
	}
	return 0;
}
int b_sv2(void){
	if( g.io.valve.sv2 == 0){
		SV2_PIN = VALVE_ON;
		g.io.valve.sv2 = 1;
		g.timer.module.on.io.sv2[0] = timer_restart_s(g_SV2_ON_T1);
		g.timer.module.on.io.sv2[2] = timer_restart_s(g_SV2_ON_T3);
		g.timer.module.on.io.sv2[1] = timer_start_ms();
		return 1;
	}
	return 0;
}
int b_sv3(void){
	if(g.io.valve.sv3 == 0){
		SV3_PIN = VALVE_ON;
		g.io.valve.sv3 = 1;
		g.timer.module.on.io.sv3[0] = timer_restart_s(g_SV3_ON_T1);
		g.timer.module.on.io.sv3[2] = timer_restart_s(g_SV3_ON_T3);
		g.timer.module.on.io.sv3[1] = timer_start_ms();
		return 0;
	}
	return 0;
}
int b_sv4(void){
	if(g.io.valve.sv4 == 0){
		SV4_PIN = VALVE_ON;
		g.io.valve.sv4 = 1;
		g.timer.module.on.io.sv4[0] = timer_restart_s(g_SV4_ON_T1);
		g.timer.module.on.io.sv4[2] = timer_restart_s(g_SV4_ON_T3);
		g.timer.module.on.io.sv4[1] = timer_start_ms();
		return 0;
	}
	return 0;
}
int b_sv5(void){
	if ( g.io.valve.sv5 == 0){
		SV5_PIN = VALVE_ON;
		g.io.valve.sv5 = 1;
		g.timer.module.on.io.sv5[0] = timer_restart_s(g_SV5_ON_T1);
		g.timer.module.on.io.sv5[2] = timer_restart_s(g_SV5_ON_T3);
		g.timer.module.on.io.sv5[1] = timer_start_ms();
		return 1;
	}
	return 0;
}
int b_sv6(void){
	if( g.io.valve.sv6 == 0 ){
		SV6_PIN = VALVE_ON;
		g.io.valve.sv6 = 1;
		g.timer.module.on.io.sv6[0] = timer_restart_s(g_SV6_ON_T1);
		g.timer.module.on.io.sv6[2] = timer_restart_s(g_SV6_ON_T3);
		g.timer.module.on.io.sv6[1] = timer_start_ms();
	}
	return SV6_PIN;
}
int b_sv7_start(void){
	if( g.io.valve.sv7 == 0){
		SV7_PIN = VALVE_ON;
		g.io.valve.sv7 = 1;
		g.timer.module.on.io.sv7[0] = timer_restart_s(g_SV7_ON_T1);
		g.timer.module.on.io.sv7[2] = timer_restart_s(g_SV7_ON_T3);
		g.timer.module.on.io.sv7[1] = timer_start_ms();
	}
	return SV7_PIN;
}

int bc_1(void){
	if(!g_C_1_F){
		g.timer.module.on.c1[0] = timer_restart_s(g_C_1_ON_T1);
		g.timer.module.on.c1[1] = timer_start_ms();
		//TODO: CVCC error??

		g_C_1_F = 1;
	}
	return 0;
}
int bc_2(void){
	if(!g_C_2_F){
		g.timer.module.on.c2[0] = timer_restart_s(g_C_2_ON_T1);
		g.timer.module.on.c2[1] = timer_start_ms();
		g_C_2_F= 1;
	}
	return 0;
}
int bc_3(void){
	if(!g_C_3_F){
		g.timer.module.on.c3[0] = timer_restart_s(g_C_3_ON_T1);
		g.timer.module.on.c3[1] = timer_start_ms();
		g_C_3_F = 1;
	}
	return 0;
}
int bc_4(void){
	if(!g_C_4_F){
		g.timer.module.on.c4[0] = timer_restart_s(g_C_4_ON_T1);
		g.timer.module.on.c4[1] = timer_start_ms();
		g_C_4_F = 1;
	}
	return 0;
}
int bc_5(void){
	if(!g_C_5_F){
		g.timer.module.on.c5[0] = timer_restart_s(g_C_5_ON_T1);
		g.timer.module.on.c5[1] = timer_start_ms();
		g.flag.module.bc5 = 1;
	}
	return 0;
}
int bc_5_1(void){
	if(!g_C_5_1_F){
		g.timer.module.on.c51[0] = timer_restart_s(g_C_5_1_ON_T1);
		g.timer.module.on.c51[1] = timer_start_ms();
		g_C_5_1_F = 1;
	}
	return 0;
}
int bc_5_2(void){
	if(!g_C_5_2_F){
		g.timer.module.on.c52[0] = timer_restart_s(g_C_5_2_ON_T1);
		g.timer.module.on.c52[1] = timer_start_ms();
		g_C_5_2_F = 1;
	}
	return 0;
}
int bc_5_3(void){
	if(!g_C_5_3_F){
		g.timer.module.on.c53[0] = timer_restart_s(g_C_5_3_ON_T1);
		g.timer.module.on.c53[1] = timer_start_ms();
		g_C_5_3_F = 1;
	}
	return 0;
}
int bc_5_3_1(void){
	if(!g_C_5_3_1_F){
		g.timer.module.on.c531[0] = timer_restart_s(g_C_5_3_1_ON_T1);
		g.timer.module.on.c531[1] = timer_start_ms();
		g_C_5_3_1_F = 1;
	}
	return 0;
}
int bc_5_4(void){
	if(!g_C_5_4_F){
		g.timer.module.on.c54[0] = timer_restart_s(g_C_5_4_ON_T1);
		g.timer.module.on.c54[1] = timer_start_ms();
		g_C_5_4_F = 1;
	}
	return 0;
}
int bc_5_5(void){
	if(!g_C_5_5_F){
		g.timer.module.on.c55[0] = timer_restart_s(g_C_5_5_ON_T1);
		g.timer.module.on.c55[1] = timer_start_ms();
		g_C_5_5_F = 1;
	}
	return 0;
}
int bc_5_6(void){
	if(!g_C_5_6_F){
		g.timer.module.on.c56[0] = timer_restart_s(g_C_5_6_ON_T1);
		g.timer.module.on.c56[1] = timer_start_ms();
		g_C_5_6_F = 1;
	}
	return 0;
}
int bc_6(void){
	if(!g_C_6_F){
		g.timer.module.on.c6[0] = timer_restart_s(g_C_6_ON_T1);
		g.timer.module.on.c6[1] = timer_start_ms();
		g_C_6_F = 1;
	}
	return 0;
}
int bc_7(void){
	if(!g_C_7_F){
		g.timer.module.on.c7[0] = timer_restart_s(g_C_7_ON_T1);
		g.timer.module.on.c7[1] = timer_start_ms();
		g_C_7_F = 1;
	}
	return 0;
}
int bc_8(void){
	if(!g_C_8_F){
		g.timer.module.on.c8[0] = timer_restart_s(g_C_8_ON_T1);
		g.timer.module.on.c8[1] = timer_start_ms();
		g_C_8_F = 1;
	}
	return 0;
}
int bc_9(void){
	if(!g_C_9_F){
		g.timer.module.on.c9[0] = timer_restart_s(g_C_9_ON_T1);
		g.timer.module.on.c9[1] = timer_start_ms();
		g_C_9_F = 1;
	}
	return 0;
}
int bc_10(void){
	if(!g_C_10_F){
		g.timer.module.on.c10[0] = timer_restart_s(g_C_10_ON_T1);
		g.timer.module.on.c10[1] = timer_start_ms();
		g_C_10_F = 1;
	}
	return 0;
}
int bc_11(void){
	if(!g_C_11_F){
		g.timer.module.on.c11[0] = timer_restart_s(g_C_11_ON_T1);
		g.timer.module.on.c11[1] = timer_start_ms();
		g_C_11_F = 1;
	}
	return 0;
}
int bc_12(void){
	if(!g_C_12_F){
		g.timer.module.on.c12[0] = timer_restart_s(g_C_12_ON_T1);
		g.timer.module.on.c12[1] = timer_start_ms();
		g_C_12_F = 1;
	}
	return 0;
}
int bc_13(void){
	if(!g_C_13_F){
		g.timer.module.on.c13[0] = timer_restart_s(g_C_13_ON_T1);
		g.timer.module.on.c13[1] = timer_start_ms();
		g_C_13_F = 1;
	}
	return 0;
}
int bc_14(void){
	if(!g_C_14_F){
		g.timer.module.on.c14[0] = timer_restart_s(g_C_14_ON_T1);
		g.timer.module.on.c14[1] = timer_start_ms();
		g_C_14_F= 1;
	}
	return 0;
}
int bc_15(void){
	if(!g_C_15_F){
		g.timer.module.on.c15[0] = timer_restart_s(g_C_15_ON_T1);
		g.timer.module.on.c15[1] = timer_start_ms();
		g_C_15_F= 1;
	}
	return 0;
}
int bc_16(void){
	if(!g_C_16_F){
		g.timer.module.on.c16[0] = timer_restart_s(g_C_16_ON_T1);
		g.timer.module.on.c16[1] = timer_start_ms();
		g_C_16_F = 1;
	}
	return 0;
}
int bc_17(void){
	if(!g_C_17_F){
		g.timer.module.on.c17[0] = timer_restart_s(g_C_17_ON_T1);
		g.timer.module.on.c17[1] = timer_start_ms();
		g_C_17_F = 1;
	}
	return 0;
}
int bc_18(void){
	if(!g_C_18_F){
		g.timer.module.on.c18[0] = timer_restart_s(g_C_18_ON_T1);
		g.timer.module.on.c18[1] = timer_start_ms();
		g_C_18_F = 1;
	}
	return 0;
}
int bc_19(void){
	if(!g_C_19_F){
		g.timer.module.on.c19[0] = timer_restart_s(g_C_19_ON_T1);
		g.timer.module.on.c19[1] = timer_start_ms();
		g_C_19_F = 1;
	}
	return 0;
}
int bc_23(void){
	if(!g_C_23_F){
		g_C_23_F = 1;
	}
	return 0;
}
int be_1(void){
	if(!g_E_1_F){
		g.timer.module.on.e1[0] = timer_restart_s(g_E_1_ON_T1);
		g.timer.module.on.e1[1] = timer_start_ms();
		g_E_1_F = 1;
	}
	return 0;
}
int b_b_led_l(void){
	if(g.flag.module.b_b_led_l == 0){
		g.timer.module.on.b_led_l[0] = timer_restart_s(g.timer.module.work.b_led_l[0]);
		g.timer.module.on.b_led_l[1] = timer_start_ms();
		hand_sensor_light(BLUE);
		g.flag.module.b_b_led_l = 1;
	}
	return 0;
}
int b_b_led_b(void){
	if(g.flag.module.b_b_led_b == 0){
		g.timer.module.on.b_led_b[0] = timer_restart_s(g.timer.module.work.b_led_b[0]);
		g.timer.module.on.b_led_b[1] = timer_start_ms();
		hand_sensor_blink(BLUE, 300);
		g.flag.module.b_b_led_b = 1;
	}
	return 0;
}
int b_r_led_l(void){
	if(g.flag.module.b_r_led_l == 0){
		g.timer.module.on.r_led_l[0] = timer_restart_s(g.timer.module.work.r_led_l[0]);
		g.timer.module.on.r_led_l[1] = timer_start_ms();
		hand_sensor_light(RED);
		g.flag.module.b_r_led_l = 1;
	}
	return 0;
}
int b_r_led_b(void){
	if(g.flag.module.b_r_led_b == 0){
		g.timer.module.on.r_led_b[0] = timer_restart_s(g.timer.module.work.r_led_b[0]);
		g.timer.module.on.r_led_b[1] = timer_start_ms();
		hand_sensor_blink(RED, 300);
		g.flag.module.b_r_led_b = 1;
	}
	return 0;
}
int b_w_led_l(void){
	if(g.flag.module.b_w_led_l == 0){
		g.timer.module.on.w_led_l[0] = timer_restart_s(g.timer.module.work.w_led_l[0]);
		g.timer.module.on.w_led_l[1] = timer_start_ms();
		hand_sensor_light(WHITE);
		g.flag.module.b_w_led_l = 1;
	}
	return 0;
}
int b_w_led_b(void){
	if(g.flag.module.b_w_led_b == 0){
		g.timer.module.on.w_led_b[0] = timer_restart_s(g.timer.module.work.w_led_b[0]);
		g.timer.module.on.w_led_b[1] = timer_start_ms();
		hand_sensor_blink(WHITE, 300);
		g.flag.module.b_w_led_b = 1;
	}
	return 0;
}
/**
 * TODO: Not have flow chart yet
 * @return
 */
int be_1_1(void){
	return 0;
}
