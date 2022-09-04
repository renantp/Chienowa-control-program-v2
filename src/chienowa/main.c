/*
 * main.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 */

#include "main.h"
#include "runtime.h"
#include "raspberry_pi_communication.h"
#include "../r_cg_serial.h"
#include "module/p_module.h"
#include "../r_cg_dac.h"
#include "module/b_module.h"

struct GLOBAL g = {
		.mode = HAND_WASHING_MODE,
};
eeprom_config e_config = { .csi_flag = &g_csi01_flag, .csi_send_receive =
		R_CSI01_Send_Receive };
struct Number_Setting_s g_V_S, g_V_S_buffer;
struct Timer_Setting_s g_T_S, g_T_S_buffer;
void set_timer_setting_default(void){
	g_T_S.t101_h = 10000;
	g_T_S.t102_h = 10000;
	g_T_S.t103_s = 10;
	g_T_S.t104_m = 20;
//	g_T_S.t105_;
//	g_T_S.t106_;
	g_T_S.t107_s = 10;
	g_T_S.t108_m = 3;
//	g_T_S.t109_;
//	g_T_S.t110_;
//	g_T_S.t111_;
//	g_T_S.t112_;
	g_T_S.t113_s = 5;
	g_T_S.t114_s = 5;
	g_T_S.t115_s = 5;
	g_T_S.t116_s = 5;
	g_T_S.t117_s = 5;
	g_T_S.t118_s = 5;
	g_T_S.t119_s = 15;
	g_T_S.t120_ms = 500;
	g_T_S.t121_s = 15;
	g_T_S.t122_ms = 500;
	g_T_S.t123_s = 2;
//	g_T_S.t124_;
	g_T_S.t125_s = 300;
	g_T_S.t126_s = 300;
	g_T_S.t127_s = 300;
	g_T_S.t128_s = 2;
//	g_T_S.t129_;
//	g_T_S.t130_;
	g_T_S.t131_s = 5;
	g_T_S.t132_s = 20;
	g_T_S.t133_s = 5;
//	g_T_S.t134_;
//	g_T_S.t135_;
//	g_T_S.t136_;
	g_T_S.t137_s = 60;
	g_T_S.t138_s = 10;
	g_T_S.t139_s = 10;
	g_T_S.t140_s = 10;
//	g_T_S.t141_;
//	g_T_S.t142_;
	g_T_S.t143_s = 600;
	g_T_S.t144_s = 2;
	g_T_S.t145_s = 5;
	g_T_S.t146_h = 168;
//	g_T_S.t147_;
//	g_T_S.t148_;
	g_T_S.t149_s = 15U * 60;
	g_T_S.t150_s = 600;
	g_T_S.t151_s = 5;
//	g_T_S.t152_;
//	g_T_S.t153_;
//	g_T_S.t154_;
	g_T_S.t155_h = 1;
	g_T_S.t156_s = 300;
//	g_T_S.t157_;
//	g_T_S.t158_;
//	g_T_S.t159_;
//	g_T_S.t160_;
	g_T_S.t161_h = 8;
	g_T_S.t162_s = 30;
//	g_T_S.t163_;
//	g_T_S.t164_;
//	g_T_S.t165_;
//	g_T_S.t166_;
}
void set_number_setting_default(void){
	g_V_S.v1_V = 11.5f;
	g_V_S.v2_V = 11.0f;
	g_V_S.v3_V = 10.5f;
	g_V_S.v4_V = 0.0f;
	g_V_S.v5_A = 4.0f;
	g_V_S.v6_A = 0.0f;
	g_V_S.v7_L_m = 7.7f;
	g_V_S.v8_L_m = 0.0f;
	g_V_S.v9_A = 2.5f;
	g_V_S.v10_V = 2.5f;
	g_V_S.v11_mg_L = 1.0f;
	g_V_S.v12_L = 1.2f;
}
void init(void) {
	R_UART2_Receive(get_pointer_uart_queue(), 6);

	// EEPROM initialize
	if (eeprom_init(&e_config) == 0) {
		eeprom_set_block(NONE_BLOCK);
	}

	// Set setting to default
	set_timer_setting_default();
	set_number_setting_default();

	uint8_t cur = 0xff * (float)(g_V_S.v9_A / 5.0f);
	uint8_t sat = 0xff * (float)(g_V_S.v10_V / 5.0f);

	R_DAC0_Set_ConversionValue(cur);
	R_DAC1_Set_ConversionValue(sat);
	b_w_led_b();
}

const uint8_t max = 39;
uint16_t sended, checked;
void loop(void) {
	p_0();
	runtime();
}
