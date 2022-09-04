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
#include "c_module.h"
#include "s_module.h"
#include "../global_variable.h"
#include "../runtime.h"
#include "../delay.h"

enum ERROR_ENUM e_occur_error;

/**
 *	Wait until the reset button on Raspberry was pressed.
 * @param clear_error: 1 to reset current_error flag to NO_ERROR, 0 to keep current error.
 */
void wait_for_reset_button(uint8_t clear_error){
	while(RESET_ERROR_FLAG == 0U){
		runtime();
	}
	RESET_ERROR_FLAG = 0;
	if (clear_error)
		e_occur_error = NO_ERROR;
}

/**
 * カラン清掃処理 Water-faucet Refresh Process
 * Version: 0.7 - 20220821
 * @return
 */
int e1_faucet_refresh_process(void){
	be_1();
	e11();
	e_occur_error = E1;
	te_1();
	return 0;
}
/**
 * カラン清掃実施処理 Do Refresh
 * Version: 0.7 - 20220821
 * @return
 */
int e11(void){
	be_1_1();
	b_sv1();
	b_sv2();
	b_b_led_b();
	wait((uint32_t)g_T_S.t162_s * 1000);
	t_sv1();
	t_sv2();
	t_w_led_b();
	te11();
	return 0;
}
/**
 * 中和処理（SV7起動） Neutralized process(SV7 ON)
 * Version: 0.7 - 20220821
 * @return
 */
int e2(void){
	b_sv7_start();
	//B_SV7_ont2>（[28]s Neutralized） ON?
	if(elapsed_time_ms(SV7_ON_T2)/1000 > g_T_S.t156_s){
		C_1_ON_T3 = 0;
		t_sv7_stop();
	}
	return 0;
}
/**
 * 電源OFF依頼処理 Power OFF request processing
 * Version: 0.7 - 20220821
 * @return
 */
int e3(void){
//	e_current_error = M5005;  //タッチパネルに電源OFF依頼表示 Power off request display on touch panel
	while(1){
		runtime();
	}
//	return 0;
}
/**
 * 流量センサ上限エラー処理 Flow Sensor Over Range
 * Version: 0.7 - 20220821
 * @return
 */
int e1000(void){
	c_1_1();
	e_occur_error = M1000;
	p9_stop();
	p_3_13_flow_rate_process();
	e3();
	return 0;
}
/**
 * 流量センサ下限エラー処理 Low Flow rate Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1001(void){
	c_1_1();
	e_occur_error = M1001;
	p9_stop();
	p_3_13_flow_rate_process();
	e3();
	return 0;
}
/**
 * 過電圧1エラー処理 Over Voltage 1
 * Version: 0.7 - 20220821
 * @return
 */
int e1002(void){
	c_1_1();
	e_occur_error = M1002;
	p9_stop();
	wait_for_reset_button(1);
	return 0;
}
/**
 * 過電圧2エラー処理 Over Voltage 2
 * Version: 0.7 - 20220821
 * @return
 */
int e1003(void){
	c_1_1();
	e_occur_error = M1003;
	p9_stop();
	wait_for_reset_button(1);
	return 0;
}
/**
 * 過電圧3エラー処理 Over Voltage 3
 * Version: 0.7 - 20220821
 * @return
 */
int e1004(void){
	c_1_1();
	e_occur_error = M1004;
	wait_for_reset_button(1);
	return 0;
}
/**
 * 低電圧エラー処理 Low Voltage Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1005(void){
	c_1_1();
	e_occur_error = M1005;
	p9_stop();
	wait_for_reset_button(1);
	return 0;
}
/**
 * 電流範囲10％エラー処理 Current 10% Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1006(void){
	e_occur_error = M1006;
	return 0;
}
/**
 * 電流範囲20％エラー処理 Current 20% Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1007(void){
	c_1_1();
	e_occur_error = M1007;
	p9_stop();
	e3();
	return 0;
}
/**
 * 給水電磁弁エラー処理 SV1 Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1008(void){
	c_1_1();
	e_occur_error = M1008;
	p9_stop();
	e3();
	return 0;
}
/**
 * CVCC電源エラー処理 CVCC Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1009(void){
	c_1_1();
	e_occur_error = M1009;
	p9_stop();
	e3();
	return 0;
}
/**
 * 塩タンク満杯エラー処理 Salt Tank Full
 * Version: 0.7 - 20220821
 * @return
 */
int e1020(void){
	c_1_1();
	e_occur_error = M1020;
//	Wait （Drain by Human）
	wait_for_reset_button(1);
	return 0;
}
/**
 * 塩タンク空エラー処理 Empty Salt Tank
 * Version: 0.7 - 20220821
 * @return
 */
