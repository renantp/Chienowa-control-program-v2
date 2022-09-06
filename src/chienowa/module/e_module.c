/*
 * e_module.c
 *
 *  Created on: Jul 29, 2022
 *      Author: Renan
 */
//2022/09/01 普喜亮太、趙立民、石井岳大　制作
#include "e_module.h"
#include "t_module.h"
#include "b_module.h"
#include "p_module.h"
#include "c_module.h"
#include "s_module.h"
#include "../delay.h"
#include "../global_variable.h"
#include "../runtime.h"

uint8_t reset_button, completion_button = 0;
//union Error_status g_error_status;
enum ERROR_ENUM last_error, current_error;
int e_1(void){                                    						            //カラン清掃処理
	be_1();                                                                          //カラン清掃起動処理
	e_1_1();                                                                          //カラン清掃実施処理
	current_error = E1;                                                             //タッチパネルエラー表示 (発生時刻、エラー番号、エラー内容)
	te_1();                                                                          //カラン清掃停止処理
	return 0;
}
int e_1_1(void){                                                                      //カラン清掃実施処理
	be_1_1();                                                                         //カラン清掃実施起動処理
	b_sv1();                                                                  //SV1起動処理
	b_sv2();                                                                  //SV2起動処理
	b_b_led_b();                                                                    //白色LED点滅処理
	wait((uint32_t)g_T_S.t162_s * 1000);                                             //[40]→[162]に変更
	t_sv1();                                                                   //SV1停止処理
	t_sv2();                                                                   //SV2停止処理
	t_w_led_b();                                                                    //白色LED点滅停止処理
	te_1_1();                                                                         //カラン清掃実施停止処理
	return 0;
}
int e_2(void){                                                                       //中和処理(SV7起動)
	b_sv7();                                                                  //中和起動処理
	if(elapsed_time_ms(g_SV7_ON_T2)/1000 > g_T_S.t156_s){                           //中和タイマーリセット
		g_NEUTRAL_T=0;                                                              //SV7起動処理
		t_sv7();                                                               //中和停止処理
		return 1;
	}
	return 0;
}
int e_3(void){                                        //電源OFF依頼処理
	last_error = current_error;
	current_error = M5005;                                                          //タッチパネルに電源OFF依頼表示 Power off request display on touch panel
	while(1){
		runtime();
	}
}
int e_1000(void){                                                                    //流量センサ上限エラー処理
	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1000;                                                          //タッチパネルエラー表示
	p_9();                                                                           //終了停止
	p_3_13();                                                                       //流量調整処理
	e_3();                                                                          //電源OFF依頼処理
	return 0;
}
int e_1001(void){                                                                    //流量センサ下限エラー処理
	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1001;                                                          //電解層流量下限エラー警報
	p_9();                                                                           //終了停止
	p_3_13();                                                                       //流量調整処理
	e_3();                                                                          //電源OFF依頼処理
	return 0;
}
int e_1002(void){                                                                    //過電圧1エラー処理
	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1002;                                                          //タッチパネルエラー表示
	p_9();                                                                           //終了停止
	while(reset_button == 1){                                                       //リセット待ち
	}
	return 0;
}
int e_1003(void){                                        //過電圧2エラー処理
	//TODO: Show alarm

	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1003;                                                          //電解層過電圧2(軽警報)
	p_9();                                                       //終了停止
	while(reset_button == 1){                                                       //リセット待ち
	}
	return 0;
}
int e_1004(void){                                                                    //過電圧3エラー処理
	c_1_1();                                 	//電解業務緊急停止処理
	current_error = M1004;                                                          //電解層過電圧3(塩水濃度)警報
	while(reset_button == 1){                                                       //リセット待ち
	}
	return 0;
}
int e_1005(void){                                                                    //低電圧エラー処理
	c_1_1();                                                                    //電解業務緊急停止処理
	current_error = M1005;                                                          //電解層低電圧(重警報)
	p_9();                                                                           //終了停止
	while(reset_button == 1){                                                       //リセット待ち
	}
	return 0;
}
int e_1006(void){                                                                    //電流範囲10％エラー処理
	current_error = M1006;                                                          //ログ書き込み処理電解層電流調整要求警報
	return 0;
}
int e_1007(void){                                                                    //電流範囲20％エラー処理
	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1007;                                                          //ログ書き込み処理電解層電流値異常
	p_9();                                                                           //終了停止
	e_3();                                                                           //電源OFF依頼処理
	return 0;
}
int e_1008(void){                                                                    //給水電磁弁エラー処理
	c_11();                                                                          //電解業務緊急停止処理
	current_error = M1008;                                                          //ログ書き込み処理電解層給水電磁弁異常
	p_9();                                                                           //終了停止
	e_3();                                                                           //電源OFF依頼処理
	return 0;
}
int e_1009(void){                                                                    //CVCC電源エラー処理
	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1009;                                                          //ログ書き込み処理電解層CVCC電源アラーム
	p_9();                                                                           //終了停止
	e_3();                                                                           //電源OFF依頼処理
	return 0;
}
int e_1020(void){                                                                    //塩タンク満杯エラー処理
	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1020;                                                          //タッチパネル表示処理塩水タンク満水警報
	//TODO: Wait （Drain by Human)                                                  //処理待ち（人による排水）
	while(reset_button == 1){                                                       //リセット待ち
	}
	current_error = NO_ERROR;                                                       //タッチパネル表示削除処理塩水タンク満水警報
	return 0;
}
int e_1021(void){                                                                    //塩タンク空エラー処理
	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1021;                                                          //タッチパネルエラー表示塩タンク下位低下警報
	p_9();                                                                           //終了停止
	while(reset_button == 1){                                                       //リセット待ち
	}
	return 0;
}
int e_1022(void){                                                                    //塩タンク蓋開異常エラー処理
	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1022;                                                          //タッチパネル表示処理塩水タンク蓋空警報
	//TODO: Wait （Close cap by human)                                              //処理待ち（人による蓋閉）
	while(reset_button == 1){                                                       //リセット待ち
	}
	current_error = NO_ERROR;                                                       //タッチパネル表示削除処理塩水タンク蓋空警報
	return 0;
}
int e_1023(void){                                                                    //塩タンクセンサエラー処理
	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1023;                                                          //タッチパネルエラー表示塩タンクセンサー異常
	p_9();                                                                           //終了停止
	e_3();                                                                           //電源OFF依頼処理
	return 0;
}
int e_1024(void){                                                                    //酸タンクセンサエラー処理
	c_1_1();                                                                          //電解業務緊急停止処理
	current_error = M1024;                                                          //酸タンクセンサ異常
	p_9();                                                                           //全てを停止する
	e_3();                                                                           //電源OFF処理依頼
	return 0;
}
int e_1025(void){						                                            //アルカリタンクセンサエラー処理
	c_1_1();								                                            //電解業務緊急停止処理
	current_error = M1025;				                                            //アルカリタンクセンサ異常
	p_9();								                                            //全てを停止する
	e_3();                                                                           //電源OFF処理依頼
	return 0;
}
int e_1026(void){						                                            //酸アルカリタンク溢れエラー処理
	c_1_1();								                                            //電解業務緊急停止処理
	current_error = M1026;				                                            //酸アルカリタンク溢れ異常
	p_9();								                                            //全てを停止する
	e_3();                                                                           //電源OFF処理依頼
	return 0;
}

