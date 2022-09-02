/*
 * e_module.h
 *
 *  Created on: Jul 29, 2022
 *      Author: Renan
 */

#ifndef CHIENOWA_MODULE_E_MODULE_H_
#define CHIENOWA_MODULE_E_MODULE_H_

#include "../../r_cg_macrodriver.h"
extern enum ERROR_ENUM{
	NO_ERROR,
	E1,
	M1000,
	M1001,
	M1002,
	M1003,
	M1004,
	M1005,
	M1006,
	M1007,
	M1008,
	M1009,
	M1020,
	M1021,
	M1022,
	M1023,
	M1024,
	M1025,
	M1026,
	M1027,
	M1028,
	M1029,
	M1030,
	M1031,
	M1032,
	M1033,
	M1034,
	M1035,
	M1036,
	M1037,
	M1038,
	M1039,
	M1051,

	//Add by Mr.Goto
	M5001,
	M5002,
	M5003,
	M5005,

	E0003,
}e_occur_error;
int e1_faucet_refresh_process(void);
int e11(void);
int e2(void);
int e3(void);
int e1000(void);
int e1001(void);
int e1002(void);
int e1003(void);
int e1004(void);
int e1005(void);
int e1006(void);
int e1007(void);
int e1008(void);
int e1009(void);
int e1020(void);
int e1021(void);
int e1022(void);
int e1023(void);
int e1024(void);
int e1025(void);
int e1026(void);
int e1028(void);
int e1029(void);
int e1030(void);
int e1031(void);
int e1031_1(void);
int e1032(void);
int e1033(void);
int e1034(void);
int e1035(void);
int e1051(void);
int e5001(void);
int e5002(void);
int e5003(void);

#endif /* CHIENOWA_MODULE_E_MODULE_H_ */
