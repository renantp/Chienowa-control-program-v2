/*
 * indivitual_mode.h
 *
 *  Created on: Sep 11, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_INDIVIDUAL_MODE_H_
#define CHIENOWA_INDIVIDUAL_MODE_H_

#include "../r_cg_macrodriver.h"
#include "global_variable.h"

extern struct IO_Struct io_buffer;

void individual_runtime(void);
void getIOData(uint8_t *p);
void outputIO(struct IO_Struct *io);
void resetIO(void);

#endif /* CHIENOWA_INDIVIDUAL_MODE_H_ */
