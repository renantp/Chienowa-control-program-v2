/*
 * main.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 */

#include "c_main.h"

#include "runtime.h"
#include "raspberry_pi_communication.h"
#include "../r_cg_serial.h"
#include "module/p_module.h"
#include "../r_cg_dac.h"
#include "module/b_module.h"
#include "hand_sensor.h"
#include "module/t_module.h"

struct GLOBAL g = {
		.mode = HAND_WASHING_MODE,
};

void set_timer_setting_default(struct Timer_Setting_s *g){
	g->t101_h = 10000;
	g->t102_h = 10000;
	g->t103_s = 10;
	g->t104_m = 20;
//	g->t105_;
//	g->t106_;
	g->t107_s = 10;
	g->t108_ms = 3;
//	g->t109_;
//	g->t110_;
//	g->t111_;
//	g->t112_;
	g->t113_s = 5;
	g->t114_s = 5;
	g->t115_s = 5;
	g->t116_s = 5;
	g->t117_s = 5;
	g->t118_s = 5;
	g->t119_s = 15;
	g->t120_ms = 500;
	g->t121_s = 15;
	g->t122_ms = 500;
	g->t123_s = 2;
//	g->t124_;
	g->t125_s = 300;
	g->t126_s = 300;
	g->t127_s = 300;
	g->t128_s = 2;
//	g->t129_;
//	g->t130_;
	g->t131_s = 5;
	g->t132_s = 20;
	g->t133_s = 5;
//	g->t134_;
//	g->t135_;
//	g->t136_;
	g->t137_s = 60;
	g->t138_s = 10;
	g->t139_s = 10;
	g->t140_s = 10;
//	g->t141_;
//	g->t142_;
	g->t143_s = 600;
	g->t144_s = 2;
	g->t145_s = 5;
	g->t146_h = 168;
//	g->t147_;
//	g->t148_;
	g->t149_s = 15;
	g->t150_s = 600;
	g->t151_s = 5;
//	g->t152_;
//	g->t153_;
//	g->t154_;
	g->t155_h = 1;
	g->t156_s = 300;
//	g->t157_;
//	g->t158_;
//	g->t159_;
//	g->t160_;
	g->t161_h = 8;
	g->t162_s = 30;
//	g->t163_;
//	g->t164_;
//	g->t165_;
//	g->t166_;
}
void set_number_setting_default(struct Number_Setting_s *g){
	g->v1_V = 11.5f;
	g->v2_V = 11.0f;
	g->v3_V = 10.5f;
	g->v4_V = 0.0f;
	g->v5_A = 4.0f;
	g->v6_A = 0.0f;
	g->v7_L_m = 7.7f;
	g->v8_L_m = 0.0f;
	g->v9_A = 2.5f;
	g->v10_V = 2.5f;
	g->v11_mg_L = 1.0f;
	g->v12_L = 1.2f;
}

void init(void) {
	R_UART2_Receive(get_pointer_uart_queue(), 6);


	///TODO: This make it don't auto run.
//	set_timer_setting_default();
//	set_number_setting_default();
//	g_V_S.v1_V = 11.5f;
//	g_V_S.v2_V = 11.0f;
//	g_V_S.v3_V = 10.5f;
//	g_V_S.v4_V = 0.0f;
//	g_V_S.v5_A = 4.0f;
//	g_V_S.v6_A = 0.0f;
//	g_V_S.v7_L_m = 7.7f;
//	g_V_S.v8_L_m = 0.0f;
//	g_V_S.v9_A = 2.5f;
//	g_V_S.v10_V = 2.5f;
//	g_V_S.v11_mg_L = 1.0f;
//	g_V_S.v12_L = 1.2f;

}

const uint8_t max = 39;
uint8_t init_flag = 0;
float max_voltage = 5.0f;
float desire_voltage = 2.5f;
uint8_t dac_output;
uint8_t sat;
void loop(void) {
	if(init_flag == 0){
		init_flag = 1;
		set_timer_setting_default(&g_T_S);
		set_number_setting_default(&g_V_S);
		R_DAC0_Set_ConversionValue(0xff * (g_V_S.v9_A / 5.0f));
		R_DAC1_Set_ConversionValue(0xff * (g_V_S.v10_V / 5.0f));
//		sat = 0xff * (5.0f / g_V_S.v10_V);
	}else if(init_flag == 1){
		init_flag = 2;
	}
	runtime();
}