int e_1028(void){						                                            //酸タンク空エラー処理
    while(s_2()==0){						                                            //酸タンクが空の時
        if(g_E_1028_F==0){				                                            //スタートフラグ＝0の場合
            t_p1();				                                            //P1のタイマーを停止する
            t_sv3();				                                            //酸性水吐水電磁弁のタイマーを停止する
			current_error = M1028;		                                            //酸タンク空を表示するためのフラグ
            b_r_led_b();			                                            //点灯する
            g_E_1028_F = 1;				                                            //酸タンク空エラーを表示するためのフラグ
        }
        runtime();
    }
    if(g_E_1028_F==1){					                                            //酸タンク空エラーを表示するためのフラグがある場合
        g_E_1028_F = 0;					                                            //スタートフラグ＝1の
        current_error = NO_ERROR;		                                            //エラーなし
        t_r_led_b();				                                            //点灯停止
    }
	return 0;
}
/**
* Under consider
 * @return
 */
int e_1029(void){						                                            //アルカリタンク空エラー処理
    while(s_1()==0){
        if(g_E_1029_F==0){				                                            //スタートフラグ＝0の場合
            t_p2();				                                            //P2を停止する
            t_sv4();				                                            //アルカリ性水吐水電磁弁
			current_error = M1029;		                                            //アルカリタンク空エラーを表示するためのフラグ
            b_b_led_b();			                                            //点灯する
            g_E_1028_F = 1;				                                            //アルカリタンク空エラーを表示するためのフラグ
        }
    }
    if(g_E_1029_F==1){					                                            //アルカリタンク空エラーを表示するためのフラグがある場合
        g_E_1029_F = 0;					                                            //スタートフラグ＝0
        current_error = NO_ERROR;		                                            //エラーなし
        t_b_led_b();				                                            //点灯停止
    }
	return 0;
}
/* Under consider
 * @return
 */
