/*
 * b_module.c
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#include "b_module.h"
#include "c_module.h"
#include "../pin_define.h"
#include "../delay.h"
#include "../global_variable.h"
#include "../hand_sensor.h"

//訂正箇所を//*とする
//*フローチャートにあるBが存在しない

#define BLINK_PERIOD_MS		(200)

int bp_0(void){
																							//該当処理ON Timer 1 :[ P-0-ON_T1 ]
																							//該当処理ON Timer 2 :[ P-0-ON_T2 ]
	if(!g_P_0_F == 0){
		//g_P_0_ON_T1  is total working time (no reset)
		g_P_0_ON_T1 = timer_restart_s(g_P_0_ON_T1);											//（リセット有）
		g_P_0_ON_T2 = timer_start_ms();														//（リセット有）
		g_P_0_F = 1;																		//（リセット無）
	}
	return 0;
}
int bs_4(void){
	return 0;
}
int bs_4_1(void){
	if(g.flag.module.bs41 == 0){
		g_S_4_1_ON_T1 = timer_restart_s(g_S_4_1_ON_T1);
		g_S_4_1_ON_T2 = timer_start_ms();
		g_P_4_1_OFF_T1 = timer_stop_s(g_P_4_1_OFF_T1);
		g_P_4_1_OFF_T2 = timer_stop_ms(g_P_4_1_OFF_T2);
		g_S_4_1_F = 1;
	}
	return 0;
}
int bs_4_2(void){
    if(g_S_4_2_F == 0){
        g_S_4_2_ON_T1 = timer_restart_s(g_S_4_2_ON_T1);
		g_S_4_2_ON_T2 = timer_start_ms();
		g_P_4_2_OFF_T1 = timer_stop_s(g_P_4_2_OFF_T1);
		g_P_4_2_OFF_T2 = timer_stop_ms(g_P_4_2_OFF_T2);
		g_S_4_2_F = 1;
	}
	return 0;
}
int bs_4_3(void){
    if(g_S_4_3_F == 0){
        g_S_4_3_ON_T1 = timer_restart_s(g_S_4_3_ON_T1);
		g_S_4_3_ON_T2 = timer_start_ms();
		g_P_4_3_OFF_T1 = timer_stop_s(g_P_4_3_OFF_T1);
		g_P_4_3_OFF_T2 = timer_stop_ms(g_P_4_3_OFF_T2);
		g_S_4_3_F = 1;
	}
	return 0;
}
int bs_4_4(void){
    if(g_S_4_4_F == 0){
        g_S_4_4_ON_T1 = timer_restart_s(g_S_4_4_ON_T1);
		g_S_4_4_ON_T2 = timer_start_ms();
		g_P_4_4_OFF_T1 = timer_stop_s(g_P_4_4_OFF_T1);
		g_P_4_4_OFF_T2 = timer_stop_ms(g_P_4_4_OFF_T2);
		g_S_4_4_F = 1;
	}
	return 0;
}
int bs_4_5(void){
    if(g_S_4_5_F == 0){
        g_S_4_5_ON_T1 = timer_restart_s(g_S_4_5_ON_T1);
		g_S_4_5_ON_T2 = timer_start_ms();
		g_P_4_5_OFF_T1 = timer_stop_s(g_P_4_5_OFF_T1);
		g_P_4_5_OFF_T2 = timer_stop_ms(g_P_4_5_OFF_T2);
		g_S_4_5_F = 1;
	}
	return 0;
}
int bs_4_6(void){
    if(g_S_4_6_F == 0){
        g_S_4_6_ON_T1 = timer_restart_s(g_S_4_6_ON_T1);
		g_S_4_6_ON_T2 = timer_start_ms();
		g_P_4_6_OFF_T1 = timer_stop_s(g_P_4_6_OFF_T1);
		g_P_4_6_OFF_T2 = timer_stop_ms(g_P_4_6_OFF_T2);
		g_S_4_6_F = 1;
	}
	return 0;
}
int bs_4_7(void){
    if(g_S_4_7_F == 0){
        g_S_4_7_ON_T1 = timer_restart_s(g_S_4_7_ON_T1);
		g_S_4_7_ON_T2 = timer_start_ms();
		g_P_4_7_OFF_T1 = timer_stop_s(g_P_4_7_OFF_T1);
		g_P_4_7_OFF_T2 = timer_stop_ms(g_P_4_7_OFF_T2);
		g_S_4_7_F = 1;
	}
	return 0;
}
int bs_4_8(void){
    if(g_S_4_8_F == 0){
        g_S_4_8_ON_T1 = timer_restart_s(g_S_4_8_ON_T1);
		g_S_4_8_ON_T2 = timer_start_ms();
		g_P_4_8_OFF_T1 = timer_stop_s(g_P_4_8_OFF_T1);
		g_P_4_8_OFF_T2 = timer_stop_ms(g_P_4_8_OFF_T2);
		g_S_4_8_F = 1;
	}
	return 0;
}
int bp_1(void){
	if(g_P_1_F == 0){																		//*2022829修正　minesima
		g_P_1_ON_T1 = timer_restart_s(g_P_1_ON_T1);
		g_P_1_ON_T2 = timer_start_ms();
		g_P_1_F = 1;
	}
	return 0;
}
int bp_1_1(void){
	if(g_P_1_1_F == 0){
		g_P_1_1_ON_T1 = timer_restart_s(g_P_1_1_ON_T1);
		g_P_1_1_ON_T2 = timer_start_ms();
		g_P_1_1_F = 1;
	}
	return 0;
}
int bp_1_1_1(void){
	if( g_P_1_1_1_F == 0){
		g_P_1_1_1_ON_T1 = timer_restart_s(g_P_1_1_1_ON_T1);
		g_P_1_1_1_ON_T2 = timer_start_ms();
		g_P_1_1_1_F = 1;
	}
	return 0;
}
int bp_1_1_2(void){
	if( g_P_1_1_2_F == 0){
		g_P_1_1_2_ON_T1 = timer_restart_s(g_P_1_1_2_ON_T1);
		g_P_1_1_2_ON_T2 = timer_start_ms();
		g_P_1_1_2_F = 1;
	}
	return 0;
}
int bp_1_2(void){
	if(g_P_1_2_F == 0){
		g_P_1_2_ON_T1 = timer_restart_s(g_P_1_2_ON_T1);
		g_P_1_2_ON_T1 = timer_start_ms();
	//	g_P_1_2_F = 1;																		// フローチャート削除の為
	}
	return 0;
}
int bp_1_3(void){
	if(g_P_1_3_F == 0){
		g_P_1_3_ON_T1 = timer_restart_s(g_P_1_3_ON_T1);
		g_P_1_3_ON_T2 = timer_start_ms();
		CVCC_CONTROL_PIN = 1U;																//CVCC(ER=電界装置)起動
		g_C_1_OFF_T2 = 0;																	//C_1_OFF_T2=0　電解処理終了後未使用タイマ	//*20220830 修正 mineshima
		g_P_1_3_F = 1;
	}
	return 0;
}
int bp_1_4(void){
	if(g_P_1_4_F == 0){
		g_P_1_4_ON_T1 = timer_restart_s(g_P_1_4_ON_T1);
		g_P_1_4_ON_T2 = timer_start_ms();
		g_P_1_4_1_F = 1;
																						//*ここのCVCC_CONTROL_PIN = 1U;はフローチャート通りではない20220829 訂正済み
	}
	return 0;
}
int bp_1_4_1(void){
	if(g_P_1_4_1_F == 0){
		g_P_1_4_1_ON_T1 = timer_restart_s(g_P_1_4_1_ON_T1);
		g_P_1_4_1_ON_T2 = timer_start_ms();
		g_P_1_4_1_F = 1;
	}
	return 0;
}
int bp_1_4_2(void){
	if(g_P_1_4_2_F == 0){
		g_P_1_4_2_ON_T1 = timer_restart_s(g_P_1_4_2_ON_T1);
		g_P_1_4_2_ON_T1 = timer_start_ms();
		g_P_1_4_2_F = 1;
	}
	return 0;
}
int bp_1_5(void){
	if(g_P_1_5_F == 0){
		g_P_1_5_ON_T1 = timer_restart_s(g_P_1_5_ON_T1);
		g_P_1_5_ON_T2 = timer_start_ms();
		CVCC_CONTROL_PIN = 1;															//CVCC（ER＝電解装置）起動
																						//*C_1_OFF_T2 = 0;に修正　←　ok　GOTO20220828　フローチャート間違え　C_1_OFF_T2 = 0では無く　C_1_OFF_T2 =STOPが正しい。
		g_C_1_OFF_T2 = timer_start_ms();										//C_1_OFF_T2=stop　電解処理終了後未使用タイマ 20220829修正済み
		g_P_1_5_F = 1;	                                                                //*で本当は、これが正しい timer_start_ms();のモジュールを他のソースで作っています。timer_restart_s();、timer_start_ms();の仲間です。
	}
	return 0;
}
int bp_2(void){
	if(g_P_2_F == 0){
		g_P_2_ON_T1 = timer_restart_s(g_P_2_ON_T1);
		g_P_2_ON_T2 = timer_start_ms();
		g_P_2_F = 1;
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int bp_2_1(void){
	if(g_P_2_1_F == 0){
		g_P_2_1_ON_T1 = timer_restart_s(g_P_2_1_ON_T1);
		g_P_2_1_ON_T2 = timer_start_ms();
		g_P_2_1_OFF_T1 = timer_stop_s(g_P_2_1_OFF_T1);  															//*g_P_2_2_OFF_T2 = timer_stop_ms(g_P_2_1_OFF_T1);20220829 修正済み
		g_P_2_1_OFF_T2 = timer_stop_ms(g_P_2_1_OFF_T2); 															//*g_P_2_1_OFF_T2 = timer_stop_ms(g_P_2_1_OFF_T2);20220829 修正済み
		g_P_2_1_F = 1;
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int bp_2_2(void){
	if(g_P_2_2_F == 0){																		//*if(g.flag.module.bp22 == 0){を追加
		g_P_2_2_ON_T1 = timer_restart_s(g_P_2_2_ON_T1);										//*g.timer.module.on.p22[0] = timer_restart_s(g.timer.module.work.p22[0]);　20220829修正済み
		g_P_2_2_ON_T2 = timer_start_ms();													//*g.timer.module.on.p22[1] = timer_start_ms(); 20220829修正済み
		g_P_2_2_OFF_T1 = timer_stop_s(g_P_2_2_OFF_T1); 							    		//*P_2_2_OFF_T1 stop;を追加 //ここではg.timer.module.work.p22[0] = timer_stop_s(g.timer.module.off.p22[0]);と書いた方が良いか　20220829修正済み
		g_P_2_2_OFF_T2 = timer_stop_ms(g_P_2_2_OFF_T2);										//*P_2_2_OFF_T2 stop;を追加 //同様にg.timer.module.work.p22[1] = timer_stop_ms(g.timer.module.off.p22[1]);←GOTO20220828　と書いた方が良い！　20220829修正済み
		 																					//*私であれば、フローチャートの変数名を使います。 g_P_2_2_OFF_T2 = timer_stop_ms(g_P_2_2_OFF_T2); ←GOTO20220828
		g_P_2_2_F = 1;																		//*g.flag.module.bp22 = 1;
	}
	return 0;
}
int bp_2_3(void){
	if(g_P_2_3_F == 0){
		g_P_2_3_ON_T1 = timer_restart_s(g_P_2_3_ON_T1);
		g_P_2_3_ON_T1 = timer_start_ms();
		g_P_2_3_F = 1;
    }
	return 0;
}
int bp_2_4(void){
	if(g_P_2_4_F == 0){
		g_P_2_4_ON_T1 = timer_restart_s(g_P_2_4_ON_T1);
		g_P_2_4_ON_T2 = timer_start_ms();
		g_P_2_4_F = 1;
	}
	return 0;
}
/**
 * Under changing
 * @return
 */
