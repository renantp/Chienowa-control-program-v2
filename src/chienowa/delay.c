/*
 * delay.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Hung
 */
/* C++ detection */

#include "delay.h"

volatile uint32_t g_systemTick = 0;

int ns_delay_ms(uint32_t *stamp, uint32_t ms) {
	if (g_systemTick >= *stamp) {
		if (g_systemTick - (*stamp) < ms)
			return 0;
	} else {
		if (g_systemTick < ms - (0xffffffff - (*stamp)))
			return 0;
	}
	*stamp = g_systemTick;
	return 1;
}

