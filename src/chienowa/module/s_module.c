/*
 * s_module.c
 *
 *  Created on: Jul 29, 2022
 *      Author: Renan
 */
//2022/09/01 普喜亮太、趙立民、石井岳大　制作
#include "s_module.h"
#include "b_module.h"
#include "t_module.h"
#include "../pin_define.h"
#include "../global_variable.h"

#define ON		(1)
#define OFF		(0)
int g_ALD, g_ACD, g_SAD;

#define g_FL1_F (g.flag.io.fl1)
#define g_FL2_F (g.flag.io.fl2)
#define g_FL3_F (g.flag.io.fl3)
#define g_FL4_F (g.flag.io.fl4)
#define g_FL5_F (g.flag.io.fl5)
#define g_FL6_F	(g.flag.io.fl6)
#define g_FL7_F (g.flag.io.fl7)
#define g_FL8_F (g.flag.io.fl8)
#define g_FL1	(g.io.fl1)
#define g_FL2	(g.io.fl2)
#define g_FL3	(g.io.fl3)
#define g_FL4	(g.io.fl4)
#define g_FL5	(g.io.fl5)
#define g_FL6	(g.io.fl6)
#define g_FL7	(g.io.fl7)
#define g_FL8	(g.io.fl8)





/**
 * Update: Change set value to g_ALD and return g_ALD
 * @return g_ALD
 */
int s_1(void) {                                         					//アルカリタンクセンサ確認処理
	s_4_4();
	s_4_5();
	s_4_6();

	if(g_FL4==1){                                                             //FL4が1を返した場合FL4まではアルカリ水で満たされている
		if(g_FL5==1){                                                         //FL5が1を返した場合FL5までアルカリ水が満たされている
			if(g_FL6==1){                                                     //FL6が1を返した場合FL6までアルカリ水で満たされている
				g_ALD = 3;                                                   //正常という結果
			}else{                                                          //またFL5が0を返した場合FL6までアルカリ水が満たされていない
				g_ALD = 2;                                                   //正常という結果
			}

		}else{                                                              //FL5が0を返した場合FL5まではアルカリ水が満たされていない
            if(g_FL6==1){                                                     //FL6が1を返すのは構造上ありえないこと
            	g_ALD = -1;                                                  //異常という結果
			}else{                                                          //またFL6が0を返すのは構造上正常
				g_ALD = 1;                                                   //正常という結果
			}

		}
	}else{                                                                  //またFL4が0を返した場合FL4まではアルカリ水が満たされていない
		if(g_FL5==1){                                                         //FL5が1を返すのは構造上ありえないこと
			if(g_FL6==1){                                                     //FL6が1を返すのは構造上ありえないこと
				g_ALD = -3;                                                  //異常という結果
			}else{                                                          //FL6が0を返した場合
				g_ALD = -4;                                                  //異常という結果
			}

		}else{                                                              //またFL5が0を返した場合FL5までアルカリ水が満たされていない
			if(g_FL6==1){                                                     //FL6が1を返すのは構造上ありえないこと
				g_ALD = -2;                                                  //異常という結果
			}else{                                                          //FL6が0を返すのは構造上正常
				g_ALD = 0;                                                   //正常という結果
			}
		}
	}
	return g_ALD;
}
int s_2_status;
/**
 * Update: Change set value to g_ALD and return g_ACD
 * @return g_ACD
 */
int s_2(void) {																//酸タンクセンサ確認処理
	s_4_1();
	s_4_2();
	s_4_3();
//	return 3;
	if(g_FL1==1){																//FL1が1を返した場合FL1まで酸が満たされている
		if(g_FL2==1){															//FL2が1を返した場合FL2まで酸が満たされている
			if(g_FL3==1){														//FL3が1を返した場合FL3まで酸が満たされている
				g_ACD = 3;                                                   //正常という結果
			}else{                                                          //またFL3が0を返した場合FL3まで酸が満たされていない
				g_ACD = 2;                                                   //正常という結果
			}

		}else{                                                              //FL2が0を返した場合FL2まで酸が満たされていない
			if(g_FL3==1){                                                     //FL3が1を返すのは構造上ありえないこと
				g_ACD = -1;                                                  //異常という結果
			}else{                                                          //またFL3が0を返すのは構造上正常
				g_ACD = 1;                                                   //正常という結果
			}

		}
	}else{                                                                  //FL1が0を返した場合FL1まで酸が満たされていない
		if(g_FL2==1){                                                         //FL2が1を返すのは構造上ありえないこと
			if(g_FL3==1){                                                     //FL3が1を返すのは構造上ありえないこと
				g_ACD = -3;                                                  //異常という結果
			}else{                                                          //またFL3が0を返した場合
				g_ACD = -4;                                                  //異常という結果
			}

		}else{                                                              //またFL2が0を返した場合構造上正常
			if(g_FL3==1){                                                     //FL3が1を返すのは構造上ありえないこと
				g_ACD = -2;                                                  //異常という結果
			}else{                                                          //またFL3が0を返すのは構造上正常
				g_ACD = 0;                                                   //正常という結果
			}
		}
	}
	return g_ACD;
}
/**
 * Update: Change set value to g_ALD and return g_SAD
 * @return g_SAD
 */
