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

#define ON		(1U)
#define OFF		(0U)

enum DEBUG{
	OPERATION_INIT,
	DRAIN_ALKA,
	OVERLAP_ALKA,
	DRAIM_ACID,
	OVERLAP_ACID,
	DRAIN_WATER,
	OVERLAP_WATER,
	DONE
}washing_debug;

int p_0(void){                                    //システムメイン起動処理
	bp_0();                                       //システムメイン起動処理
	/**
	 * TODO Bypass init progcess for testing
	 */
//	SYSTEM_MODE = NORMAL;
	if(SYSTEM_MODE == INIT)
		p_1();                                        //初期動作モード
	runtime();
	SYSTEM_MODE = NORMAL;
	while ( 1 )	{												//20220903 フローチャートとの違いのため作成　goto
		switch (SYSTEM_MODE) {                    //メモリに書かれているモードへ
		case INDIVIDUAL:
			p_3();									//個別動作モード
			break;
		case NORMAL:						        	//SYSTEM＿MOD値を確認
		case WASHING:
			p_2();                                //通常動作モード
			break;
		default:
			//Not going here
			break;
		}															//20220903 フローチャートとの違いのため作成　goto
		runtime();
	}
}								//TODO Fix add }
int p_1(void){
	runtime();
	t_b_led_l();
	t_r_led_l();
	t_w_led_l();
	bp_1();                                       //初期動作モード起動水処理
	p_1_1();                                      //初期抜水処理
	p_1_2();                                      //初期給水処理
	c_4();                                        //塩Tankチェック処理
	//c_5();                                        //電解業務チェック処理　フローチャートと相違　コメント行に　20220903goto
	p_1_3();                                      //初期Electrolysis水生成処理
	p_1_4();                                      //初期抜水第２処理
	p_1_5(); 							//Electrolysis水作成第２処理
//	p_1_5_2();
	//Drain water
//	p_1_1();                                      //replace p15 by this p11
	tp_1();                                       //初期動作モードStop process
	return 0;
}


int p_1_1(void) {                                 //初期抜水処理
	bp_1_1();                                     //初期抜水起動処理
	p_1_1_1();                                    //初期両タンク抜水処理
	tp_1_1();                                     //初期抜水終了処理
	return 0;
}

int p_1_1_1(void){                                //初期両タンク抜水処理          		//20220903 このモジュール全体修正　goto
	bp_1_1_1();                                  //両タンク抜水起動処理
	if(s_1() > 0){   							//アルタンク空ではない     //if(s1_alkali_tank_data_set() && g_ALD > 0)　簡素化　20220903goto
		b_sv6();                                  //(Alkali Drain) 開 ON
		wait(500);
		b_p2();                                   //(Alkali Pump) ポンプ ON
		//g.flag.alkali_drainning = 1;              //いらない
	}

	if(s_2() > 0){     							  //酸タンク空ではない && g_ACD > 0を追加　イシイ  // s2_acid_tank_data_set() && g_ACD > 0  簡素化　20220903goto
		b_sv5();                                  //(Acid Drain) 起動処理
		wait(500);
		b_p1();                                   //(Acid Pump) ポンプ 起動処理
		g.flag.acid_drainning = 1;                //いらない
	}
	while(s_1() > 0 || s_2() > 0){                //タンク空確認
		if(s_1() == 0 ){ 								//アルタンク空ではない,=を＞に修正　イシイ　　　//フロー＾チャート変更
			if(g_P2_F == 1){     				//アルカリタンク抜水処理フラグ = 1 TODO: change to g_P2_F
				// g.flag.alkali_drainning = 0;      //アルカリタンク抜水処理フラグ = 0,いらない
				p_1_1_2();                        //アルカリタンク抜水一時停止処理
			}
		}
		if(s_2() == 0 ){							 //酸タンク空ではない,=を＞に修正　イシイ
			if(g_P1_F == 1){       				//酸タンク抜水処理フラグ = 1
				// g.flag.acid_drainning = 0;        //酸タンク抜水処理フラグ = 0,いらない
				p_1_1_3();                        //酸タンク抜水一時停止処理
			}
		}
		runtime();
	}
	p_1_1_4();                                    //アルカリタンク抜水最終処理
	p_1_1_5();                                    //酸タンク抜水最終処理
	tp_1_1_1();                                   //両タンク抜水停止処理
	return 0;
}
int p_1_1_2(void){                                //アルカリタンク抜水一時停止処理
	t_p2();                                       //(アルポンプ) 停止処理
	t_sv6();                                      //(アル抜水) 停止処理
	return 0;
}
int p_1_1_3(void){                                //酸タンク抜水一時停止処理
	t_p1();                                       //(酸ポンプ) 停止処理
	t_sv5();                                      //(酸抜水) 停止処理
	return 0;
}
int p_1_1_4(void){                                //アルカリタンク抜水最終停止処理
	b_sv6();                                      //(アル抜水) 起動処理
	wait(500);
	b_p2();                                       //(アルポンプ) 起動処理
	wait(g_T_S.t108_ms);                            //g_T_S.t1_msをg_T_S.t108_Mに修正 (CY)
	t_p2();                                       //(アルポンプ) 停止処理
	t_sv6();                                      //(アル抜水) 停止処理
	return 0;
}
int p_1_1_5(void){                                //酸タンク抜水最終停止処理
	b_sv5();                                      //(酸抜水) 開
	wait(500);
	b_p1();                                       //(酸ポンプ) 動
	wait(g_T_S.t108_ms);                            //g_T_S.t1_msをg_T_S.t108_Mに修正 (CY)
	t_p1();                                       //(酸ポンプ) 停止処理
	t_sv5();                                      //(酸抜水) 停止処理
	return 0;
}
//new_plan イシイ
int p_1_2(void) {                                 //初期給水処理
	bp_1_2();                                     //初期給水起動処理
	b_sv2();                                      //(水吐水) ON 起動処理
	wait(30 * 1000);	//TODO Lower the value for testing
    b_sv1();
    wait(500);
	t_sv2();                                      //(水吐水) OFF 停止処理
	wait(g_T_S.t149_s * 1000);                      //g_T_S.t2_msをg_T_S.t149_Mに修正 (CY)
	p_3_13();
	tp_1_2();                                     //初期給水停止処理
	return 0;
}

