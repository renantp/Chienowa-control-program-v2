/*
 * main.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 */

#include "main.h"
#include "../r_cg_serial.h"

eeprom_config e_config = { .csi_flag = &g_csi01_flag, .csi_send_receive =
		R_CSI01_Send_Receive };
uint32_t tick;
struct Number_Setting_s{
	float upperVoltage1;
	float upperVoltage2;
	float upperVoltage3;
	float lowerVoltage;
	float upperCurrent;
	float lowerCurrent;
	float upperFlow;
	float lowerFlow;
	float cvccCurrent;
	float saltPumpVoltage;
	char crc;
}g_numberSetting, clone;
struct Timer_Setting_s{
	uint32_t t1_initialWaterDrainageOperation_s;
	uint32_t t2_flowSensorStartTime_s;
	uint32_t t3_flowSensorMonitorTime_s;
	uint32_t t4_electrolysisOperationStart_s;
	uint32_t t5_electrolysisStopDelay_s;
	uint32_t t6_drainageOffTime_h;
	uint32_t t7_powerOnPreparation_s;
	uint32_t t8_flowRateAdjustmentRelease_s;
	uint32_t t9_currentAdjustmentRelease_s;
	uint32_t t10_electrolysisCurrentAlarmSpecified_s;
	uint32_t t11_overVoltage1Time_s;
	uint32_t t12_overVoltage2Time_s;
	uint32_t t13_overVoltage3Time_s;
	uint32_t t14_lowVoltageStartTime_s;
	uint32_t t15_lowVoltageDelayTime_s;
	uint32_t t16_currentMonitoringStart_s;
	uint32_t t17_solenoidLeakageStartTime_s;
	uint32_t t18_fullSaltWaterMonitoringStart_h;
	uint32_t t19_waterFilterAlarm_h;
	uint32_t t20_waterFilterAlarmIgnore_h;
	uint32_t t21_onDelayEmptyLevel_s;
	uint32_t t22_onDelayLowLevel_s;
	uint32_t t23_onDelayHighLevel_s;
	uint32_t t24_offDelayEmptyLevel_s;
	uint32_t t25_saltLowLevelDelay_s;
	uint32_t t26_saltHighLevelDelay_s;
	uint32_t t27_neutralizationStartTime_h;
	uint32_t t28_neutralizationOpenTime_s;
	uint32_t t29_alkalineWaterSpoutingTime_s;
	uint32_t t30_acidWaterSpoutingTime_s;
	uint32_t t31_washingWaterSpoutingTime_s;
	uint32_t t32_overLapTime_ms;
	uint32_t t33_waterDischargeDelay_s;
	uint32_t t34_acidWaterDownTime_s;
	uint32_t t35_alkalineWaterDownTime_s;
	uint32_t t36;
	uint32_t t37;
	uint32_t t38_washDischargeDelay_s;
	uint32_t t39_cleaningIntervalTime_h;
	uint32_t t40_washSpoutingTime_s;
	char crc;
}g_timerSetting;
const uint8_t timeSettingSize = sizeof(struct Timer_Setting_s) - 1;
uint8_t my_data[40], read_data[40];
uint8_t eeprom_count, eeprom_working;
//union Cast {
//	struct Number_Setting_s a;
//	uint8_t cast[41];
//}caster;
void init(void) {
	R_UART2_Receive(circular_buffer_calloc(&g_rx_data, 1), 6);

	for(uint8_t i = 0; i < 40; i++){
		my_data[i] = i;
	}

	if (eeprom_init(&e_config) == 0){
		eeprom_set_block(NONE_BLOCK);
//		eeprom_read((uint8_t*)&g_timerSetting, 0x0800, timeSettingSize);
//		eeprom_write((uint8_t *)my_data, 0x0800 + timeSettingSize, sizeof(my_data));
//		eeprom_read((uint8_t *)read_data, 0x0800 + timeSettingSize, sizeof(read_data));
//		clone.crc = 100;
//		eeprom_write((uint8_t *)&clone, 0x0000, 41);
		eeprom_read((uint8_t *)&g_numberSetting, 0x0000, 41);
//		caster.a = g_numberSetting;
	}

	while(eeprom_runtime());

}

const uint8_t max = 40;
uint16_t sended, checked;
void loop(void) {
	if (ns_delay_ms(&tick, 10*1000)) {
		g_count++;
		if(g_count % 2){
			if(sended == 0){
				checked = 0;
			}else{

			}
			my_data[0]++;
			my_data[max/2]++;
			my_data[max - 1]++;
			eeprom_write((uint8_t *)my_data, 0x0800 + timeSettingSize, max);
//			eeprom_set_block(BLOCK_ALL);
//			eeprom_write((uint8_t *)my_data, 0x0800 + timeSettingSize, max);
		}else {
			sended++;
			eeprom_read((uint8_t *)read_data, 0x0800 + timeSettingSize, 40);
//			eeprom_set_block(NONE_BLOCK);
		}
	}
	if(eeprom_runtime() == 1 && eeprom_working == 0){
		eeprom_working = 1;
	}else if(eeprom_working == 1 && eeprom_runtime() == 0){
		if(my_data[0] == read_data[0] &&
				my_data[max/2] == read_data[max/2] &&
				my_data[max - 1] == read_data[max - 1]){

			sended = sended > 0 ? sended - 1: sended;
		}
		eeprom_working = 0;
	}
}
