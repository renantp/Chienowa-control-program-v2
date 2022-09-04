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
#include "../hand_sensor.h"

#define MINUTES_TO_MS	(60UL * 1000)
#define SEC_TO_MS(s)	(1000UL * (s))
// TODO Need to implement
int p3_individual_test(void) {
	return 0;
}
/* end things need to implement */


/**
 * Don't need this function
 * @return System mode
 */
int p(void) {
	return SYSTEM_MODE;
}

int p_0(void){
	bp_0();
	p_1();
	switch (SYSTEM_MODE) {
		case 0:
			p_2();
			break;
		case 1:
			p3_individual_test();
			break;
		default:
			//Not going here
			p_2();
			break;
	}
	return 0;
}
/**
 * Change name and check valid 02092022
 * @return
 */
int p_1(void) {									//初期動作モード
	bp_1();                                     //初期動作モード起動水処理
	p_1_1();                                    //初期抜水処理
	p_1_2();                                    //初期給水処理
	c_3();                                      //塩Tankチェック処理
	c_5();                                      //電解業務チェック処理
	p_1_3();                                    //初期Electrolysis水生成処理
	p_1_4();                                    //初期抜水第２処理
	p_1_5();                                   //Electrolysis水作成第２処理
	p_1_1();                                    //replace p15 by this p11
	tp_1();                                     //初期動作モードStop process
	return 0;
}
/**
 * Checked in hardware 31082022
 * Change name and check valid 02092022
 * @return
 */
int p_1_1(void) {
	bp_1_1();
	p_1_1_1();
	tp_1_1();
	return 0;
}
/**
 * 初期両タンク抜水処理
 * Checked in hardware 31082022
 * Change name and check valid 02092022
 * @return
 */
int p_1_1_1(void){
	//両タンク抜水起動処理
	bp_1_1_1();
	//アルタンク空ではない
	if(s1_alkali_tank_data_set > 0){
		b_sv6();
		wait(500);
		b_p2();
		g.flag.alkali_drainning = 1;
	}
	//酸タンク空ではない && g_ACD > 0を追加　イシイ
	if(s2_acid_tank_data_set() > 0){
		b_sv5();
		wait(500);
		b_p1();
		g.flag.acid_drainning = 1;
	}
	//タンク空確認
	while(g_ALD > 0 || g_ACD > 0){
		runtime();
		if(s1_alkali_tank_data_set() >= 0){
			if(g.flag.alkali_drainning == 1){
				g.flag.alkali_drainning = 0;
				//アルカリタンク抜水一時停止処理
				p_1_1_2();
			}
		}
		if(s2_acid_tank_data_set() >= 0){
			if(g.flag.acid_drainning == 1){
				g.flag.acid_drainning = 0;
				//酸タンク抜水一時停止処理
				p_1_1_3();
			}
		}
	}
	//アルカリタンク抜水最終処理
	p_1_1_4();
	//酸タンク抜水最終処理
	p_1_1_5();
	//両タンク抜水停止処理
	tp_1_1_1();
	return 0;
}
/**
 * アルカリタンク抜水一時停止処理
 * Rename and check valid 02092022
 * @return
 */
int p_1_1_2(void){
	t_p2();
	t_sv6();
	return 0;
}
/**
 * 酸タンク抜水一時停止処理
 * Rename and check valid 02092022
 * @return
 */
int p_1_1_3(void){
	t_p1();
	t_sv5();
	return 0;
}
/**
 * アルカリタンク抜水最終停止処理
 * Rename and check valid 02092022
 * @return
 */
int p_1_1_4(void){
	b_sv6();
	wait(500);
	b_p2();
	//g_T_S.t1_msをg_T_S.t108_Mに修正 (CY)
	wait(MINUTES_TO_MS * g_T_S.t108_m);
	t_p2();
	t_sv6();
	return 0;
}
/**
 * 酸タンク抜水最終停止処理
 * Rename and check valid 02092022.
 * @return
 */
int p_1_1_5(void){
	b_sv5();
	wait(500);
	b_p1();
	//g_T_S.t1_msをg_T_S.t108_Mに修正 (CY)
	wait(MINUTES_TO_MS * g_T_S.t108_m);
	t_p1();
	t_sv5();
	return 0;
}
/**
 * 初期給水処理
 * Rename and check valid 02092022
 * @return
 */