int p_1_3(void) {                                 //初期Electrolysis水生成処理
	p_1_3_1();                                    //初期ElectrolysisStart処理
	do {
		c_5();										//*電解チェック　追加　20220903　goto
		s_1();
		s_2();
		runtime();
	} while (g_ALD != 3 || g_ACD != 3);
	p_1_3_2();                                    //初期ElectrolysisStart終了処理
	return 0;
}

int neutralized_timer_on(void) {
	g.timer.c1_on = timer_start_ms();
	return g.timer.c1_on;
}
int neutralized_timer_off(void) {
	return elapsed_time_ms(g.timer.c1_on);
}


int p_1_3_1(void) {                               //初期電解起動t処理
	b_sv1();                                      //(給水) 起動処理
	b_sp();                                       //(Salt Pump) 起動処理
	wait(g_T_S.t107_s * 1000);                     //g_T_S.t16_sをg_T_S.t107_Sに修正 (CY)
	bp_1_3();                                     //初期Electrolysis終了処理
	// neutralized_timer_on();                       //Neutralized Timer起動 (初起動)
	g_NEUTRAL_T=timer_start_s();						 //Neutralized Timer起動 (初起動) 20220903修正
	//g.timer.faucet_off = timer_start_ms();              //カラン未使用タイマタイマ (初起動)
	g_FAUCET_OFF_T3 = timer_start_s();				//カラン未使用タイマタイマ (初起動)
	return 0;
}

int p_1_3_2(void) {                               //初期ElectrolysisStart終了処理
	tp_1_3();                                     //Initial Electrolysis Stop Process
	t_sp();                                       //(Salt Pump) 停止処理
	wait(g_T_S.t145_s * 1000);						 //g_T_S.t5_sをg_T_S.t145_Sに修正 (CY)
	t_sv1();                                      //SV1（給水）停止処理
	//neutralized_timer_off();                      //Neutralized Timer 停止処理
	g_NEUTRAL_T = timer_stop_ms(g_NEUTRAL_T);				 //Neutralized Timer 停止処理 20220903 sdd GOTO
	return 0;
}
uint16_t we_are_here;

int p_1_4(void) {                                 //初期抜水第２処理
	we_are_here++;
	bp_1_4();                                     //初期抜水第２起動処理
	we_are_here++;
	p_1_1_1();                                    //初期両タンク抜水処理
	we_are_here++;
	tp_1_4();                                     //初期抜水第２終了処理
	we_are_here++;
	return 0;
}
int p_1_5(void) {                                 //2nd Electrolysis Start Process
	we_are_here++;
	p_1_5_1();                                   //電解開始第２処理
	we_are_here++;
	do {
		c_5();									// 20220902 add goto
		s_1();
		s_2();
		runtime();
	} while (g_ALD != 3 || g_ACD != 3);
	we_are_here++;
	p_1_5_2();                                    //2nd Electrolysis Stop process; 電解終了第２処理
	we_are_here++;
	return 0;
}
int p_1_5_1(void) {   //2nd Electrolysis Start Process
	b_sv1();                                      //(給水) 起動処理 ON
	b_sp();                                       //(Salt Pump) 起動処理 ON
	wait(g_T_S.t144_s * 1000);						//g_T_S.t4_2_sをg_T_S.t144_Sに修正 (CY)
	bp_1_5();                                     //Electrolysis Start Process
	//neutralized_timer_on();                       //Neutralized Timer 起動
	g_NEUTRAL_T=timer_restart_s(g_NEUTRAL_T);						//Neutralized Timer 起動20220903 sdd GOTO
	return 0;
}


