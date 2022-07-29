/*
 * pin_define.h
 *
 *  Created on: Jul 27, 2022
 *      Author: Hung
 */

#ifndef CHIENOWA_PIN_DEFINE_H_
#define CHIENOWA_PIN_DEFINE_H_

#include "../r_cg_macrodriver.h"

#define VALVE_ON	(1U)
#define VALVE_OFF	(0U)
#define PUMP_ON		(0U)
#define PUMP_OFF	(1U)
#define LEVEL_ON	(0U)
#define LEVEL_OFF	(1U)

#define SV1		(P1_bit.no7)
#define SV2		(P5_bit.no5)
#define SP		(P6_bit.no0)

#define FL1		(P7_bit.no1)
#define FL2		(P7_bit.no2)
#define FL3		(P7_bit.no3)
#define FL4		(P0_bit.no5)
#define FL5		(P0_bit.no6)
#define FL6		(P7_bit.no0)
#define FL7		(P5_bit.no4)
#define FL8		(P3_bit.no3)

#endif /* CHIENOWA_PIN_DEFINE_H_ */
