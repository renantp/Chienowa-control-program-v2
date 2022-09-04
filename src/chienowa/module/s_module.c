/*
 * s_module.c
 *
 *  Created on: Jul 29, 2022
 *      Author: Renan
 */

#include "s_module.h"
#include "../pin_define.h"

int g_ALD, g_ACD, g_SAD;

float s5_filter_change_formula(long SV1_T3, long SV2_T3, long g_V_S_v11_mg_L,long g_V_S_v12_L) {
	float A,B,C;
	C= 0.067f*(float)SV1_T3;
	B= 0.034f*(float)SV2_T3;
	A= ((float)g_V_S_v11_mg_L*650)/(55/(float)g_V_S_v12_L);
	return A/(B+C);
}

////TODO: S4 - Water softener input data
//int s4_water_softener_input_data(void) {
//
//	return -128;
//}

/**
 * Check level sensor Salt tank and return result
 * @return int [-1:2, -128]
 * -1: NG
 * 0, 1, 2: OK
 * -128: Crash
 */
int s3_salt_tank_data_set(void) {
	union {
		struct {
			uint8_t bit0 :1;
			uint8_t bit1 :1;
		};
		uint8_t bit;
	} data;

	data.bit0=!FL7;
	data.bit1=!FL8;

	//data.bit = 2^2 = 4bit
	//FL7.FL8 ---> bit1.bit0

	switch (data.bit) {
	case 0://00
		return 0;
	case 1://01
		return 1;
	case 2://10
		return -1;
	case 3: //11
		return 2;
	default:
		break;
	}
	return -128;
}

/**
 * Save level sensor of Salt tank to SAD variable
 * @return int [0:1]
 * 1 - if ACD changed
 * 0 - if ACD not changed
 */
//int s3_salt_tank_data_set(void) {
//	int pre_SAD = g_SAD;
//	g_SAD = s31_salt_tank_data_check();
//	if (pre_SAD != g_SAD)
//		return 1;
//	return 0;
//}

/**
 * Checked with hardware 31082022
 * Check level sensor of Acid tank and return result
 * @return int [-4:3]
 * -4, -3, -2, -1: NG
 * 0, 1, 2, 3: OK
 */
int s2_acid_tank_data_set(void) {
	union {
		struct {
			uint8_t bit0 :1;
			uint8_t bit1 :1;
			uint8_t bit2 :1;
		};
		uint8_t bit;
	} data;


	data.bit2 = FL3 == LEVEL_ON ? 1 : 0;
	data.bit1= FL2 == LEVEL_ON ? 1 : 0;
	data.bit0=FL1 == LEVEL_ON ? 1 : 0;

	//data.bit = 2^3 = 8bit
	//FL1.FL2.FL3 ---> bit2.bit1.bit0

	switch (data.bit) {
	case 0: //000
		return 0;
	case 1: //001
		return 1;
	case 2: //010
		return -4;
	case 3: //011
		return 2;
	case 4: //100
		return -2;
	case 5: //101
		return -1;
	case 6: //110
		return -3;
	case 7: //111
		return 3;
	}
	return -128;
}

/**
 * Save level sensor to ACD variable
 * @return int [0:1]
 * 1 - if ACD changed
 * 0 - if ACD not changed
 */
//int s2_acid_tank_data_set(void) {
//	int pre_ACD = g_ACD;
//	g_ACD = s21_acid_tank_data_check();
//	if (pre_ACD != g_ACD)
//		return 1;
//	return 0;
//}

/**
 * Checked with hardware 31082022
 * Check level sensor Alkali tank and return result
 * @return int [-4:3]
 * -4, -3, -2, -1: NG
 * 0, 1, 2, 3: OK
 */
int s1_alkali_tank_data_set(void) {

	union {
		struct {
			uint8_t bit0 :1;
			uint8_t bit1 :1;
			uint8_t bit2 :1;
		};
		uint8_t bit;
	} data;


	data.bit2=!FL6;
	data.bit1=!FL5;
	data.bit0=!FL4;

	//data.bit = 2^3 = 8bit
	//FL4.FL5.FL6 ---> bit2.bit1.bit0

	switch (data.bit) {
	case 0: //000
		g_ALD = 0;
		break;
	case 1: //001
		g_ALD = 1;
		break;
	case 2: //010
		g_ALD = -4;
		break;
	case 3: //011
		g_ALD = 2;
		break;
	case 4: //100
		g_ALD = -2;
		break;
	case 5: //101
		g_ALD = -1;
		break;
	case 6: //110
		g_ALD = -3;
		break;
	case 7: //111
		g_ALD = 3;
		break;
	}
	return g_ALD;
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
