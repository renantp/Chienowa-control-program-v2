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
#include "e_module.h"
#include "../pin_define.h"
#include "../global_variable.h"
#include "../delay.h"
#include "../adc.h"
#include "../runtime.h"
/**
 * Check valid 02092022
 * @param on_off
 * @return
 */
int c_1(uint8_t on_off){
	switch (on_off) {
		case 1:
			if(!g_C_1_F){
				if(!g_SP_F){
					b_sv1();
				}
				if(elapsed_time_ms(g.timer.module.on.io.sp[1]/1000) >= g_T_S.t151_s){		// Change from g_T_S.t17_s to g_T_S.t151_s
					bc_1();
					g.timer.module.on.c1[2] = timer_restart_s(C_1_ON_T3);
					return 1;
				}
				return -1;
			}
			c_5();
			c_23();
			return 0;
		case 0:
			if(g_C_1_F){
				if(g_SP_F){
					t_sp();
				}
				if(elapsed_time_s(g.timer.module.off.io.sp[1])/1000 >= g_T_S.t145_s){		// Change from g_T_S.t5_s to g_T_S.t145_s
					t_sv1();
					tc_1();
					C_1_ON_T3 = timer_stop_s(g.timer.module.on.c1[2]);
					return 2;
				}
				return -2;
			}
			return 0;
		default:
			return 0;
	}
}
/**
 * Check valid 02092022
 * @return
 */
int c_1_1(void) {
	tc_1();
	t_sp();
	wait(g_T_S.t140_s * 1000); // Change g_T_S.t15_s to g_T_S.t140_s
	t_sv1();
	C_1_ON_T3 = timer_stop_s(g.timer.module.on.c1[2]);
	return 1;
}
/**
 * Check valid 02092022
 * @return
 */
int c_2(void) { 						//new_plan
	bc_3();
	s1_alkali_tank_data_set();
	switch(g_ALD){
		case -3:
		case -2:
		case -1:
			e1025();
			break;
		case 0:
			e1029();
			break;
		case 1:
		case 2:
		case 3:
			return g_ALD;
		default:
			break;
	}
	return g_ALD;
}
/**
 * Check valid 02092022
 * @return
 */
int c_3(void){
	bc_3();
	g_SAD = s3_salt_tank_data_set();
	switch(g_SAD){
		case 0:
			e1028();
			return 0;
		case 1:
			return 1;
		case 2:
			return 2;
		default:
			e1024();
			return -1;
	}
}
/**
 * Check valid 02092022
 * @return
 */
int c_4(void){
	bc_4();
	//	塩タンク状況（SAD）取得
	g_SAD = s3_salt_tank_data_set();
	switch(g_SAD){
		case 0:
			e1021();	//TODO: E1021
			break;
		case 1:
			return g_SAD;
		case 2:
			e1020();
			return g_SAD;
		default:
			e1023();
			break;
	}
	return 0;
}
int c_5(void){
	if(CVCC_CONTROL_PIN == 1U){
		bc_5();
		//過電圧1チェック処理
		c_5_1(&g_V_S.v1_V);
		c_5_2(&g_V_S.v2_V);
		c_5_3(&g_V_S.v3_V);
		c_5_4();
		c_5_5();
		c_5_6();
		tc_5();
	}
	return 0;
}
int c_5_1(float *voltage){
	if(elapsed_time_ms(g.timer.module.on.c1[1])/1000 > g_T_S.t131_s){	// Change g_T_S.t11_s to g_T_S.t131_s
		//CVCC_VOLT= CVCC出力電圧
		const float cvcc_voltage = g_adc.voltage;
		//過電圧1チェック起動処理
		bc_5_1();
		//CVCC_VOLT>OVER_V1_ALARM_VALUE
		if(cvcc_voltage > g_V_S.v1_V){
			e1002();
			return -255;
		}
		return 1;
	}
	return 0;
}
int c_5_2(float *voltage){
	//CVCC_VOLT= CVCC出力電圧
	const float cvcc_voltage = g_adc.voltage;
	//CVCC_VOLT>OVER_V2_ALARM_VALUE
	if(cvcc_voltage > g_V_S.v2_V){
		//C_5_2_F=0
		if(g.flag.module.bc52 == 0){
			//過電圧2チェック起動処理
			bc_5_2();
			g.timer.module.on.c52[2] = timer_start_ms();
		}
		if(elapsed_time_ms(g.timer.module.on.c52[2])/1000 > g_T_S.t139_s){
			e1003();
			return -255;
		}else{
			return -1;
		}

	}else{
		tc_5_2();
		return 0;
	}
}
int c_5_3(float *voltage){
	if(elapsed_time_ms(g.timer.module.on.c1[1])/1000 > g_T_S.t139_s){
		//CVCC_VOLT= CVCC出力電圧
		const float cvcc_voltage = g_adc.voltage;
		//CVCC_VOLT>OVER_V3_ALARM_VALUE
		if(cvcc_voltage > g_V_S.v3_V){
			if(g.flag.module.bc53 == 0){
				bc_5_3();
				g.timer.module.on.c53[2] = timer_start_ms();
			}
			c_5_3_1();
			return -1;
		}else{
			return 1;
		}
	}
	return 0;
}

