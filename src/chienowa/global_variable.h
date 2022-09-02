/*
 * global_variable.h
 *
 *  Created on: Jul 25, 2022
 *      Author: Hung
 */

#ifndef CHIENOWA_GLOBAL_VARIABLE_H_
#define CHIENOWA_GLOBAL_VARIABLE_H_

#include "../r_cg_macrodriver.h"
#include "circular_buffer.h"

#define UART_MAX_LEN (6)
#define TIMER_SETTING_MAX (40)
#define SYSTEM_MODE (g.system_mode)
#define WASH_MODE	(g.mode)

#define RESET_ERROR_FLAG		g.flag.reset_button
#define FILTER_COMPLETE_FLAG	g.flag.completion_button

/*************************************************
 * Total working timers & last working timers
 *************************************************/
#define g_P_0_ON_T1		g.timer.module.work.p0[0]
#define g_P_0_ON_T2		g.timer.module.work.p0[1]
#define g_P_1_ON_T1		g.timer.module.work.p1[0]
#define g_P_1_ON_T2		g.timer.module.work.p1[1]
#define g_P_1_1_ON_T1	g.timer.module.work.p11[0]
#define g_P_1_1_ON_T2	g.timer.module.work.p11[1]
#define g_P_1_1_1_ON_T1	g.timer.module.work.p111[0]
#define g_P_1_1_1_ON_T2	g.timer.module.work.p111[1]
#define g_P_1_1_2_ON_T1	g.timer.module.work.p112[0]
#define g_P_1_1_2_ON_T2	g.timer.module.work.p112[1]
#define g_P_1_2_ON_T1	g.timer.module.work.p12[0]
#define g_P_1_2_ON_T2	g.timer.module.work.p12[1]
#define g_P_1_3_ON_T1	g.timer.module.work.p13[0]
#define g_P_1_3_ON_T2	g.timer.module.work.p13[1]
#define g_P_1_4_ON_T1	g.timer.module.work.p14[0]
#define g_P_1_4_ON_T2	g.timer.module.work.p14[1]
#define g_P_1_4_1_ON_T1		g.timer.module.work.p141[0]
#define g_P_1_4_1_ON_T2		g.timer.module.work.p141[1]
#define g_P_1_4_2_ON_T1		g.timer.module.work.p142[0]
#define g_P_1_4_2_ON_T2		g.timer.module.work.p142[1]
#define g_P_1_5_ON_T1	g.timer.module.work.p15[0]
#define g_P_1_5_ON_T2	g.timer.module.work.p15[1]
#define g_P_2_ON_T1		g.timer.module.work.p2[0]
#define g_P_2_ON_T2		g.timer.module.work.p2[1]
#define g_P_2_1_ON_T1	g.timer.module.work.p21[0]
#define g_P_2_1_ON_T2	g.timer.module.work.p21[1]
#define g_P_2_2_ON_T1	g.timer.module.work.p22[0]
#define g_P_2_2_ON_T2	g.timer.module.work.p22[1]
#define g_P_2_3_ON_T1	g.timer.module.work.p23[0]
#define g_P_2_3_ON_T2	g.timer.module.work.p23[1]
#define g_P_2_4_ON_T1	g.timer.module.work.p24[0]
#define g_P_2_4_ON_T2	g.timer.module.work.p24[1]
#define g_P_2_4_1_ON_T1	g.timer.module.work.p241[0]
#define g_P_2_4_1_ON_T2	g.timer.module.work.p241[1]
#define g_P_2_4_1_OFF_T1	g.timer.module.not_work.p241[0]
#define g_P_2_4_1_OFF_T2	g.timer.module.not_work.p241[1]
#define g_P_2_4_2_ON_T1		g.timer.module.work.p242[0]
#define g_P_2_4_2_ON_T2		g.timer.module.work.p242[1]
#define g_P_2_4_2_OFF_T1	g.timer.module.not_work.p242[0]
#define g_P_2_4_2_OFF_T2	g.timer.module.not_work.p242[1]
#define g_P_2_4_3_ON_T1		g.timer.module.work.p243[0]
#define g_P_2_4_3_ON_T2		g.timer.module.work.p243[1]
#define g_P_3_ON_T1		g.timer.module.work.p3[0]
#define g_P_3_ON_T2		g.timer.module.work.p3[1]
#define g_P_3_1_4_ON_T1		g.timer.module.work.p243[0]
#define g_P_3_1_4_ON_T2		g.timer.module.work.p243[1]
#define g_P_8_ON_T1		g.timer.module.work.p8[0]
#define g_P_8_ON_T2		g.timer.module.work.p8[1]