//new_plan イシイ
int p_1_5_2(void) { //2nd initial Electrolysis Stop process
    tp_1_5();                                     //Electrolysis水生成第2停止処理 追加
	t_sp();                                       //(Salt Pump) 停止処理 OFF
	wait(g_T_S.t145_s * 1000); 						//g_T_S.t5_sをg_T_S.t145_Sに修正 (CY)
	t_sv1();                                      //(給水) 停止処理 OFF
	//neutralized_timer_off();                      // 中和タイマー停止処理
	g_NEUTRAL_T=timer_stop_s(g_NEUTRAL_T);				 // 中和タイマー停止処理
	return 0;
}
int p_2(void){                                    //吐水モード
	bp_2();										  //吐水モード起動処理
	do{
		c_1(C1_ON);				                  //電解業務開始処理
		switch ( WASH_MODE) {					//TODO: Change to WASHING_MODE
			case HAND_WASHING_MODE:
				p_2_4();                          //手洗いモード
				break;
			case WATER_MODE:
				p_2_3();                          //水吐水モード
				break;
			case ACID_MODE:
				p_2_2();                          //酸性水吐水モード
				break;
			case ALKALI_MODE:
				p_2_1();                          //アルカリ水吐水モード
				break;
			default:
				//Crash
				break;
		}
		runtime();
	}while(SYSTEM_MODE == WASHING);
	c_1(OFF);                                  //電解業務停止処理  //c_1(C_1 OFF)を修正20220903goto
	tp_2();                                       //吐水モード停止処理
	return 0;
}
int p_2_1(void){                                  //アルカリ水吐水モード
	bp_2_1();                                     //アルカリ水吐水モード起動処理
	// Large loop
	do {
		c_1(ON);                               //電解業務処理 (ON)
		c_23();
		c_24();                                  //長時間チェック処理  追加(CY)
		if(SYSTEM_MODE != WASHING ||  WASH_MODE != ALKALI_MODE ){	//吐水モードでないか、アルカリ性水モードでない
			t_p_2_1();                                     //アルカリ吐水モード停止処理
			return 0;
		}
		if(check_hand_sensor() == 1){
			b_sv4();                              //SV4(アル吐水) 起動処理
			b_p2();                               //P2(アルポンプ) 起動処理
			b_b_led_l();						//TODO: Blink led on Hand sensor

			//g.timer.alkali_discharge = timer_start_ms();
			// Small loop
			while( check_hand_sensor() == 1 || elapsed_time_ms(g_P_2_1_ON_T2) >= g_T_S.t125_s * 1000){	//g_T_S.t35_sをg_T_S.t125_Sに修正 (CY))
				c_1(ON);
				runtime();
			}

			t_p2();                               //P2(アルポンプ) OFF 設定処理
			t_sv4();                              //SV4 (アル吐水) OFF 設定処理
			t_b_led_l();						//TODO: Turn off blinking LED on hand sensor
			g_FAUCET_OFF_T3 = timer_start_s();
		}
		runtime();
	}while(SYSTEM_MODE == WASHING);				//吐水モードの間は続ける
	return 0;

}
int p_2_2(void){                                   //酸性水吐水モード
	bp_2_2();                                     //酸性水吐水モード起動処理
	// Large loop
	do {
		c_1(ON);                               //電解業務処理 (ON)
		c_23();									//主チェック処理
		c_24();                                  //長時間チェック処理  追加(CY)
		if(SYSTEM_MODE != WASHING ||  WASH_MODE !=  ACID_MODE ){		//吐水モードでないか、酸性水モードでない
			tp_2_2();                                     //酸性水吐水モード停止処理
			return 0;
		}
		if(check_hand_sensor() == 1){
			b_sv3();                              //SV3(酸性吐水) 起動処理
			b_p1();                               //P2（酸性ポンプ) 起動処理
			b_r_led_l();						//TODO: Blink led on Hand sensor

			//g.timer.alkali_discharge = timer_start_ms();
			// Small loop
			while( check_hand_sensor() == 1 || elapsed_time_ms(g_P_2_2_ON_T2) >= g_T_S.t126_s * 1000){	//g_T_S.t35_sをg_T_S.t126_Sに修正 (CY))
				c_1(ON);
				c_23();									//主チェック処理
				runtime();
			}
			t_p1();                               //P2(酸性ポンプ) OFF 設定処理
			t_sv3();                              //SV4 (酸性吐水) OFF 設定処理
			t_r_led_l();						//TODO: Turn off blinking LED on hand sensor
			g_FAUCET_OFF_T3 = timer_start_s();
		}
		runtime();
	}while(SYSTEM_MODE == WASHING);					//吐水モードの間は続ける
	return 0;
}
//
//int p_2_3(void){                                   //水吐水吐水モード
//	bp_2_3();                                     //水吐水吐水モード起動処理
//	// Large loop
//	do {
//		c_1(ON);                               //電解業務処理 (ON)
//		c_23();									//主チェック処理
//		c_24();                                  //長時間チェック処理  追加(CY)
//		if(SYSTEM_MODE != WASHING ||  WASH_MODE != WATER_MODE ){		//吐水モードでないか、酸性水モードでない
//			tp_2_2();                                     //水吐水吐水モード停止処理
//			return 0;
//		}
//		if(check_hand_sensor() == 1){
//			b_sv2();                              //SV2(水吐水吐水) 起動処理
//			b_w_led_l();						//TODO: Blink led on Hand sensor
//
//			//g.timer.alkali_discharge = timer_start_ms();
//			// Small loop
//			while( check_hand_sensor() == 1 || elapsed_time_ms(g_P_2_3_ON_T2) >= g_T_S.t127_s * 1000){	//g_T_S.t34_sをg_T_S.t127_Sに修正 (CY))
//				c_1(ON);
//				c_23();									//主チェック処理
//				runtime();
//			}
//			t_sv2();                              //SV4 (水吐水吐水) OFF 設定処理
//			t_w_led_l();						//TODO: Turn off blinking LED on hand sensor
//			FAUCET_OFF_T3 = timer_start_s();
//		}
//		runtime();
//	}while(SYSTEM_MODE == WASHING);					//吐水モードの間は続ける
//	return 0;
//}


