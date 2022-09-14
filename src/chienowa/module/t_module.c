/*
 * t_module.c
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#include "t_module.h"
#include "../pin_define.h"
#include "../global_variable.h"
#include "../delay.h"
#include "../hand_sensor.h"

int tp_0(void) {                    //システムメイン停止処理
	if (g_P_0_F) {
		g_P_0_ON_T1 = timer_stop_s(g.timer.module.on.p0[0]);//P_0_ON_T1 STOP
		g_P_0_ON_T2 = timer_stop_ms(g.timer.module.on.p0[1]);//P_0_ON_T2 STOP
		g_P_0_F = 0;//P_0_F = 0     //* 20220831 修正　（渡部夢二）
	}
	return 0;
}
int tp_1(void) {                  //初期抜水停止処理
	if (g_P_1_F) {
		g_P_1_ON_T1 = timer_stop_s(g.timer.module.on.p1[0]);//P_1_ON_T1 STOP
		g_P_1_ON_T2 = timer_stop_ms(g.timer.module.on.p1[1]);//P_1_ON_T2 STOP
		g_P_1_F = 0;//P_1_F = 0

	}
	return 0;
}
int tp_1_1(void) {                  //初期抜水停止処理
	if (g_P_1_1_F) {
		g_P_1_1_ON_T1 = timer_stop_s(g.timer.module.on.p11[0]);//P_1_1_ON_T1 STOP
		g_P_1_1_ON_T2 = timer_stop_ms(g.timer.module.on.p11[1]);//P_1_1_ON_T2 STOP
		g_P_1_1_F = 0;//P_1_1_F = 0

	}
	return 0;
}
int tp_1_1_1(void) {                //初期アルカリタンク抜水停止処理
	if (g_P_1_1_1_F) {
		g_P_1_1_1_ON_T1 = timer_stop_s(g.timer.module.on.p111[0]);//P_1_1_1_ON_T1 STOP
		g_P_1_1_1_ON_T2 = timer_stop_ms(g.timer.module.on.p111[1]);//P_1_1_1_ON_T2 STOP
		g_P_1_1_1_F = 0;//P_1_1_1_F = 0
	}
	return 0;
}
int tp_1_1_2(void) {                //初期酸タンク抜水停止処理
	if (g_P_1_1_2_F) {
		g_P_1_1_2_ON_T1 = timer_stop_s(g.timer.module.on.p112[0]);//P_1_1_2_ON_T1 STOP
		g_P_1_1_2_ON_T2 = timer_stop_ms(g.timer.module.on.p112[1]);//P_1_1_2_ON_T2 STOP
		g_P_1_1_2_F = 0;//P_1_1_2_F = 0
	}
	return 0;
}
int tp_1_2(void) {                  //初期給水停止処理
	if (g_P_1_2_F) {
		g_P_1_2_ON_T1 = timer_stop_s(g.timer.module.on.p12[0]);//P_1_2_ON_T1 STOP
		g_P_1_2_ON_T2 = timer_stop_ms(g.timer.module.on.p12[1]);//P_1_2_ON_T2 STOP
		g_P_1_2_F = 0;//P_1_2_F = 0
	}
	return 0;
}
int tp_1_3(void) {                  //初期電解停止処理
	if (g_P_1_3_F) {
		g_P_1_3_ON_T1 = timer_stop_s(g.timer.module.on.p13[0]);//P_1_3_ON_T1 STOP
		g_P_1_3_ON_T2 = timer_stop_ms(g.timer.module.on.p13[1]);//P_1_3_ON_T2 STOP
		CVCC_CONTROL_PIN = 0U;//（ER＝電解装置） 停止
		g_C_1_OFF_T2=timer_start_ms(); //C_1_OFF_T2 START  電解処理未動作使用タイマ  //*20220831 修正　（渡部夢二）
		g_P_1_3_F = 0;//P_1_3_F = 0
	}
	return 0;
}

int tp_1_4(void) {                  //初期抜水第2停止処理
	if (g_P_1_4_F) {
		g_P_1_4_ON_T1 = timer_stop_s(g.timer.module.on.p14[0]);//P_1_4_ON_T1 STOP
		g_P_1_4_ON_T2 = timer_stop_ms(g.timer.module.on.p14[1]);//P_1_4_ON_T2 STOP
		g_P_1_4_F = 0;//P_1_4_F = 0
	}
	return 0;
}
int tp_1_4_1(void) {                //初期アルカリタンク抜水第2停止処理
	if (g_P_1_4_1_F) {
		g_P_1_4_1_ON_T1 = timer_stop_s(g.timer.module.on.p141[0]);//P_1_4_1_ON_T1 STOP
		g_P_1_4_1_ON_T2 = timer_stop_ms(g.timer.module.on.p141[1]);//P_1_4_1_ON_T2 STOP
		g_P_1_4_1_F = 0;//P_1_4_1_F = 0    //*20220831 修正（渡部夢二）
	}
	return 0;
}
int tp_1_4_2(void) {                //初期酸タンク抜水第2停止処理
	if (g_P_1_4_2_F) {
		g_P_1_4_2_ON_T1 = timer_stop_s(g.timer.module.on.p142[0]);//P_1_4_2_ON_T1 STOP
		g_P_1_4_2_ON_T2 = timer_stop_ms(g.timer.module.on.p142[1]);//P_1_4_2_ON_T2 STOP
		g_P_1_4_2_F = 0;//P_1_4_2_F = 0
	}
	return 0;
}

int tp_1_5(void) {                  //電解水生成第2停止処理
	if (g_P_1_5_F) {
		g_P_1_5_ON_T1 = timer_stop_s(g.timer.module.on.p15[0]);//P_1_5_ON_T1 STOP
		g_P_1_5_ON_T2 = timer_stop_ms(g.timer.module.on.p15[1]);//P_1_5_ON_T2 STOP
		CVCC_CONTROL_PIN = 0U;//（ER＝電解装置） 停止
		g_C_1_OFF_T2=timer_start_ms(); //C_1_OFF_T2 START  電解処理未動作使用タイマ  //*20220831 修正　（渡部夢二）
		g_P_1_5_F = 0;//P_1_5_F = 0
	}
	return 0;
}
int tp_2(void) {                    //吐水モード停止処理
	if (g_P_2_F) {
		g_P_2_ON_T1 = timer_stop_s(g.timer.module.on.p2[0]);//P_2_ON_T1 STOP
		g_P_2_ON_T2 = timer_stop_ms(g.timer.module.on.p2[1]);//P_2_ON_T2 STOP
		g_P_2_F = 0;//P_2_F = 0
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp_2_1(void) {                //アルカリ水吐水モード停止処理
	if (g.flag.module.bp21) {
		g_P_2_1_ON_T1 = timer_stop_s(g.timer.module.on.p21[0]);//P_2_1_ON_T1 STOP
		g_P_2_1_ON_T2 = timer_stop_ms(g.timer.module.on.p21[1]);//P_2_1_ON_T2 STOP
		g.timer.module.off.p21[0] = timer_restart_s(g_P_2_1_OFF_T1);//P_2_1_ OFF_T1 RESTART
		g.timer.module.off.p21[1] = timer_start_ms();//P_2_1_ OFF_T2  START
		g_P_2_1_F = 0;//P_2_1_F = 0　　//*20220831 修正　（渡部夢二）
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp_2_2(void) {                //酸性水吐水モード停止処理　　//*20220831 修正　（渡部夢二）
	if (g.flag.module.bp22) {
		g_P_2_2_ON_T1 = timer_stop_s(g.timer.module.on.p22[0]);//P_2_2_ON_T1 STOP
		g_P_2_2_ON_T2 = timer_stop_ms(g.timer.module.on.p22[1]);//P_2_2_ON_T2 STOP
		g.timer.module.off.p22[0] = timer_restart_s(g_P_2_2_OFF_T1);//P_2_2_ OFF_T1 RESTART
		g.timer.module.off.p22[1] = timer_start_ms();//P_2_2_ OFF_T2  START
		g_P_2_2_F = 0;//P_2_2_F = 0　　//*20220831 修正　（渡部夢二）
	}
	return 0;
}
int tp_2_3(void) {                  //水吐水モード停止処理
	if (g_P_2_3_F) {
		g_P_2_3_ON_T1 = timer_stop_s(g.timer.module.on.p23[0]);//P_2_3_ON_T1 STOP
		g_P_2_3_ON_T2 = timer_stop_ms(g.timer.module.on.p23[1]);//P_2_3_ON_T2 STOP
		g_P_2_3_F = 0;//P_2_3_F = 0
	}
	return 0;
}
int tp_2_4(void) {                  //手洗いモード停止処理
	if (g_P_2_4_F) {
		g_P_2_4_ON_T1 = timer_stop_s(g.timer.module.on.p24[0]);//P_2_4_ON_T1 STOP
		g_P_2_4_ON_T2 = timer_stop_ms(g.timer.module.on.p24[1]);//P_2_4_ON_T2 STOP
		g_P_2_4_F = 0;//P_2_4_F = 0
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp_2_4_1(void) {                //手洗いモード用アルカリ吐水停止処理
	if (g.flag.module.bp241) {
		g_P_2_4_1_ON_T1 = timer_stop_s(g.timer.module.on.p241[0]);//P_2_4_1_ON_T1 STOP
		g_P_2_4_1_ON_T2 = timer_stop_ms(g.timer.module.on.p241[1]);//P_2_4_1_ON_T2 STOP
		g.timer.module.off.p241[0] = timer_restart_s(g_P_2_4_1_OFF_T1);//P_2_4_1_ OFF_T1 RESTART
		g.timer.module.off.p241[1] = timer_start_ms();//P_2_4_1_ OFF_T2  START
		g_P_2_4_1_F = 0;//P_2_4_1_F = 0　　//*20220831 修正　（渡部夢二）
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int tp_2_4_2(void) {                //手洗いモード用酸性水吐水停止処理
	if (g.flag.module.bp242) {
		g_P_2_4_2_ON_T1 = timer_stop_s(g.timer.module.on.p242[0]);//P_2_4_2_ON_T1 STOP
		g_P_2_4_2_ON_T2 = timer_stop_ms(g.timer.module.on.p242[1]);//P_2_4_2_ON_T2 STOP
		g.timer.module.off.p242[0] = timer_restart_s(g_P_2_4_2_OFF_T1);//P_2_4_2_ OFF_T1 RESTART
		g.timer.module.off.p242[1] = timer_start_ms();//P_2_4_2_ OFF_T2  START
		g_P_2_4_2_F = 0;//P_2_4_2_F = 0　　//*20220831 修正　（渡部夢二）
	}
	return 0;
}
int tp_2_4_3(void) {                //手洗いモード用水吐水停止処理
	if (g_P_2_4_3_F) {
		g_P_2_4_3_ON_T1 = timer_stop_s(g.timer.module.on.p243[0]);//P_2_4_3_ON_T1 STOP
		g_P_2_4_3_ON_T2 = timer_stop_ms(g.timer.module.on.p243[1]);//P_2_4_3_ON_T2 STOP
		g_P_2_4_3_F = 0;//P_2_4_3_F = 0
	}
	return 0;
}
int tp_3(void) {                    //個別（試運転）停止処理
	if (g_P_3_F) {
		g_P_3_ON_T1 = timer_stop_s(g.timer.module.on.p3[0]);//P_3_ON_T1 STOP
		g_P_3_ON_T2 = timer_stop_ms(g.timer.module.on.p3[1]);//P_3_ON_T2 STOP
		g_P_3_F = 0;//P_3_F = 0
	}
	return 0;
}
int tp_3_13(void) {                    //個別（試運転）停止処理
	if (g_P_3_13_F) {
		g_P_3_13_ON_T1 = timer_stop_s(g.timer.module.on.p313[0]);//P_3_13_ON_T1 STOP
		g_P_3_13_ON_T2 = timer_stop_ms(g.timer.module.on.p313[1]);//P_3_13_ON_T2 STOP
		g_P_3_13_F = 0;//P_3_13_F = 0
	}
	return 0;
}
//int tp_3_14(void) {                    //個別（試運転）停止処理
//	if (g_P_3_14_F) {
//		g_P_3_14_ON_T1 = timer_stop_s(g.timer.module.on.p314[0]);//P_3_14_ON_T1 STOP
//		g_P_3_14_ON_T2 = timer_stop_ms(g.timer.module.on.p314[1]);//P_3_14_ON_T2 STOP
//		g_P_3_14_F = 0;//P_3_14_F = 0
//	}
//	return 0;
//}
int t_sv1(void) {              //電磁バルブSV1停止処理
	if (g.io.valve.sv1 == 1) {
		g_SV1_ON_T1 = timer_stop_s(g.timer.module.on.io.sv1[0]);//SV1_ON_T1 STOP
		g_SV1_ON_T2 = timer_stop_ms(g.timer.module.on.io.sv1[1]);//SV1_ON_T2 STOP  //*20220831 修正　（渡部夢二）
		g_SV1_ON_T3 = timer_stop_ms(g.timer.module.on.io.sv1[2]);//フィルター交換で使用  //*20220831 修正　（渡部夢二）
		SV1_PIN = VALVE_OFF;  //*20220831 修正　（渡部夢二）
		g_SV1_F = 0; // SV1_F = 0    //*20220831 追加　（渡部夢二）
		return 1;
	}
	return 0;
}
int t_sv2(void) {              //電磁バルブSV2停止処理
	SV2_PIN = VALVE_OFF;
	if (g_SV2_F == 1) {
		g_SV2_ON_T1 = timer_stop_s(g.timer.module.on.io.sv2[0]);//SV2_ON_T1 STOP
		g_SV2_ON_T2 = timer_stop_ms(g.timer.module.on.io.sv2[1]);//SV2_ON_T2 STOP  //*20220831 修正　（渡部夢二）
		g_SV2_ON_T3 = timer_stop_ms(g.timer.module.on.io.sv2[2]);//フィルター交換で使用  //*20220831 修正　（渡部夢二）
		SV2_PIN = VALVE_OFF;  //*20220831 修正　（渡部夢二）
	    g_FAUCET_OFF_T=timer_start_ms(); //カラン未使用タイマー　スタート  //*20220831 追加　（渡部夢二）
		g_SV2_F = 0; // SV2_F = 0    //*20220831 追加　（渡部夢二）
		return 1;
	}
	return 0;
}
int t_sv3(void) {              //電磁バルブSV3停止処理
	if (g.io.valve.sv3 == 1) {
		g_SV3_ON_T1 = timer_stop_s(g.timer.module.on.io.sv3[0]);//SV3_ON_T1 STOP
		g_SV3_ON_T2 = timer_stop_ms(g.timer.module.on.io.sv3[1]);//SV3_ON_T2 STOP　　//*20220831 修正　（渡部夢二）
		SV3_PIN = VALVE_OFF;  //*20220831 修正　（渡部夢二）
		g_FAUCET_OFF_T=timer_start_ms(); //カラン未使用タイマー　スタート  //*20220831 追加　（渡部夢二）
		g_SV3_F = 0; // SV3_F = 0    //*20220831 追加　（渡部夢二）
		return 1;
	}
	return 0;
}
int t_sv4(void) {              //電磁バルブSV4停止処理
	if (g.io.valve.sv4 == 1) {
		g_SV4_ON_T1 = timer_stop_s(g.timer.module.on.io.sv4[0]);//SV4_ON_T1 STOP
		g_SV4_ON_T2 = timer_stop_ms(g.timer.module.on.io.sv4[1]);//SV4_ON_T2 STOP //*20220831 修正　（渡部夢二）
		SV4_PIN = VALVE_OFF;  //*20220831 修正　（渡部夢二）
		g_FAUCET_OFF_T=timer_start_ms(); //カラン未使用タイマー　スタート  //*20220831 追加　（渡部夢二）
		g_SV4_F = 0; // SV4_F = 0    //*20220831 追加　（渡部夢二）
		return 1;
	}
	return 0;
}
int t_sv5(void) {              //電磁バルブSV5停止処理
	if (g.io.valve.sv5 == 1) {
		g_SV5_ON_T1 = timer_stop_s(g.timer.module.on.io.sv5[0]);//SV5_ON_T1 STOP
		g_SV5_ON_T2 = timer_stop_ms(g.timer.module.on.io.sv5[1]);//SV5_ON_T2 STOP  //*20220831 修正　（渡部夢二）
		SV5_PIN = VALVE_OFF;  //*20220831 修正　（渡部夢二）
		g_SV5_F = 0; // SV5_F = 0    //*20220831 追加　（渡部夢二）
		return 1;
	}
	return 0;
}
int t_sv6(void) {              //電磁バルブSV6停止処理
	if (g.io.valve.sv6 == 1) {
		g_SV6_ON_T1 = timer_stop_s(g.timer.module.on.io.sv6[0]);//SV6_ON_T1 STOP
		g_SV6_ON_T2 = timer_stop_ms(g.timer.module.on.io.sv6[1]);//SV6_ON_T2 STOP  //*20220831 修正　（渡部夢二）
		SV6_PIN = VALVE_OFF;  //*20220831 修正　（渡部夢二）
		g_SV6_F = 0; // SV6_F = 0    //*20220831 追加　（渡部夢二）
		return 1;      //*20220831 修正　（渡部夢二）
	}
	return 0;
}
int t_sv7(void) {              //電磁バルブSV7（中和処理）停止処理
	if (g.io.valve.sv7 == 1) {
		g_SV7_ON_T1 = timer_stop_s(g.timer.module.on.io.sv7[0]);//SV7_ON_T1 STOP
		g_SV7_ON_T2 = timer_stop_ms(g.timer.module.on.io.sv7[1]);//SV7_ON_T2 STOP　　//*20220831 修正　（渡部夢二）
		SV7_PIN = VALVE_OFF;  //*20220831 修正　（渡部夢二）
		g_NEUTRAL_T = timer_start_s();												//中和処理タイマースタート　SV７起動は中和処理開始のため　20220904追記　goto
		g_SV7_F = 0; // SV7_F = 0    //*20220831 追加　（渡部夢二）
		return 1;  //*20220831 修正　（渡部夢二）
	}
	return 0;
}
int t_p1(void) {               //ポンプ1停止処理
	if (g.io.pump_1 == 1) {
		g_P1_ON_T1 = timer_stop_s(g.timer.module.on.io.p1[0]);//P1_ON_T1 STOP
		g_P1_ON_T2 = timer_stop_ms(g.timer.module.on.io.p1[1]);//P1_ON_T2 STOP
		PUMP_1_PIN = PUMP_OFF;  //*20220831 修正　（渡部夢二）
		g_P1_OFF_T2=timer_start_ms();
		return 1;  //*20220831 修正　（渡部夢二）
	}
	return 0;
}

int t_p2(void) {               //ポンプ2停止処理
	if (g.io.pump_2 == 1) {
		g_P2_ON_T1 = timer_stop_s(g.timer.module.on.io.p2[0]);//P2_ON_T1 STOP
		g_P2_ON_T2 = timer_stop_ms(g.timer.module.on.io.p2[1]);//P2_ON_T1 STOP
		PUMP_2_PIN = PUMP_OFF;  //*20220831 修正　（渡部夢二）
		g_P2_OFF_T2=timer_start_ms();
		return 1;  //*20220831 修正　（渡部夢二）
	}
	return 0;
}
int t_sp(void) {               //ポンプSP停止処理
	if (g.io.salt_pump == 1) {
		g_SP_ON_T1 = timer_stop_s(g.timer.module.on.io.sp[0]);//SP_ON_T1 STOP
		g_SP_ON_T2 = timer_stop_ms(g.timer.module.on.io.sp[1]);//SP_ON_T2 STOP
		SP_PIN = PUMP_OFF;  //*20220831 修正　（渡部夢二）
		g_SP_OFF_T2=timer_start_ms();
		return 1;  //*20220831 修正　（渡部夢二）
	}
	return 0;
}

int tp_3_14(void) {                //塩タンク抜水処理停止処理
	if (g_P_3_14_F) {
		g_P_3_14_ON_T1 = timer_stop_s(g.timer.module.on.p314[0]);//P_3_14_ON_T1 STOP
		g_P_3_14_ON_T2 = timer_stop_ms(g.timer.module.on.p314[1]);//P_3_14_ON_T2 STOP
		g_P_3_14_F = 0;//P_3_1_4_F = 0
	}
	return 0;
}
int tp_8(void) {                    //全機能停止処理停止処理
	if (g_P_8_F) {
		g_P_8_ON_T1 = timer_stop_s(g.timer.module.on.p8[0]);//P_8_ON_T1 STOP
		g_P_8_ON_T2 = timer_stop_ms(g.timer.module.on.p8[1]);//P_8_ON_T2 STOP
		g_P_8_F = 0;//P_8_F = 0
	}
	return 0;
}
int tc_1(void){                     //電解業務制御停止処理
	if(g_C_1_F){
		g_C_1_ON_T1 = timer_stop_s(g.timer.module.on.c1[0]);	//C_1_ON_T1 停止処理
		g_C_1_ON_T2 = timer_stop_ms(g.timer.module.on.c1[1]);	//C_1_ON_T2 停止処理
		g_C_1_ON_T3 = timer_stop_s(g_C_1_ON_T3);				//C_1_ON_T3 電解装置起動積算時間一時停止処理
		g_NEUTRAL_T = timer_stop_s(g_NEUTRAL_T);				//g_NEUTRAL_T中和処理用タイマ一時停止処理
		CVCC_CONTROL_PIN = 0U;									//CVCC「ER＝電解装置」停止処理
		g_C_1_OFF_T2 = timer_start_ms(); 						//C_1_OFF_T2 START
		g_CVCC_RUN_F = 0;
		g_C_1_F = 0;											//C_1_F = 0
	}
	return 0;
}
int tc_2(void){                     //酸タンク状態チェック停止処理
	if(g_C_2_F){
		g_C_2_ON_T1 = timer_stop_s(g.timer.module.on.c2[0]);// C_2_ON_T1 停止処理
		g_C_2_ON_T2 = timer_stop_ms(g.timer.module.on.c2[1]);//C_2_ON_T2 停止処理
		g_C_2_F = 0;//C_2_F = 0
	}
	return 0;
}
/**
 * Do not have information yet
 * @return
 */