int p_1_2(void) {
	//初期給水起動処理
	bp_1_2();
	b_sv2();
	wait(SEC_TO_MS(30));
	b_sv1();
	wait(500);
	t_sv2();
	//g_T_S.t2_msをg_T_S.t149_sに修正 (CY)
	wait(SEC_TO_MS(g_T_S.t149_s));
	p_3_13_flow_rate_process();
	tp_1_2();
	return 0;
}
/**
 * 初期 Electrolyte 水生成処理
 * Rename and check valid 02092022
 * @return
 */
int p_1_3(void) {
	// 初期ElectrolysisStart処理
	p_1_3_1();
	do {
		s1_alkali_tank_data_set();
		s2_acid_tank_data_set();
		c_5();
		runtime();
	} while (g_ALD != 3 || g_ACD != 3);
	p_1_3_2();
	return 0;
}

int neutralized_timer_on(void) {
	g.timer.c1_on = timer_start_ms();
	return g.timer.c1_on;
}
int neutralized_timer_off(void) {
	return timer_stop_ms(g.timer.c1_on);
}
/**
 * 初期電解起動t処理
 *
 * @return
 */
int p_1_3_1(void) {
	b_sv1();
	b_sp_start();
	// g_T_S.t16_sをg_T_S.t107_Sに修正 (CY)
	wait(SEC_TO_MS(g_T_S.t107_s));
	// 初期Electrolyte終了処理
	bp_1_3();
	neutralized_timer_on();
	g.timer.faucet_off = timer_start_ms();
	return 0;
}
/**
 * 初期ElectrolysisStart終了処理
 * Rename and check valid 02092022
 * @return
 */
int p_1_3_2(void) {
	tp_1_3(); //CVCC OFF
	t_sp();
	// g_T_S.t5_sをg_T_S.t145_sに修正 (CY)
	wait(SEC_TO_MS(g_T_S.t145_s));
	t_sv1();
	neutralized_timer_off();
	return 0;
}
/**
 * 初期抜水第２処理
 * Rename and check valid 02092022
 * @return
 */
int p_1_4(void) {
	bp_1_4();
	//初期両タンク抜水処理
	p_1_1_1();
	tp_1_4();
	return 0;
}
/**
 * Electrolyte Process Second Time
 * Rename and check valid 02092022
 * @return
 */
int p_1_5(void) {
	/* Delete by Mr.Goto 02092022
	do {
			s1_alkali_tank_data_set();
			s2_acid_tank_data_set();
			runtime();
		} while (g_ALD != 3 || g_ACD != 3);
	******************************************/
	//電解開始第２処理
	p_1_5_1();
	do {
		c_5();	// Add by Mr.Goto 02092022
		s1_alkali_tank_data_set();
		s2_acid_tank_data_set();
		runtime();
	} while (g_ALD != 3 || g_ACD != 3);
	//電解終了第２処理
	p_1_5_2();
	return 0;
}
/**
 * Electrolyte Process Second Time Start
 * Rename and check valid 02092022
 * @return
 */
int p_1_5_1(void) {
	b_sv1();
	b_sp_start();
	// g_T_S.t17_sをg_T_S.t103_sに修正 (CY)
	wait(SEC_TO_MS(g_T_S.t103_s));
	bp_1_5();
	neutralized_timer_on();
	return 0;
}
/**
 * Electrolyte Process Second Time Stop
 * Rename and check valid 02092022
 * @return
 */
int p_1_5_2(void) {
	tp_1_5();
	t_sp();
	// g_T_S.t5_sをg_T_S.t145_sに修正 (CY)
	wait(SEC_TO_MS(g_T_S.t145_s));
	t_sv1();
	neutralized_timer_off();
	return 0;
}
/**
 * 吐水モード
 * Rename and check valid 02092022
 * @return
 */
int p_2(void){
	// 吐水モード起動処理
	bp_2();
	do{
		c_1(C1_ON);				//電解業務開始処理
		switch ((enum WASH_MODE_E) WASH_MODE) {
			case HAND_WASHING_MODE:
				//手洗いモード
				p_2_4();
				break;
			case WATER_MODE:
				//水吐水モード
				p_2_3();
				break;
			case ACID_MODE:
				//酸性水吐水モード
				p_2_2();
				break;
			case ALKALI_MODE:
				//アルカリ水吐水モード
				p_2_1();
				break;
			default:
				//Crash
				break;
		}
		runtime();
	}while(SYSTEM_MODE != 2);
	c_1(C1_OFF);
	// 吐水モード停止処理
	tp_2();
	return 0;
}
/**
 * アルカリ水吐水モード
 * Rename and check valid 02092022
 * @return
 */
