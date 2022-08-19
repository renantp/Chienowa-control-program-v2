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

#define P_1_5_F			g.flag.module.bp15
#define P_1_5_ON_T1		g.timer.module.work.p15[0]
#define P_1_5_ON_T2		g.timer.module.work.p15[1]
#define C_1_ON_T3		g.timer.module.on.c1[2]
#define C_1_OFF_T1		g.timer.module.off.c1[0]
#define C_1_OFF_T2		g.timer.module.off.c1[1]
#define SP_OFF_T2		g.timer.off.salt_pump[0]
#define SP_ON_T2		g.timer.on.salt_pump[1]

extern uint8_t g_uart2_rx_data[UART_MAX_LEN], g_uart2_tx_data[UART_MAX_LEN];
extern circular_buffer g_rx_data;
extern volatile int8_t g_uart2_recieve_end, g_uart2_send_end;
extern volatile int8_t g_csi01_flag;
extern uint32_t g_count;

extern struct Timer_Setting_s{
	uint16_t t1_ms;
	uint16_t t2_s;
	uint16_t t3_s;
	uint16_t t4_2_s;
	uint16_t t5_s;
	uint16_t t6_h;
	uint16_t t7_s;
	uint16_t t8_s;
	uint16_t t9_s;
	uint16_t t10_s;
	uint16_t t11_s;
	uint16_t t12_s;
	uint16_t t13_s;
	uint16_t t14_s;
	uint16_t t15_s;
	uint16_t t16_s;
	uint16_t t17_s;
	uint16_t t18_h;
	uint16_t t19_h;
	uint16_t t20_h;
	uint16_t t21_s;
	uint16_t t22_s;
	uint16_t t23_s;
	uint16_t t24_s;
	uint16_t t25_s;
	uint16_t t26_s;
	uint16_t t27_h;
	uint16_t t28_s;
	uint16_t t29_s;
	uint16_t t30_s;
	uint16_t t31_s;
	uint16_t t32_ms;
	uint16_t t33_s;
	uint16_t t34_s;
	uint16_t t35_s;
	uint16_t t36;
	uint16_t t37;
	uint16_t t38_s;
	uint16_t t39_h;
	uint16_t t40_s;
	char crc;
}g_T_S;
extern struct Number_Setting_s {
	float upperVoltage1;
	float upperVoltage2;
	float upperVoltage3;
	float lowerVoltage;
	float upperCurrent;
	float lowerCurrent;
	float upperFlow;
	float lowerFlow;
	float cvccCurrent;
	float saltPumpVoltage;
	char crc;
} g_numberSetting;

enum WASH_MODE_E {
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
	uint8_t AlkalineEmptyLevel: 1;
	uint8_t AlkalineLowLevel: 1;
	uint8_t AlkalineHighLevel: 1;
	uint8_t AcidEmptyLevel: 1;
	uint8_t AcidLowLevel: 1;
	uint8_t AcidHighLevel: 1;
	uint8_t SaltLowLevel: 1;
	uint8_t SaltHighLevel: 1;

	struct{
		uint8_t sv1: 1;
		uint8_t sv2: 1;
		uint8_t sv3: 1;
		uint8_t sv4: 1;
		uint8_t sv5: 1;
		uint8_t sv6: 1;
		uint8_t sv7: 1;
		uint8_t sv8: 1;

		uint8_t RSVD: 8; //	Reserved
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

		uint8_t e1 : 1;
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
	uint32_t c8[2];
	uint32_t c9[2];
	uint32_t c10[2];
	uint32_t c11[2];
	uint32_t c12[2];
	uint32_t c13[2];
	uint32_t c14[2];
	uint32_t c15[2];
	uint32_t c16[2];
	uint32_t c17[2];
	uint32_t c18[2];
	uint32_t c19[2];

	uint32_t c51[2];
	uint32_t c52[2];
	uint32_t c53[2];
	uint32_t c54[2];
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
		uint32_t sv1[2];
		uint32_t sv2[2];
		uint32_t sv3[2];
		uint32_t sv4[2];
		uint32_t sv5[2];
		uint32_t sv6[2];
		uint32_t sv7[2];

		uint32_t p1[2];
		uint32_t p2[2];
		uint32_t sp[2];
	}io;
};

struct Timer {
	struct Module_Timer work; //Total working time (0) and lasted working time (1)
	struct Module_Timer not_work;
	struct Module_Timer on;
	struct Module_Timer off;
};

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
	}flag;

	struct{
		uint32_t c1_on;
		uint32_t faucet_off;
		uint32_t water_discharge;
		uint32_t alkali_discharge;
		uint32_t acid_discharge;
		struct Timer module;
		struct{
			uint32_t salt_pump[2];
		}on, off;
	}timer;

	struct IO_Struct io;
//	struct {
//		union{
//
//		};
//	}error;
	uint8_t system_mode;
	enum WASH_MODE_E mode, previous_mode;
	enum STATUS status;
}g;


#endif /* CHIENOWA_GLOBAL_VARIABLE_H_ */