int p_2_3(void){                                  //水吐水処理
	bp_2_3();                                     //水吐水モード起動処理
	// Large loop
	do{
		c_1(C1_ON);                               //電解業務処理 (ON)
		c_23();									//主チェック処理
		c_24();                                   //長時間チェック処理  追加(CY)
		if(check_hand_sensor() || SYSTEM_MODE == NORMAL){
			b_sv2();                              //(水吐水) 起動処理
			//TODO: Blink LED on hand sensor

			g.timer.water_discharge = timer_start_ms();
			// Small loop
			do {
				if (check_hand_sensor() || elapsed_time_ms(g.timer.water_discharge) >= g_T_S.t127_s * 1000 ){//g_T_S.t34_sをg_T_S.t127_Sに修正 (CY)
					SYSTEM_MODE = NORMAL;
				}else{
					c_1(C1_ON);                   //電解業務処理 (ON)
					c_23();							//主チェック処理
				}
				runtime();
			}while(SYSTEM_MODE == WASHING);
			t_sv2();                              //(水吐水) 停止処理
			//TODO: Turn off blinking LED on hand sensor

		}
		runtime();
	}while(SYSTEM_MODE != INDIVIDUAL);

	tp_2_3();                                     //水吐水モード停止処理
	return 0;
}
uint8_t running_hand_washing_debug;
//uint8_t state, pre_state;
int p_2_4(void){                                  //手洗いモード(全部出る)
	bp_2_4();                                     //手洗いモード起動処理
	running_hand_washing_debug = 1;
	do{
		runtime();
		c_1(C1_ON);                               //電解業務処理 (ON)
		c_23();									//主チェック処理
		c_24();                                   //長時間チェック処理  追加(CY)
		if ((SYSTEM_MODE != NORMAL && SYSTEM_MODE != WASHING ) ||  WASH_MODE != HAND_WASHING_MODE){
			tp_2_4();							//手洗い水モード停止処理
			return 0;
		}

		if(check_hand_sensor() == 1){
			++running_hand_washing_debug;
		//	SYSTEM_MODE = WASHING;
			p_2_4_1_1();                          //手洗いモード用アルカリ吐水開始処理
			running_hand_washing_debug++;			//3
//			runtime();
			p_2_4_1_2();                          //手洗いモード用アルカリ吐水処理
			running_hand_washing_debug++;			//4
//			runtime();
			p_2_4_2_1();                          //手洗いモード用酸吐水開始処理
			running_hand_washing_debug++;
//			runtime();
			p_2_4_1_3();                          //手洗いモード用アルカリ吐水終了処理
			running_hand_washing_debug++;			//6
//			runtime();
			p_2_4_2_2();                          //手洗いモード用酸吐水処理
			running_hand_washing_debug++;			//7
//			runtime();
			p_2_4_3_1();                          //手洗いモード用水吐水開始処理
			running_hand_washing_debug++;			//8
//			runtime();
			p_2_4_2_3();                          //手洗いモード用酸吐水終了処理
			running_hand_washing_debug++;			//9
			p_2_4_3_2();                          //手洗いモード用水水出処理
			running_hand_washing_debug++;			//10
			p_2_4_3_3();                          //手洗いモード用水吐水終了処理
			running_hand_washing_debug++;			//11
		}
		runtime();
	}while(1);
}