int e1021(void){
	c_1_1();
	e_occur_error = M1021;
	p9_stop();
	wait_for_reset_button(1);
	return 0;
}
/**
 * 塩タンク蓋開異常エラー処理 Salt Tank Cap Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1022(void){
	c_1_1();
	e_occur_error = M1022;
//	Wait （Close cap by human）
	wait_for_reset_button(1);
	return 0;
}
/**
 * 塩タンクセンサエラー処理 Salt tank level sensor Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1023(void){
	c_1_1();
	e_occur_error = M1023;
	p9_stop();
	e3();
	return 0;
}
/**
 * 酸タンクセンサエラー処理 Acid Tank Level Sensor Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1024(void){
	c_1_1();
	e_occur_error = M1024;
	p9_stop();
	e3();
	return 0;
}
/**
 * アルカリタンクセンサエラー処理 Alkali tank level sensor Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1025(void){
	c_1_1();
	e_occur_error = M1025;
	p9_stop();
	e3();
	return 0;
}
/**
 * 酸アルカリタンク溢れエラー処理 Acid and Alkali Tank overflow Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1026(void){
	c_1_1();
	e_occur_error = M1026;
	p9_stop();
	e3();
	return 0;
}
/**
 * 酸タンク空エラー処理 Acid Tank Empty Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1028(void){
	while(s2_acid_tank_data_set() == 0){
		if(g.flag.module.e1028 == 0){
			t_p1();
			t_sv3();
			e_occur_error = M1028;
			b_r_led_b();
			g.flag.module.e1028 = 1;
		}
		runtime();
	}
	if(g.flag.module.e1028 == 1){
		g.flag.module.e1028 = 0;
		e_occur_error = NO_ERROR;
		t_r_led_b();
	}
	return 0;
}
/**
 * アルカリタンク空エラー処理 Alkali tank Empty
 * Version: 0.7 - 20220821
 * @return
 */
int e1029(void){
    while(s1_alkali_tank_data_set() == 0){
        if(g.flag.module.e1029 == 0){
            t_p2();
            t_sv4();
			e_occur_error = M1029;
            b_b_led_b();
            g.flag.module.e1029 = 1;
        }
        runtime();
    }
    if(g.flag.module.e1029 == 1){
    	g.flag.module.e1029 = 0;
        e_occur_error = NO_ERROR;
        t_b_led_b();
    }
	return 0;
}
/**
 * フィルタ交換警報処理 Filter Replace Alarm
 * Version: 0.7 - 20220821
 * @return
 */
int e1030(void){
	M1030_F++;
	e_occur_error = M1030;
	return 0;
}
int e1031(void){
	c_1_1();
	e_occur_error = M1031;
//	Wait filter changed （Replace by human）
	wait_for_reset_button(1);
	return 0;
}
/**
 * フィルター交換 Filter Replace
 * Version: 0.7 - 20220821
 * @return
 */
int e1031_1(void){
	wait_for_reset_button(0);
	p9_stop();
//	Filter changing by human
	while(FILTER_COMPLETE_FLAG == 0){
		runtime();
	}
	g.flag.m1030 = 0;
	SV1_ON_T3 = 0; //Reset SV1 timer3
	return 0;
}
/**
 * 運転積算時間エラー警報処理 Total power on time
 * Version: 0.7 - 20220821
 * @return
 */
int e1032(void){
	e_occur_error = M1032;
	g.flag.module.e1032 = 1;
	return 0;
}
/**
 * 電解積算時間エラー警報処理 Total Electrolyte time Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1033(void){
	e_occur_error = M1033;
	g.flag.module.e1033 = 1;
	return 0;
}
/**
 * 塩水経路３方向弁循環OFF警報処理 Salt-water Drain direction Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1034(void){
	c_1_1();
	e_occur_error = M1034;
	g.flag.module.e1034 = 1;
	return 0;
}
/**
 * 塩水排水経路V4弁方向不良警報処理 Salt Tank Drain Valve Direction Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1035(void){
	c_1_1();
	e_occur_error = M1035;
	g.flag.module.e1035 = 1;
	return 0;
}
/**
 * 漏水エラー処理 Water Leak Error
 * Version: 0.7 - 20220821
 * @return
 */
int e1051(void){
	c_1_1();
	e_occur_error = M1051;
	p9_stop();
	e3();
	return 0;
}
/**
 * 貯水タンク満水エラー処理 Tank Full Check Log process
 * Version: 0.7 - 20220821
 * @return
 */
int e5001(void){
	c_1_1();
	e_occur_error = M5001;
	return 0;
}
/**
 * 貯水タンク満水エラー解除処理 Tank Full Check Log reset process
 * Version: 0.7 - 20220821
 * @return
 */
int e5002(void){
	e_occur_error = M5002;
	return 0;
}
/**
 * 電解未処理対応実施処理 Not Electrolyte Time Report
 * Version: 0.7 - 20220821
 * @return
 */
int e5003(void){
	c_1_1();
	e_occur_error = M5003;
	p_8();
	p_1();
	return 0;
}
