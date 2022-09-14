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
#include "../runtime.h"

uint8_t g_c_5_5_10F, g_c_5_5_20F, g_M1030_F;

#define ON		(1U)
#define OFF		(0U)
																			//訂正部分を//*とする
int c_1(uint8_t on_off){
	runtime();
	switch(on_off){
		case ON: 															//電解業務停止中(C_1_F=0)であれば停止処理実施
			s_1();
			s_2();
			if(g_ALD == 3 && g_ACD == 3){
				tc_1();
				t_sv1();											//SV１（給水） 起動処理
				t_sp();
				return 0;
			}
			if(g_ALD == 1 || g_ACD == 1){
				b_sv1();											//SV１（給水） 起動処理
				b_sp();
				bc_1();
				g_C_1_F = 1;
				return 1;
			}
//			if(elapsed_time_s(g_SP_ON_T2)/1000 > g_T_S.t144_s){			//設定値[144]：規定値2s  //*t4-2からt144へ変更　20220901
//				t_sv1();											//SV１（給水） 起動処理
//				t_sp();
//				tc_1(); 													//BC-1 電解業務起動処理
				//				g_NEUTRAL_T = timer_restart_s(g_NEUTRAL_T); 				//中和タイマー起動　NEUTRAL_Tを再起動　 廃止　bc_1()モジュール内で実施　20220904goto
//				return 1;
	//		}
			c_5(); 															//電解業務チェック処理
//			b_w_led_b();
			c_23();			//TODO: c23()									//主チェック処理
//			t_w_led_b();
			return 0;

		case OFF:							//電解業務停止中(C_1_F=1)であれば停止処理実施
			if(g_C_1_F == 1){
				if(g_SP_F == 1 ){
					t_sp();											//SP（塩ポンプ） 停止処理
				}
				if(elapsed_time_s(g_SP_F)/1000 >= g_T_S.t145_s){
																			//設定値[145]：規定値5s
					t_sv1();											//SV１（給水） 停止処理
					tc_1();											//電解業務停止処理
//					g_NEUTRAL_T = timer_stop_s(g_NEUTRAL_T); 					//中和タイマー停止処理　　廃止　bc_1()モジュール内で実施　20220904goto
					return 2;
				}
				return -2;
			}
			return 0;
		}
	return 0;
}


int c_1_1(void) {
	tc_1(); 																//電解停止処理
	t_sp(); 															//SP（塩ポンプ）停止処理
	wait(g_T_S.t145_s * 1000); 												//設定値[145]：規定値5s　 //*t5からt145へ変更　20220901
	t_sv1(); 														//SV１（給水）停止処理
	g_NEUTRAL_T = timer_stop_s(g_NEUTRAL_T);				 				//中和タイマー停止処理
	return 1;
}

int c_2(void) {
	bc_2();//アルカリタンク状態チェック起動処理
	const int status = s_1();												//アルカリタンク状況（ALD）
	switch(status){														//※FL4,FL5,FL6センサーの異常を確認
		case 0:											//ALD 0 タンク（空）
			e_1029(); 														//アルカリタンク空エラー処理
			return 0;
		case 1: 															//ALD 1
			return 1;
		case 2:															//ALD 2
			return 2;
		case 3:											//ALD 3
			return 3;
		default: 															//ALD -1以下（センサ異常）
			e_1025(); 														//アルカリタンクセンサーエラー処理
			return -1;
	}
}

