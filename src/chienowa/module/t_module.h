/*
 * t_module.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_MODULE_T_MODULE_H_
#define CHIENOWA_MODULE_T_MODULE_H_

#include "../../r_cg_macrodriver.h"

int tp0(void);
int tp1_stop_process_initial_working_mode_stop_process(void);
int tp11_initial_draining_stop_process(void);
int tp111_initial_alkali_tank_drainage_stop_process(void);
int tp112_inital_acid_tank_drainage_stop_process(void);
int tp12_inital_water_supply_stop_process(void);
int tp13_initial_electrolysis_stop_process(void);
int tp14_initial_2nd_draining_stop_process(void);
int tp141_2nd_alkali_tank_drain_stop_process(void);
int tp142_2nd_acid_tank_drain_stop_process(void);
int tp15_electrolysis_stop_process(void);
int tp2_wash_mode_stop_process(void);
int tp21_alkali_discharge_stop(void);
int tp22_acid_discharge_stop(void);
int tp23_water_discharge_stop(void);
int tp24_hand_wash_stop(void);
int tp241(void);
int tp242(void);
int tp243(void);
int tp3_individual_stop(void);

int t_sv1_stop(void);
int t_sv2_stop(void);
int t_sv3_stop(void);
int t_sv4_stop(void);
int t_sv5_stop(void);
int t_sv6_stop(void);
int t_sv7_stop(void);
int t_p1_stop(void);
int t_p2_stop(void);
int t_sp_stop(void);

int tp314(void);
int tp8(void);
int tc1(void);
int tc2(void);
int tc3(void);
int tc4(void);
int tc5(void);
int tc51(void);
int tc52(void);
int tc53(void);
int tc531(void);
int tc54(void);
int tc55(void);
int tc56(void);
int tc6(void);
int tc7(void);
int tc8(void);
int tc9(void);
int tc10(void);
int tc11(void);
int tc12(void);
int tc13(void);
int tc14(void);
int tc15(void);
int tc16(void);
int tc17(void);
int tc18(void);
int tc19(void);
int tc_23(void);

int te1(void);
int t_b_led_l(void);
int t_b_led_b(void);
int t_r_led_l(void);
int t_r_led_b(void);
int t_r_led_l(void);
int t_w_led_b(void);
int t_w_led_b(void);
int te11(void);
#endif /* CHIENOWA_MODULE_T_MODULE_H_ */
