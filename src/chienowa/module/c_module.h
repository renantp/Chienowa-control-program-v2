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
int c11(void);
int c2_alkali_tank_level_check(void);
int c3_acid_tank_level_check(void);
int c4_salt_tank_sensor_value_check_process(void);
int c5_electrolysis_check_process(void);
int c51_over_voltage_1_check(float *voltage);
int c52_over_voltage_2_check(float *voltage);
int c53_over_voltage_3_check(float *voltage);
int c531(void);
int c19_salt_tank_drain_check(void);

#endif /* CHIENOWA_MODULE_C_MODULE_H_ */
