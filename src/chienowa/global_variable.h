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
	uint8_t CVCC_ON: 1;
	uint8_t HandSensorON: 1;
	uint8_t HandSensorOFF: 1;
	uint8_t RSVD1: 2; // Reserved
};
extern struct GLOBAL{
	struct {
		uint8_t electrolysis;
		uint8_t cvcc_run;
		uint8_t c1;
		uint8_t c22_start;
		uint8_t hand_sensor;
		uint8_t alkali_drainning;
		uint8_t acid_drainning;

		uint8_t individual;
		struct IO_Struct io;
	}flag;
	struct{
		uint32_t c1_on;
		uint32_t faucet_off;
		uint32_t water_discharge;
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
