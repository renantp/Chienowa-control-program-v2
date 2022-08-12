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

volatile uint32_t g_systemTick = 0;

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
//sleep_time()
int wait(uint32_t ms){
	uint32_t stamp = g_systemTick;
	while(!ns_delay_ms(&stamp, ms)){
		runtime();
	}
	return 0;
}
