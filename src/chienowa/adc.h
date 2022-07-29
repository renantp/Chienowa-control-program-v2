/*
 * adc.h
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_ADC_H_
#define CHIENOWA_ADC_H_

#include "../r_cg_macrodriver.h"

#define MAX_VOLTAGE (5.0)

extern struct ADC_Struct {
	uint16_t ani0;
	uint16_t ani1;

	float current;
	float voltage;
} g_adc;

void adc_interupt_handle(void);

#endif /* CHIENOWA_ADC_H_ */
