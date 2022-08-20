/*
 * main.h
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_MAIN_H_
#define CHIENOWA_MAIN_H_

#include "../r_cg_macrodriver.h"
#include "pin_define.h"
#include "global_variable.h"
#include "delay.h"
#include "eeprom.h"
#include "adc.h"

#include "module/p_module.h"

/***********************************************************************************************************************
 Global variable struct
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Starting point
 ***********************************************************************************************************************/
void init(void);
void loop(void);

/***********************************************************************************************************************
 Status check
 ***********************************************************************************************************************/
//int8_t c1_alkali_tank_status(void);
//int8_t c2_acid_tank_status(void);
//int8_t c3_salt_water_tank_status(void);
//int8_t c4_available(void);
//int8_t c5_electrolysis_CVCC_status(void);
//int8_t c51_over_voltage_1_status(void);
//int8_t c52_over_voltage_2_status(void);
//int8_t c53_over_voltage_3_status(void);
//int8_t c54_low_voltage_status(void);
//int8_t c55_current_range_status(void);
//int8_t c56_over_current_check(void);
//int8_t c6_faucet_using_check(void);
//int8_t c7_ER_not_working_time_check(void);
//int8_t c8_flow_sensor_check(void);
//int8_t c9_neutralization_timer_check(void);
//int8_t c10_flow_sensor_check_for_leak_SV1_SV2(void);
//int8_t c11_leak_sensor_check(void);
//int8_t c12_filter_replace_check(void);
//int8_t c13_alkali_acid_tank_over_flow_check(void);
//int8_t c14_alkali_acid_tank_full_check(void);
//int8_t c15(void);

/***********************************************************************************************************************
 Error
 ***********************************************************************************************************************/
//void e1_faucet_refresh_alarm(void);
//void e11_faucet_refresh(void);
//void e2_available(void);
//void e3_water_leak_alarm(void);
//void e4_alkali_acid_tank_overflow_alarm(void);
//void e5_alkaline_tank_skip_alarm(void);
//void e6_acid_tank_skip_alarm(void);
//void e7_salt_water_tank_alarm(void);
//void e8_alkali_tank_empty_alarm(void);
//void e9_acid_tank_empty_alarm(void);
//void e10_salt_water_tank_alarm(void);
//void e11_alkali_acid_tank_full_log(void);
//void e12_alkali_tank_drain_alarm(void);
//void e13_acid_tank_drain_alarm(void);
//void e14_flow_sensor_alarm(void);
//void e15_current_range_20_over(void);
//void e16_current_range_10_over(void);

/***********************************************************************************************************************
 Common
 ***********************************************************************************************************************/
void k1(void);
void k2(void);
void k3(void);
void k4_salt_water_neutralization(void);
void k5(void);
void k6(void);
void k7_filter_replace(void);
void k8(void);
void k9(void);

/***********************************************************************************************************************
 Setting
 ***********************************************************************************************************************/
//void s1_alkali_acid_tank_setting(void);
//void s11_alkali_tank_data_set(void);
//void s111_alkali_tank_data_check(void);
//void s12_acid_tank_data_set(void);
//void s121_acid_tank_data_check(void);
//void s13_salt_tank_data_set(void);
//void s131_salt_tank_data_check(void);
//void s2_water_softer_data_check(void);
//void s3_water_softer_filter_replace_calculate(void);
//void s4(void);
//void s5(void);

/***********************************************************************************************************************
 B sector
 ***********************************************************************************************************************/
//void b1_initial_process_mode(void);
//void b11_startup_draining_water(void);
//void b12_startup_water_supply(void);
//void b13_startup_electrolysis_operation(void);
//void b131_electrolysis_start(void);
//void b14_startup_draining_water_2nd(void);
//void b2_normal_operation_mode(void);
//void b21_water_mode_select(void);
//void b211_alkali_water_ON(void);
//void b212_acid_water_ON(void);
//void b213_water_water_ON(void);
//void b214_auto_hand_wash_water_ON(void);
//void b2141_alkali_water_start_hwm(void);
//void b2142_alkali_water_ON_hwm(void);
//void b2143_alkali_water_OFF_hwm(void);
//void b2144_acid_water_start_hwm(void);
//void b2145_acid_water_ON_hwm(void);
//void b2146_acid_water_OFF_hwm(void);
//void b2147_water_start_hwm(void);
//void b2148_water_ON_hwm(void);
//void b2149_water_OFF_hwm(void);
//void b22_electrolyzed_water_making(void);
//void b221_electrolysis_start(void);
//void b222_electrolysis_stop(void);
//void b3_individual_mode(void);
//void b31_SV1_open_close_operation(void);
//void b32_SV2_open_close_operation(void);
//void b33_SV3_open_close_operation(void);
//void b34_SV4_open_close_operation(void);
//void b35_SV5_open_close_operation(void);
//void b36_SV6_open_close_operation(void);
//void b37_SV7_open_close_operation(void);
//void b38_P1_open_close_operation(void);
//void b39_P2_open_close_operation(void);
//void b310_SP_open_close_operation(void);
//void b311_electrolysis_start_stop_operation(void);
//void b312_alarm_on_off_operation(void);
//void b9_stop_operation(void);

/***********************************************************************************************************************
 T sector
 ***********************************************************************************************************************/
//void t1_initial_process_mode(void);
//void t11_startup_draining_water(void);
//void t12_startup_water_supply(void);
//void t13_startup_electrolysis_operation(void);
//void t131_electrolysis_start(void);
//void t14_startup_draining_water_2nd(void);
//void t2_normal_operation_mode(void);
//void t21_water_mode_select(void);
//void t211_alkaline_water_ON(void);
//void t212_acid_water_ON(void);
//void t213_water_ON(void);
//void t214_auto_hand_wash_water_ON(void);
//void t2141_alkali_water_start_hwm(void);
//void t2142_alkali_water_ON_hwm(void);
//void t2143_alkali_water_OFF_hwm(void);
//void t2144_acid_water_start_hwm(void);
//void t2145_acid_water_ON_hwm(void);
//void t2146_acid_water_OFF_hwm(void);
//void t2147_water_start_hwm(void);
//void t2148_water_ON_hwm(void);
//void t2149_water_OFF_hwm(void);
//void t22_electrolyzed_water_making(void);
//void t221_electrolysis_start(void);
//void t222_electrolysis_stop(void);
//void t3_individual_mode(void);
//void t31_SV1_open_close_operation(void);
//void t32_SV2_open_close_operation(void);
//void t33_SV3_open_close_operation(void);
//void t34_SV4_open_close_operation(void);
//void t35_SV5_open_close_operation(void);
//void t36_SV6_open_close_operation(void);
//void t37_SV7_open_close_operation(void);
//void t38_P1_open_close_operation(void);
//void t39_P2_open_close_operation(void);
//void t310_SP_open_close_operation(void);
//void t311_electrolysis_start_stop_operation(void);
//void t312_alarm_on_off_operation(void);
//void t9_stop_operation(void);

#endif /* CHIENOWA_MAIN_H_ */
