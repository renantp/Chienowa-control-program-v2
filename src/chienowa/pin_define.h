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

#define SV1_PIN			(P1_bit.no7)
#define SV2_PIN			(P5_bit.no5)
#define SV3_PIN			(P7_bit.no6)
#define SV4_PIN			(P7_bit.no7)
#define SV5_PIN			(P6_bit.no7)
#define SV6_PIN			(P6_bit.no6)
#define SV7_PIN			(P6_bit.no5)
#define PUMP_1_PIN		(P6_bit.no2)
#define PUMP_2_PIN		(P6_bit.no1)
#define SP_PIN			(P6_bit.no0)

#define SW1_PIN			(P5_bit.no2)
#define SW2_PIN			(P14_bit.no7)
#define SW3_PIN			(P10_bit.no0)

#define CVCC_CONTROL_PIN	(P14_bit.no2)
#define CVCC_ALARM_OUT_PIN	(P0_bit.no4)

#define FL1		(P7_bit.no1)
#define FL2		(P7_bit.no2)
#define FL3		(P7_bit.no3)
#define FL4		(P0_bit.no5)
#define FL5		(P0_bit.no6)
#define FL6		(P7_bit.no0)
#define FL7		(P5_bit.no4)
#define FL8		(P5_bit.no3)

#define O_HS_IDA_PIN	(P1_bit.no5)
#define O_HS_ICL_PIN	(P1_bit.no6)
#define I_HS_OCL_PIN	(P7_bit.no4)
#define I_HS_ODA_PIN	(P7_bit.no5)

#endif /* CHIENOWA_PIN_DEFINE_H_ */