#define g_C_1_ON_T1			g.timer.module.work.c1[0]
#define g_C_1_ON_T2			g.timer.module.work.c1[1]
#define g_C_1_OFF_T2		g.timer.module.not_work.c1[1]
#define g_C_2_ON_T1			g.timer.module.work.c2[0]
#define g_C_2_ON_T2			g.timer.module.work.c2[1]
#define g_C_3_ON_T1			g.timer.module.work.c3[0]
#define g_C_3_ON_T2			g.timer.module.work.c3[1]
#define g_C_4_ON_T1			g.timer.module.work.c4[0]
#define g_C_4_ON_T2			g.timer.module.work.c4[1]
#define g_C_5_ON_T1			g.timer.module.work.c5[0]
#define g_C_5_ON_T2			g.timer.module.work.c5[1]
#define g_C_5_1_ON_T1		g.timer.module.work.c51[0]
#define g_C_5_1_ON_T2		g.timer.module.work.c51[1]
#define g_C_5_2_ON_T1		g.timer.module.work.c52[0]
#define g_C_5_2_ON_T2		g.timer.module.work.c52[1]
#define g_C_5_3_ON_T1		g.timer.module.work.c53[0]
#define g_C_5_3_ON_T2		g.timer.module.work.c53[1]
#define g_C_5_3_1_ON_T1		g.timer.module.work.c531[0]
#define g_C_5_3_1_ON_T2		g.timer.module.work.c531[1]
#define g_C_5_4_ON_T1		g.timer.module.work.c54[0]
#define g_C_5_4_ON_T2		g.timer.module.work.c54[1]
#define g_C_5_5_ON_T1		g.timer.module.work.c55[0]
#define g_C_5_5_ON_T2		g.timer.module.work.c55[1]
#define g_C_5_6_ON_T1		g.timer.module.work.c56[0]
#define g_C_5_6_ON_T2		g.timer.module.work.c56[1]
#define g_C_6_ON_T1			g.timer.module.work.c6[0]
#define g_C_6_ON_T2			g.timer.module.work.c6[1]
#define g_C_7_ON_T1			g.timer.module.work.c7[0]
#define g_C_7_ON_T2			g.timer.module.work.c7[1]
#define g_C_8_ON_T1			g.timer.module.work.c8[0]
#define g_C_8_ON_T2			g.timer.module.work.c8[1]
#define g_C_9_ON_T1			g.timer.module.work.c9[0]
#define g_C_9_ON_T2			g.timer.module.work.c9[1]
#define g_C_10_ON_T1			g.timer.module.work.c10[0]
#define g_C_10_ON_T2			g.timer.module.work.c10[1]
#define g_C_11_ON_T1			g.timer.module.work.c11[0]
#define g_C_11_ON_T2			g.timer.module.work.c11[1]
#define g_C_12_ON_T1			g.timer.module.work.c12[0]
#define g_C_12_ON_T2			g.timer.module.work.c12[1]
#define g_C_13_ON_T1			g.timer.module.work.c13[0]
#define g_C_13_ON_T2			g.timer.module.work.c13[1]
#define g_C_14_ON_T1			g.timer.module.work.c14[0]
#define g_C_14_ON_T2			g.timer.module.work.c14[1]
#define g_C_15_ON_T1			g.timer.module.work.c15[0]
#define g_C_15_ON_T2			g.timer.module.work.c15[1]
#define g_C_16_ON_T1			g.timer.module.work.c16[0]
#define g_C_16_ON_T2			g.timer.module.work.c16[1]
#define g_C_17_ON_T1			g.timer.module.work.c17[0]
#define g_C_17_ON_T2			g.timer.module.work.c17[1]
#define g_C_18_ON_T1			g.timer.module.work.c18[0]
#define g_C_18_ON_T2			g.timer.module.work.c18[1]
#define g_C_19_ON_T1			g.timer.module.work.c19[0]
#define g_C_19_ON_T2			g.timer.module.work.c19[1]

