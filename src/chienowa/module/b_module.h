/*
 * b_module.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_MODULE_B_MODULE_H_
#define CHIENOWA_MODULE_B_MODULE_H_

#include "../../r_cg_macrodriver.h"

int b_inital_acid_tank_drainage_start_process(void);

int bp111_inital_alkali_tank_drainage_start_process(void);
int bp112_inital_acid_tank_drainage_start_process(void);
int bp112_p1_start_process(void);
int bp141_2nd_alkali_tank_drain_startup_process(void);
int bp142_2nd_acid_tank_drain_startup_process(void);
int bp11_initial_drainage_start_process(void);
int bp12_initial_water_supply_start_process(void);
int bp13_initial_electrolysis_start_process(void);
int bp14_initial_2nd_draining_start_process(void);
int bp15_electrolysis_start_process(void);
int bp1_initial_working_mode_start_process(void);
int bp2_wash_mode_start_process(void);
int bp211_alkali_mode_start_process(void);

int b_p1_start_process(void);
int b_p2_start_process(void);
int b_sp_start(void);
int b_sv1_start(void);
int b_sv2_start(void);
int b_sv5_start_process(void);
int b_sv6_start_process(void);
#endif /* CHIENOWA_MODULE_B_MODULE_H_ */