int bp_2_4_1(void){
	if(g_P_2_4_1_F == 0){
		g_P_2_4_1_ON_T1 = timer_restart_s(g_P_2_4_1_ON_T1);
		g_P_2_4_1_ON_T2 = timer_start_ms();
		g_P_2_4_1_OFF_T1 = timer_stop_s(g_P_2_4_1_OFF_T1);
		g_P_2_4_1_OFF_T2 = timer_stop_ms(g_P_2_4_1_OFF_T2);
		g_P_2_4_1_F = 1;
	}
	return 0;
}
/**
 * Under changing
 * @return
 */
int bp_2_4_2(void){
	if(g_P_2_4_2_F == 0){
		g_P_2_4_2_F = 1;
		g_P_2_4_2_ON_T1 = timer_restart_s(g_P_2_4_2_ON_T1);
		g_P_2_4_2_ON_T2 = timer_start_ms();
		g_P_2_4_2_OFF_T1 = timer_stop_s(g_P_2_4_2_OFF_T1);
		g_P_2_4_2_OFF_T2 = timer_stop_ms(g_P_2_4_2_OFF_T2);
	}
	return 0;
}
int bp_2_4_3(void){
	if(g_P_2_4_3_F == 0){
		g_P_2_4_3_ON_T1 = timer_restart_s(g_P_2_4_3_ON_T1);
		g_P_2_4_3_ON_T2 = timer_start_ms();
		g_P_2_4_3_F = 1;
	}
	return 0;
}
int bp_3(void){
	if(g_P_3_F == 0){
		g_P_3_ON_T1 = timer_restart_s(g_P_3_ON_T1);
		g_P_3_ON_T2 = timer_start_ms();
		g_P_3_F = 1;
	}
	return 0;
}
int bp_3_14(void){
	if(g_P_3_14_F == 0){
		g_P_3_14_ON_T1 = timer_restart_s(g_P_3_14_ON_T1);
		g_P_3_14_ON_T2 = timer_start_ms();
		g_P_3_14_F = 1;
	}
	return 0;
}

