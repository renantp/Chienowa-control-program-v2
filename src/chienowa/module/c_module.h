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
int c3_acid_tank_level_check(void);
int c5_electrolysis_CVCC_status(void);
int c19_salt_tank_drain_check(void);
int c11_electrolysis_status(void);

#endif /* CHIENOWA_MODULE_C_MODULE_H_ */