int tc_3(void){                     //酸タンク状態チェック停止処理
	if(g_C_3_F){
		g_C_3_ON_T1 = timer_stop_s(g.timer.module.on.c3[0]);//C_3_ON_T1 STOP
		g_C_3_ON_T2 = timer_stop_ms(g.timer.module.on.c3[1]);//C_3_ON_T2 STOP
		g_C_3_F = 0;//C_3_F = 0
	}
	return 0;
}
int tc_4(void){                     //塩タンク状態チェック停止処理
	if(g_C_4_F){
		g_C_4_ON_T1 = timer_stop_s(g.timer.module.on.c4[0]);//C_4_ON_T1 STOP
		g_C_4_ON_T2 = timer_stop_ms(g.timer.module.on.c4[1]);//C_4_ON_T2 STOP
		g_C_4_F = 0;//C_4_F = 0
	}
	return 0;
}
int tc_5(void){                     //電解業務チェック停止処理
	if(g_C_5_F){
		g_C_5_ON_T1 = timer_stop_s(g.timer.module.on.c5[0]);//C_5_ON_T1 STOP
		g_C_5_ON_T2 = timer_stop_ms(g.timer.module.on.c5[1]);//C_5_ON_T2 STOP
		g_C_5_F = 0;//C_5_F = 0
	}
	return 0;
}
int tc_5_1(void){                   //過電圧1チェック停止処理
	if(g_C_5_1_F){
		g_C_5_1_ON_T1 = timer_stop_s(g.timer.module.on.c51[0]); //C_5_1_ON_T1 STOP
		g_C_5_1_ON_T2 = timer_stop_ms(g.timer.module.on.c51[1]);//C_5_1_ON_T2 STOP
		g_C_5_1_F = 0;//C_5_1_F = 0
	}
	return 0;
}
int tc_5_2(void){                   //初期動作モード停止処理
	if(g_C_5_2_F){
		g_C_5_2_ON_T1 = timer_stop_s(g.timer.module.on.c52[0]); //C_5_2_ON_T1 STOP
		g_C_5_2_ON_T2 = timer_stop_ms(g.timer.module.on.c52[1]);//C_5_2_ON_T2 STOP
		g_C_5_2_F = 0;//C_5_2_F = 0
	}
	return 0;
}
int tc_5_3(void){                   //過電圧3チェック停止処理
	if(g_C_5_3_F){
		g_C_5_3_ON_T1 = timer_stop_s(g.timer.module.on.c53[0]); //C_5_3_ON_T1 STOP
		g_C_5_3_ON_T2 = timer_stop_ms(g.timer.module.on.c53[1]);//C_5_3_ON_T2 STOP
		g_C_5_3_F = 0;//C_5_3_F = 0
	}
	return 0;
}
int tc_5_3_1(void){                 //過電圧3チェック子停止処理
	if(g_C_5_3_1_F){
		g_C_5_3_1_ON_T1 = timer_stop_s(g.timer.module.on.c531[0]);//C_5_3_1_ON_T1 STOP
		g_C_5_3_1_ON_T2 = timer_stop_ms(g.timer.module.on.c531[1]);//C_5_3_1_ON_T2 STOP
		g_C_5_3_1_F = 0;//C_5_3_1_F = 0
	}
	return 0;
}
int tc_5_4(void){                   //低電圧チェック停止処理
	if(g_C_5_4_F){
		g_C_5_4_ON_T1 = timer_stop_s(g.timer.module.on.c54[0]);//C_5_4_ON_T1 STOP
		g_C_5_4_ON_T2 = timer_stop_ms(g.timer.module.on.c54[1]);//C_5_4_ON_T2 STOP
		g_C_5_4_F = 0;//C_5_4_F = 0
	}
	return 0;
}
int tc_5_5(void){                   //初期動作モード停止処理
	if(g_C_5_5_F){
		g_C_5_5_ON_T1 = timer_stop_s(g.timer.module.on.c55[0]);//C_5_5_ON_T1 STOP
		g_C_5_5_ON_T2 = timer_stop_ms(g.timer.module.on.c55[1]);//C_5_5_ON_T2 STOP
		g_C_5_5_F = 0;//C_5_5_F = 0
	}
	return 0;
}
int tc_5_6(void){                   //CVCC電源チェック停止処理
	if(g_C_5_6_F){
		g_C_5_6_ON_T1 = timer_stop_s(g.timer.module.on.c56[0]);//C_5_6_ON_T1 STOP
		g_C_5_6_ON_T2 = timer_stop_ms(g.timer.module.on.c56[1]); //C_5_6_ON_T2 STOP
		g_C_5_6_F = 0;//C_5_6_F = 0
	}
	return 0;
}
int tc_6(void){                     //カラン未使用チェック停止処理
	if(g_C_6_F){
		g_C_6_ON_T1 = timer_stop_s(g.timer.module.on.c6[0]);//C_6_ON_T1 STOP
		g_C_6_ON_T2 = timer_stop_ms(g.timer.module.on.c6[1]);//C_6_ON_T2 STOP
		g_C_6_F = 0;//C_6_F = 0
	}
	return 0;
}
int tc_7(void){                     //電解処理未使用チェック停止処理
	if(g_C_7_F){
		g_C_7_ON_T1 = timer_stop_s(g.timer.module.on.c7[0]);//C_7_ON_T1 STOP
		g_C_7_ON_T2 = timer_stop_ms(g.timer.module.on.c7[1]);//C_7_ON_T2 STOP
		g_C_7_F = 0;//C_7_F = 0
	}
	return 0;
}
int tc_8(void){                     //流量センサチェック停止処理
	if(g_C_8_F){
		g_C_8_ON_T1 = timer_stop_s(g.timer.module.on.c8[0]);//C_8_ON_T1 STOP
		g_C_8_ON_T2 = timer_stop_ms(g.timer.module.on.c8[1]);//C_8_ON_T2 STOP
		g_C_8_F = 0;//C_8_F = 0
	}
	return 0;
}
int tc_9(void){                     //中和処理チェック停止処理
	if(g_C_9_F){
		g_C_9_ON_T1 = timer_stop_s(g.timer.module.on.c9[0]);//C_9_ON_T1 STOP
		g_C_9_ON_T2 = timer_stop_ms(g.timer.module.on.c9[1]);//C_9_ON_T2 STOP
		g_C_9_F = 0;//C_9_F = 0
	}
	return 0;
}
int tc_10(void){                    //給水電磁弁漏れチェック停止処理
	if(g_C_10_F){
		g_C_10_ON_T1 = timer_stop_s(g.timer.module.on.c10[0]);//C_10_ON_T1 STOP
		g_C_10_ON_T2 = timer_stop_ms(g.timer.module.on.c10[1]);//C_10_ON_T2 STOP
		g_C_10_F = 0;//C_10_F = 0
	}
	return 0;
}
int tc_11(void){                    //漏水チェック停止処理
	if(g_C_11_F){
		g_C_11_ON_T1 = timer_stop_s(g.timer.module.on.c11[0]);//C_11_ON_T1 STOP
		g_C_11_ON_T2 = timer_stop_ms(g.timer.module.on.c11[1]);//C_11_ON_T2 STOP
		g_C_11_F = 0;//C_11_F = 0
	}
	return 0;
}
int tc_12(void){                    //フィルターチェック停止処理
	if(g_C_12_F){
		g_C_12_ON_T1 = timer_stop_s(g.timer.module.on.c12[0]);//C_12_ON_T1 STOP
		g_C_12_ON_T2 = timer_stop_ms(g.timer.module.on.c12[1]);//C_12_ON_T2 STOP
		g_C_12_F = 0;//C_12_F = 0
	}
	return 0;
}
int tc_13(void){                    //酸アルカリタンク溢れチェック停止処理
	if(g_C_13_F){
		g_C_13_ON_T1 = timer_stop_s(g.timer.module.on.c13[0]);//C_13_ON_T1 STOP
		g_C_13_ON_T2 = timer_stop_ms(g.timer.module.on.c13[1]);//C_13_ON_T2 STOP
		g_C_13_F = 0;//C_13_F = 0
	}
	return 0;
}
int tc_14(void){                    //貯水タンク (アルカリ・酸) 満水チェック停止処理
	if(g_C_14_F){
		g_C_14_ON_T1 = timer_stop_s(g.timer.module.on.c14[0]);//C_14_ON_T1 STOP
		g_C_14_ON_T2 = timer_stop_ms(g.timer.module.on.c14[1]);//C_14_ON_T2 STOP
		g_C_14_F = 0;//C_14_F = 0
	}
	return 0;
}
int tc_15(void){                    //塩タンク蓋開異常チェック停止処理
	if(g_C_15_F){
		g_C_15_ON_T1 = timer_stop_s(g.timer.module.on.c15[0]);//C_15_ON_T1 STOP
		g_C_15_ON_T2 = timer_stop_ms(g.timer.module.on.c15[1]);//C_15_ON_T2 STOP
		g_C_15_F = 0;//C_15_F = 0
	}
	return 0;
}
int tc_16(void){                    //運転積算時間警報チェック停止処理
	if(g_C_16_F){
		g_C_16_ON_T1 = timer_stop_s(g.timer.module.on.c16[0]);//C_16_ON_T1 STOP
		g_C_16_ON_T2 = timer_stop_ms(g.timer.module.on.c16[1]);//C_16_ON_T2 STOP
		g_C_16_F = 0;//C_16_F = 0
	}
	return 0;
}
int tc_17(void){                    //電解積算時間警報チェック停止処理
	if(g_C_17_F){
		g_C_17_ON_T1 = timer_stop_s(g.timer.module.on.c17[0]);//C_17_ON_T1 STOP
		g_C_17_ON_T2 = timer_stop_ms(g.timer.module.on.c17[1]);//C_17_ON_T2 STOP
		g_C_17_F = 0;//C_17_F = 0
	}
	return 0;
}
int tc_18(void){                    //塩水経路３方向弁循環OFF警報チェック停止処理
	if(g_C_18_F){
		g_C_18_ON_T1 = timer_stop_s(g.timer.module.on.c18[0]);//C_18_ON_T1 STOP
		g_C_18_ON_T2 = timer_stop_ms(g.timer.module.on.c18[1]);//C_18_ON_T2 STOP
		g_C_18_F = 0;//C_18_F = 0
	}
	return 0;
}
int tc_19(void){
	if(g_C_19_F){                   //塩タンク排水処理チェック停止処理
		g_C_19_ON_T1 = timer_stop_s(g.timer.module.on.c19[0]);//C_19_ON_T1 STOP
		g_C_19_ON_T2 = timer_stop_ms(g.timer.module.on.c19[1]);//C_19_ON_T2 STOP
		g_C_19_F = 0;//C_19_F = 0
	}
	return 0;
}
int te_1(void){                     //カラン清掃停止処理
	if(g_E_1_F){
		g_E_1_ON_T1 = timer_stop_s(g.timer.module.on.e1[0]);//E_1_ON_T1 STOP
		g_E_1_ON_T2 = timer_stop_ms(g.timer.module.on.e1[1]);//E_1_ON_T2 STOP
		g_E_1_F = 0;//E_1_F = 0
	}
	return 0;
}
/**
 * Blue LED light
 * @return
 */