#define g_E_1_ON_T1			g.timer.module.work.e1[0]
#define g_E_1_ON_T2			g.timer.module.work.e1[1]

#define g_SV1_ON_T1			g.timer.module.work.io.sv1[0]
#define g_SV1_ON_T2			g.timer.module.work.io.sv1[1]
#define g_SV1_ON_T3			g.timer.module.work.io.sv1[2]
#define g_SV2_ON_T1			g.timer.module.work.io.sv2[0]
#define g_SV2_ON_T2			g.timer.module.work.io.sv2[1]
#define g_SV2_ON_T3			g.timer.module.work.io.sv2[2]
#define g_SV3_ON_T1			g.timer.module.work.io.sv3[0]
#define g_SV3_ON_T2			g.timer.module.work.io.sv3[1]
#define g_SV3_ON_T3			g.timer.module.work.io.sv3[2]
#define g_SV4_ON_T1			g.timer.module.work.io.sv4[0]
#define g_SV4_ON_T2			g.timer.module.work.io.sv4[1]
#define g_SV4_ON_T3			g.timer.module.work.io.sv4[2]
#define g_SV5_ON_T1			g.timer.module.work.io.sv5[0]
#define g_SV5_ON_T2			g.timer.module.work.io.sv5[1]
#define g_SV5_ON_T3			g.timer.module.work.io.sv5[2]
#define g_SV6_ON_T1			g.timer.module.work.io.sv6[0]
#define g_SV6_ON_T2			g.timer.module.work.io.sv6[1]
#define g_SV6_ON_T3			g.timer.module.work.io.sv6[2]
#define g_SV7_ON_T1			g.timer.module.work.io.sv7[0]
#define g_SV7_ON_T2			g.timer.module.work.io.sv7[1]
#define g_SV7_ON_T3			g.timer.module.work.io.sv7[2]
#define g_P1_ON_T1			g.timer.module.work.io.p1[0]
#define g_P1_ON_T2			g.timer.module.work.io.p1[1]
#define g_P1_ON_T3			g.timer.module.work.io.p1[2]
#define g_P2_ON_T1			g.timer.module.work.io.p2[0]
#define g_P2_ON_T2			g.timer.module.work.io.p2[1]
#define g_P2_ON_T3			g.timer.module.work.io.p2[2]
#define g_SP_ON_T1			g.timer.module.work.io.sp[0]
#define g_SP_ON_T2			g.timer.module.work.io.sp[1]
#define g_SP_ON_T3			g.timer.module.work.io.sp[2]

#define C_5_5_20T		g.timer.c55_20

/*************************************************
 * Module Flags
 *************************************************/
