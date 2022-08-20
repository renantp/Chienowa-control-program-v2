/*
 * e_module.h
 *
 *  Created on: Jul 29, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_MODULE_E_MODULE_H_
#define CHIENOWA_MODULE_E_MODULE_H_

#include "../../r_cg_macrodriver.h"

extern union Error_status {
	struct{
		int over_voltage_1: 1;
		int over_voltage_2: 1;
		int over_voltage_3: 1;

		uint32_t rsvd: 29;
	};
	uint32_t data;
}g_error_status;


int e1_faucet_refresh_process(void);
#endif /* CHIENOWA_MODULE_E_MODULE_H_ */
