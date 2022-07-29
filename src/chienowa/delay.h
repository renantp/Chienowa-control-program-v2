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
int ns_delay_ms(uint32_t *stamp, uint32_t ms);

#ifdef __cplusplus
}
#endif
#endif /* CHIENOWA_DELAY_H_ */
