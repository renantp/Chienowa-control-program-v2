/*
 * t_module.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_MODULE_T_MODULE_H_
#define CHIENOWA_MODULE_T_MODULE_H_

#include "../../r_cg_macrodriver.h"
int tp2_wash_mode_stop_process(void);
int tp111_initial_alkali_tank_drainage_stop_process(void);
int tp112_inital_acid_tank_drainage_stop_process(void);
int tp13_initial_electrolysis_stop_process(void);
int tp141_2nd_alkali_tank_drain_stop_process(void);
int tp142_2nd_acid_tank_drain_stop_process(void);
int tp15_electrolysis_stop_process(void);
int tp11_initial_draining_stop_process(void);
int tp12_inital_water_supply_stop_process(void);
int tp14_initial_2nd_draining_stop_process(void);
int tp1_stop_process_initial_working_mode_stop_process(void);

int t_sv1_stop(void);
int t_sv2_stop(void);
int t_sv5_stop_process(void);
int t_sv6_stop_process(void);
int t_p1_stop_process(void);
int t_p2_stop_process(void);
int t_sp_stop(void);

#endif /* CHIENOWA_MODULE_T_MODULE_H_ */