int t_b_led_l(void){                //青色LED点灯停止処理
	hand_sensor_blink(HS_OFF, 0);
	if(g.flag.module.b_b_led_l){
		//B_LED_L_ON_T1 STOP
		g.timer.module.work.b_led_l[0] = timer_stop_s(g.timer.module.on.b_led_l[0]);
		//B_LED_L_ON_T2 STOP
		g.timer.module.work.b_led_l[1] = timer_stop_ms(g.timer.module.on.b_led_l[1]);//Blue LED OFF
		//B_LED_L_F = 0
		g.flag.module.b_b_led_l = 0;
	}
	return 0;
}
/**
 * Blue LED blink
 * @return
 */
int t_b_led_b(void){                //青色LED点滅停止処理
	hand_sensor_blink(HS_OFF, 0);
	if(g.flag.module.b_b_led_b){
		//B_LED_B_ON_T1 STOP
		g.timer.module.work.b_led_b[0] = timer_stop_s(g.timer.module.on.b_led_b[0]);
		//B_LED_B_ON_T2 STOP
		g.timer.module.work.b_led_b[1] = timer_stop_ms(g.timer.module.on.b_led_b[1]);//Blue LED OFF
		//B_LED_B_F = 0
		g.flag.module.b_b_led_b = 0;
	}
	return 0;
}
/**
 * Red LED light
 * @return
 */
