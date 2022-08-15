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
}g_timerSetting;
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

enum WASH_MODE {
	HAND_WASHING_MODE,
	WATER_MODE,
	ACID_MODE,
	ALKALI_MODE
};
enum STATUS {
	NORMAL
};

extern struct GLOBAL{
	struct {
		uint8_t electrolysis;
		uint8_t cvcc_run;
		uint8_t c22_start;
		uint8_t hand_sensor;
	}flag;
	uint8_t system_mode;
	enum WASH_MODE mode, previous_mode;
	enum STATUS status;
}g;


#endif /* CHIENOWA_GLOBAL_VARIABLE_H_ */
