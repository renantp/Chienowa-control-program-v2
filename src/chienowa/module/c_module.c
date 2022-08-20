/*
 * c_module.c
 *
 *  Created on: Jul 29, 2022
 *      Author: Renan
 */

#include "c_module.h"
#include "s_module.h"
#include "b_module.h"
#include "t_module.h"
#include "../pin_define.h"
#include "../global_variable.h"
#include "../delay.h"
#include "../adc.h"
#include "e_module.h"

int c1_on_off(uint8_t on_off){
	if(on_off){
		if(g.flag.module.c1 == 0){
			c5_electrolysis_check_process();
			//TODO: c23()

			return 0;
		}
		SP_PIN = PUMP_OFF; //SP_F=0?
		b_sv1_start(); //SV１（給水） ON処理
		b_sp_start(); //SP（塩ポンプ） ON処理
		if(elapsed_time_s(SP_ON_T2)/1000 >= g_T_S.t17_s){
			//BC-1 電解業務起動処理
			bc1();
			C_1_ON_T3 = timer_restart_s(C_1_ON_T3);
			return 0;
		}else{
			return -1;
		}
	}else{
		//C_1_F=1
		if(g.flag.module.c1){
			return 0;
		}
		//SP_F=1
		SP_PIN = PUMP_ON;
		//T-SP   SP（塩ポンプ）Stop処理
		t_sp_stop();
		if(elapsed_time_ms(SP_OFF_T2)/1000 >= g_T_S.t5_s){
			t_sv1_stop();
			//TODO: tc1() flow chart is missing

			C_1_ON_T3 = timer_stop_s(C_1_ON_T3);
			return -1;
		}else{
			return -2;
		}
	}
	return 0;
}
int c11(void) {
	tc1();
	t_sp_stop();
	wait(g_T_S.t15_s * 1000);
	t_sv1_stop();
	//中和タイマー停止処理
	C_1_ON_T3 = timer_start_s();
	return 1;
}
int c2_alkali_tank_level_check(void) {
	bc3();
	const int status = s1_alkali_tank_data_set();
	if(status < -1){
		//TODO: E1025

		return -255;
	}else if(status == 0){
		//TODO: E1029

		return g_ALD;
	}else {
		return g_ALD;
	}
	return 0;
}
int c3_acid_tank_level_check(void){
	bc3();
	const int status = s2_acid_tank_data_set();
	if(status <= -1){
		//TODO: E1024

		return -255;
	}else if(status == 0){
		//TODO: E1028

		return g_ACD;
	}else{
		return g_ACD;
	}
	return 0;
}
int c4_salt_tank_sensor_value_check_process(void){
	bc4();
	//塩タンク状況（SAD）取得
	const int status = s3_salt_tank_data_set();
	if(status == -1){
		//TODO: E1023
	}else if(status == 0){
		//TODO: E1021
	}else if(status == 1){
		return g_SAD;
	}else if(status == 2){
		return g_SAD;
	}
	return 0;
}
int c5_electrolysis_check_process(void){
	bc5();
	//過電圧1チェック処理
	c51_over_voltage_1_check(&g_V_S.v1_V);
	c52_over_voltage_2_check(&g_V_S.v2_V);
	c53_over_voltage_3_check(&g_V_S.v3_V);
	//TODO: Ask
	return 0;
}
int c51_over_voltage_1_check(float *voltage){
	if(elapsed_time_ms(C_1_ON_T2)/1000 > g_T_S.t11_s){
		//CVCC_VOLT= CVCC出力電圧
		const float cvcc_voltage = g_adc.voltage;
		//過電圧1チェック起動処理
		bc51();
		//CVCC_VOLT>OVER_V1_ALARM_VALUE
		if(cvcc_voltage > g_V_S.v1_V){
			//TODO: E1002

			return -255;
		}
		return 1;
	}
	return 0;
}
int c52_over_voltage_2_check(float *voltage){
	//CVCC_VOLT= CVCC出力電圧
	const float cvcc_voltage = g_adc.voltage;
	//CVCC_VOLT>OVER_V2_ALARM_VALUE
	if(cvcc_voltage > g_V_S.v2_V){
		//C_5_2_F=0
		if(g.flag.module.bc52 == 0){
			//過電圧2チェック起動処理
			bc52();
			C_5_2_ON_T3 = timer_start_ms();
		}
		if(elapsed_time_ms(C_5_2_ON_T3)/1000 > g_T_S.t41_s){
			//TODO: E1003

			return -255;
		}else{
			return -1;
		}

	}else{
		tc52();
		return 0;
	}
	return 1;
}
int c53_over_voltage_3_check(float *voltage){
	if(elapsed_time_ms(C_1_ON_T2)/1000 > g_T_S.t41_s){
		//CVCC_VOLT= CVCC出力電圧
		const float cvcc_voltage = g_adc.voltage;
		//CVCC_VOLT>OVER_V3_ALARM_VALUE
		if(cvcc_voltage > g_V_S.v3_V){
			if(g.flag.module.bc53 == 0){
				bc53();
				C_5_2_ON_T3 = timer_start_ms();
			}
			c531();
			return -1;
		}else{
			return 1;
		}
	}
	return 0;
}
int c531(void){
	bc531();
	//TODO: Alarm
	const float cvcc_voltage = g_adc.voltage;
	if(cvcc_voltage > g_V_S.v3_V){
		if(elapsed_time_ms(C_5_2_ON_T3)/1000 > g_T_S.t13_s){
			//TODO: E1004

			return -1;
		}else
			return 1;
	}else{
		//TODO: タッチパネルエラー削除

		tc531();
		return 0;
	}
}
int c54(void){
	if(elapsed_time_ms(C_1_ON_T2)/1000 > g_T_S.t14_s){
		const float cvcc_current = g_adc.current;
		if(cvcc_current < g_V_S.v6_A){
			if(g.flag.module.bc54 == 0){
				bc54();
				//経過時間タイマ＝0　C_5_4_T3=time_start()
				C_5_4_ON_T3 = timer_start_ms();
			}
			//C_5_4_F2＝1
			if(g.flag.module.c54 != 1){
				//TODO: Alarm

				g.flag.module.c54 = 1;

			}
			if(elapsed_time_ms(C_5_4_ON_T3)/1000 > g_T_S.t15_s){
				//TODO: E1005

				return -255;
			}else
				return 1;

		}else {
			if(g.flag.module.c54 == 1){
				//TODO: タッチパネルエラー削除

				//C_5_4_F2＝0
				g.flag.module.c54 = 0;
			}
			tc54();
			return 1;
		}
	}
	return 0;
}
int c55(void){
	if(elapsed_time_ms(C_1_ON_T2)/1000 > g_T_S.t16_s){
		bc55();
		c551();
		return 1;
	}
	return 0;
}
int c551(void){
	const int ret = c552();
	switch (ret) {
		case 1:
			if(g.flag.c55_10 == 1){
				//TODO: E1006

				return -255;
			}
			g.flag.c55_10 = 0;
			g.flag.c55_20 = 0;
			g.timer.c55_20 = 0;
			return 0;
		case -1:
			if(g.flag.c55_10 == 0){
				g.flag.c55_10 = 1;
				//TODO: E1006

				return -255;
			}
			break;
		case -2:
			if(g.flag.c55_20 == 0){
				g.flag.c55_20 = 1;
				C_5_5_20T = timer_start_ms();
			}
			//elapsed_time(C_5_5_ON_20T)/1000>1分
			if(elapsed_time_ms(C_5_5_20T)/1000 > 60){
				//TODO: E1007 電流範囲20％エラー処理

				return -255;
			}else
				return -1;
			break;
		default:
			break;
	}
	return -255;
}
int c552(void){
	//CVCC_CURRENT= CVCC電解電流値取得
	const float cvcc_current = g_adc.current;
	//設定値⑨：規定値　1A
	if(g_V_S.v9_A * 1.1f < cvcc_current){
		if(g_V_S.v9_A * 1.2f < cvcc_current){
			return -2;
		}
		return -1;
	}else if(g_V_S.v9_A * 0.9f > cvcc_current){ ////⑨-（⑨ ×0.1）>CVCC_CURRENT
		if(g_V_S.v9_A * 0.8f > cvcc_current){
			return -2;
		}
		return -1;
	}
	return 1;
}
/**
 * Control PCB doesn't have CVCC power supply monitor pin
 * @return
 */