int t_r_led_l(void){                //赤色LED点灯停止処理
	hand_sensor_blink(HS_OFF, 0);
	if(g.flag.module.b_r_led_l){
		//R_LED_L_ON_T1 STOP
		g.timer.module.work.r_led_l[0] = timer_stop_s(g.timer.module.on.r_led_l[0]);
		//R_LED_L_ON_T2 STOP
		g.timer.module.work.r_led_l[1] = timer_stop_ms(g.timer.module.on.r_led_l[1]);//Red LED OFF

		//R_LED_L_F = 0
		g.flag.module.b_r_led_l = 0;
	}
	return 0;
}
/**
 * Red LED blink
 * @return
 */
int t_r_led_b(void){                //赤色LED点滅停止処理
	hand_sensor_blink(HS_OFF, 0);
	if(g.flag.module.b_r_led_b){
		//R_LED_B_ON_T1 STOP
		g.timer.module.work.r_led_b[0] = timer_stop_s(g.timer.module.on.r_led_b[0]);
		//R_LED_B_ON_T2 STOP
		g.timer.module.work.r_led_b[1] = timer_stop_ms(g.timer.module.on.r_led_b[1]);//Red LED OFF

		//R_LED_B_F = 0
		g.flag.module.b_r_led_b = 0;
	}
	return 0;
}
/**
 * White LED light
 * @return
 */