int e_1030(void){						                                            //フィルタ交換警報処理
	g_M1030_F++;						                                            //フィルタ交換警報を表示するためのフラグ
	current_error = M1030;				                                            //フィルタ交換警報
	return 0;
}
int e_1031(void){						                                            //フィルタ交換警報無視警告処理
	c_1_1();								                                            //電解業務緊急停止処理
	current_error = M1031;				                                            //フィルタ交換警報無視処理
	e_1031_1();							                                            //フィルタ交換
	e_3();								                                            //電源OFF処理依頼
	return 0;
}
/**
 * Under consider
 * @return
 */
int e_1031_1(void){						                                            //フィルタ交換処理
    while(reset_button == 1){
	}
	p_9();								                                            //終了処理
	while(completion_button == 1){
	}
	g_M1030_F = 0;						                                            //フィルタ交換警報エラーを表示するためのフラグ
	g_SV1_ON_T3 = 0;					                                            //給水電磁弁のタイマー3をリセット
	return 0;
}
int e_1032(void){						                                            //運転積算時間エラー処理
	current_error = M1032;				                                            //運転積算時間エラー
	g_E_1032_F = 1;						                                            //運転積算時間エラーを表示するためのフラグ
	return 0;
}
int e_1033(void){						                                            //電解積算時間エラー警報処理
	current_error = M1033;				                                            //電解積算時間エラー
	g_E_1033_F=1;						                                            //電解積算時間エラー警報を表示ためのフラグ
	return 0;
}
int e_1034(void){						                                            //塩水経路3方向弁循環OFF警報処理
	c_1_1();								                                            //電解業務緊急停止処理
	current_error = M1034;				                                            //塩水経路3方向弁循環OFF警報
	g_E_1034_F=1;						                                            //電解実施可能チェック処理を表示するためのフラグ
	return 0;
}
int e_1035(void){						                                            //塩水排水経路V4弁方向不良警報処理
	c_1_1();								                                            //電解業務緊急停止処理
	current_error = M1035;				                                            //塩水排水経路V4弁方向不良警報
	g_E_1035_F = 1;						                                            //塩水排水経路V4弁方向不良警報を表示するためのフラグ
	return 0;
}
int e_1051(void){						                                            //漏水エラー処理
	c_1_1();							                                            //電解業務緊急停止処理
	current_error = M1051;				                                            //漏水エラー
	p_9();								                                            //全てを停止する
	e_3();                                                                           //電源OFF処理依頼
	return 0;
}
int e_5001(void){						                                            //貯水タンク満水エラー処理
	c_1_1();						                                            //電解業務緊急停止処理
	current_error = M5001;			                                                //貯水ランク満水報告
	return 0;
}
int e_5002(void){						                                            //貯水ランク満水エラー解除処理
	current_error = M5002;			                                                //貯水タンク満水回復報告
	return 0;
}
int e_5003(void){						                                            //電解未処理対応実施処理
	c_1_1();								                                            //電解業務緊急停止処理
	current_error = M5003;				                                            //電解未処理対応実施
	p_8();								                                            //全機能停止処理
	p_1();								                                            //初期動作モード
	return 0;
}
//