int c_5_3_1(void){
	bc_5_3_1();
	//TODO: Alarm

	const float cvcc_voltage = g_adc.voltage;
	if(cvcc_voltage > g_V_S.v3_V){
		if(elapsed_time_ms(g.timer.module.on.c53[2])/1000 > g_T_S.t132_s){
			e1004();
			return -1;
		}else
			return 1;
	}else{
		e_occur_error = NO_ERROR;
		tc_5_3_1();
		return 0;
	}
}
/**
 * Check CVCC under voltage
 * @return
 */
int c_5_4(void){
	if(elapsed_time_ms(C_1_ON_T2)/1000 > g_T_S.t137_s){
		const float cvcc_current = g_adc.current;
		if(cvcc_current < g_V_S.v6_A){
			if(!g_C_5_4_F){
				bc_5_4();
				//経過時間タイマ＝0　C_5_4_T3=time_start()
				g.timer.module.on.c54[2] = timer_start_ms();
			}
			//TODO: Please check this condition. Is it same as above condition?
			if(g_C_5_4_F != 1){
				//TODO: Alarm

				g.flag.module.c54 = 1;

			}
			if(elapsed_time_ms(g.timer.module.on.c54[2])/1000 > g_T_S.t140_s){
				e1005();
				return -255;
			}else
				return 1;

		}else {
			if(g_C_5_4_F == 1){
				e_occur_error = NO_ERROR;
				g_C_5_4_F = 0;
			}
			tc_5_4();
			return 1;
		}
	}
	return 0;
}
int c_5_5(void){
	if(elapsed_time_ms(C_1_ON_T2)/1000 > g_T_S.t133_s){
		bc_5_5();
		c_5_5_1();
		return 1;
	}
	return 0;
}
int c_5_5_1(void){
	const int ret = c_5_5_2();
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
				e1007();
				return -255;
			}else
				return -1;
		default:
			break;
	}
	return -255;
}
int c_5_5_2(void){
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
 * TODO: Check this.
 * @return
 */
int c_5_6(void){
	bc_5_6();
	const double cvcc_voltage = g_adc.voltage;
	if(cvcc_voltage < 0.1){
		e1009();
	}
	return 0;
}
int c_6(void){
	bc_6();
	//FAUCET_OFF_T＞8ｈ
	if(elapsed_time_s(FAUCET_OFF_T) > 8 * 60 * 60){
		FAUCET_OFF_T = 0;
		e1_faucet_refresh_process();
		return 1;
	}
	return 0;
}
int c_7(void){
	bc_7();
	if(elapsed_time_ms(g.timer.module.off.c1[1]) / 1000 > (uint32_t)168 * 60 * 60){
		e5003();
		return -255;
	}
	return 0;
}
int c_8(void){
	if(elapsed_time_ms(g.timer.module.on.io.sv1[1])/1000 > g_T_S.t149_s){
		if(g.flag.module.c8 == 0){
			bc_8();
			g.timer.module.on.c8[2] = timer_start_ms();
		}
		if(g_V_S.v7_L_m < g.flow_rate){
			if(g.flow_rate < g_V_S.v7_L_m){
				tc_8();
				return 1;
			}else if(elapsed_time_ms(g.timer.module.on.c8[2])/1000 > g_T_S.t151_s){
				tc_8();
				e1000();
				return -255;
			}
			return -2;
		}else if(elapsed_time_ms(g.timer.module.on.c8[2])/1000 > g_T_S.t132_s){
			tc_8();
			e1001();
			return -255;
		}
		return -1;
	}
	return 0;
}
int c_9(void){
	bc_9();
	if(elapsed_time_ms(g.timer.module.on.c1[2])/1000 > (uint32_t)g_T_S.t155_h * 60 * 60){
		e2();
		return -255;
	}
	return 0;
}
int c_10(void){
	if(SV1_PIN == VALVE_OFF){
		if(SV2_PIN == VALVE_OFF){
			if(g.flow_rate >= 0.1f){
				if(g.flag.module.c10 == 0){
					bc_10();
					g.timer.module.on.c10[2] = timer_start_ms();
				}
				if(elapsed_time_ms(g.timer.module.on.c10[2])/1000 > g_T_S.t151_s){
					e1008();
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
		t_sv2();
		t_sv3();
		t_sv4();
		t_sv5();
		t_sv6();
		if(g.flag.leak_sensor == 1){
			if(elapsed_time_ms(g.timer.module.on.c21[1])/1000 > g_T_S.t137_s){
				e1051();
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
			SV1_ON_T1,
			SV2_ON_T1,
			g_V_S.v11_mg_L,
			g_V_S.v12_L);
	if(fc < g_T_S.t113_s){
		if(fc < g_T_S.t114_s){
			e1030();
			return -1;
		}else{
			e1031();
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
			e1026();
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
			e5001();
			return -1;
		}
		return 1;
	}
	if(g.flag.module.c14 == 1){
		g.flag.module.c14 = 0;
		e5002();
		return 0;
	}
	return 1;
}
int c_15(void){
	bc_15();
	const int c_15_d = SW1_PIN;
	if(c_15_d == 0){
		tc_15();
		e1022();
		return -1;
	}
	return 1;
}
int c_16(void){
	if(elapsed_time_s(g.timer.module.on.p0[0]) > (uint32_t)g_T_S.t128_s * 60 * 60){
		bc_16();
		if(g.flag.module.e1032 == 0){
			e1032();
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
	if(elapsed_time_s(g.timer.module.on.c1[0]) > (uint32_t)g_T_S.t149_s * 60 * 60){
		bc_17();
		if(g.flag.module.e1033 == 0){
			e1033();
			return -1;
		}
		return 0;
	}
	return 1;
}
int c_18(void){
	if(g.flag.electrolysis){
		bc_18();
		if(SW2_PIN == 0){
			if(g.flag.module.e1034 == 0){
				e1034();
				tc_18();
				return 0;
			}
			tc_18();
			return 0;
		}
	}
	return 0;
}
int c_19(void){
	c_1_1();
	bc_19();
	if(SW3_PIN)	{
		tc_19();
		return 1;
	}else{
		e1035();
		tc_19();
		return -1;
	}
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
	c_2();
	c_3();
	c_4();
	c_8();
	c_9();
	c_10();
	c_11();
	c_13();
	c_14();
	c_15();
	tc_2_3();
	return 0;
}
int c_24(void){
	bc_23();
	c_6();
	c_7();
	c_12();
	c_16();
	c_17();
	tc_2_3();
	return 0;
}