int c56(void){
	bc56();

	return 0;
}
int c6(void){
	bc6();
	//FAUCET_OFF_T＞8ｈ
	if(elapsed_time_s(FAUCET_OFF_T) > 8 * 60 * 60){
		FAUCET_OFF_T = 0;
		e1_faucet_refresh_process();
		return 1;
	}
	return 0;
}
int c7(void){
	bc7();
	if(elapsed_time_ms(C_1_OFF_T2) / 1000 > (uint32_t)168 * 60 * 60){
		//TODO: E5003

		return -255;
	}
	return 0;
}
int c8(void){
	if(elapsed_time_ms(SV1_ON_T2)/1000 > g_T_S.t2_s){
		if(g.flag.module.c8 == 0){
			bc8();
			C_8_T3 = timer_start_ms();
		}
		if(g_V_S.v7_L_m < g.flow_rate){
			if(g.flow_rate < g_V_S.v7_L_m){
				tc8();
				return 1;
			}else if(elapsed_time_ms(C_8_T3)/1000 > g_T_S.t3_s){
				tc8();
				//TODO: E1000

				return -255;
			}
			return -2;
		}else if(elapsed_time_ms(C_8_T3)/1000 > g_T_S.t13_s){
			tc8();
			//TODO: E1001

			return -255;
		}
		return -1;
	}
	return 0;
}
int c9(void){
	bc9();
	if(elapsed_time_ms(C_1_ON_T3)/1000 > (uint32_t)g_T_S.t27_h * 60 * 60){
		//TODO: E2

		return -255;
	}
	return 0;
}
int c_10(void){
	if(SV1_PIN == VALVE_OFF){
		if(SV2_PIN == VALVE_OFF){
			if(g.flow_rate >= 0.1f){
				if(C_10_F == 0){
					bc_10();
					C_10_ON_T3 = timer_start_ms();
				}
				if(elapsed_time_ms(C_10_ON_T3)/1000 > g_T_S.t17_s){
					//TODO: E1008

					return -255;
				}
				return -1;
			}
			return 1;
		}
	}
	return 0;
}