#define g_P_0_F			g.flag.module.bp0
#define g_P_1_F			g.flag.module.bp1
#define g_P_1_1_F		g.flag.module.bp11
#define g_P_1_1_1_F		g.flag.module.bp111
#define g_P_1_1_2_F		g.flag.module.bp112
#define g_P_1_2_F		g.flag.module.bp12
#define g_P_1_3_F		g.flag.module.bp13
#define g_P_1_4_F		g.flag.module.bp14
#define g_P_1_4_1_F		g.flag.module.bp141
#define g_P_1_4_2_F		g.flag.module.bp142
#define g_P_1_5_F		g.flag.module.bp15
#define g_P_2_F			g.flag.module.bp2
#define g_P_2_1_F		g.flag.module.bp21
#define g_P_2_2_F		g.flag.module.bp22
#define g_P_2_3_F		g.flag.module.bp23
#define g_P_2_4_F		g.flag.module.bp24
#define g_P_2_4_1_F		g.flag.module.bp241
#define g_P_2_4_2_F		g.flag.module.bp242
#define g_P_2_4_3_F		g.flag.module.bp243
#define g_P_3_F			g.flag.module.bp3
#define g_P_3_1_4_F			g.flag.module.bp314
#define g_P_8_F			g.flag.module.bp8

#define g_C_1_F			g.flag.module.bc1
#define g_C_2_F			g.flag.module.bc2
#define g_C_3_F			g.flag.module.bc3
#define g_C_4_F			g.flag.module.bc4
#define g_C_5_F			g.flag.module.bc5
#define g_C_5_1_F			g.flag.module.bc51
#define g_C_5_2_F			g.flag.module.bc52
#define g_C_5_3_F			g.flag.module.bc53
#define g_C_5_3_1_F			g.flag.module.bc531
#define g_C_5_4_F			g.flag.module.bc54
#define g_C_5_5_F			g.flag.module.bc55
#define g_C_5_6_F			g.flag.module.bc56
#define g_C_6_F			g.flag.module.bc6
#define g_C_7_F			g.flag.module.bc7
#define g_C_8_F			g.flag.module.bc8
#define g_C_9_F			g.flag.module.bc9
#define g_C_10_F			g.flag.module.bc10
#define g_C_11_F			g.flag.module.bc11
#define g_C_12_F			g.flag.module.bc12
#define g_C_13_F			g.flag.module.bc13
#define g_C_14_F			g.flag.module.bc14
#define g_C_15_F			g.flag.module.bc15
#define g_C_16_F			g.flag.module.bc16
#define g_C_17_F			g.flag.module.bc17
#define g_C_18_F			g.flag.module.bc18
#define g_C_19_F			g.flag.module.bc19
#define g_C_23_F			g.flag.module.bc23

#define g_E_1_F			g.flag.module.e1
#define g_E_2_F			g.flag.module.e2

/*************************************************
 * IO Flags
 *************************************************/

#define g_P1_F			g.io.pump_1
#define g_P2_F			g.io.pump_2
#define g_SP_F			g.io.salt_pump

/*************************************************
 *
 *************************************************/
#define C_1_ON_T2		g.timer.module.on.c1[1]
#define C_1_ON_T3		g.timer.module.on.c1[2]
#define C_1_OFF_T1		g.timer.module.off.c1[0]
#define C_5_2_ON_T3		g.timer.module.on.c52[2]
#define C_5_4_ON_T3		g.timer.module.on.c54[2]
#define SP_OFF_T2		g.timer.module.off.io.sp[1]
#define SP_ON_T2		g.timer.module.on.io.sp[1]

#define SV7_ON_T2		g.timer.module.on.io.sv7[1]
#define SV1_ON_T1		g.timer.module.on.io.sv1[0]
#define SV2_ON_T1		g.timer.module.on.io.sv2[0]
#define SV1_ON_T2		g.timer.module.on.io.sv1[1]
#define SV1_ON_T3		g.timer.module.on.io.sv1[2]
#define SV2_ON_T3		g.timer.module.on.io.sv2[2]
#define C_8_T3			g.timer.module.on.c8[2]
#define C_10_ON_T3		g.timer.module.on.c10[2]
#define C_21_T2			g.timer.module.on.c21[1]

