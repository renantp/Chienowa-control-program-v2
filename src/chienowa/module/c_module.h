/*
 * c_module.h
 *
 *  Created on: Jul 29, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_MODULE_C_MODULE_H_
#define CHIENOWA_MODULE_C_MODULE_H_

#include "../../r_cg_macrodriver.h"

#define C1_ON	(1)
#define C1_OFF	(0)

int c1_on_off(uint8_t on_off);
int c_1_1(void);
int c2_alkali_tank_level_check(void);
int c3_acid_tank_level_check(void);
int c4_salt_tank_sensor_value_check_process(void);
int c5_electrolysis_check_process(void);
int c51_over_voltage_1_check(float *voltage);
int c52_over_voltage_2_check(float *voltage);
int c53_over_voltage_3_check(float *voltage);
int c531(void);
int c54(void);
int c55(void);
int c551(void);
int c552(void);
int c56(void);
int c6(void);
int c7(void);
int c8(void);
int c9(void);
int c_10(void);
int c_11(void);
int c_12(void);
int c_13(void);
int c_131(void);
int c_14(void);
int c_15(void);
int c_16(void);
int c_17(void);
int c_18(void);
int c_19(void);
int c_20(void);
int c_21(void);
int c_22(void);
int c_23(void);
int c_24(void);

#endif /* CHIENOWA_MODULE_C_MODULE_H_ */
