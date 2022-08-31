/*
 * runtime.c
 *
 *  Created on: Aug 11, 2022
 *      Author: Renan
 */
#include "eeprom.h"
#include "raspberry_pi_communication.h"
#include "global_variable.h"
#include "pin_define.h"

void input_flag_update(void){
	g.io.fl1 = !FL1;
	g.io.fl2 = !FL2;
	g.io.fl3 = !FL3;
	g.io.fl4 = !FL4;
	g.io.fl5 = !FL5;
	g.io.fl6 = !FL6;
	g.io.fl7 = !FL7;
	g.io.fl8 = !FL8;
}

void runtime(void){
	input_flag_update();
	eeprom_runtime();
	communication_runtime();
}