int c_3(void){
	bc_3();																//酸タンク状態チェック起動処理
	 											//酸タンク(ACD)
	switch(s_2()){ 														//※FL1,FL2,FL3センサーの異常確認
		case 0: 															//ACD 0 （タンク空）
			e_1028(); 														//酸タンク空エラー処理
			return 0;
		case 1: 															//ACD 1
			return 1;
		case 2:																//ACD 2
			return 2;
		case 3:	 															//ACD 3
			return 3;
		default: 															//ACD -1以下（センサ異常）
			e_1024(); 														//酸タンクセンサーエラー処理
			return -1;
	}
}
int c_4(void){
	bc_4(); 																	//塩タンクセンサーチェック起動処理
																			//塩タンク状況（SAD）取得
	const int status = s_3();											//塩タンク状況（SAD）
	switch(status){																		//FL7,FL8センサーの異常確認
		case 0: 															//0
			e_1021();														//塩タンク空エラー処理 TODO: E1021
			break;
		case 1:																//1
			return g_SAD;
		case 2:															//2
			e_1020();													//塩タンク満杯エラー処理 TODO: E1020
			return g_SAD;
		default: 															//-1以下（センサ異常）
			e_1023(); 													//塩タンクセンサエラー処理 TODO: E1023
			break;
	}
	return -1;
}
int c_5(void){
	if(CVCC_CONTROL_PIN == 1){												// 20220902 追加　電解処理中のみ実施　goto
		bc_5(); 																//電解業務チェック起動処理
		c_5_1(&g_V_S.v1_V); 													//過電圧1チェック処理
		c_5_2(&g_V_S.v2_V); 													//過電圧2チェック処理
		c_5_3(&g_V_S.v3_V); 													//過電圧3チェック処理
		c_5_4(); 																//低過電圧3チェック処理
		c_5_5(); 																//電流調整範囲チェック処理
		c_5_6(); 																//ER(CVCC基盤)チェック処理
		tc_5(); 																//電解業務チェック停止処理
	}																		// 20220902 追加　電解処理中のみ実施　goto
	return 0;
}
int c_5_1(float *voltage){
																			//規定値[131]:5秒
	if(elapsed_time_ms(g_C_1_ON_T2)/1000 > g_T_S.t131_s){
																			//電解処理開始後[131]s経ったか?
																			//CVCC_VOLT= CVCC出力電圧
		const float cvcc_voltage = g_adc.voltage;
																			//過電圧1チェック起動処理
		bc_5_1(); 															//過電圧1チェック起動処理
																			//CVCC_VOLT>OVER_V1_ALARM_VALUE
		if(cvcc_voltage > g_V_S.v1_V){
																			//過電圧1か?
																			//※CVCC(定電流基盤)からの出力電圧(CVCC_VOLT)
			e_1002();														//過電圧エラー処理 TODO: E1002

			return -255; 													//E1002にてリセット処理
		}
		return 1;
	}
	return 0;
}
int c_5_2(float *voltage){
	const float cvcc_voltage = g_adc.voltage;								//CVCC_VOLT= CVCC出力電圧

	if(cvcc_voltage > g_V_S.v2_V){											//過電圧2か?
			bc_5_2(); 													//過電圧2チェック起動処理
		if(elapsed_time_ms(g_C_5_2_ON_T2)/1000 > g_T_S.t138_s){			//*t[12]sをt[138]sに変更 20220901　//*T3をT2に変更(8/29 2022)
																			//エラー感知連続[12]s経ったか?
			e_1003(); 													//過電圧2エラー処理 TODO: E1003

			return -255;
		}
		 else{
																			//設定値[138]：規定値10秒
			return -1;
		}

	}else{
		tc_5_2(); 															//過電圧2チェック停止処理
		return 0;
	}
}
int c_5_3(float *voltage){
	if(elapsed_time_ms(g_C_1_ON_T2)/1000 > g_T_S.t132_s){			//電解処理開始後[132]s経ったか?  //*[13]を[132]に変更(8/29 2022)
//		const float cvcc_voltage = g_adc.voltage;							//CVCC_VOLT= CVCC出力電圧
		if(g.cvvc_voltage > g_V_S.v3_V){										//過電圧3か?
			bc_5_3();														//過電圧3チェック起動処理
			c_5_3_1();													//過電圧3チェック子処理
			return -1;
		}else{
			return 1;
		}
	}
	return 0;
}
int c_5_3_1(void){
	bc_5_3_1();																//過電圧3チェック子起動処理

	const float cvcc_voltage = g_adc.voltage;								//過電圧3か？
	if(cvcc_voltage > g_V_S.v3_V){											//塩水濃度警報　過電圧3エラー処理
		if(elapsed_time_ms(g_C_5_3_ON_T2)/1000 > g_T_S.t139_s){				//エラー関知連続[139]s経ったか? //*C_5_2_ON_T3をC_5_3_ON_T3に変更(8/25 2022 レビュー後変更)　 //*T3をT2に、[41]を[139]に変更(8/29 2022)
																			//alarm(); フローチャートと違うため削除
			e_1004(); 														//TODO: E1004 フローチャートに合わせて追加

			return -1;
		}else
																			//設定値[41]:規定値10秒
			return 1;
	}else{
		current_error = NO_ERROR;											//TODO: タッチパネルエラー削除

		tc_5_3_1();															//過電圧3チェック子停止処理
		return 0;
	}
}
int c_5_4(void){
	if(elapsed_time_ms(C_1_ON_T2)/1000 > g_T_S.t137_s){						//電界処理開始後[137]s経ったか?
		const float cvcc_current = g_adc.current;							//CVCC_VOLT= CVCC出力電圧
		if(cvcc_current < g_V_S.v4_V){										//低電圧か?
			if(g_C_5_4_F == 0){
				bc_5_4();													//低電圧チェック起動処理
																			//経過時間タイマ＝0　C_5_4_T3=time_start()
				C_5_4_ON_T3 = timer_start_ms();
			}
																			//C_5_4_F2＝1
			if(g_C_5_4_F != 1){
//				alarm(); //TODO: Alarm

				g_C_5_4_F = 1;

			}
			if(elapsed_time_ms(C_5_4_ON_T3)/1000 > g_T_S.t140_s){			//エラー関知連続[140]s経ったか?
				e_1005();													//TODO: E1005 低電圧エラー処理

				return -255;
			}else
																			//設定値[140]：規定値10秒
				return 1;

		}else {
			if(g_C_5_4_F == 1){
				current_error = NO_ERROR;									//TODO: タッチパネルエラー削除
				g_C_5_4_F = 0;												//C_5_4_F2＝0
			}
			tc_5_4();														//低電圧チェック停止処理
			return 1;
		}
	}
	return 0;
}
int c_5_5(void){
	if(elapsed_time_ms(g_C_1_ON_T2)/1000 > g_T_S.t133_s){					//電界処理開始後[133]s経ったか?
		bc_5_5();															//電流調整範囲チェック起動処理
		c_5_5_1();														//電流調整範囲チェック子処理
		return 1;
	}
	return 0;
}
int c_5_5_1(void){															//*フローチャート側に表記ミスがある
	const int ret = c_5_5_1_1();											//ER(CVCC)確認処理 //*項番変更c552→c5511に変更(8/25 2022 レビュー後変更)
	switch (ret) {
		case 1:																//戻値1 正常
			if(g_c_5_5_10F == 1){
				e_1006();													//TODO: E1006 電界範囲10％警報表示削除

				return -255;
			}
			g_c_5_5_10F = 0;
			g_c_5_5_20F = 0;
			g_c_5_5_20F = 0;
			return 0;
		case -1:															//戻値-1 設定値より10％範囲外の場合の処理
			if(g_c_5_5_10F == 0){											//10％範囲外初めての処理
				g_c_5_5_10F = 1;											//10％実施フラグON
				e_1006(); //TODO: E1006										//電流範囲10％エラー処理

				return -255;
			}
			break;
		case -2:															//戻値-2 設定値より20％範囲外の場合の処理
			if(g_c_5_5_20F == 0){											//20％範囲外初めての処理
				g_c_5_5_20F = 1;											//20％実施フラグON
				g_C_5_5_ON_T2 = timer_start_ms();								//20％タイマON
			}
			//elapsed_time(g_C_5_5_ON_20T)/1000>1分
			if(elapsed_time_ms(g_C_5_5_ON_T2)/1000 > 60){
				e_1007();													//TODO: E1007 電流範囲20％エラー処理

				return -255;
			}else
				return -1;
		default:
			break;
	}
	return -255;
}
int c_5_5_1_1(void){														//*項番変更c552→5511に変更(8/25 2022 レビュー後変更)
																			//CVCC_CURRENT= CVCC電解電流値取得
	const float cvcc_current = g_V_S.v9_A;
	//設定値g_V_S.v9_A：規定値　1A											//*g_V_S.v9_Aに修正しましたが合っていますでしょうか。
	if(g_V_S.v9_A * 1.1f < cvcc_current){									//10%超えているか? //*g_V_S.v5_pに修正 20220831 mineshima
		if(g_V_S.v9_A * 1.2f < cvcc_current){								//20%超えているか? //*g_V_S.v5_pに修正 20220831 mineshima
			return -2;
		}
		return -1;
	}else if(g_V_S.v9_A * 0.9f > cvcc_current){
																			//10%以上の減か? //*g_V_S.v6_pに修正 20220831 mineshima
		if(g_V_S.v9_A * 0.8f > cvcc_current){
																			//20%以上の減か? //*g_V_S.v5_pに修正 20220831 mineshima
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
int c_5_6(void){
	bc_5_6();																//CVCC電源チェック起動処理	 　　  //*const float cvcc_voltage = g_adc.voltage; 削除(2022.8.29)			//CVCC_ELE_VOLT= CVCC電源
	if(g.io.cvcc_alarm_in == 1){												//電源異常か?　//*cvcc_voltage<XXをcvcc_alarm_in == 1に変更(8/25 2022　LINE連絡後変更)
		e_1009();	//TODO:	E1009											//CVCC電源エラー処理
	}
	return 0;
}
int c_6(void){
	bc_6();																	//カラン未使用チェック起動処理
																			//カランを使わなければ（8時間水の流れが無い場合
																			//FAUCET_OFF_T＞[161]8ｈ
	if(elapsed_time_s(g_FAUCET_OFF_T) > g_T_S.t161_h * 60 * 60){		    //カラン未使用タイマ //*設定値を[39]から[161]に変更 20220901
		g_FAUCET_OFF_T = 0;													//カラン未使用タイマ（リセット)
		e_1();																//カラン清掃処理
		return 1;
	}
	return 0;
}
int c_7(void){
																			//電解水が作成停止後（設定値[146]：規定値[168ｈ]）以上？
	bc_7();																	//電解処理未使用チェック起動処理
	if(elapsed_time_ms(g_C_1_OFF_T2) / 1000 > g_T_S.t146_h * 60 * 60){
																			//未使用経過時間 C_1_OFF_T2 > [146] 168H
		e_5003();  //TODO: E5003　											//電解未処理対応実施処理
		return -255;
	}
	return 0;
}
int c_8(void){
	if(elapsed_time_ms(g_SV1_ON_T2)/1000 > g_T_S.t149_s){
																			//SV１（給水） 動作後［149」秒以上経過した場合
		if(g_C_8_F == 0){
																			//流量センサチェック起動フラグ＝0
			bc_8(); 														//流量センサチェック起動処理
			g_C_8_ON_T3 = timer_start_ms();									//経過時間タイマ＝0
		}
		if(g_V_S.v7_L_m < g.flow_rate){										//* g_V_S.v7_L_mに修正 20220831 mineshima
																			//流量値：FLOW_RATE
			if(g.flow_rate < g_V_S.v8_L_m){									//* g_V_S.v8_L_mに修正 20220831 mineshima
				tc_8();													//流量センサチェック起動処理
				return 1;
			}else if(elapsed_time_ms(g_C_8_ON_T3)/1000 > g_T_S.t151_s){
																			//設定値[151]：規定値5秒
																			//タイマは[151] を超えたか？
				tc_8(); 													//流量センサチェック起動処理 //*フローチャート側の表記ミス(8/25 2022 レビュー後変更)
				e_1000();	 												//流量センサエラー処理

				return -255;
			}
			return -2;
		}else if(elapsed_time_ms(g_C_8_ON_T3)/1000 > g_T_S.t151_s){				//*t13をt3に変更(8/25 2022 レビュー後変更) t3 -> t151
																			//タイマは[3] を超えたか？
			tc_8(); 														//流量センサチェック起動処理  //*フローチャート側の表記ミス(8/25 2022 レビュー後変更)
			e_1001();										 				//流量センサエラー処理

			return -255;
		}
		return -1;
	}
	return 0;
}
int keika_taime;
int c_9(void){
																		//中和タイマ（電解処理積算時間（3））を設置し利用 NEUTRAL_T
	bc_9(); 
	keika_taime=elapsed_time_s(g_NEUTRAL_T);															//通話処理チェック起動処理
	if(keika_taime > (g_T_S.t155_h * 3600)  ){     //* 60 add  * 60* 60 OK 20220906goto
																			//中和タイマーが設定時間（[155]分） 超えた場合（注1）
																		//設定値[155]：規定値60分																//※注1：電解処理を一定時間実施したら、中和処理を実施する
		e_2();			//TODO: E2 											//中和処理
		return 0;
	}
	return 0;
}
int c_10(void){
	if(SV1_PIN == VALVE_OFF){
		if(SV1_PIN == VALVE_OFF){
			if(g.flow_rate >= 0.1f){
																			//流量センサ：0.1L/m以上流れているか?
				if(g_C_10_F == 0){
					bc_10();												//給水電磁弁漏れチェック起動処理
					g_C_10_ON_T3 = timer_start_ms(); 						//給水電磁弁漏れタイマスタート
				}
				if(elapsed_time_ms(g_C_10_ON_T3)/1000 > g_T_S.t104_m * 60){
																			//漏れが[104]秒間続いたか？ t17からt104へ変更 20220901
																			//設定値[104]：規定値5秒
					e_1008(); //TODO: E1008 								//給水電磁弁エラー処理 //*e_1008();が抜けている(8/25 2022 レビュー後変更)

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
																			//漏水センサが反応したら電磁弁停止処理なので、漏水チェックを優先再起動の方法を検討する
	if(g.flag.leak_sensor == 1){
																			//漏水センサーON
		bc_11(); 															//漏水チェック起動処理
		t_sv2();														//SV2（水吐水）停止処理
		t_sv3();														//SV3（酸吐水）停止処理
		t_sv4(); 														//SV4（アル吐水）停止処理
		t_sv5();														//SV5（酸抜水）停止処理
		t_sv6();														//SV6（アル抜水）停止処理
		if(g.flag.leak_sensor == 1){
																			//漏水センサーON
			if(elapsed_time_ms(C_21_T2)/1000 > g_T_S.t103_s){
																			//漏水しているかチェック：
																			//設定値[103]：規定値60ｓ
				e_1051(); //TODO: E1051 									//漏水エラー処理
			}
			return 1;
		}
		return 1;
	}
	return 0;
}

int c_12(void){
	bc_12();																//フィルターチェック起動処理
	const float g_fc = s_5();						//FC=フィルタ交換計算取得
	if(g_fc < 500.0f){													//*g_T_S.t13_nに修正 20220901
		if(g_fc < 1000.0f){												//*g_T_S.t14_nに修正 20220901
			e_1030();				//TODO: E1030							//フィルタ交換警報処理
																			//表示方法検討（毎回表示か？）
			return -1;														//設定値[13]：規定値500回
		}else{
																			//M1031　フィルタ交換警報無視警告
			e_1031();		//TODO: E1031 									//フィルタ交換警報無視警告処理
			return -2;
		}
	}else
		return 0; 															//設定値[14]：規定値1000回 s
}
int c_13(void){
	if(elapsed_time_ms(g_C_1_ON_T2)/1000 >= g_T_S.t104_m * 60){
																			//電解業務実施中か？//*g.flag.module.c1をC_1_ON_T2 >= [16]minに変更(8/25 2022 LINE連絡後変更)
																			//*t16をt105に変更　20220901 mineshima
		const int r = c_13_1();												//酸アルカリタンク溢れチェック確認処理
		if(r == 1){
																			//条件2　電解処理ON且つ酸アルカリ吐水OFFが継続２０分の場合
			bc_13();														//酸アルカリタンク溢れチェック起動処理
			e_1026();														//酸アルカリタンク漏れエラー処理
			return -255;
		}
		return 1;
	}
	return -0;
}
int c_13_1(void){
	if(elapsed_time_s(g_P2_OFF_T2) > g_T_S.t104_m * 60 ){				//*設定値[105]:規定値20minに変更(8/25 2022 LINE連絡後変更)
																			//*t16をt105に変更　20220901 mineshima
																			//アルカリ未吐水20分以上 P2_OFF_T2> [105]　分
																			//電解処理ON且つ酸アルカリ吐水・抜水OFFが継続[16]２０分の場合

		if(elapsed_time_s(g_P1_OFF_T2) > g_T_S.t104_m * 60 ){      	//*設定値[105]:規定値20minに変更(8/25 2022 LINE連絡後変更)
																			//酸吐水20分以上 P1_OFF_T2> [105] 分

			return 1;
		}
	}
																			//P2_OFF_T2=アルカリタンク未排水タイマ
																			//P1_OFF_T2=酸タンク未排水タイマ

	return 0;
}
int c_14(void){
	bc_14(); 																//貯水タンク満水チェック起動処理
	g_C_14_F = 0;													    //両タンク満水フラグ off
																			//C_14_TF_F=両タンク満水フラグ
	if(g_ALD == 3){
  																			//ALD(アルカリタンク情報)＝3
		if(g_ACD == 3){
      																		//ACD(塩タンク情報）＝3
			if(g_C_14_F == 0){
        																	//満水フラグoff（C_14_TF_F＝0）？
				g_C_14_F = 1;

				c_1(0);
        																	//満水フラグon(C_14_TF_F＝1)
				e_5001(); 													//貯水タンク満水エラー処理
				return -1;
			}
			return 1;
		}
	}
	if(g_C_14_F == 1){
    																		//満水フラグon（C_14_TF_F＝1）？
		g_C_14_F = 0;

		c_1(1);
    																		//満水フラグoff(C_14_TF_F＝0)
		e_5002(); 															//貯水タンク満水エラー解除処理
		return 0;
	}
	return 1;
}
int c_15(void){

	bc_15(); 																//塩タンク蓋開異常チェック起動処理
	const int g_C_15_D = SALT_LID_PIN; 										//塩タンク蓋情報取得
	if(g_C_15_D == 1){
    																		//開
		tc_15(); 															//塩タンク蓋開異常チェック停止処理
		e_1022();															//塩タンク蓋開異常エラー処理
		return -1;
	}
	return 1;
}
int c_16(void){
	if(elapsed_time_s(g.timer.module.on.p0[0]) > (uint32_t)g_T_S.t101_h * 60 * 60){
																			//*設定値を[101]に変更
    																		//設定値[101]:規定値10000時間 //*設定値[43]を設定値[101]に変更(20220901修正)
    																		//システム運転積算タイマが([101]時間)を超えた場合
		bc_16(); 															//運転積算時間警報チェック起動処理
		if(g_E_1032_F == 0){
      																		//エラー表示未実施?
			e_1032();														//運転積算時間エラー警報処理
			return -1;
		}
		return 0;
	}
	return 1;
}
int c_17(void){
	if(elapsed_time_s(C_1_ON_T3) > (uint32_t)g_T_S.t102_h * 60 * 60){
																			//*設定値を[102]に変更 20220901修正 mineshima
																			//電解運転起算タイマが（[102]時間）	超えた場合	C_1_ON_T3> [102]
  																			//設定値[102]:規定値10000時間
		bc_17(); 															//電解積算時間警報チェック起動処理
		if(g_E_1033_F == 0){
     																		//エラー表示未実施?
			e_1033(); 													//電解積算時間エラー警報処理
			return -1;
		}
		tc_17();
		return 0;
	}
	tc_17();
	return 1;
}
int c_18(void){
	if(CVCC_CONTROL_PIN){
    																		//旋回処理フラグ＝1 C_1_F=1
		bc_18(); 															//塩水回路3報告弁循環OFF警報チェック起動処理
		if(SW2_PIN == 1){														//塩水路循環希望の場合でV4弁が循環側になっていない場合
			if(g_E_1034_F == 0){
        																	//エラー表示未実施？ E_1034_F=0?
				e_1034(); 												//塩水経路3報告弁巡回OFF警報処理
		 		tc_18(); 													//塩水回路3報告弁循環OFF警報チェック停止処理
				return 0;
			}
		}
		 		tc_18(); 													//塩水回路3報告弁循環OFF警報チェック停止処理
		return 0;
	}
	return 0;
}
int c_19(void){
  																			//起動条件＝P-3-13から呼ばれる
	c_1_1(); 																//電解業務緊急停止処理
  	bc_19(); 																	//塩タンク排水チェック起動処理
	if( SW3_PIN == 1)	{//TODO: V4弁が排水側になっている場合
		tc_19(); 															//塩タンク排水チェック停止処理
		return 1;
	}else{
		e_1035(); 														//塩水排水V4弁方向異常警報処理
		tc_19(); 															//塩タンク排水チェック停止処理
		return -1;
	}
}
int c_23(void){
	bc_23(); 																//主チェック起動処理
	c_2(); 																			//アルカリタンク状態チェック処理
	c_3(); 																			//酸タンク状態チェック処理
	c_4();  																			//塩タンク状態チェック処理
	c_8(); 																	//流量センサチェック処理
	c_9(); 																	//中和処理チェック処理
	c_10();				 													//給水電磁弁漏れチェック処理
	c_11(); 																//漏水チェック処理
	c_13(); 																//酸アルカリタンク溢れ処理
	c_14(); 																//貯水タンク(アルカリ・酸)満水処理
	c_15(); 																//塩タンク蓋開異常処理																//主チェック停止処理
	tc_23();
	return 0;
}
int c_24(void){
	bc_24(); 																//長時間起動処理
	c_6(); 																	//カラン未使用チェック処理
	c_7(); 																	//電解処理未使用チェック処理
	c_12(); 																//フィルターチェック処理
	c_16(); 																//運転積算時間警報チェック処理
	c_17(); 																//電解積算時間警報チェック処理
	tc_24(); 																//長時間チェック停止処理
	return 0;
}