void p_2_4_1_1(void){                             //手洗モード用アルカリ吐出開始処理
	bp_2_4_1();                                   //手洗モード用アルカリ吐出起動処理
	b_sv4();                                      //(アル吐水) 起動処理
	b_p2();                                       //(アルポンプ) 起動処理
	//g.timer.alkali_discharge = timer_start_ms();　　　　//フローチャート上では消されている P2ポンプのタイマーを使用20220903goto
}

void p_2_4_1_2(void){                             //手洗モード用アルカリ吐出処理
	b_b_led_l();	                               //LED点灯処理 追加
	washing_debug = DRAIN_ALKA;
	if (elapsed_time_ms(g_P2_ON_T2) < (g_T_S.t119_s - 2)*1000){      //変更 (イシイ)
		c_1(C1_ON);                               //電解業務処理（ON）
	}
	b_b_led_b();                                     //Callan 青LED 点滅処理  // 20220905 修正　b_b_led_l→t_b_led_l goto

	if (elapsed_time_ms(g_P2_ON_T2) > (g_T_S.t119_s * 1000) -  g_T_S.t120_ms){    //規定値
		c_1(C1_ON);                               //電解業務処理（ON）
	}
    return ;
}
void p_2_4_1_3(void){                             //手洗モード用アルカリ吐出終了処理
	washing_debug = OVERLAP_ALKA;
	while (elapsed_time_ms(g_P2_ON_T2) <= g_T_S.t119_s * 1000){       //g_T_S.t29_sをg_T_S.t119_Sに修正 (イシイ)
		c_1(C1_ON);                               //電解業務処理（ON）
		runtime();
	}
	t_b_led_l();                                 //LED点灯処理 追加

	t_p2();                                       //P2（アルポンプ）停止処理
	t_sv4();                                      //SV4（アル吐水）停止処理
//	NOT_SPOUTING_TSTART

	tp_2_4_1();                                   //手洗いモードアルカリ吐出停止処理
}
void p_2_4_2_1(void){                             //手洗モード用酸吐出開始処理
	bp_2_4_2();                                   //手洗いモード酸吐出起動処理
	b_sv3();                                      //SV3（酸吐水）起動処理
	b_p1();                                       //P1（酸ポンプ）起動処理
	g.timer.acid_discharge = timer_start_ms();          //いらない イシイ
}
void p_2_4_2_2(void){                             //手洗モード用酸吐出処理
	b_r_led_l();			//TODO: Turn ON hand sensor LED (Red)         //Callan 赤LED 点灯処理
	washing_debug = DRAIM_ACID;
	if(elapsed_time_ms(g_P1_ON_T2) < (g_T_S.t121_s - 2)*1000){
        c_1(ON);
    }
	while(g_T_S.t121_s * 1000 - elapsed_time_ms(g_P1_ON_T2) > 2 * 1000 ){		 //g_T_S.t31_sをg_T_S.t121_Sに修正 (イシイ
		c_1(C1_ON);                               //電解業務処理（ON）
		runtime();
	}
	b_r_led_b();		//TODO: Blink hand sensor LED (Red)           //Callan 赤LED 点滅処理

	while (elapsed_time_ms(g_P1_ON_T2) <= g_T_S.t121_s * 1000 &&
			(uint32_t)g_T_S.t121_s * 1000 - elapsed_time_ms(g_P1_ON_T2) <= g_T_S.t120_ms){//g_T_S.t30_sをg_T_S.t121_Sに修正 g_T_S.t32_msをg_T_S.t120_msに修正 (CY)
		runtime();
		c_1(C1_ON);                               //電解業務処理（ON）
	}
}

void p_2_4_2_3(void){                             //手洗モード用酸吐出終了処理
	washing_debug = OVERLAP_ACID;
	while (elapsed_time_ms(g_P1_ON_T2) <= (uint32_t)g_T_S.t121_s * 1000){//g_T_S.t30_sをg_T_S.t121_Sに修正 (CY)
		c_1(C1_ON);                               //電解業務処理（ON）
		runtime();
	}
	t_r_led_b();	//TODO: Turn off hand sensor LED              //Callan 赤LED 停止処理

	t_p1();                                       //P1（酸ポンプ）OFF 設定処理
	t_sv3();                                      //SV3（酸吐水）OFF 設定処理
			//TODO: 酸未吐水タイマ＝0 P1_ON_T2 =0

	tp_2_4_2();                                   //手洗いモード酸吐出停止処理
}
int p_2_4_3(void){                                //手洗いモード用水吐出処理
    p_2_4_3_1();                                  //手洗いモード用水吐出開始処理
    p_2_4_3_2();                                  //手洗いモード用水吐出処理
    p_2_4_3_3();                                  //手洗いモード用水吐出終了処理
    return 0;
}

