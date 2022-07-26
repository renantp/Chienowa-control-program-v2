/*
 * delay.h
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_DELAY_H_
#define CHIENOWA_DELAY_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "../r_cg_macrodriver.h"

extern volatile uint32_t g_systemTick;
extern volatile uint32_t g_sec;
extern uint32_t g_us;

int ns_delay_ms(uint32_t *stamp, uint32_t ms);
int wait(uint32_t ms);
unsigned long timer_start_ms(void);
unsigned long elapsed_time_ms(unsigned long start_time);
unsigned long timer_restart_ms(unsigned long* elapsed_time);
unsigned long timer_stop_ms(unsigned long start_time);

unsigned long timer_start_s(void);
unsigned long elapsed_time_s(unsigned long start_time);
unsigned long timer_restart_s(unsigned long elapsed_time);
unsigned long timer_stop_s(unsigned long start_time);

unsigned long timer_restart_us(unsigned long* elapsed_time);
#ifdef __cplusplus
}
#endif
#endif /* CHIENOWA_DELAY_H_ */