int t_w_led_l(void){                //白色LED点灯停止処理
	hand_sensor_blink(HS_OFF, 0);
	if(g.flag.module.b_w_led_l){
		//W_LED_L_ON_T1 STOP
		g.timer.module.work.r_led_l[0] = timer_stop_s(g.timer.module.on.r_led_l[0]);
		//W_LED_L_ON_T2 STOP
		g.timer.module.work.r_led_l[1] = timer_stop_ms(g.timer.module.on.r_led_l[1]);//White LED OFF

		//W_LED_L_F = 0
		g.flag.module.b_w_led_l = 0;
	}
	return 0;
}
/**
 * White LED blink
 * @return
 */
int t_w_led_b(void){                //白色LED点滅停止処理
	hand_sensor_blink(HS_OFF, 0);
	if(g.flag.module.b_w_led_b){
		//W_LED_B_ON_T1 STOP
		g.timer.module.work.w_led_b[0] = timer_stop_s(g.timer.module.on.w_led_b[0]);
		//W_LED_B_ON_T2 STOP
		g.timer.module.work.w_led_b[1] = timer_stop_ms(g.timer.module.on.w_led_b[1]);//White LED OFF

		//W_LED_B_F = 0
		g.flag.module.b_w_led_b = 0;
	}
	return 0;
}
/**
 * TODO: Not have flow chart yet
 * @return
 */


