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

int bp0_system_main_start(void);

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
int bp2_water_discharge_start_process(void);
int bp21_alkali_discharge_start(void);
int bp22_acid_discharge_start(void);
int bp23_water_discharge_start(void);
int bp24_hand_wash_start(void);
int bp241(void);
int bp242(void);
int bp243(void);
int bp314(void);

int bp3_individual_start(void);

int b_p1_start(void);
int b_p2_start(void);
int b_sp_start(void);
int b_sv1_start(void);
int b_sv2_start(void);
int b_sv3_start(void);
int b_sv4_start(void);
int b_sv5_start(void);
int b_sv6_start(void);
int b_sv7_start(void);

#endif /* CHIENOWA_MODULE_B_MODULE_H_ */
