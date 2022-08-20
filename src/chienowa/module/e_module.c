/*
 * e_module.c
 *
 *  Created on: Jul 29, 2022
 *      Author: Renan
 */

#include "e_module.h"
#include "t_module.h"
#include "b_module.h"
#include "p_module.h"
#include "../global_variable.h"

union Error_status g_error_status;

enum{
	NO_ERROR,
	E1,
	M1000,
	M1001,
	M1002,
	M1003,
	M1004,
	M1005,
	M1006,
	M1007,
	M1008,
	M1009,
	M1020,
	M1021,
	M1022,
	M1023,
	M1024,
	M1025,
	M1026,
	M1027,
	M1028,
	M1029,
	M1030,
	M1031,
	M1032,
	M1033,
	M1034,
	M1035,
	M1036,
	M1037,
	M1038,
	M1039,
	M1051,
}current_error;

int e1_faucet_refresh_process(void){
	be1();
	e11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = E1;
	te1();
	return 0;
}
int e11(void){
	be11();
	b_sv1_start();
	b_sv2_start();
	b_b_led_b();
	wait((uint32_t)g_T_S.t40_s * 1000);
	t_sv1_stop();
	t_sv2_stop();
	t_w_led_b();
	te11();
	return 0;
}
int e2(void){
	b_sv7_start();
	//B_SV7_ont2>（[28]sec Naturalizing） ON?
	if(elapsed_time_ms(g.timer.module.on.io.sv7[1])/1000 > g_T_S.t28_s){
		t_sv7_stop();
	}
	return 0;
}
int e1000(void){
	//TODO: Show alarm

	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1000;
	//All Stop P_9??
	p8_stop_all_processing();
	//TODO: P-3-13 Flow adjustment （Individual mode）
	//TODO: Wait reset

	return 0;
}
int e1001(void){
	//TODO: Show alarm

	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1001;
	//All Stop P_9??
	p8_stop_all_processing();
	//TODO: P-3-13 Flow adjustment （Individual mode）
	//TODO: Wait reset

	return 0;
}
int e1002(void){
	//TODO: Show alarm

	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1002;
	//All Stop P_9??
	p8_stop_all_processing();
	//TODO: Wait reset

	return 0;
}
int e1003(void){
	//TODO: Show alarm

	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1003;
	//All Stop P_9??
	p8_stop_all_processing();
	//TODO: Wait until choose return

	return 0;
}
int e1004(void){
	//TODO: Show alarm

	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1004;
	return 0;
}
int e1005(void){
	//TODO: Show alarm

	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1005;
	//All Stop P_9??
	p8_stop_all_processing();
	//TODO: Wait until choose return

	return 0;
}
int e1006(void){

	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1006;
	return 0;
}
int e1007(void){
	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1007;
	//TODO: Show power reset

	return 0;
}
int e1008(void){
	E_1008_CVCC_STOP_F = 1;
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1008;
	//TODO: Show power reset

	return 0;
}
int e1009(void){
	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1009;
	//TODO: Show power reset

	return 0;
}
int e1020(void){
	E_1020_CVCC_STOP_F = 0;
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1020;
	//TODO: Wait （Drain by Human）

	current_error = NO_ERROR;
	E_1020_CVCC_STOP_F = 0;

	return 0;
}
int e1021(void){
	//TODO: Show alarm

	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1021;
	//All Stop P_9??
	p8_stop_all_processing();
	//TODO: Reset

	return 0;
}
int e1022(void){
	E_1022_CVCC_STOP_F = 1;
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1022;
	//TODO: Wait （Close cap by human）

	//Delete Error on Screen
	current_error = NO_ERROR;
//	E_1022_CVCC_STOP_F = 1;
	return 0;
}
int e1023(void){
	//TODO: Show alarm

	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1023;
	//All Stop P_9??
	p8_stop_all_processing();
	//TODO: Wait power reset

	return 0;
}
int e1025(void){
	//TODO: Show alarm

	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1025;
	//All Stop P_9??
	p8_stop_all_processing();
	//TODO: Wait power reset

	return 0;
}
int e1024(void){
	//TODO: Show alarm

	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1024;
	//All Stop P_9??
	p8_stop_all_processing();
	//TODO: Wait power reset

	return 0;
}
int e1025(void){
	//TODO: Show alarm

	c11();
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1025;
	//All Stop P_9??
	p8_stop_all_processing();
	//TODO: Wait power reset

	return 0;
}
int e1026(void){
	E_1026_CVCC_STOP_F = 1;
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1026;
	//All Stop P_9??
	p8_stop_all_processing();
//	E_1022_CVCC_STOP_F = 1;
	return 0;
}

