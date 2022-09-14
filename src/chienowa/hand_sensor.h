/*
 * hand_sensor.h
 *
 *  Created on: Aug 12, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_HAND_SENSOR_H_
#define CHIENOWA_HAND_SENSOR_H_

#include "../r_cg_macrodriver.h"

enum HS_COLOR{
	HS_OFF,
	BLUE,
	RED,
	GREEN,
	WHITE
};
extern struct HAND_SENSOR_S {
	uint8_t blink;
	uint32_t start;
	uint32_t period;
	uint8_t on, off;
	enum HS_COLOR color;

	uint8_t state, pre_state;
}g_hs;
void hand_sensor_blink(enum HS_COLOR color, uint32_t duration);
int check_hand_sensor(void);
void hand_sensor_runtime(void);
void hs_reset(void);

void hs_oda_intc_callback(void);
void hs_ocl_intc_callback(void);
#endif /* CHIENOWA_HAND_SENSOR_H_ */