int s_3(void) {																//塩タンクセンサ確認処理
	s_4_7();
	s_4_8();
	if(g_FL7==1){																//FL7が１を返した場合はFL7まで塩水が満たされている
		if(g_FL8==1){															//FL8が1を返した場合はFL8まで塩水が満たされている
			g_SAD = 2;														//正常という結果
		}else{																//またFL8が0を返した場合FL8までは塩水が満たされていない
			g_SAD = 1;														//正常という結果
		}
	}else{																	//FL7が0を返した場合FL7まで塩水が満たされていない
		if(g_FL8==1){															//FL8が1を返すのは構造上ありえないこと
			g_SAD = -1;														//異常という結果
		}else{																//またFL8が0を返すのは構造上正常
			g_SAD = 0;														//正常という結果
		}
	}
	return g_SAD;
}
int s_4(void){
	bs_4();
	s_4_1();
	s_4_2();
	s_4_3();
	s_4_4();
	s_4_5();
	s_4_6();
	s_4_7();
	s_4_8();
	ts_4();
	return 0;
}

int	s_4_1(void){															//FL1チャタリング処理
	switch (g_FL1){															//ONとOFFでスイッチ
		case OFF:																//OFFの場合
			switch(g_FL1_F){													//g_FL1_Fが0か1かでスイッチ
				case 0:															//0の場合
					g_FL1_F=0;													//0を返す
					return 0;													//終了
				case 1:															//1の場合
					ts_4_1();													//FL1チャタリング防止停止処理、以下新フローチャートに合わせ修正
					if(g_S_4_1_OFF_T2 >= g_T_S.t118_s){							//貯水タンク下下限センサ(OFF時)安定化時間を超えた場合
						g_FL1_F=1;												//1を返す
						return 1;												//終了
					}else{														//超えなかった場合
						g_FL1_F=0;											//0を返す
						return 0;												//終了
					}
			}
			break;
		case ON:																//ONの場合
			switch(g_FL1_F){													//g_FL1_Fが0か1かでスイッチ
				case 0:															//0の場合
					bs_4_1();													//FL1チャタリング防止起動処理
					if(g_S_4_1_ON_T2 >= g_T_S.t113_s){							//T2==[21]から修正、貯水タンク下下限センサ(ON時)安定化時間を超えた場合
						g_FL1_F=1;												//1を返す
						return 1;												//フローチャートではRETURNのみ、終了
					}else{														//超えなかった場合
						g_FL1_F=0;												//0を返す
						return 0;												//終了
					}
				case 1:															//1だった場合
					g_FL1_F=1;													//1を返す
					return 1;													//終了
			}
			break;
		default:
			break;
	}
	return 0;
}
int	s_4_2(void){															//FL2チャタリング処理
	switch (g_FL2){
	case OFF:																//スイッチFL2がOFFの場合
		switch(g_FL2){
			case 0:
				g_FL2_F=0;													//FL2＿F＝0の場合
				return 0;													//0を返す
			case 1:
				ts_4_2();													//FL2チャタリング防止停止処理
				g_FL2_F=0;													//FL2＿F＝0の場合
				return 0;						//0を返す
		}
		break;
	case ON:																//スイッチFL2がONの場合
		switch(g_FL2){
			case 0:
				bs_4_2();													//FL2チャタリング防止起動処理
				if(g_S_4_2_ON_T2 == g_T_S.t114_s){							//T2 >= [22]としたら
					g_FL2_F=1;												//FL2＿F＝1の場合
					return 1;												//1を返す
				}else{
					g_FL2_F=0;												//FL2＿F＝0の場合
					return 0;												//0を返す
				}
			case 1:
				g_FL2_F=1;													//ケース1の場合FL2＿F＝1でしたら
				return 1;													//1を返す（フローチャートではRETURNのみ）
			default:
			break;
		}
		break;
	}
    return 0;
}
int	s_4_3(void){															//FL3チャタリング処理
	switch (g_FL3){
	case OFF:																//スイッチFL3がOFFの場合
		switch(g_FL3){
			case 0:
				g_FL3_F=0;													//FL3＿F＝0の場合
				return 0;													//0を返す
			case 1:
				ts_4_3();													//FL3チャタリング防止停止処理
				g_FL3_F=0;													//FL3＿F＝0の場合
				return 0;													//0を返す
		}
		break;
	case ON:																//スイッチFL3がONの場合
		switch(g_FL3){
			case 0:
				bs_4_3();													//FL3チャタリング防止起動処理
				if(g_S_4_3_ON_T2 == g_T_S.t115_s){											//T2 >= [23]としたら
					g_FL3_F=1;												//FL3＿F＝1の場合
					return 1;												//1を返す
				}else{
					g_FL3_F=0;												//FL3＿F＝0の場合
					return 0;												//0を返す
				}
			case 1:
				g_FL3_F=1;													//ケース1の場合FL3＿F＝1でしたら
				return 1;													//1を返す（フローチャートではRETURNのみ）
			default:
			break;
		}
	break;
	}
	return 0;
}
int	s_4_4(void){															//FL4チャタリング処理
	switch (g_FL4){
	case OFF:																//スイッチFL4がOFFの場合
		switch(g_FL4){
			case 0:
				g_FL4_F=0;													//FL4＿F＝0の場合
				return 0;													//0を返す
			case 1:
				ts_4_4();													//FL4チャタリング防止停止処理
				if(g_S_4_4_OFF_T2 == g_T_S.t118_s){							//貯水タンク下下限センサ(OFF時)安定時間を超えた場合
					g_FL4_F=1;												//FL4＿F＝1の場合
					return 1;												//0を返す
				}else{														//超えなかった場合
				g_FL4_F=0;													//FL4＿F＝0の場合
				return 0;													//0を返す
				}
		}
		break;
	case ON:																//スイッチFL4がONの場合
		switch(g_FL4){
			case 0:
				bs_4_4();													//FL4チャタリング防止起動処理
				if(g_S_4_4_ON_T2 == g_T_S.t113_s){							//貯水タンク下下限センサ(ON時)安定化時間を超えた場合
					g_FL4_F=1;												//FL4＿F＝1の場合
					return 1;												//1を返す
				}else{														//超えなかった場合
					g_FL4_F=0;												//FL4＿F＝0の場合
					return 0;												//0を返す
				}
			case 1:
				g_FL4_F=1;													//ケース1の場合FL4＿F＝1でしたら
				return 1;													//1を返す（フローチャートではRETURNのみ）
			default:
			break;
		}
		break;
	default:
	break;
	}
	return 0;
}
int s_4_5(void){                                      						//FL5チャタリンング
    switch (g_FL5){                                   						//ONとOFFスイッチ
    case OFF:                                         						//OFFの場合
        switch(g_FL5_F){                              						//フローチャートでは0か1にスイッチ
            case 0:                                   						//0の場合
                g_FL5_F=0;                            						//g_FL5_Fは0を返す
                return 0;                             						//終了
            case 1:                                   						//1の場合
                ts_4_5();                             						//FL5チャタリング防止処理
                g_FL5_F=0;                            						//g_FL5_Fは0を返す
                return 0;                             						//フローチャートではreturnのみ
            default:
                break;
        }
        break;
    case ON:                                          						//ONの場合
        switch(g_FL5){                                						//ONとOFFのスイッチ
            case  0:                                  						//0の場合
                bs_4_5();                                						//FL4チャタリング防止起動処理
                if (g_S_4_5_ON_T2>=g_T_S.t114_s){     						//貯水タンク下限センサ(ON時)安定化時間を超えた場合
                    g_FL5_F=1;                        						//g_FL5_Fは1を返す
                    return 1;                         						//終了
                }else{                                						//超えなかった場合
                    g_FL5_F=0;                        						//g_FL5_Fは0を返す
                    return 0;                        		 				//フローチャートではreturnのみ
                }
            case 1:                                   						//1の場合
                g_FL5_F=1;                            						//g_FL5_Fは1を返す
                return 1;                             						//終了

            default:
                break;
        }
        break;
    default:
        break;
    }
    return 0;
}
int s_4_6(void){                                      						//FL6チャタリング処理
    switch (g_FL6){                                   						//g_FL6がONかOFFかでスイッチ
    case OFF:                                         						//OFFの場合
        switch (g_FL6_F){                             						//g_FL6_Fが0か1でスイッチ
            case 0:                                   						//0の場合
                g_FL6_F=0;                            						//g_FL6_Fは0を返す
                return 0;                             						//終了
            case 1:                                   						//1の場合
                ts_4_6();                               						//FL6チャタリング防止停止処理
                g_FL6_F=0;                            						//g_FL6_Fは0を返す
                return 0;                             						//フローチャートではreturnのみ、終了
            default:
                break;
        }
        break;
    case ON:                                          						//ONの場合
        switch (g_FL6_F){                             						//g_FL6_FがONかOFFでスイッチ
            case 0:                                   						//0の場合
                bs_4_6();                               						//FL6チャタリング防止起動処理
                if(g_S_4_6_ON_T2>=g_T_S.t115_s){        						//貯水タンク上限センサ(ON時)安定化時間を超えた場合
                    g_FL6_F=1;                        						//g_FL6_Fは1を返す
                    return 1;                         						//終了
                }else{                                						//超えなかった場合
                    g_FL6_F=0;
                    return 0;                         						//フローチャートではreturnのみ
                }
            case 1:                                   						//1の場合
                g_FL6_F=1;                            						//g_FL6_Fは0を返す
                return 1;                             						//終了
            default:
                break;
        }
        break;
    default:
        break;
    }
    return 0;
}
int s_4_7(void){                                                			//FL7チャタリング処理
    switch (g_FL7){                                             			//ONとOFFでスイッチ
    case OFF:                                                   			//OFFの場合
        switch(g_FL7_F){                                        			//見本ではg_FL7のみ、FL7_Fが0か1かでスイッチ
            case 0:                                             			//0の場合
                g_FL7_F=0;                                      			//g_FL7_Fは0を返す
                return 0;                                       			//終了

            case 1:                                             			//1の場合
                ts_4_7();                                       			//FL7チャタリング防止停止処理
                g_FL7_F=0;                                      			//g_FL7_Fは0を返す
                return 0;                                       			//終了

            default:                                            			//case文すべての文末にdefaultを追加
                break;
        }
        break;                                                  			//OFF終了
    case ON:                                                    			//ONの場合
        switch(g_FL7_F){                                        			//g_FL7_Fが0か1かでスイッチ
            case  0:                                            			//0の場合
                bs_4_7();                                  			//FL7チャタリング防止起動処理
                if (g_S_4_7_ON_T2>=g_T_S.t116_s){               			//見本は==になっている、(センサ安定化)塩タンク下限センサ(ON時)安定化時間を超えた場合
                    g_FL7_F=1;                                  			//1を返す
                    return 1;                                   			//終了
                }else{                                          			//超えなかった場合
                    g_FL7_F=0;                                  			//0を返す
                    return 0;                                   			//終了
                }
            case 1:                                             			//1の場合
                g_FL7_F=1;                                      			//1を返す
                return 1;                                      	 			//終了
            default:
                break;
        }
        break;
    default:
        break;
    }
    return 0;
}
int s_4_8(void){                                                			//FL8チャタリング処理
    switch (g_FL8){                                             			//g_FL8がONかOFFかでスイッチ
    case OFF:                                                   			//OFFの場合
        switch (g_FL8_F){                                       			//g_FL8_Fが0か1かでスイッチ
            case 0:                                             			//0の場合
                g_FL8_F=0;                                      			//0を返す
                return 0;                                       			//終了
            case 1:                                             			//1の場合
                ts_4_8();                                         			//フローチャートにFL7とミスあり、FL8チャタリング防止停止処理
                g_FL8_F=0;                                     	 			//0を返す
                return 0;                                      	 			//終了

            default:
                break;
        }
        break;
    case ON:                                                    			//ONの場合
        switch (g_FL8_F){                                       			//g_FL8_Fが0か1かでスイッチ
            case 0:                                             			//0の場合
                bs_4_8();                                         			//FL8チャタリング防止起動処理
                if(g_S_4_8_ON_T2>=g_T_S.t117_s){                  			//見本は==になっている、(センサ安定化)塩タンク上限センサ(ON時)安定化時間を超えた場合
                    g_FL8_F=1;                                  			//1を返す
                    return 1;                                   			//終了

                }else{                                          			//超えなかった場合
                    g_FL8_F=0;                                  			//0を返す
                    return 0;                                   			//終了

                }
            case 1:                                             			//1の場合
                g_FL8_F=1;                                      			//1を返す
                return 1;                                       			//終了
            default:
                break;
        }
        break;
    default:
        break;
    }
    return 0;
}


float s_5(void) {                                      						//フィルタ交換計算セット
	float A,B,C;
	C= 0.067f*(float)g_SV1_ON_T3;                                           //C=0.067×SV13
	B= 0.034f*(float)g_SV2_ON_T3;                                           //B=0.034×SV23
	A = ((float)g_V_S.v11_mg_L*650)/(55/(float)g_V_S.v12_L);                 //A=(フィルタ樹脂容量)L×650/(55/X(原水硬度))
	return A/(B+C);                                                         //FC=A/(B+C)
}

/**
 * Save level sensor to ALD variable
 * @return int [0:1]
 * 1 - if ALD changed
 * 0 - if ALD not changed
 */
//int s1_alkali_tank_data_set(void) {
//	int pre_ALD = g_ALD;
//	g_ALD = s11_alkali_tank_data_check();
//	if (pre_ALD != g_ALD)
//		return 1;
//
//}