/**
 * Under consider
 * @return
 */
int e1028(void){
	return 0;
}
/**
 * Under consider
 * @return
 */
int e1029(void){
	return 0;
}
int e1030(void){
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1030;
	return 0;
}
int e1031(void){
	c11();
	//Delete Error on Screen
	current_error = NO_ERROR;
	//ログ書き込み処理 (log error)
	//TODO: タッチパネルエラー表示
	current_error = M1031;
	//TODO: Wait filter changed （Replace by human）

	//Delete Error on Screen
	current_error = NO_ERROR;
	return 0;
}
/**
 * Under consider
 * @return
 */
int e1031_1(void){
	return 0;
}
int e1032(void){
	//TODO: Log Memory
	//Show Time up on screen
	//E_1032_F = 1;
	current_error = M1032;
	return 0;
}
int e1033(void){
	//TODO: Log Memory
	//Show error on screen
	//E_1033_F = 1;
	current_error = M1033;
	return 0;
}
int e1034(void){
	c11();
	//TODO: Log Memory
	//Show error on screen
	//E_1034_F = 1;
	current_error = M1034;
	return 0;
}
int e1035(void){
	c11();
	//TODO: Log Memory
	//Show error on screen
	current_error = M1035;
	return 0;
}
int e1051(void){
	//TODO: Alarm

	c11();
	//TODO: Log Memory
	//Show error on screen
	current_error = M1051;
	//P_9 stop??
	p8_stop_all_processing();
	//TODO: Wait power reset

	return 0;
}
int e5001(void){
	c11();

	return 0;
}
//int e1051_water_leak_error(void){
//	return 0;
//}
//
//int e1035_salt_tank_drain_valve_direction_error(void){
//	return 0;
//}
//
//int e1034_saltwater_drain_direction_error(void){
//	return 0;
//}
//
//int e1033_total_electrolysis_time_error(void){
//	return 0;
//}
//
//int e1032_total_power_on_time(void){
//	return 0;
//}
//
//int e10311_filter_replace(void){
//	return 0;
//}
//
//int e1031_continue_filter_alarm(void){
//	return 0;
//}
//
//int e1030_filter_replace_alarm(void){
//	return 0;
//}
//
//int e1029_alkali_tank_empty(void){
//	return 0;
//}
//
//int e1028_acid_tank_error(void){
//	return 0;
//}
//
//int e1026_acid_and_alkali_tank_over_flow_error(void){
//	return 0;
//}
//
//int e1025_alkali_tank_level_sensor_error(void){
//	return 0;
//}
//
//int e1024_acid_tank_level_sensor_error(void){
//	return 0;
//}
//
//int e1023_salt_tank_level_sensor_error(void){
//	return 0;
//}
//
//int e1022_salt_tank_cap_error(void){
//	return 0;
//}
//
//int e1021_empty_salt_tank(void){
//	return 0;
//}
//
//int e1020_salt_tank_error(void){
//	return 0;
//}
//
//int e1009_cvcc_error(void){
//	return 0;
//}
//
//int e1008_sv1_error(void){
//	return 0;
//}
//
//int e1007_current_20_error(void){
//	return 0;
//}
//
//int e1006_current_10_error(void){
//	return 0;
//}
//
//int e1005_low_voltage_error(void){
//	return 0;
//}
//
//int e1004_over_voltage_3(void){
//	return 0;
//}
//
//int e1003_over_voltage_2(void){
//	return 0;
//}
//
//int e1002_over_voltage_1(void){
//	return 0;
//}
//
//int e1001_low_flow_rate_error(void){
//	return 0;
//}
//
//int e1000_flow_sensor_over_range(void){
//	return 0;
//}
//
//int e2_naturalizing_process(void){
//	return 0;
//}
//
//int e11_do_refresh(void){
//	return 0;
//}
//
//int e1_faucet_refresh_process(void){
//	return 0;
//}