#define C_10_F			g.flag.module.c10
#define E_1008_CVCC_STOP_F	g.flag.e_1008_cvcc_stop
#define E_1020_CVCC_STOP_F	g.flag.e_1020_cvcc_stop
#define E_1022_CVCC_STOP_F	g.flag.e_1022_cvcc_stop
#define E_1026_CVCC_STOP_F	g.flag.e_1026_cvcc_stop
#define M1030_F				g.flag.m1030

#define FAUCET_OFF_T		g.timer.faucet_off
#define WATER_DISCHARGE_T	(2)
#define ACID_DISCHARGE_T	(3)
#define ALKALI_DISCHARGE_T	(4)

extern uint8_t g_uart2_rx_data[UART_MAX_LEN], g_uart2_tx_data[UART_MAX_LEN];
extern circular_buffer g_rx_data;
extern volatile int8_t g_uart2_recieve_end, g_uart2_send_end;
extern volatile int8_t g_csi01_flag;
extern uint32_t g_count;
extern struct Timer_Setting_s{
	uint16_t t101_h;
	uint16_t t102_h;
	uint16_t t103_s;
	uint16_t t104_m;
	uint16_t t105_;
	uint16_t t106_;
	uint16_t t107_s;
	uint16_t t108_m;
	uint16_t t109_;
	uint16_t t110_;
	uint16_t t111_;
	uint16_t t112_;
	uint16_t t113_s;
	uint16_t t114_s;
	uint16_t t115_s;
	uint16_t t116_s;
	uint16_t t117_s;
	uint16_t t118_s;
	uint16_t t119_s;
	uint16_t t120_ms;
	uint16_t t121_s;
	uint16_t t122_ms;
	uint16_t t123_s;
	uint16_t t124_;
	uint16_t t125_s;
	uint16_t t126_s;
	uint16_t t127_s;
	uint16_t t128_s;
	uint16_t t129_;
	uint16_t t130_;
	uint16_t t131_s;
	uint16_t t132_s;
	uint16_t t133_s;
	uint16_t t134_;
	uint16_t t135_;
	uint16_t t136_;
	uint16_t t137_s;
	uint16_t t138_s;
	uint16_t t139_s;
	uint16_t t140_s;
	uint16_t t141_;
	uint16_t t142_;
	uint16_t t143_s;
	uint16_t t144_s;
	uint16_t t145_s;
	uint16_t t146_h;
	uint16_t t147_;
	uint16_t t148_;
	uint16_t t149_s;
	uint16_t t150_s;
	uint16_t t151_s;
	uint16_t t152_;
	uint16_t t153_;
	uint16_t t154_;
	uint16_t t155_h;
	uint16_t t156_s;
	uint16_t t157_;
	uint16_t t158_;
	uint16_t t159_;
	uint16_t t160_;
	uint16_t t161_h;
	uint16_t t162_s;
	uint16_t t163_;
	uint16_t t164_;
	uint16_t t165_;
	uint16_t t166_;

	uint16_t crc;
}g_T_S, g_T_S_buffer;
extern struct Number_Setting_s {
	float v1_V;
	float v2_V;
	float v3_V;
	float v4_V;
	float v5_A;
	float v6_A;
	float v7_L_m;
	float v8_L_m;
	float v9_A;
	float v10_V;
	float v11_mg_L;
	float v12_L;
	uint32_t crc;
} g_V_S, g_V_S_buffer;

enum WASH_MODE_E {
	WASH_MODE_INIT,
	HAND_WASHING_MODE,
	WATER_MODE,
	ACID_MODE,
	ALKALI_MODE
};
enum STATUS {
	NORMAL,
	INDIVIDUAL,
	WASHING,
};
struct IO_Struct{
	uint8_t fl1: 1;
	uint8_t fl2: 1;
	uint8_t fl3: 1;
	uint8_t fl4: 1;
	uint8_t fl5: 1;
	uint8_t fl6: 1;
	uint8_t fl7: 1;
	uint8_t fl8: 1;

