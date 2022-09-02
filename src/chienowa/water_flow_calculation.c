/*
 * water_flow_calculation.c
 *
 *  Created on: Sep 2, 2022
 *      Author: Renan
 */
#include "water_flow_calculation.h"
#include "delay.h"
#include "global_variable.h"
#include "pin_define.h"

#define MAX_LENGHT  10
#define CALIB_VALUE_10HZ 1.34f
#define CALIB_VALUE_100HZ 1.45f
#define CALIB_VALUE_1KHZ 1.49f
#define FLOW_PULSE_TIMEOUT_MS	200UL

typedef struct{
    unsigned long buff[MAX_LENGHT];
    unsigned char buff_index;
}Circle_buffer;
Circle_buffer flow_buff = {
    .buff[0] = 10,
    .buff[1] = 10,
    .buff[2] = 10,
    .buff[3] = 50,
    .buff[4] = 10,
    .buff[5] = 52,
    .buff[6] = 50,
    .buff[7] = 50,
    .buff[8] = 50,
    .buff[9] = 99,
    .buff_index = 2
};
unsigned long flow_timer;
uint32_t flow_pluse;
uint8_t new_flow_pluse = 0;
uint32_t flow_timeout;
uint32_t flow_timeout_count;
void add_flow_elapse_time(Circle_buffer *data, unsigned long input);
float calculate_flow(Circle_buffer *data);

void flow_pluse_callback(void){
	flow_pluse++;
	unsigned long timer_result = timer_restart_us(&flow_timer);
	add_flow_elapse_time(&flow_buff, timer_result);
	new_flow_pluse = 1;
}
void water_flow_runtime(void){
	if(new_flow_pluse){
		new_flow_pluse = 0;
		g.flow_rate = calculate_flow(&flow_buff);
		flow_timeout = timer_start_ms();
		flow_timeout_count = flow_timeout_count > 0 ? --flow_timeout_count: flow_timeout_count;
	}else{
		if(elapsed_time_ms(flow_timeout) > FLOW_PULSE_TIMEOUT_MS){
			if (flow_timeout_count <= 5){
				++flow_timeout_count;
			}
			flow_timeout = timer_start_ms();
			add_flow_elapse_time(&flow_buff, 1000UL * flow_timeout_count * 1000UL);
			g.flow_rate = calculate_flow(&flow_buff);
		}
	}
}
void add_flow_elapse_time(Circle_buffer *data, unsigned long input){
    data->buff[data->buff_index] = input;
    data->buff_index++;
    if(data->buff_index == MAX_LENGHT){ data->buff_index = 0; }
}
float flow_result;
unsigned long time_sum;
float time_avg, pulse_avg;
float calculate_flow(Circle_buffer *data){
	time_sum = 0;
	unsigned char sum_index = data->buff_index;
	for(int i = 0; i < MAX_LENGHT; i++){
		unsigned char last_index = sum_index;
		if (sum_index > 0) sum_index--;
		else sum_index = MAX_LENGHT - 1;
		if(data->buff[last_index] >= data->buff[sum_index] &&
				data->buff[last_index] - data->buff[sum_index] > 2000UL*1000){
			continue;
		}else if(data->buff[last_index] < data->buff[sum_index] &&
				data->buff[sum_index] - data->buff[last_index] > 2000UL*1000){
			continue;
		}
		time_sum += data->buff[sum_index];
	}
	if(flow_timeout_count >= 5){
		flow_result = 0.0f;
		return flow_result;
	}
	time_avg = time_sum / MAX_LENGHT;
	if (time_avg < 10UL * 1000UL){
		time_avg = time_avg * CALIB_VALUE_100HZ;
	}else if(time_avg < 100UL * 1000UL){
		time_avg = time_avg * CALIB_VALUE_10HZ;
	}
	pulse_avg = (1000UL * 1000UL) / time_avg;
	flow_result = pulse_avg  * .7f * 60 / 1000UL;
	return flow_result;
}
