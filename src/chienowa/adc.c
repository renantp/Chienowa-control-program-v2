/*
 * adc.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 */

#include "adc.h"
#include "../r_cg_adc.h"

struct ADC_Struct g_adc;
void adc_interupt_handle(void) {
	switch (ADS) {
	case _00_AD_INPUT_CHANNEL_0:
		R_ADC_Get_Result(&g_adc.ani0);
		g_adc.current = ((float) g_adc.ani0 / 1024) * MAX_VOLTAGE;
		ADS = _01_AD_INPUT_CHANNEL_1;
		break;
	case _01_AD_INPUT_CHANNEL_1:
		R_ADC_Get_Result(&g_adc.ani1);
		g_adc.voltage = ((float) g_adc.ani1 / 1024) * MAX_VOLTAGE;
		ADS = _00_AD_INPUT_CHANNEL_0;
		break;
	default:
		break;
	}
	R_ADC_Start();
}