	struct{
		uint8_t sv1: 1;
		uint8_t sv2: 1;
		uint8_t sv3: 1;
		uint8_t sv4: 1;
		uint8_t sv5: 1;
		uint8_t sv6: 1;
		uint8_t sv7: 1;
		uint8_t sv8: 1;

		uint8_t sw1: 1;
		uint8_t sw2: 1;
		uint8_t sw3: 1;
		uint8_t RSVD: 5; //	Reserved
	}valve; // 2 byte

	uint8_t pump_1: 1;
	uint8_t pump_2: 1;
	uint8_t salt_pump: 1;
	uint8_t cvcc_control: 1;
	uint8_t cvcc_alarm_out : 1;
	uint8_t cvcc_alarm_in: 1;
	uint8_t RSVD1: 2; // Reserved
};
union B_MODULE_F {
	struct {
		uint8_t bp0 : 1;
		uint8_t bp1 : 1;
		uint8_t bp2	: 1;
		uint8_t bp3 : 1;
//		uint8_t bp4 : 1;
		uint8_t bp8 : 1;

		uint8_t bp11 : 1;
		uint8_t bp12 : 1;
		uint8_t bp13 : 1;
		uint8_t bp14 : 1;
		uint8_t bp15 : 1;
		uint8_t bp21 : 1;
		uint8_t bp22 : 1;
		uint8_t bp23 : 1;
		uint8_t bp24 : 1;
		uint8_t bp314 : 1;

		uint8_t bp111 : 1;
		uint8_t bp112 : 1;
		uint8_t bp141 : 1;
		uint8_t bp142 : 1;
		uint8_t bp241 : 1;
		uint8_t bp242 : 1;
		uint8_t bp243 : 1;

		uint8_t bc1 : 1;
		uint8_t bc2 : 1;
		uint8_t bc3 : 1;
		uint8_t bc4 : 1;
		uint8_t bc5 : 1;
		uint8_t bc6 : 1;
		uint8_t bc7 : 1;
		uint8_t bc8 : 1;
		uint8_t bc9 : 1;
		uint8_t bc10 : 1;
		uint8_t bc11 : 1;
		uint8_t bc12 : 1;
		uint8_t bc13 : 1;
		uint8_t bc14 : 1;
		uint8_t bc15 : 1;
		uint8_t bc16 : 1;
		uint8_t bc17 : 1;
		uint8_t bc18 : 1;
		uint8_t bc19 : 1;
		uint8_t bc23 : 1;

		uint8_t bc51 : 1;
		uint8_t bc52 : 1;
		uint8_t bc53 : 1;
		uint8_t bc54 : 1;
		uint8_t bc55 : 1;
		uint8_t bc56 : 1;

		uint8_t bc531 : 1;

		uint8_t be1 : 1;
		uint8_t b_b_led_l : 1;
		uint8_t b_b_led_b : 1;
		uint8_t b_r_led_l : 1;
		uint8_t b_r_led_b : 1;
		uint8_t b_w_led_l : 1;
		uint8_t b_w_led_b : 1;

		uint8_t c1 : 1;
		uint8_t c2 : 1;
		uint8_t c52: 1;
		uint8_t c54 : 1;
		uint8_t c8 : 1;
		uint8_t c10 : 1;
		uint8_t c14 : 1;
		uint8_t c20 : 1;

		uint8_t e1 : 1;
		uint8_t e1028 : 1;
		uint8_t e1029 : 1;
		uint8_t e1032 : 1;
		uint8_t e1033 : 1;
		uint8_t e1034 : 1;
		uint8_t e1035 : 1;
	};
	uint8_t raw[32];
};

struct Module_Timer{
	uint32_t p0[2];
	uint32_t p1[2];
	uint32_t p2[2];
	uint32_t p3[2];
//	uint32_t p4[2];
	uint32_t p8[2];