int p_2_1(void){
	// アルカリ水吐水モード起動処理
	bp_2_1();
	// Large loop
	do {
		// 電解業務処理 (ON)
		c_1(C1_ON);
		if(check_hand_sensor() || SYSTEM_MODE == NORMAL){
			b_sv4();
			b_p2();
			b_b_led_b();
			g.timer.alkali_discharge = timer_start_ms();
			do {
				// g_T_S.t35_sをg_T_S.t125_sに修正 (CY)
				if(check_hand_sensor() ||
						elapsed_time_ms(g.timer.alkali_discharge) >= SEC_TO_MS(g_T_S.t125_s)){
					SYSTEM_MODE = NORMAL;
				}else{
					//電解業務処理 (ON)
					c_1(C1_OFF);
				}
				runtime();
			}while(SYSTEM_MODE == WASHING);
			t_p2();
			t_sv4();
			t_b_led_b();
		}
		runtime();
	}while(SYSTEM_MODE != INDIVIDUAL);
	tp_2_1();
	return 0;
}
/**
 * 酸性水吐水モード
 * Rename and check valid 02092022
 * @return
 */
int p_2_2(void){
	// 酸性水吐水モード起動処理
	bp_2_2();
	//Large loop
	do{
		// 電解業務処理 (ON)
		c_1(C1_ON);
		// 長時間チェック処理  追加(CY)
		c_24();
		if(check_hand_sensor() && SYSTEM_MODE == NORMAL){
			SYSTEM_MODE = WASHING;
			b_sv3();
			b_p1();
			b_r_led_b();
			g.timer.acid_discharge = timer_start_ms();
			//Small loop
			do{
				if (check_hand_sensor() ||
						// g_T_S.t34_sをg_T_S.t126_sに修正 (CY)
						elapsed_time_ms(g.timer.acid_discharge) >= SEC_TO_MS(g_T_S.t126_s)){
					SYSTEM_MODE = NORMAL;
				}else{
					// 電解業務処理 (ON)
					c_1(C1_ON);
				}
				runtime();
			}while(SYSTEM_MODE == WASHING);
			t_p1();
			t_sv3();
			t_r_led_b();
		}
		runtime();
	}while(SYSTEM_MODE != INDIVIDUAL);
	// 酸性水吐水モード停止処理
	tp_2_2();
	return 0;
}
/**
 * 水吐水処理
 * Rename and check valid 02092022
 * @return
 */
int p_2_3(void){
	// 水吐水モード起動処理
	bp_2_3();
	// Large loop
	do{
		// 電解業務処理 (ON)
		c_1(C1_ON);
		// 長時間チェック処理  追加(CY)
		c_24();
		if(check_hand_sensor() || SYSTEM_MODE == NORMAL){
			b_sv2();
			b_w_led_b();
			g.timer.water_discharge = timer_start_ms();
			// Small loop
			do {
				if (check_hand_sensor() || elapsed_time_ms(g.timer.water_discharge) >= g_T_S.t126_s * 1000 ){
					SYSTEM_MODE = NORMAL;
				}else{
					// 電解業務処理 (ON)
					c_1(C1_ON);
				}
				runtime();
			}while(SYSTEM_MODE == WASHING);
			t_sv2();
			t_w_led_b();
		}
		runtime();
	}while(SYSTEM_MODE != INDIVIDUAL);
	// 水吐水モード停止処理
	tp_2_3();
	return 0;
}
/**
 * 手洗いモード(全部出る)
 * Check valid 02092022. New plan
 * @return
 */
int p_2_4(void){
	p_2_4_1_1();	//手洗モード用アルカリ吐出開始処理
	p_2_4_1_2();	//手洗モード用アルカリ吐出処理
	p_2_4_1_3();	//手洗モード用アルカリ吐出終了処理
	return 0;
}
/**
 * 手洗モード用アルカリ吐出開始処理
 */
void p_2_4_1_1(void){
	bp_2_4_1();
	b_sv4();
	b_p2();
	g.timer.alkali_discharge = timer_start_ms();
}
/**
 * 手洗モード用アルカリ吐出処理
 * New plan 02092022
 */