void p_2_4_3_1(void){                             //手洗モード用水吐出開始処理
	bp_2_4_3();                                   //手洗いモード水吐出起動処理
	b_sv2();                                      //SV2（水吐水）起動処理
	g.timer.water_discharge = timer_start_ms();
	washing_debug = DRAIN_WATER;
}
void p_2_4_3_2(void){                             //手洗モード用水吐出処理
	 b_w_led_l();//TODO: Turn ON hand sensor (WHITE)           //Callan 白LED 点灯処理

}
void p_2_4_3_3(void){                             //手洗モード用水吐出終了処理
	while (elapsed_time_ms(g_SV2_ON_T2) <= g_T_S.t123_s * 1000){				//g_T_S.t31_sをg_T_S.t123_Sに修正 (CY)
		c_1(C1_ON);                               //電解業務処理（ON）
		runtime();
	}
	t_w_led_b();//TODO: Turn off hand sensor LED

	t_sv2();                                      //SV2（水吐水）停止処理
					//TODO: 水未吐水タイマ＝0

	tp_2_4_3();                                   //手洗いモード水吐出停止処理
	washing_debug = DONE;
}

/*
#define VALVE_ON	(1U)
#define VALVE_OFF	(0U)
#define PUMP_ON		(0U)
#define PUMP_OFF	(1U)
#define LEVEL_ON	(0U)
#define LEVEL_OFF	(1U)


#define SV1_PIN			(P1_bit.no7)
#define SV2_PIN			(P5_bit.no5)
#define SV3_PIN			(P7_bit.no6)
#define SV4_PIN			(P7_bit.no7)
#define SV5_PIN			(P6_bit.no7)
#define SV6_PIN			(P6_bit.no6)
#define SV7_PIN			(P6_bit.no5)
#define PUMP_1_PIN		(P6_bit.no2)
#define PUMP_2_PIN		(P6_bit.no1)
#define SP_PIN			(P6_bit.no0)

#define SW1_PIN			(P5_bit.no2)
#define SW2_PIN			(P14_bit.no7)
#define SW3_PIN			(P10_bit.no0)

#define CVCC_CONTROL_PIN	(P14_bit.no2)
#define CVCC_ALARM_OUT_PIN	(P13_bit.no0)
#define CVCC_ALARM_IN_PIN	(P0_bit.no4)

#define FL1		(P7_bit.no1)
#define FL2		(P7_bit.no2)
#define FL3		(P7_bit.no3)
#define FL4		(P0_bit.no5)
#define FL5		(P0_bit.no6)
#define FL6		(P7_bit.no0)
#define FL7		(P5_bit.no4)
#define FL8		(P5_bit.no3)

#define FLOW_SENSOR_PIN		(P0_bit.no1)

#define O_HS_IDA_PIN	(P1_bit.no5)
#define O_HS_ICL_PIN	(P1_bit.no6)
#define I_HS_OCL_PIN	(P7_bit.no4)
#define I_HS_ODA_PIN	(P7_bit.no5)
*/
int p_3(void){
    p_8();
    bp_3();
    while(SYSTEM_MODE == 1){
 /*       if(g_SV1_SF != SV1_PIN)         {    p_3_1();    }             //   SV1
        if(g_SV2_SF != SV2_PIN)         {    p_3_2();    }             //   SV2
        if(g_SV3_SF != SV3_PIN)         {    p_3_3();    }             //   SV3
        if(g_SV4_SF != SV4_PIN)         {    p_3_4();    }             //   SV4
        if(g_SV5_SF != SV5_PIN)         {    p_3_5();    }             //   SV5
        if(g_SV6_SF != SV6_PIN)         {    p_3_6();    }             //   SV6
        if(g_SV7_SF != SV7_PIN)         {    p_3_7();    }             //   SV7
        if(g_P1_SF  != PUMP_1_PIN )     {    p_3_8();    }             //   SV8
        if(g_P2_SF  != PUMP_2_PIN )     {    p_3_9();    }             //   SV9
        if(g_SP_SF  == SP_PIN )         {    p_3_10();   }             //   SV10
        if(g_C_1_SF == CVCC_CONTROL_PIN){    p_3_11();   }             //   SV11

        g_SV1_SF = SV1_PIN;
        g_SV2_SF = SV2_PIN;
        g_SV3_SF = SV3_PIN;
        g_SV4_SF = SV4_PIN;
        g_SV5_SF = SV5_PIN;
        g_SV6_SF = SV6_PIN;
        g_SV7_SF = SV7_PIN;
        g_p1_SF  = PUMP_1_PIN_PIN;
        g_p2_SF  = PUMP_2_PIN_PIN;
        g_SP_SF  = SP_PIN;
        g_C_1_SF = CVCC_CONTROL_PIN;        */
    }
    p_8();
    tp_3();
    return 0;
}

