/*
 * b_module.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_MODULE_B_MODULE_H_
#define CHIENOWA_MODULE_B_MODULE_H_

#include "../../r_cg_macrodriver.h"

int bp0_system_main_start(void);

int bp111_inital_alkali_tank_drainage_start_process(void);
int bp112_inital_acid_tank_drainage_start_process(void);
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
int bc1(void);
int bc2(void);
int bc3(void);
int bc4(void);
int bc5(void);
int bc51(void);
int bc52(void);
int bc53(void);
int bc531(void);
int bc54(void);
int bc55(void);
int bc56(void);
int bc6(void);
int bc7(void);
int bc8(void);
int bc9(void);
int bc_10(void);
int bc_11(void);
int bc_12(void);
int bc_13(void);
int bc_14(void);
int bc_15(void);
int bc_16(void);
int bc_17(void);
int bc_18(void);
int bc_19(void);
int bc_23(void);
int be1(void);
int b_b_led_l(void);
int b_b_led_b(void);
int b_r_led_l(void);
int b_r_led_b(void);
int b_w_led_l(void);
int b_w_led_b(void);

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
int bc1(void);

int be11(void);
#endif /* CHIENOWA_MODULE_B_MODULE_H_ */