void p_2_4_1_2(void){
	b_b_led_l();
	/* Deleted by Mr.Goto 02092022
	while (g_T_S.t119_s * 1000 - elapsed_time_ms(g.timer.alkali_discharge) > 2 * 1000 ){
		c_1(C1_ON);
		runtime();
	}
	*********************************************************/
	//Add by Mr.Goto 02092022. g_T_S.t29_sをg_T_S.t119_sに修正
	if(elapsed_time_ms(g.timer.alkali_discharge) < SEC_TO_MS(g_T_S.t119_s - 2)){
		c_1(C1_ON);
		return;
	}
	t_b_led_l();

	/* Deleted by Mr.Goto 02092022
	while (elapsed_time_ms(g.timer.alkali_discharge) <= SEC_TO_MS(g_T_S.t119_s) &&
			SEC_TO_MS(g_T_S.t119_s) - elapsed_time_ms(g.timer.alkali_discharge) <= g_T_S.t120_ms){
		runtime();
		c_1(C1_ON);
	}
	************************************************************/
	// Add by Mr.Goto 02092022. g_T_S.t32_msをg_T_S.t120_msに修正
	if(elapsed_time_ms(g.timer.alkali_discharge) > SEC_TO_MS(g_T_S.t119_s) - g_T_S.t120_ms){
		c_1(C1_ON);
	}
}
/**
 * 手洗モード用アルカリ吐出終了処理
 * Rename and check valid 02092022
 */
void p_2_4_1_3(void){
	// g_T_S.t29_sをg_T_S.t119_Sに修正 (イシイ)
	while (elapsed_time_ms(g.timer.alkali_discharge) <= g_T_S.t119_s){
		c_1(C1_ON);
		runtime();
	}
	b_b_led_l();
	t_p2();
	t_sv4();
	//TODO アルカリ未吐水タイマ＝0

	tp_2_4_1();
}
/**
 * 手洗モード用酸吐出開始処理
 * Rename
 */
void p_2_4_2_1(void){
	bp_2_4_2();
	b_sv3();
	b_p1();
	g.timer.acid_discharge = timer_start_ms();
}
void p_2_4_2_2(void){
	b_r_led_l();
	/* Delete 02092022

	*/
	// Add 02092022
	if (elapsed_time_ms(g.timer.acid_discharge) < SEC_TO_MS(g_T_S.t119_s)){
		c_1(C1_ON);
	}
	while(SEC_TO_MS(g_T_S.t121_s) - elapsed_time_ms(g.timer.acid_discharge) > 2 * 1000 ){
		c_1(C1_ON);
		runtime();
	}
	b_r_led_b();

	while (elapsed_time_ms(g.timer.acid_discharge) <= SEC_TO_MS(g_T_S.t121_s) &&
			 SEC_TO_MS(g_T_S.t121_s) - elapsed_time_ms(g.timer.acid_discharge) <= g_T_S.t120_ms){
		runtime();
		c_1(C1_ON);
	}
}
/**
 * 手洗モード用酸吐出終了処理
 */
void p_2_4_2_3(void){
	while (elapsed_time_ms(g.timer.acid_discharge) <=  SEC_TO_MS(g_T_S.t121_s)){
		c_1(C1_ON);
		runtime();
	}
	t_r_led_b();
	t_p1();
	t_sv3();
	//TODO: 酸未吐水タイマ＝0

	tp_2_4_2();
}
/**
 * 手洗いモード用水吐出処理
 * Add 02092022
 * @return
 */
int p_2_4_3(void){                                //手洗いモード用水吐出処理
    p_2_4_3_1();                                  //手洗いモード用水吐出開始処理
    p_2_4_3_2();                                  //手洗いモード用水吐出処理
    p_2_4_3_3();                               //手洗いモード用水吐出終了処理
    return 0;
}
/**
 * 手洗モード用水吐出開始処理
 *
 */
void p_2_4_3_1(void){
	//手洗いモード水吐出起動処理
	bp_2_4_3();
	b_sv2();
	g.timer.water_discharge = timer_start_ms();
}
/**
 * 手洗モード用水吐出処理
 */
void p_2_4_3_2(void){
	b_w_led_l();
}
/**
 * 手洗モード用水吐出終了処理
 */
