/*
 * p_module.h
 *
 *  Created on: Jul 27, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_MODULE_P_MODULE_H_
#define CHIENOWA_MODULE_P_MODULE_H_

#include "../../r_cg_macrodriver.h"

/***********************************************************************************************************************
 Main operation
 ***********************************************************************************************************************/
int p1_initial_working_mode_start_process(void);
int p0_system_main_prpocess(void);
int p01_system_main_sub_system(void); //Do not need
int p11_startup_draining_water(void);
int p111_startup_drain_tank(void);
int p112_alkali_drain_stop(void);
int p113_acid_drain_stop(void);
int p114_alkali_drain_final_stop(void);
int p115_acid_drain_final_stop(void);
int p12_startup_water_supply(void);
int p13_startup_electrolysis_operation(void);
int p131_electrolysis_start(void);
int p132_initial_electrolysis_stop(void);
int p14_initial_2nd_draining_water(void);
int p15_2nd_electrolysis_water_generation_process(void);
int p151_2nd_electrolysis_start_process(void);
int p152_2nd_initial_electrolysis_stop_process(void);

int p2_water_discharge_mode(void);
int p21_alkali_water_discharge_mode(void);
int p22_acid_water_discharge_mode(void);
int p23_water_discharge_mode(void);
int p24_hand_wash_mode(void);
void p2411(void);
void p2412(void);
void p2413(void);
void p2421(void);
void p2422(void);
void p2423(void);
void p2431(void);
void p2432(void);
void p2433(void);


int p31_sv1_individual_process(void);
int p32_sv2_individual_process(void);
int p33_sv3_individual_process(void);
int p34_sv4_individual_process(void);
int p35_sv5_individual_process(void);
int p36_sv6_individual_process(void);
int p37_sv7_individual_process(void);
int p38_p1_individual_process(void);
int p39_p2_individual_process(void);
int p310_sp_individual_process(void);
int p311_electrolysis_equipment_process(void);
int p312_alarm_on_off_process(void);
int p_3_13_flow_rate_process(void);
int p314_salt_tank_drain_process(void);

int p8_stop_all_processing(void);
int p9_stop(void);

//int p_main(void);
//int p1_initial_startup_operation(void);
//int p11_startup_draining_water(void);
//int p111_startup_drain_alkali_tank_water(void);
//int p112_startup_drain_acid_tank_water(void);
//int p12_startup_water_supply(void);
//int p13_startup_electrolysis_operation(void);
//int p131_electrolysis_start(void);
//int p14_initial_2nd_draining_water(void);
//int p2_normal_operation(void);
//int p21_water_mode_select(void);
//int p211_alkaline_mode(void);
//int p212_acid_mode(void);
//int p213_water_mode(void);
//int p214_auto_hand_wash_mode(void);
//int p2141_alkali_water_start_hwm(void);
//int p2142_alkali_water_ON_hwm(void);
//int p2143_alkali_water_OFF_hwm(void);
//int p2144_acid_water_start_hwm(void);
//int p2145_acid_water_ON_hwm(void);
//int p2146_acid_water_OFF_hwm(void);
//int p2147_water_start_hwm(void);
//int p2148_water_ON_hwm(void);
//int p2149_water_OFF_hwm(void);
//
//int p151_electrolysis_start_process(void);
//
//void p22_electrolyzed_water_making(void);
//void p221_electrolysis_start(void);
//void p222_electrolysis_stop(void);
//void p3_individual_test_mode(void);
//void p31_SV1_open_close(void);
//void p32_SV2_open_close(void);
//void p33_SV3_open_close(void);
//void p34_SV4_open_close(void);
//void p35_SV5_open_close(void);
//void p36_SV6_open_close(void);
//void p37_SV7_open_close(void);
//void p38_P1_ON_OFF(void);
//void p39_P2_ON_OFF(void);
//void p310_SP_ON_OFF(void);
//void p311_electrolysis_start_stop(void);
//void p312_alarm_ON_OFF(void);
//void p313_flow_rate_adjustment(void);
//void p9_all_stop(void);

#endif /* CHIENOWA_MODULE_P_MODULE_H_ */