	uint32_t p11[2];
	uint32_t p12[2];
	uint32_t p13[2];
	uint32_t p14[2];
	uint32_t p15[2];
	uint32_t p21[2];
	uint32_t p22[2];
	uint32_t p23[2];
	uint32_t p24[2];
	uint32_t p314[2];

	uint32_t p111[2];
	uint32_t p112[2];
	uint32_t p141[2];
	uint32_t p142[2];
	uint32_t p241[2];
	uint32_t p242[2];
	uint32_t p243[2];

	uint32_t c1[3];
	uint32_t c2[2];
	uint32_t c3[2];
	uint32_t c4[2];
	uint32_t c5[2];
	uint32_t c6[2];
	uint32_t c7[2];
	uint32_t c8[3];
	uint32_t c9[2];
	uint32_t c10[3];
	uint32_t c11[2];
	uint32_t c12[2];
	uint32_t c13[2];
	uint32_t c14[2];
	uint32_t c15[2];
	uint32_t c16[2];
	uint32_t c17[2];
	uint32_t c18[2];
	uint32_t c19[2];
	uint32_t c21[2];

	uint32_t c51[2];
	uint32_t c52[3];
	uint32_t c53[3];
	uint32_t c54[3];
	uint32_t c55[2];
	uint32_t c56[2];

	uint32_t c531[2];

	uint32_t e1[2];

	uint32_t b_led_l[2];
	uint32_t b_led_b[2];
	uint32_t r_led_l[2];
	uint32_t r_led_b[2];
	uint32_t w_led_l[2];
	uint32_t w_led_b[2];
	struct{
		uint32_t sv1[3];
		uint32_t sv2[3];
		uint32_t sv3[3];
		uint32_t sv4[3];
		uint32_t sv5[3];
		uint32_t sv6[3];
		uint32_t sv7[3];

		uint32_t p1[3];
		uint32_t p2[3];
		uint32_t sp[3];
	}io;
};

struct Timer {
	struct Module_Timer work; //Total working time (0) and lasted working time (1)
	struct Module_Timer not_work;
	struct Module_Timer on;
	struct Module_Timer off;
};

#define NUMBER_OF_IO_BYTE				(4 + 12)
#define NUMBER_OF_TIMER_SETTING_BYTE	(sizeof(g_T_S))
#define NUMBER_OF_NUMBER_SETTING_BYTE	(sizeof(g_V_S))

extern struct GLOBAL{
	struct {
		uint8_t electrolysis;
		uint8_t cvcc_run;
		uint8_t c22_start;
		uint8_t hand_sensor;
		uint8_t alkali_drainning;
		uint8_t acid_drainning;
		uint8_t individual;
		struct IO_Struct io;
		union B_MODULE_F module;
		uint8_t c55_20;
		uint8_t c55_10;
		uint8_t leak_sensor;
		uint8_t e_1008_cvcc_stop;
		uint8_t e_1020_cvcc_stop;
		uint8_t e_1022_cvcc_stop;
		uint8_t e_1026_cvcc_stop;
		uint8_t m1030;
		//For error button handle
		uint8_t reset_button,
		completion_button,
		setting_button;
	}flag;

	struct{
		uint32_t c1_on;
		uint32_t faucet_off;
		uint32_t water_discharge;
		uint32_t alkali_discharge;
		uint32_t acid_discharge;
		struct Timer module;
		uint32_t c55_20;
	}timer;
	struct IO_Struct io;
	float flow_rate;
	float cvvc_voltage; // 4 bytes
	float cvcc_current; // 4 bytes
	union {
		struct{
			uint8_t drain :1;
			uint8_t power_on :1;
			uint8_t filter :1;
			uint8_t biomectric :1;
			uint8_t RSVD :4;
		};
		uint32_t raw;
	}control_setting;
	uint8_t system_mode;
	enum WASH_MODE_E mode, previous_mode;
	enum STATUS status;
}g;


#endif /* CHIENOWA_GLOBAL_VARIABLE_H_ */
