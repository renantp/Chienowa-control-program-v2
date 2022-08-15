/*
 * delay.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Hung
 */
/* C++ detection */

#include "delay.h"
#include "runtime.h"

#define millis() (g_systemTick)
#define MAX_QUEUE_LEN (16)

volatile uint32_t g_systemTick = 0;

struct{
	struct Timer_pakage{
		uint32_t *p;
		uint32_t start;
		uint8_t running;
	}pakages[MAX_QUEUE_LEN];
}timer_queue;
int ns_delay_ms(uint32_t *stamp, uint32_t ms) {
	if (millis() >= *stamp) {
		if (millis() - (*stamp) < ms)
			return 0;
	} else {
		if (millis() < ms - (0xffffffff - (*stamp)))
			return 0;
	}
	*stamp = g_systemTick;
	return 1;
}

uint32_t calculate_timer_eslapse(uint8_t timer){
	if(timer <= MAX_QUEUE_LEN){
		if (millis() >= timer_queue.pakages[timer].start) {
				return millis() - (timer_queue.pakages[timer].start);
		} else {
				return (0xffffffff - (timer_queue.pakages[timer].start)) + millis();
		}
	}
	return 0;
}
//sleep_time()
int wait(uint32_t ms){
	uint32_t stamp = g_systemTick;
	while(!ns_delay_ms(&stamp, ms)){
		runtime();
	}
	return 0;
}

int start_timer(uint32_t *const counter, uint8_t timer){
	if(timer <= MAX_QUEUE_LEN && !timer_queue.pakages[timer].running){
		timer_queue.pakages[timer].p = counter;
		timer_queue.pakages[timer].start = g_systemTick;
		timer_queue.pakages[timer].running = 1U;
		return 1;
	}
	return 0;
}

int stop_timer(uint8_t timer){
	if(timer <= MAX_QUEUE_LEN && timer_queue.pakages[timer].running){
		(*timer_queue.pakages[timer].p) += calculate_timer_eslapse(timer);
		return 1;
	}
	return 0;
}