int bp_8(void){
	if(g_P_8_F == 0){
		g_P_8_ON_T1 = timer_restart_s(g_P_8_ON_T1);
		g_P_8_ON_T2 = timer_start_ms();
		g_P_8_F = 1;
	}
	return 0;
}

int b_sv1(void){
	if( g_SV1_F == 0){
		//SV1_PIN = VALVE_ON;																//2022829修正
		g_SV1_ON_T1 = timer_restart_s(g_SV1_ON_T1);
		g_SV1_ON_T2 = timer_start_ms();
		g_SV1_ON_T3 =  timer_restart_s(g_SV1_ON_T3);										//（フィルター交換で使用）//*g_SV1_ON_T3 =  timer_restart_s(g_SV1_ON_T3);を追加 2022829
	    SV1_PIN = VALVE_ON;
		g_SV1_F = 1;                                                                      //先頭より位置変更
		return 1;
	}
	return 0;
}
int b_sv2(void){
	if( g_SV2_F == 0){
		g_SV2_ON_T1 = timer_restart_s(g_SV2_ON_T1);											//（フィルター交換で使用）//*T3のコードが足りない　T3のコード必要です。　ただし、20220826の打ち合わせで、不要となりました。（給水経路変更で）でもこの時は必要です！20220828goto
		g_SV2_ON_T2 = timer_start_ms();
		SV2_PIN = VALVE_ON;																	//*SV2 = ON;を追加
		g_FAUCET_OFF_T = 0; 													 			//カラン未使用タイマ＝0 //*FAUCET_OFF_T = 0;を追加
		g_SV2_F = 1;
		return 1;
	}
	return 0;
}
int b_sv3(void){
	if(g_SV3_F == 0){
		//SV3_PIN = VALVE_ON;
		g_SV3_ON_T1 = timer_restart_s(g_SV3_ON_T1);
		g_SV3_ON_T2 = timer_start_ms();
        SV3_PIN = VALVE_ON;                                                                 //先頭より位置変更
		g_SV3_F = 1;
		return 0;
	}
	return 0;
}
int b_sv4(void){
	if(g_SV4_F == 0){
		//SV4_PIN = VALVE_ON;
		g_SV4_ON_T1 = timer_restart_s(g_SV4_ON_T1);
		g_SV4_ON_T2 = timer_start_ms();
        SV4_PIN = VALVE_ON;                                                                 //先頭より位置変更
		g_SV4_F = 1;
		return 0;
	}
	return 0;
}
int b_sv5(void){
	if ( g_SV5_F == 0){
		//SV5_PIN = VALVE_ON;
		g_SV5_ON_T1 = timer_restart_s(g_SV5_ON_T1);
		g_SV5_ON_T2 = timer_start_ms();
        SV5_PIN = VALVE_ON;                                                                 //先頭より位置変更
		g_SV5_F = 1;
		return 1;
	}
	return 0;
}
int b_sv6(void){
	if( g_SV6_F == 0 ){
		//SV6_PIN = VALVE_ON;
		g_SV6_ON_T1 = timer_restart_s(g_SV6_ON_T1);
		g_SV6_ON_T2 = timer_start_ms();
        SV6_PIN = VALVE_ON;                                                                 //先頭より位置変更
		g_SV6_F = 1;
        return 1;
	}
	return SV6_PIN;
}
int b_sv7(void){
	if( g_SV7_F == 0 ){
		//SV7_PIN = VALVE_ON;
		g_SV7_ON_T1 = timer_restart_s(g_SV7_ON_T1);
		g_SV7_ON_T2 = timer_start_ms();
		g_NEUTRAL_T = 0 ;																	//中和処理タイマー”0”セット　SV７起動は中和処理開始のため　20220904追記　goto
        SV7_PIN = VALVE_ON;                                                                 //先頭より位置変更
		g_SV7_F = 1;
        return 1;
	}
	return SV7_PIN;
}
													//*SV1~7のコードがフローチャート通りではない←GOTO20220828大問題！　フローチャート通りに作成しなくてはいけない。(ここは未作成と思われる）作れますか？
													//*2022829 修正