int c_11(void){
	//漏水センサーON
	if(g.flag.leak_sensor == 1){
		bc_11();
		t_sv2_stop();
		t_sv3_stop();
		t_sv4_stop();
		t_sv5_stop();
		t_sv6_stop();
		if(g.flag.leak_sensor == 1){
			if(elapsed_time_ms(C_21_T2)/1000 > g_T_S.t37_s){
				//TODO: E1051

			}
			return 1;
		}
		return 1;
	}
	return 0;
}
int c_12(void){
	bc_12();
	const float fc = s5_filter_change_formula(
			SV1_ON_T3,
			SV2_ON_T3,
			g_V_S.v11_mg_L,
			g_V_S.v12_L);
	if(fc < g_T_S.t19_h){
		if(fc < g_T_S.t20_h){
			//TODO: E1030

			return -1;
		}else{
			//TODO: E1031

			return -2;
		}
	}else
		return 0;
}
int c_13(void){
	if(g.flag.module.c1){
		const int r = c_131();
		if(r == 1){
			bc_13();
			//TODO: E1026

			return -255;
		}
		return 1;
	}
	return -0;
}
int c_131(void){
	if(elapsed_time_ms(g.timer.module.off.io.p2[1])/1000 > 20 * 60){
		if(elapsed_time_ms(g.timer.module.off.io.p1[1])/1000 > 20 * 60){
			return 1;
		}
	}
	return 0;
}
int c_14(void){
	bc_14();
	//C_14_TF_F=両タンク満水フラグ
	g.flag.module.c14 = 0;
	if(g_ALD == 3 && g_ACD == 3){
		if(g.flag.module.c14 == 0){
			g.flag.module.c14 = 1;
			//TODO: E5001

			return -1;
		}
		return 1;
	}
	if(g.flag.module.c14 == 1){
		g.flag.module.c14 = 0;
		//TODO: E5002

		return 0;
	}
	return 1;
}
int c_15(void){
	bc_15();
	const int c_15_d = SALT_LID_PIN;
	if(c_15_d == 0){
		tc15();
		//TODO: E1022

		return -1;
	}
	return 1;
}
int c_16(void){
	if(elapsed_time_s(g.timer.module.on.p0[0]) > (uint32_t)g_T_S.t36_h * 60 * 60){
		bc_16();
		if(g.flag.module.e1032 == 0){
			//TODO: E1032

			return -1;
		}
		return 0;
	}
	return 1;
}
int c_17(void){
	/**
	 * 電解運転起算タイマが（[37]時間）
		超えた場合
		C_1_ON_T1> [42]
	 */
	if(elapsed_time_s(g.timer.module.on.c1[0]) > (uint32_t)g_T_S.t42_h * 60 * 60){
		bc_17();
		if(g.flag.module.e1033 == 0){
			//TODO: E1033

			return -1;
		}
		return 0;
	}
	return 1;
}
int c_18(void){
	if(g.flag.electrolysis){
		bc_18();
		/** TODO:
		 * 塩水路循環希望の場合で
		 * V4弁が循環側になっていない場合
		 */

		if(g.flag.module.e1034 == 0){
			//TODO: E1034

			tc18();
			return 0;
		}else{
			tc18();
			return 0;
		}
	}
	return 0;
}
int c19(void){
	while(g.flag.electrolysis != 0){
		runtime();
	}
	bc_19();
	//TODO: V4弁が排水側になっている場合

	//TODO: E-1035

	tc19();
	return 0;
}
/**
 * Need more information
 * @return
 */
int c_20(void){
	while(g.flag.module.c20 != 1){
		runtime();
	}
	//TODO: システム設定モードデータ来たか

	return 0;
}
/**
 * Need more information
 * @return
 */
int c_21(void){
	return 0;
}
/**
 * Need more information
 * @return
 */
int c_22(void){
	return 0;
}
int c_23(void){
	bc_23();
	c2_alkali_tank_level_check();
	c3_acid_tank_level_check();
	c4_salt_tank_sensor_value_check_process();
	c8();
	c9();
	c_10();
	c_11();
	c_13();
	c_14();
	c_15();
	tc_23();
	return 0;
}
int c_24(void){
	bc_23();
	c6();
	c7();
	c_12();
	c_16();
	c_17();
	tc_23();
	return 0;
}