void p_2_4_3_3(void){
	while (elapsed_time_ms(g.timer.water_discharge) <= SEC_TO_MS(g_T_S.t123_s)){
		c_1(C1_ON);
		runtime();
	}
	t_w_led_l();
	t_sv2();
	//TODO: 水未吐水タイマ＝0

	tp_2_4_3();
}
/* Delete 02092022
int p3_individual_mode(void) {
	p_8();
	bp_3();
	while (SYSTEM_MODE == INDIVIDUAL) {
		if (g.flag.individual) {
		//個別処理実施 (Individual processing)
//			p31_sv1_individual_process();
//			p32_sv2_individual_process();
//			p33_sv3_individual_process();
//			p34_sv4_individual_process();
//			p35_sv5_individual_process();
//			p36_sv6_individual_process();
//			p37_sv7_individual_process();
//			p38_p1_individual_process();
//			p39_p2_individual_process();
//			p310_sp_individual_process();
//			p311_electrolysis_equipment_process();
		}
		runtime();
	}
	// 全機能停止
	p_8();
	tp_3();
	return 0;
}************************************************/
/**
 * New plan 02092022
 * @return
 */
int p_3(void) {
	//TODO Implement this
	return 0;
}
int p31_sv1_individual_process(void){
	if(g.flag.io.valve.sv1){
		b_sv1();
	}else{
		t_sv2();
	}
	return SV1_PIN;
}
int p32_sv2_individual_process(void){
	if(g.flag.io.valve.sv2){
		b_sv2();
	}else{
		t_sv2();
	}
	return SV2_PIN;
}
int p33_sv3_individual_process(void){
	if(g.flag.io.valve.sv3){
		b_sv3();
	}else if (PUMP_1_PIN == PUMP_OFF || SV5_PIN == VALVE_ON){
		t_sv3();
	}
	return SV3_PIN;
}
int p34_sv4_individual_process(void){
	if(g.flag.io.valve.sv4){
		b_sv4();
	}else if(PUMP_2_PIN == PUMP_OFF || SV6_PIN == VALVE_ON) {
		t_sv4();
	}
	return SV4_PIN;
}
int p35_sv5_individual_process(void){
	if(g.flag.io.valve.sv5){
		b_sv5();
	}else if (PUMP_1_PIN == PUMP_OFF || SV3_PIN == VALVE_ON){
		t_sv5();
	}
	return SV5_PIN;
}
int p36_sv6_individual_process(void){
	if(g.flag.io.valve.sv6){
		b_sv6();
	}else if(PUMP_2_PIN == PUMP_OFF || SV4_PIN == VALVE_ON){
		t_sv6();
	}
	return SV6_PIN;
}
int p37_sv7_individual_process(void){
	if(g.flag.io.valve.sv7){
		b_sv7_start();
	}else{
		t_sv7_stop();
	}
	return SV7_PIN;
}
int p38_p1_individual_process(void){
	if(g.flag.io.pump_1 && (SV3_PIN == VALVE_ON || SV5_PIN == VALVE_ON)){
		b_p1();
	}else{
		t_p1();
	}
	return PUMP_1_PIN;
}
int p39_p2_individual_process(void){
	if(g.flag.io.pump_2 && (SV4_PIN == VALVE_ON || SV6_PIN == VALVE_ON)){
		b_p2();
	}else{
		t_p2();
	}
	return PUMP_2_PIN;
}
int p310_sp_individual_process(void){
	if(g.flag.io.salt_pump && g.flag.electrolysis == 0){
		b_sp_start();
	}else if(!g.flag.io.salt_pump){
		t_sp();
	}
	return SP_PIN;
}
int p311_electrolysis_equipment_process(void){
	if(g.flag.io.cvcc_control){
		p_1_3_1();
	}else{
		p_1_3_2();
	}
	return CVCC_CONTROL_PIN;
}
int p312_alarm_on_off_process(void){
	if(g.flag.io.cvcc_alarm_out){
		CVCC_ALARM_OUT_PIN = 1U;
	}else{
		CVCC_ALARM_OUT_PIN = 0U;
	}
	return CVCC_ALARM_OUT_PIN;
}
int p_3_13_flow_rate_process(void){
	b_sv1();
	wait(g_T_S.t107_s * 1000);
	//TODO: Flow rate adjust process by hand

	return 0;
}
int p314_salt_tank_drain_process(void){
	bp_3_1_4();
	c_19();
	//TODO: How could we check V4 ??

	b_sp_start();
	//TODO: Wait for how long?
	t_sp();
	tp_3_1_4();
	return 0;
}

int p_8(void){
	//TODO: C11 Electrolytic service emergency stop processing
	c_1_1();
	t_p1();
	t_p2();
	t_sp();
	t_sv1();
	t_sv2();
	t_sv3();
	t_sv4();
	t_sv5();
	t_sv6();
	t_sv7_stop();
	CVCC_CONTROL_PIN = 0U;
	return 0;
}
int p9_stop(void){
	p_8();
	tp_0();
	return 0;
}