int b_p1(void){																							//* new plan 20220828 goto　この書き方が正しいと思います。
	if (g_P1_F == 0){
		g_P1_ON_T1 = timer_restart_s(g_P1_ON_T1);														//* フローチャートに掛かれている変数(大文）は、全て　グローバル変数として使用する. + 最初に"g_"を付けると約束をしています。　20220828 goto
		g_P1_ON_T2 = timer_start_ms();																	//*　しかも勝手に”g.timer.module.work.io.p1[0])”を作って使っています。　これは大問題ですが、後で、説教をする予定です。（ベトナムの外注先）　20220828 goto
																										//* 因みに、タイマモジュールの後についている "s" "ms"は　単位の違いで使い分けています。　”ｓ”はＴ１で、　Ｔ２，Ｔ３は、"ms"を使っています、
																										//* ”ｓ”は秒　"ms"はミリ秒です。
		PUMP_1_PIN = PUMP_ON;
		if( SV3_PIN == VALVE_ON ){																				//*この部分は、フローチャートと判断を逆にして、ソースを見やすくしています。　フローチャートがいけないですね。　20220829 修正済み
			g_FAUCET_OFF_T = 0;
		}
		g_P1_OFF_T2 = timer_stop_ms(g_P1_OFF_T2);
		g_P1_F = 1;
	}
	return 0;
}
int b_p2(void){
	if( g_P2_F == 0 ){																		//*後藤さんの修正内容を基に修正 2022829
		g_P2_ON_T1 = timer_restart_s(g_P2_ON_T1);
		g_P2_ON_T2 = timer_start_ms();

		PUMP_2_PIN = PUMP_ON;
		if( SV4_PIN == VALVE_ON ){
			g_FAUCET_OFF_T = 0;																//カラン未使用タイマ＝0
		}
		g_P2_OFF_T2 = timer_stop_ms(g_P2_OFF_T2); 											//アルカリ吐水抜水停止タ
		g_P2_F = 1;																			//*g_P2_F = 1を追加
	}
	return 0;
}
int b_sp(void){
	if( g_SP_F == 0 ){
		//PUMP_2_PIN = PUMP_ON;																//*フローチャートに存在しない
		g_SP_ON_T1 = timer_restart_s(g_SP_ON_T1);											//*g_SP_ON_T2 = timer_start_ms();	を追加
		g_SP_ON_T2 = timer_start_ms();														//*g_SP_ON_T2 = timer_start_ms();	を追加 2022829
        SP_PIN = PUMP_ON;																//*PUMP_SP_PIN = PUMP_ON; こちらではないか？ 2022829 修正
		g_SP_OFF_T2 = timer_stop_ms(g_SP_OFF_T2); 											//*g_SP_OFF_T2 = timer_stop_ms(g_SP_OFF_T2); 2022829
        g_SP_F = 1;																			//*g_SP_F = 1を追加 2022829
	}
	return 0;
}


