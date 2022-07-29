/*
 * p_module.h
 *
 *  Created on: Jul 27, 2022
 *      Author: Hung
 */

#ifndef CHIENOWA_MODULE_P_MODULE_H_
#define CHIENOWA_MODULE_P_MODULE_H_

#include "../../r_cg_macrodriver.h"

/***********************************************************************************************************************
 Main operation
 ***********************************************************************************************************************/
void p_main(void);
void p1_initial_startup_operation(void);
void p11_startup_draining_water(void);
void p111_startup_drain_alkali_tank_water(void);
void p112_startup_drain_alkalin_tank_water(void);
void p12_startup_water_supply(void);
void p13_startup_electrolysis_operation(void);
void p131_electrolysis_start(void);
void p14_startup_drain_water_2(void);
void p2_normal_operation(void);
void p21_water_mode_select(void);
void p211_alkaline_mode(void);
void p212_acid_mode(void);
void p213_water_mode(void);
void p214_auto_hand_wash_mode(void);
void p2141_alkali_water_start_hwm(void);
void p2142_alkali_water_ON_hwm(void);
void p2143_alkali_water_OFF_hwm(void);
void p2144_acid_water_start_hwm(void);
void p2145_acid_water_ON_hwm(void);
void p2146_acid_water_OFF_hwm(void);
void p2147_water_start_hwm(void);
void p2148_water_ON_hwm(void);
void p2149_water_OFF_hwm(void);

int p151_electrolysis_start_process(void);

void p22_electrolyzed_water_making(void);
void p221_electrolysis_start(void);
void p222_electrolysis_stop(void);
void p3_individual_test_mode(void);
void p31_SV1_open_close(void);
void p32_SV2_open_close(void);
void p33_SV3_open_close(void);
void p34_SV4_open_close(void);
void p35_SV5_open_close(void);
void p36_SV6_open_close(void);
void p37_SV7_open_close(void);
void p38_P1_ON_OFF(void);
void p39_P2_ON_OFF(void);
void p310_SP_ON_OFF(void);
void p311_electrolysis_start_stop(void);
void p312_alarm_ON_OFF(void);
void p313_flow_rate_adjustment(void);
void p9_all_stop(void);

#endif /* CHIENOWA_MODULE_P_MODULE_H_ */
