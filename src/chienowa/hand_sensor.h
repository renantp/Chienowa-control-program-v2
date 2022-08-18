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
	enum HS_COLOR color;

	uint8_t state, pre_state;
}g_hs;
void hand_sensor_blink(enum HS_COLOR color, uint32_t duration);
void hand_sensor_light(enum HS_COLOR color);
int check_hand_sensor(void);
void hand_sensor_runtime(void);

#endif /* CHIENOWA_HAND_SENSOR_H_ */