//以下FLチャタリング停止処理
int ts_4(void) {                //チャタリング停止処理
	if (g.flag.module.bs4) {
		g_S_4_ON_T1 = timer_stop_s(g.timer.module.on.s4[0]);//S_4_ON_T1 STOP
		g_S_4_ON_T2 = timer_stop_ms(g.timer.module.on.s4[1]);//S_4_ON_T2 STOP
		g.timer.module.off.s4[0] = timer_restart_s(g_S_4_OFF_T1);//S_4 OFF_T1 RESTART
		g.timer.module.off.s4[1] = timer_start_ms();//S_4 OFF_T2  START
		g_S_4_F = 0;//S_4_F = 0
	}
	return 0;
}
int ts_4_1(void) {                //FL1チャタリング停止処理
	if (g.flag.module.bs41) {
		g_S_4_1_ON_T1 = timer_stop_s(g.timer.module.on.s41[0]);//S_4_1_ON_T1 STOP
		g_S_4_1_ON_T2 = timer_stop_ms(g.timer.module.on.s41[1]);//S_4_1_ON_T2 STOP
		g.timer.module.off.s41[0] = timer_restart_s(g_S_4_1_OFF_T1);//S_4_1_ OFF_T1 RESTART
		g.timer.module.off.s41[1] = timer_start_ms();//S_4_1_ OFF_T2  START
		g_S_4_1_F = 0;//S_4_1_F = 0　　//*20220831 修正（渡部夢二）
	}
	return 0;
}
int ts_4_2(void) {                //FL2チャタリング停止処理
	if (g.flag.module.bs42) {
		g_S_4_2_ON_T1 = timer_stop_s(g.timer.module.on.s42[0]);//S_4_2_ON_T1 STOP
		g_S_4_2_ON_T2 = timer_stop_ms(g.timer.module.on.s42[1]);//S_4_2_ON_T2 STOP
		g.timer.module.off.s42[0] = timer_restart_s(g_S_4_2_OFF_T1);//S_4_2_ OFF_T1 RESTART
		g.timer.module.off.s42[1] = timer_start_ms();//S_4_2_ OFF_T2  START
		g_S_4_2_F = 0;//S_4_2_F = 0　　//*20220831 修正（渡部夢二）
	}
	return 0;
}
int ts_4_3(void) {                //FL3チャタリング停止処理
	if (g.flag.module.bs43) {
		g_S_4_3_ON_T1 = timer_stop_s(g.timer.module.on.s43[0]);//S_4_3_ON_T1 STOP
		g_S_4_3_ON_T2 = timer_stop_ms(g.timer.module.on.s43[1]);//S_4_3_ON_T2 STOP
		g.timer.module.off.s43[0] = timer_restart_s(g_S_4_3_OFF_T1);//S_4_3_ OFF_T1 RESTART
		g.timer.module.off.s43[1] = timer_start_ms();//S_4_3_ OFF_T2  START
		g_S_4_3_F = 0;//S_4_3_F = 0　　//*20220831 修正（渡部夢二）
	}
	return 0;
}
int ts_4_4(void) {                //FL4チャタリング停止処理
	if (g.flag.module.bs44) {
		g_S_4_4_ON_T1 = timer_stop_s(g.timer.module.on.s44[0]);//S_4_4_ON_T1 STOP
		g_S_4_4_ON_T2 = timer_stop_ms(g.timer.module.on.s44[1]);//S_4_4_ON_T2 STOP
		g.timer.module.off.s44[0] = timer_restart_s(g_S_4_4_OFF_T1);//S_4_4 OFF_T1 RESTART
		g.timer.module.off.s44[1] = timer_start_ms();//S_4_4_ OFF_T2  START
		g_S_4_4_F = 0;//S_4_4_F = 0　　//*20220831 修正（渡部夢二）
	}
	return 0;
}
int ts_4_5(void) {                //FL5チャタリング停止処理
	if (g.flag.module.bs45) {
		g_S_4_5_ON_T1 = timer_stop_s(g.timer.module.on.s45[0]);//S_4_5_ON_T1 STOP
		g_S_4_5_ON_T2 = timer_stop_ms(g.timer.module.on.s45[1]);//S_4_5_ON_T2 STOP
		g.timer.module.off.s45[0] = timer_restart_s(g_S_4_5_OFF_T1);//S_4_5_ OFF_T1 RESTART
		g.timer.module.off.s45[1] = timer_start_ms();//S_4_5_ OFF_T2  START
		g_S_4_5_F = 0;//S_4_5_F = 0　　//*20220831 修正（渡部夢二）
	}
	return 0;
}
int ts_4_6(void) {                //FL6チャタリング停止処理
	if (g.flag.module.bs46) {
		g_S_4_6_ON_T1 = timer_stop_s(g.timer.module.on.s46[0]);//S_4_6_ON_T1 STOP
		g_S_4_6_ON_T2 = timer_stop_ms(g.timer.module.on.s46[1]);//S_4_6_ON_T2 STOP
		g.timer.module.off.s46[0] = timer_restart_s(g_S_4_6_OFF_T1);//S_4_6_ OFF_T1 RESTART
		g.timer.module.off.s46[1] = timer_start_ms();//S_4_6_ OFF_T2  START
		g_S_4_6_F = 0;//S_4_6_F = 0  //*20220831 修正（渡部夢二）
	}
	return 0;
}
int ts_4_7(void) {                //FL7チャタリング停止処理
	if (g.flag.module.bs47) {
		g_S_4_7_ON_T1 = timer_stop_s(g.timer.module.on.s47[0]);//S_4_7_ON_T1 STOP
		g_S_4_7_ON_T2 = timer_stop_ms(g.timer.module.on.s47[1]);//S_4_7_ON_T2 STOP
		g.timer.module.off.s47[0] = timer_restart_s(g_S_4_7_OFF_T1);//S_4_7_ OFF_T1 RESTART
		g.timer.module.off.s47[1] = timer_start_ms();//S_4_7_ OFF_T2  START
		g_S_4_7_F = 0;//S_4_7_F = 0　　//*20220831 修正（渡部夢二）
	}
	return 0;
}
int ts_4_8(void) {                //FL8チャタリング停止処理
	if (g.flag.module.bs48) {
		g_S_4_8_ON_T1 = timer_stop_s(g.timer.module.on.s48[0]);//S_4_8_ON_T1 STOP
		g_S_4_8_ON_T2 = timer_stop_ms(g.timer.module.on.s48[1]);//S_4_8_ON_T2 STOP
		g.timer.module.off.s48[0] = timer_restart_s(g_S_4_8_OFF_T1);//S_4_8_ OFF_T1 RESTART
		g.timer.module.off.s48[1] = timer_start_ms();//S_4_8_ OFF_T2  START
		g_S_4_8_F = 0;//S_4_8_F = 0　　//*20220831 修正（渡部夢二）
	}
	return 0;
}
int te_1_1(void){
	return 0;
}

int tc_23(void){
	return 0;
}
int tc_24(void){
	return 0;
}

int t_p_2_1(void){
	return 0;
}
