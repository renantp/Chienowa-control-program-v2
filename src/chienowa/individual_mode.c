/*
 * individual_mode.c
 *
 *  Created on: Sep 11, 2022
 *      Author: Renan
 */

#include "individual_mode.h"
#include "pin_define.h"
#include "global_variable.h"

struct IO_Struct io_buffer;
void outputIO(struct IO_Struct *io);
uint8_t init_individual = 0;
/**
 * Individual runtime will check the io_buffer and change the output
 */
void individual_runtime(void){
	if(SYSTEM_MODE == INDIVIDUAL && !init_individual){
		g.io = io_buffer;
		outputIO(&g.io);
		init_individual = 1;
	}
}
union BitOfByte{
	struct{
		uint8_t no1: 1;
		uint8_t no2: 1;
		uint8_t no3: 1;
		uint8_t no4: 1;
		uint8_t no5: 1;
		uint8_t no6: 1;
		uint8_t no7: 1;
		uint8_t no8: 1;
	};
	uint8_t data;
};
void getIOData(uint8_t *p){
	union BitOfByte data0, data1;
	data0.data = p[3];
	data1.data = p[5];
	io_buffer.valve.sv1 = data0.no1;
	io_buffer.valve.sv2 = data0.no2;
	io_buffer.valve.sv3 = data0.no3;
	io_buffer.valve.sv4 = data0.no4;
	io_buffer.valve.sv5 = data0.no5;
	io_buffer.valve.sv6 = data0.no6;
	io_buffer.valve.sv7 = data0.no7;
	io_buffer.valve.sv8 = data0.no8;

	io_buffer.pump_1 = data1.no1;
	io_buffer.pump_2 = data1.no2;
	io_buffer.salt_pump = data1.no3;
	io_buffer.cvcc_control = data1.no4;
}
void outputIO(struct IO_Struct *io){
	SV1_PIN = io->valve.sv1;
	SV2_PIN = io->valve.sv2;
	SV3_PIN = io->valve.sv3;
	SV4_PIN = io->valve.sv4;
	SV5_PIN = io->valve.sv5;
	SV6_PIN = io->valve.sv6;
	SV7_PIN = io->valve.sv7;

	PUMP_1_PIN = !io->pump_1;
	PUMP_2_PIN = !io->pump_2;
	SP_PIN = !io->salt_pump;

	CVCC_CONTROL_PIN = io->cvcc_control;
}
void resetIO(void){
	SV1_PIN = 0;
	SV2_PIN = 0;
	SV3_PIN = 0;
	SV4_PIN = 0;
	SV5_PIN = 0;
	SV6_PIN = 0;
	SV7_PIN = 0;

	PUMP_1_PIN = 1;
	PUMP_2_PIN = 1;
	SP_PIN = 1;

	CVCC_CONTROL_PIN = 0;
}
