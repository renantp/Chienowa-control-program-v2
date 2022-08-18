/*
 * delay.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Hung
 */
/* C++ detection */

#include "delay.h"
#include "runtime.h"

#define millis() 	(g_systemTick)
#define seconds()	(g_sec)
#define MAX_QUEUE_LEN (16)

volatile uint32_t g_systemTick = 0;
volatile uint32_t g_sec = 0;
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

//uint32_t calculate_timer_eslapse(uint8_t timer){
//	if(timer <= MAX_QUEUE_LEN){
//		if (millis() >= timer_queue.pakages[timer].start) {
//				return millis() - (timer_queue.pakages[timer].start);
//		} else {
//				return (0xffffffff - (timer_queue.pakages[timer].start)) + millis();
//		}
//	}
//	return 0;
//}
//sleep_time()
int wait(uint32_t ms){
	uint32_t stamp = g_systemTick;
	while(!ns_delay_ms(&stamp, ms)){
		runtime();
	}
	return 0;
}
void f(void){
	unsigned long start = timer_start_ms();
	//...do something take 5 second

	unsigned long working_time = timer_stop(start); // working_time will be 5s

	start = timer_restart_s(working_time); // start = current time - working time
	//..do something else 3s

	working_time = timer_stop(start);// working_time will be 8s
}
unsigned long timer_start_ms(void){
	return millis(); //Return currently milli-second
}
unsigned long elapsed_time_ms(unsigned long start_time){
	unsigned long elaps_time = 0;
	if(millis() >= start_time)
		elaps_time = millis() - start_time;	//return elapsed time
	else
		elaps_time = 0xffffffff - start_time + millis();
	return elaps_time;
}
unsigned long timer_restart(unsigned long elapsed_time){
	unsigned long reset_start_time;
	if(millis() >= elapsed_time)
		reset_start_time = millis() - elapsed_time;
	else{
		reset_start_time = 0xffffffff - (elapsed_time - millis());
	}
	return reset_start_time;
}
unsigned long timer_stop(unsigned long start_time){
	unsigned long elaps_time;
	if(millis() >= start_time)
		elaps_time = millis() - start_time;	//return elapsed time
	else
		elaps_time = 0xffffffff - start_time + millis();
	return elaps_time;
}

unsigned long timer_start_s(void){
	return seconds(); //Return currently second counter
}
unsigned long elapsed_time_s(unsigned long start_time){
	unsigned long elaps_time = 0;
	if(seconds() >= start_time)
		elaps_time = seconds() - start_time;	//return elapsed time
	else
		elaps_time = 0xffffffff - start_time + millis();
	return elaps_time;
}
unsigned long timer_restart_s(unsigned long elapsed_time){
	unsigned long reset_start_time;
	if(seconds() >= elapsed_time)
		reset_start_time = seconds() - elapsed_time;
	else{
		reset_start_time = 0xffffffff - (elapsed_time - seconds());
	}
	return reset_start_time;
}
unsigned long timer_stop_s(unsigned long start_time){
	unsigned long elaps_time;
	if(seconds() >= start_time)
		elaps_time = seconds() - start_time;	//return elapsed time
	else
		elaps_time = 0xffffffff - start_time + seconds();
	return elaps_time;
}
