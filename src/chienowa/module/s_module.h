/*
 * s_module.h
 *
 *  Created on: Jul 29, 2022
 *      Author: Hung
 */

#ifndef CHIENOWA_MODULE_S_MODULE_H_
#define CHIENOWA_MODULE_S_MODULE_H_

#include "../../r_cg_macrodriver.h"

extern int g_ALD, g_ACD, g_SAD;

int s1_alkali_tank_data_set(void);
int s11_alkali_tank_data_check(void);
int s2_acid_tank_data_set(void);
int s21_acid_tank_data_check(void);
int s3_salt_tank_data_set(void);
int s31_salt_tank_data_check(void);

#endif /* CHIENOWA_MODULE_S_MODULE_H_ */
