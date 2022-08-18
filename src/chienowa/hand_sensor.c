/*
 * hand_sensor.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Renan
 */

#include "hand_sensor.h"
#include "pin_define.h"
#include "global_variable.h"
#include "delay.h"

#define DETECT_U() (I_HS_ODA_PIN == 1U ? 1:0)
#define DETECT_D() (I_HS_OCL_PIN == 1U ? 1:0)

uint32_t hs_start_time;
struct HAND_SENSOR_S g_hs;

void hand_sensor_light(enum HS_COLOR color){
	switch (color) {
		case HS_OFF:
			O_HS_ICL_PIN = 1U;
			O_HS_IDA_PIN = 1U;
			break;
		case BLUE:
			O_HS_ICL_PIN = 0U;
			O_HS_IDA_PIN = 0U;
			break;
		case RED:
			O_HS_ICL_PIN = 1U;
			O_HS_IDA_PIN = 0U;
			break;
		case WHITE:
			O_HS_ICL_PIN = 0U;
			O_HS_IDA_PIN = 1U;
			break;
		default:
			break;
	}
}
void hand_sensor_blink(enum HS_COLOR color, uint32_t period_ms){
	g_hs.color = color;
	g_hs.period = period_ms;
	switch (color) {
		case HS_OFF:
			hand_sensor_light(HS_OFF);
			g_hs.blink = 0U;
			break;
		default:
			g_hs.start = timer_start_ms();
			break;
	}
}
void hand_sensor_runtime(void){
	if(DETECT_U() && g_hs.pre_state == 0){
		g_hs.state = 1;
		g_hs.pre_state = 1;
	}else if(g_hs.state != g_hs.pre_state && !DETECT_U()){
		g_hs.pre_state = 0;
	}

	//Handle blink sequence
	if(g_hs.blink && elapsed_time_ms(g_hs.start) % g_hs.period == 0){
		if(g_hs.blink == 1){
			hand_sensor_light(g_hs.color);
		}else{
			hand_sensor_light(HS_OFF);
			g_hs.blink = 2;
		}
	}
}

int check_hand_sensor(void){
	if(g_hs.state){
		g_hs.state = 0;
		return 1;
	}
	return 0;
}