/*
int p_3_1(void){                                  //電磁弁操作処理（SV1（給水））
	if(g_SV1_F == 0){                             //g_sv1_F == 0に変更 イシイ
		b_sv1();                                  //SV1（給水）起動処理
		return ;                                  //追加　イシイ
	}else{
		t_sv2();                                  //SV1（給水）停止処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}
	return SV1_PIN;
}
int p_3_2(void){                                  //電磁弁操作処理（SV2（水吐水））
	if(g_SV2_F == 0){                             //g_sv2_F == 0に変更 イシイ
		b_sv2();                                  //SV2（水吐水）起動処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}else{
		t_sv2();                                  //SV2（水吐水）停止処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}
	return SV2_PIN;
}
int p_3_3(void){                                  //電磁弁操作処理（SV3（酸吐水））
	if(g_SV3_F == 0){                             //g_sv3_F == 0に変更 イシイ
		b_sv3();                                  //SV3（酸吐水）起動処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}else if (PUMP_1_PIN == PUMP_OFF || SV5_PIN == VALVE_ON){
		t_sv3();                                  //SV3（酸吐水）停止処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}
	return SV3_PIN;
}
int p_3_4(void){                                  //電磁弁操作処理（SV4（アル吐水））
	if(g_SV4_F == 0){                             ////g_sv4_F == 0に変更 イシイ
		b_sv4();                                  //SV4（アル吐水）起動処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}else if(PUMP_2_PIN == PUMP_OFF || SV6_PIN == VALVE_ON) {
		t_sv4();                                  //SV4（アル吐水）停止処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}
	return SV4_PIN;
}
int p_3_5(void){                                  //電磁弁操作処理（SV5（酸抜水））
	if(g_SV5_F == 0){                             //g_sv5_F == 0に変更 イシイ
		b_sv5();                                  //SV5（酸抜水）起動処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}else if (PUMP_1_PIN == PUMP_OFF || SV3_PIN == VALVE_ON){
		t_sv5();                                  //SV5（酸抜水）停止処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}
	return SV5_PIN;
}
int p_3_6(void){                                  //電磁弁操作処理（SV6（アル抜水））
	if(g_SV6_F == 0){                             //g_sv6_F == 0に変更 イシイ
		b_sv6();                                  //SV6（アル抜水）ON設定処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}else if(PUMP_2_PIN == PUMP_OFF || SV4_PIN == VALVE_ON){
		t_sv6();                                  //SV6（アル抜水）OFF設定処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}
	return SV6_PIN;
}
int p_3_7(void){                                  //電磁弁操作処理（SV7（中和））
	if(g_SV7_F == 0 && ){                             //g_sv2_F == 0に変更 イシイ
		b_sv7();                                  //SV7（中和）起動処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}else{
		t_sv7();                                  //SV7（中和）停止処理
		return ;　　　　　　　　　　　　　　　　　　//追加　イシイ
	}
	return SV7_PIN;
}

int p_3_8(void){                                  //ポンプ操作処理P1（酸ポンプ）
 	if(g_SV3_F == ){
        if(g_SV5_F == 0){
            return 0;
        }
    }
    if(g_P1_F == 0){
         b_p1();                               //P1（酸ポンプ）起動処理
        return 0 ;                              //追加　イシイ
    }else{
        t_p1();                               //P1（酸ポンプ）停止処理
        return 0 ;                              //追加　イシイ
    }
}

int p_3_9(void){                                  //ポンプ操作処理P1（アルカリポンプ）
 	if(g_SV4_F == ){
        if(g_SV6_F == 0){
            return 0;
        }
    }
    if(g_P2_F == 0){
         b_p2();                               //P2（アルポンプ）起動処理
        return 0 ;                              //追加　イシイ
    }else{
        t_p2();                               //P2（アルポンプ）停止処理
        return 0 ;                              //追加　イシイ
    }
}

int p_3_10(void){                                 //ポンプ操作処理（塩ポンプ）
	if(g.flag.io.salt_pump && g.flag.electrolysis == 0){
		b_sp();                                   //SP（塩ポンプ）起動処理
	}else if(!g.flag.io.salt_pump){
		t_sp();                                   //SP（塩ポンプ）停止処理
	}
	return SP_PIN;
}


int p_3_11(void){                                 //電解機器操作処理
	if(g_CVCC_RUN_F == 0){                        //g_CVCC_RUN_F == 0に変更 イシイ
		p_1_3_1();                                //単独電解業務開始処理
        g_CVCC_RUN_F = 1                          //追加 イシイ
	}else{
		p_1_3_2();                                //電解業務終了処理
        g_CVCC_RUN_F = 0                          //追加 イシイ
	}
	return CVCC_CONTROL_PIN;
}
//追加 ワタベ
int p_3_11_1(void){　　　　　　　　　　//20220901 修正（渡部夢二）
	if(P_1_3_F == 1){
		if(P_1_3_T2/1000 > g_T_S.t143_S){
			p_1_3_2(); //電解業務終了処理
			CVCC_RUN_F=0;//電解機器OFF表示
			return 1;
		}else{
			return -1;
		}
	}else{
		return 0;
	}
}
//new_plan ワタベ
int p_3_12(void){                                 //アラーム有無設定処理
	if(g.flag.io.cvcc_alarm_out){                 //アラーム無しを選択したか？
		CVCC_ALARM_OUT_PIN = 0U;                  //アラーム表示状態OFF(0)  //20220901 修正（渡部夢二）
	}else{
		CVCC_ALARM_OUT_PIN = 1U;                  //アラーム表示状態ON(1)　　//20220901 修正（渡部夢二）
	}
	return CVCC_ALARM_OUT_PIN;
}
int p_3_12(void){                                 //アラーム有無設定処理
	if(g.flag.io.cvcc_alarm_out){                 //アラーム無しを選択したか？
		CVCC_ALARM_OUT_PIN = 1U;                  //アラーム表示状態ON(1)
	}else{
		CVCC_ALARM_OUT_PIN = 0U;                  //アラーム表示状態OFF(0)
	}
	return CVCC_ALARM_OUT_PIN;
}
//new_plan
int p_3_13( void){                                //流量調整処理
    BP_3_13();                                    //流量調整起動処理
    B_SV1();                                      //SV1起動処理
    wait(g_T_S.t103_s);
    current_error = E4001;　　　　       //流量手動調整警報表示　20220901後藤
    do{
        if(g_P_3_13_T2 > g_T_S.t150_s){
            Wait(g_T_S.t107_s);
            T_SV1();                              //SV1停止処理
            TP_3_13();                            //流量調整停止処理
            return -1;
        }
    }while(tachi_panel_enter=0)         // タッチパネルエンター　後日変数確認20220901後藤
    Wait(g_T_S.t107_s);
    T_SV1();                                      //SV1停止処理
    TP_3_13();                                    //流量調整停止処理
    return 0;
}
int p_3_14(void){                                 //塩タンク排水処理
	bp_3_14();                                   //塩タンク排水起動処理
	c_19();                                       //塩タンク排水チェック処理
	//TODO: How could we check V4 ??

	b_sp();                                       //SPポンプ起動起動処理
	//TODO: Wait for how long?
	t_sp();                                       //SPポンプ停止待ち
	tp_3_14();                                   //塩タンク排水停止処理
	return 0;
}
//new new_plan
int p_3_14(void){                                 //塩タンク排水処理
	bp_3_1_4();                                   //塩タンク排水起動処理
	c_19();                                       //塩タンク排水チェック処理
	current_error = E4002						　 //V４手動弁方向確認表示　20220901後藤記載
	while(tachi_panel_enter=0) {				　 //確認後タッチパネルでエンター
	                                              //手動弁操作
	}  //TODO: How could we check V4 ??
	b_sp();                                       //SPポンプ起動起動処理
	while(s_3()=0){}							  //塩タンク確認　空になるまで　20220901後藤記載
	t_sp();                                       //SPポンプ停止待ち
	tp_3_14();                                    //塩タンク排水停止処理
	return 0;
}*/

int p_8(void){//全機能停止処理
	//TODO: C11 Electrolytic service emergency stop processing
	c_1_1();                                      //電解業務緊急停止処理
	t_p1();                                       //P1（酸ポンプ）停止処理
	t_p2();                                       //P2（アルポンプ）停止処理
	t_sp();                                       //SP（塩ポンプ）停止処理
	t_sv1();                                      //SV1（給水）停止処理
	t_sv2();                                      //SV2（水吐水）停止処理
	t_sv3();                                      //SV3（酸吐水）停止処理
	t_sv4();                                      //SV4（アル吐水）停止処理
	t_sv5();                                      //SV5（酸抜水）停止処理
	t_sv6();                                      //SV6（アル抜水）停止処理
	t_sv7();                                      //SV7（中和）停止処理
	return 0;
}
int p_9(void){                                    //終了停止
	p_8();                                        //全機能停止処理
	tp_0();                                       //システムメイン終了停止
	return 0;
}
int p_3_13(void){
	return 0;
}
