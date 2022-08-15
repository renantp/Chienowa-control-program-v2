/*
 * s_module.c
 *
 *  Created on: Jul 29, 2022
 *      Author: Renan
 */

#include "s_module.h"
#include "../pin_define.h"

int g_ALD, g_ACD, g_SAD;

//TODO: S5 - Filter change formula
int s5_filter_change_formula(void) {
	return -128;
}

//TODO: S4 - Water softener input data
int s4_water_softener_input_data(void) {

	return -128;
}

/**
 * Check level sensor Salt tank and return result
 * @return int [-1:2, -128]
 * -1: NG
 * 0, 1, 2: OK
 * -128: Crash
 */
int s31_salt_tank_data_check(void) {
	union {
		struct {
			uint8_t fl7 :1;
			uint8_t fl8 :1;
			uint8_t rsvd :6;
		};
		uint8_t raw;
	} data = { .fl7 = FL7 == LEVEL_ON ? 1U : 0U, .fl8 =
			FL8 == LEVEL_ON ? 1U : 0U, .rsvd = 0b000000 };
	switch (data.raw) {
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return -1;
	case 3:
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
int s3_salt_tank_data_set(void) {
	int pre_SAD = g_SAD;
	g_SAD = s31_salt_tank_data_check();
	if (pre_SAD != g_SAD)
		return 1;
	return 0;
}

/**
 * Check level sensor of Acid tank and return result
 * @return int [-4:3]
 * -4, -3, -2, -1: NG
 * 0, 1, 2, 3: OK
 */
int s21_acid_tank_data_check(void) {
	union {
		struct {
			uint8_t fl1 :1;
			uint8_t fl2 :1;
			uint8_t fl3 :1;
			uint8_t rsvd :5;
		};
		uint8_t raw;
	} data = { .fl1 = FL1 == LEVEL_ON ? 1U : 0U, .fl2 =
			FL2 == LEVEL_ON ? 1U : 0U, .fl3 = FL3 == LEVEL_ON ? 1U : 0U, .rsvd =
			0b00000 };
	switch (data.raw) {
	case 0: //0b0000 0000
		return 0;
	case 1: //0b0000 0001
		return 1;
	case 2: //0b0000 0010
		return -4;
	case 3: //0b0000 0011
		return 2;
	case 4: //0b0000 0100
		return -2;
	case 5: //0b0000 0101
		return -1;
	case 6: //0b0000 0110
		return -3;
	case 7: //0b0000 0111
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
int s2_acid_tank_data_set(void) {
	int pre_ACD = g_ACD;
	g_ACD = s21_acid_tank_data_check();
	if (pre_ACD != g_ACD)
		return 1;
	return 0;
}

/**
 * Check level sensor Alkali tank and return result
 * @return int [-4:3]
 * -4, -3, -2, -1: NG
 * 0, 1, 2, 3: OK
 */
int s11_alkali_tank_data_check(void) {
	union {
		struct {
			uint8_t fl4 :1;
			uint8_t fl5 :1;
			uint8_t fl6 :1;
			uint8_t rsvd :5;
		};
		uint8_t raw;
	} data = { .fl4 = FL4 == LEVEL_ON ? 1U : 0U, .fl5 =
			FL5 == LEVEL_ON ? 1U : 0U, .fl6 = FL6 == LEVEL_ON ? 1U : 0U, .rsvd =
			0b00000 };
	switch (data.raw) {
	case 0: //0b0000 0000
		return 0;
	case 1: //0b0000 0001
		return 1;
	case 2: //0b0000 0010
		return -4;
	case 3: //0b0000 0011
		return 2;
	case 4: //0b0000 0100
		return -2;
	case 5: //0b0000 0101
		return -1;
	case 6: //0b0000 0110
		return -3;
	case 7: //0b0000 0111
		return 3;
	}
	return -128;
}

/**
 * Save level sensor to ALD variable
 * @return int [0:1]
 * 1 - if ALD changed
 * 0 - if ALD not changed
 */
int s1_alkali_tank_data_set(void) {
	int pre_ALD = g_ALD;
	g_ALD = s11_alkali_tank_data_check();
	if (pre_ALD != g_ALD)
		return 1;
	return 0;
}
