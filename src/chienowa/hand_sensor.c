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
#include "module/b_module.h"
#include "module/t_module.h"

#define SOFT_TIMEOUT_MS		(500U)

uint32_t hs_start_time;
struct HAND_SENSOR_S g_hs;

uint32_t reset_hs_timeout;
struct {
	uint8_t ocl_intc8;
	uint8_t oda_intc9;
}hs_input, hs_last_input;
//hs_input.ocl = I_HS_OCL_PIN; //Detected, HiGH. Not detected, low
//hs_input.oda = I_HS_ODA_PIN; //Not detected, LOW, Detected high
void hs_oda_intc_callback(void){
	hs_input.oda_intc9++;
}
void hs_ocl_intc_callback(void){
	hs_input.ocl_intc8++;
}

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
	if(period_ms == 0) g_hs.blink = 0; else g_hs.blink = 1;
	switch (color) {
		case HS_OFF:
			g_hs.blink = 0;
			hand_sensor_light(HS_OFF);
			break;
		default:
			hand_sensor_light(color);
			break;
	}
}



void hand_sensor_runtime(void){
	//Handle blink sequence
	if(g_hs.blink != 0 && elapsed_time_ms(g_hs.start) >= g_hs.period){
		if(g_hs.blink == 1){
			hand_sensor_light(g_hs.color);
			g_hs.blink = 2;
		}else{
			hand_sensor_light(HS_OFF);
			g_hs.blink = 1;
		}
		g_hs.start = timer_start_ms();
	}else{
		reset_hs_timeout++;
	}
}

int check_hand_sensor(void){
	if(hs_input.ocl_intc8 != hs_last_input.ocl_intc8){
		hs_last_input.ocl_intc8 = hs_input.ocl_intc8;
//		 switch (hs_input.ocl_intc8 % 7) {
//			case 0:
//				t_b_led_l();
//				break;
//			case 1:
//				b_b_led_l();
//				break;
//			case 2:
//				b_b_led_b();
//				break;
//			case 3:
//				b_r_led_l();
//				break;
//			case 4:
//				b_r_led_b();
//				break;
//			case 5:
//				b_w_led_l();
//				break;
//			case 6:
//				b_w_led_b();
//				break;
//			default:
//				break;
//		}
		return 1;
	}
	return 0;
}