int bc_1(void){
	if(g_C_1_F == 0){
		g_C_1_ON_T1 = timer_restart_s(g_C_1_ON_T1);
		g_C_1_ON_T2 = timer_start_ms();
		g_C_1_ON_T3 = timer_restart_s(g_C_1_ON_T3);											//電解装置積算タイマ　リスタート
		g_NEUTRAL_T = timer_restart_s(g_NEUTRAL_T);											//中和タイマ　リスタートスタート
		CVCC_CONTROL_PIN = 1;																//CVCC（ER＝電解装置） 起動 //*CVCC_CONTROL_PIN = 1;を追加
		g_C_1_OFF_T2 = timer_stop_ms(g_C_1_OFF_T2); 										//C_1_OFF_T2=0　電解処理終了後未使用タイマ //*C_1_OFF_T2 =  = timer_stop_ms(g_C_1_OFF_T2);を追加
		g_CVCC_RUN_F = 1;
		c_5();																				//電解業務開始時、必ず電解業務チェック処理を起動する　20220904GOTO追記
		g_C_1_F = 1;
	}
	return 0;
}
int bc_2(void){
	if(g_C_2_F == 0){
		g_C_2_ON_T1 = timer_restart_s(g_C_2_ON_T1);                                         // 20220828 修正 		g_SV3_ON_T1 = timer_restart_s(g_SV3_ON_T1);と記載されていた
		g_C_2_ON_T2 = timer_start_ms();                                                     // 20220828 修正        g_SV3_ON_T2 = timer_start_ms();と記載されていた。
		g_C_2_F = 1;
	}
	return 0;
}
int bc_3(void){
	if(g_C_3_F == 0){
		g_C_3_ON_T1 = timer_restart_s(g_C_3_ON_T1);
		g_C_3_ON_T2 = timer_start_ms();
		g_C_3_F = 1;
	}
	return 0;
}
int bc_4(void){
	if(g_C_4_F == 0){
		g_C_4_ON_T1 = timer_restart_s(g_C_4_ON_T1);
		g_C_4_ON_T2 = timer_start_ms();
		g_C_4_F = 1;
	}
	return 0;
}
int bc_5(void){
	if(g_C_5_F == 0){
		g_C_5_ON_T1 = timer_restart_s(g_C_5_ON_T1);
		g_C_5_ON_T2 = timer_start_ms();
		g_C_5_F = 1;
	}
	return 0;
}
int bc_5_1(void){
	if(g_C_5_1_F == 0){
		g_C_5_1_ON_T1 = timer_restart_s(g_C_5_1_ON_T1);
		g_C_5_1_ON_T2 = timer_start_ms();
		g_C_5_1_F = 1;
	}
	return 0;
}
int bc_5_2(void){
	if(g_C_5_2_F == 0){
		g_C_5_2_ON_T1 = timer_restart_s(g_C_5_2_ON_T1);
		g_C_5_2_ON_T2 = timer_start_ms();
		g_C_5_2_F = 1;
	}
	return 0;
}
int bc_5_3(void){
	if(g_C_5_3_F == 0){
		g_C_5_3_ON_T1 = timer_restart_s(g_C_5_3_ON_T1);
		g_C_5_3_ON_T2 = timer_start_ms();
		g_C_5_3_F = 1;
	}
	return 0;
}
int bc_5_3_1(void){
	if(g_C_5_3_1_F == 0){
		g_C_5_3_1_ON_T1 = timer_restart_s(g_C_5_3_1_ON_T1);
		g_C_5_3_1_ON_T2 = timer_start_ms();
		g_C_5_3_1_F = 1;
	}
	return 0;
}
int bc_5_4(void){
	if(g_C_5_4_F == 0){
		g_C_5_4_ON_T1 = timer_restart_s(g_C_5_4_ON_T1);
		g_C_5_4_ON_T2 = timer_start_ms();
		g_C_5_4_F = 1;
	}
	return 0;
}
int bc_5_5(void){
	if(g_C_5_5_F == 0){
		g_C_5_5_ON_T1 = timer_restart_s(g_C_5_5_ON_T1);
		g_C_5_5_ON_T2 = timer_start_ms();
		g_C_5_5_F = 1;
	}
	return 0;
}
int bc_5_6(void){
	if(g_C_5_6_F == 0){
		g_C_5_6_ON_T1 = timer_restart_s(g_C_5_6_ON_T1);
		g_C_5_6_ON_T2 = timer_start_ms();
		g_C_5_6_F = 1;
	}
	return 0;
}
int bc_6(void){
	if(g_C_6_F == 0){
		g_C_6_ON_T1 = timer_restart_s(g_C_6_ON_T1);
		g_C_6_ON_T2 = timer_start_ms();
		g_C_6_F = 1;
	}
	return 0;
}
int bc_7(void){
	if(g_C_7_F == 0){
		g_C_7_ON_T1 = timer_restart_s(g_C_7_ON_T1);
		g_C_7_ON_T2 = timer_start_ms();
		g_C_7_F = 1;
	}
	return 0;
}
int bc_8(void){
	if(g_C_8_F == 0){
		g_C_8_ON_T1 = timer_restart_s(g_C_8_ON_T1);
		g_C_8_ON_T2 = timer_start_ms();
		g_C_8_F = 1;
	}
	return 0;
}
int bc_9(void){																							//*bc_9が抜けていたので追加
	if(g_C_9_F == 0){
		g_C_9_ON_T1 = timer_restart_s(g_C_9_ON_T1);
		g_C_9_ON_T2 = timer_start_ms();
		g_C_9_F = 1;
	}
	return 0;
}
int bc_10(void){
	if(g_C_10_F == 0){
		g_C_10_ON_T1 = timer_restart_s(g_C_10_ON_T1);
		g_C_10_ON_T2 = timer_start_ms();
		g_C_10_F = 1;
	}
	return 0;
}
int bc_11(void){
	if(g_C_11_F == 0){
		g_C_11_ON_T1 = timer_restart_s(g_C_11_ON_T1);
		g_C_11_ON_T2 = timer_start_ms();
		g_C_11_F = 1;
	}
	return 0;
}
int bc_12(void){
	if(g_C_12_F == 0){
		g_C_12_ON_T1 = timer_restart_s(g_C_12_ON_T1);
		g_C_12_ON_T2  = timer_start_ms();
		g_C_12_F = 1;
	}
	return 0;
}
int bc_13(void){
	if(g_C_13_F == 0){
		g_C_13_ON_T1 = timer_restart_s(g_C_13_ON_T1);
		g_C_13_ON_T2 = timer_start_ms();
		g_C_13_F = 1;
	}
	return 0;
}
int bc_14(void){
	if(g_C_14_F == 0){
		g_C_14_ON_T1 = timer_restart_s(g_C_14_ON_T1);
		g_C_14_ON_T2 = timer_start_ms();
		g_C_14_F = 1;
	}
	return 0;
}
int bc_15(void){
	if(g_C_15_F == 0){
		g_C_15_ON_T1 = timer_restart_s(g_C_15_ON_T1);
		g_C_15_ON_T2 = timer_start_ms();
		g_C_15_F = 1;
	}
	return 0;
}
int bc_16(void){
	if(g_C_16_F == 0){
		g_C_16_ON_T1 = timer_restart_s(g_C_16_ON_T1);
		g_C_16_ON_T2 = timer_start_ms();
		g_C_16_F = 1;
	}
	return 0;
}
int bc_17(void){
	if(g_C_17_F == 0){
		g_C_17_ON_T1 = timer_restart_s(g_C_17_ON_T1);
		g_C_17_ON_T2 = timer_start_ms();
		g_C_17_F = 1;
	}
	return 0;
}
int bc_18(void){
	if(g_C_18_F == 0){
		g_C_18_ON_T1 = timer_restart_s(g_C_18_ON_T1);
		g_C_18_ON_T2 = timer_start_ms();
		g_C_18_F = 1;
	}
	return 0;
}
int bc_19(void){
	if(g_C_19_F == 0){
		g_C_19_ON_T1 = timer_restart_s(g_C_19_ON_T1);
		g_C_19_ON_T2 = timer_start_ms();
		g_C_19_F = 1;
	}
	return 0;
}
int be1(void){
	if(g_E_1_F == 0){
		g_E_1_ON_T1 = timer_restart_s(g_E_1_ON_T1);
		g_E_1_ON_T2 = timer_start_ms();
		g_E_1_F = 1;
	}
	return 0;
}
int b_b_led_l(void){
	hand_sensor_blink(BLUE, 0);																		//Blue LED Light
	if(g_B_LED_L_F == 0){
		g_B_LED_L_ON_T1 = timer_restart_s(g_B_LED_L_ON_T1);
		g_B_LED_L_ON_T2 = timer_start_ms();
		g_B_LED_L_F = 1;
	}
	return 0;
}
int b_b_led_b(void){
	hand_sensor_blink(BLUE, BLINK_PERIOD_MS);																	//Blue LED Blink
	if(g_B_LED_B_F == 0){
		g_B_LED_B_ON_T1 = timer_restart_s(g_B_LED_B_ON_T1);
		g_B_LED_B_ON_T2 = timer_start_ms();
		g_B_LED_B_F = 1;
	}
	return 0;
}
int b_r_led_l(void){
	hand_sensor_blink(RED, 0);																			//Red LED Light
	if(g_R_LED_L_F == 0){
		g_B_LED_L_ON_T1 = timer_restart_s(g_B_LED_L_ON_T1);
		g_B_LED_L_ON_T2 = timer_start_ms();
		g_R_LED_L_F = 1;
	}
	return 0;
}
int b_r_led_b(void){
	hand_sensor_blink(RED, BLINK_PERIOD_MS);																	//Red LED Blink
	if(g_B_LED_B_F == 0){
		g_B_LED_B_ON_T1 = timer_restart_s(g_B_LED_B_ON_T1);
		g_B_LED_B_ON_T2 = timer_start_ms();
		g_B_LED_B_F = 1;
	}
	return 0;
}
int b_w_led_l(void){
	hand_sensor_blink(WHITE, 0);																		//White LED Light
	if(g_W_LED_L_F == 0){
		g_W_LED_L_ON_T1 = timer_restart_s(g_W_LED_L_ON_T1);
		g_W_LED_L_ON_T2 = timer_start_ms();
		g_W_LED_L_F = 1;
	}
	return 0;
}
int b_w_led_b(void){
	hand_sensor_blink(WHITE, BLINK_PERIOD_MS);																	//White LED Blink
	if(g_W_LED_B_F == 0){
		g_W_LED_B_ON_T1 = timer_restart_s(g_W_LED_B_ON_T1);
		g_W_LED_B_ON_T2 = timer_start_ms();
		g_W_LED_B_F = 1;
	}
	return 0;
}
int be_1_1(void){
	if(g_E_1_F == 0){
		g_E_1_1_ON_T1 = timer_restart_s(g_E_1_1_ON_T1);
		g_E_1_1_ON_T2  = timer_start_ms();
		g_E_1_1_F = 1;
	}
	return 0;
}
int be_1(void){
	if(g_E_1_F == 0){
		g_E_1_ON_T1 = timer_restart_s(g_E_1_ON_T1);
		g_E_1_ON_T2  = timer_start_ms();
		g_E_1_F = 1;
	}
	return 0;
}
int bc_23(void){
	if(g_C_23_F == 0){
		g_C_23_ON_T1 = timer_restart_s(g_C_23_ON_T1);
		g_C_23_ON_T2  = timer_start_ms();
		g_C_23_F = 1;
	}
	return 0;
}
int bc_24(void){
	if(g_C_24_F == 0){
		g_C_24_ON_T1 = timer_restart_s(g_C_24_ON_T1);
		g_C_24_ON_T2  = timer_start_ms();
		g_C_24_F = 1;
	}
	return 0;
}
