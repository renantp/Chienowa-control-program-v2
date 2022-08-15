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

#define C_1_ON_T3			(0)
#define FAUCET_OFF_T		(1)
#define WATER_DISCHARGE_T	(2)
#define ACID_DISCHARGE_T	(3)
#define ALKALI_DISCHARGE_T	(4)

extern volatile uint32_t g_systemTick;
int ns_delay_ms(uint32_t *stamp, uint32_t ms);
int wait(uint32_t ms);
uint32_t calculate_timer_eslapse(uint8_t timer);
int start_timer(uint32_t *const counter, uint8_t timer);
int stop_timer(uint8_t timer);

#ifdef __cplusplus
}
#endif
#endif /* CHIENOWA_DELAY_H_ */
