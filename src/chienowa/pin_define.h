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

#define SV1_PIN		(P1_bit.no7)
#define SV2_PIN		(P5_bit.no5)
#define SV3_PIN		(P7_bit.no6)
#define SV4_PIN		(P7_bit.no7)
#define SV5_PIN		(P6_bit.no7)
#define SV6_PIN		(P6_bit.no6)
#define SV7_PIN		(P6_bit.no5)
#define PUMP_1_PIN	(P6_bit.no2)
#define PUMP_2_PIN	(P6_bit.no1)
#define SP_PIN		(P6_bit.no0)

#define FL1		(P7_bit.no1)
#define FL2		(P7_bit.no2)
#define FL3		(P7_bit.no3)
#define FL4		(P0_bit.no5)
#define FL5		(P0_bit.no6)
#define FL6		(P7_bit.no0)
#define FL7		(P5_bit.no4)
#define FL8		(P3_bit.no3)

extern union FLAG_U {
	struct {
		uint8_t sv1 : 1;
		uint8_t sv2 : 1;
		uint8_t sv3 : 1;
		uint8_t sv4 : 1;
		uint8_t sv5 : 1;
		uint8_t sv6 : 1;
		uint8_t sv7 : 1;

		uint8_t pump_1 : 1;
		uint8_t pump_2 : 1;
		uint8_t salt_pump : 1;

		uint8_t p111 : 1;
		uint8_t p112 : 1;
	};
	uint8_t raw[10];
}flag;

#endif /* CHIENOWA_PIN_DEFINE_H_ */
