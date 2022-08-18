/*
 * module.c
 *
 *  Created on: Aug 3, 2022
 *      Author: Renan
 */

#include "b_module.h"
#include "../pin_define.h"
#include "../delay.h"
#include "../global_variable.h"

int bp0_system_main_start(void){
	if(!g.flag.module.bp0){
		g.flag.module.bp0 = 1;
		//g.timer.module.work.p0[0] is total working time
		g.timer.module.on.p0[0] = timer_restart_s(g.timer.module.work.p0[0]);
		g.timer.module.on.p0[1] = timer_start_ms();
	}
	return 0;
}
int bp1_initial_working_mode_start_process(void){
	if(g.flag.module.bp1 == 0){
		g.flag.module.bp1 = 1;
		g.timer.module.on.p1[0] = timer_restart_s(g.timer.module.work.p1[0]);
		g.timer.module.on.p1[1] = timer_start_ms();
	}
	return 0;
}
int bp11_initial_drainage_start_process(void){
	if(g.flag.module.bp11 == 0){
		g.flag.module.bp11 = 1;
		g.timer.module.on.p11[0] = timer_restart_s(g.timer.module.work.p11[0]);
		g.timer.module.on.p11[1] = timer_start_ms();
	}
	return 0;
}
int bp111_inital_alkali_tank_drainage_start_process(void){
	if( g.flag.module.bp111 == 0 ){
		g.flag.module.bp111 = 1;
		g.timer.module.on.p111[0] = timer_restart_s(g.timer.module.work.p111[0]);
		g.timer.module.on.p111[1] = timer_start_ms();
	}
	return 0;
}
int bp112_inital_acid_tank_drainage_start_process(void){
	if( g.flag.module.bp112 == 0 ){
		g.flag.module.bp112 = 1;
		g.timer.module.on.p112[0] = timer_restart_s(g.timer.module.work.p112[0]);
		g.timer.module.on.p112[1] = timer_start_ms();
	}
	return 0;
}
int bp12_initial_water_supply_start_process(void){
	if(g.flag.module.bp12 == 0){
		g.flag.module.bp12 = 1;
		g.timer.module.on.p12[0] = timer_restart_s(g.timer.module.work.p12[0]);
		g.timer.module.on.p12[1] = timer_start_ms();
	}
	return 0;
}
int bp13_initial_electrolysis_start_process(void){
	if(g.flag.module.bp13 == 0){
		g.flag.module.bp13 = 1;
		g.timer.module.on.p13[0] = timer_restart_s(g.timer.module.work.p13[0]);
		g.timer.module.on.p13[1] = timer_start_ms();
		CVCC_CONTROL_PIN = 1U;
	}
	return 0;
}
int bp14_initial_2nd_draining_start_process(void){
	if(g.flag.module.bp14 == 0){
		g.flag.module.bp14 = 1;
		g.timer.module.on.p14[0] = timer_restart_s(g.timer.module.work.p14[0]);
		g.timer.module.on.p14[1] = timer_start_ms();
//		CVCC_CONTROL_PIN = 1U;
	}
	return 0;
}
int bp141_2nd_alkali_tank_drain_startup_process(void){
	if(g.flag.module.bp141 == 0){
		g.flag.module.bp141 = 1;
		g.timer.module.on.p141[0] = timer_restart_s(g.timer.module.work.p141[0]);
		g.timer.module.on.p141[1] = timer_start_ms();
	}
	return 0;
}
int bp142_2nd_acid_tank_drain_startup_process(void){
	if(g.flag.module.bp142 == 0){
		g.flag.module.bp142 = 1;
		g.timer.module.on.p142[0] = timer_restart_s(g.timer.module.work.p142[0]);
		g.timer.module.on.p142[1] = timer_start_ms();
	}
	return 0;
}
int bp15_electrolysis_start_process(void){
	if(g.flag.module.bp15 == 0){
		g.flag.module.bp15 = 1;
		g.timer.module.on.p15[0] = timer_restart_s(g.timer.module.work.p15[0]);
		g.timer.module.on.p15[1] = timer_start_ms();
		CVCC_CONTROL_PIN = 1;
		//TODO: CVCC error
		//TODO: C_1_OFF_T2 = 0

	}
	return 0;
}
int bp2_water_discharge_start_process(void){
	if(g.flag.module.bp2 == 0){
		g.flag.module.bp2 = 1;
		g.timer.module.on.p2[0] = timer_restart_s(g.timer.module.work.p2[0]);
		g.timer.module.on.p2[1] = timer_start_ms();
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int bp21_alkali_discharge_start(void){
	if(g.flag.module.bp21 == 0){
		g.flag.module.bp21 = 1;
		g.timer.module.on.p21[0] = timer_restart_s(g.timer.module.work.p21[0]);
		g.timer.module.on.p21[1] = timer_start_ms();
		//TODO: P_2_1_OFF_T1 stop
		//TODO: P_2_1_OFF_T2 stop
	}
	return 0;
}
/**
 * Deleted
 * @return
 */
int bp22_acid_discharge_start(void){
	return 0;
}
int bp23_water_discharge_start(void){
	if(g.flag.module.bp23 == 0){
		g.flag.module.bp23 = 1;
		g.timer.module.on.p23[0] = timer_restart_s(g.timer.module.work.p23[0]);
		g.timer.module.on.p23[1] = timer_start_ms();
	}
	return 0;
}
int bp24_hand_wash_start(void){
	if(g.flag.module.bp24 == 0){
		g.flag.module.bp24 = 1;
		g.timer.module.on.p24[0] = timer_restart_s(g.timer.module.work.p24[0]);
		g.timer.module.on.p24[1] = timer_start_ms();
	}
	return 0;
}
/**
 * Under changing
 * @return
 */
int bp241(void){
	if(g.flag.module.bp241 == 0){
		g.flag.module.bp241 = 1;
		g.timer.module.on.p241[0] = timer_restart_s(g.timer.module.work.p241[0]);
		g.timer.module.on.p241[1] = timer_start_ms();
		//TODO: P_2_4_1_OFF_T1 stop
		//TODO: P_2_4_1_OFF_T2 stop
	}
	return 0;
}
/**
 * Under changing
 * @return
 */
int bp242(void){
	return 0;
}
int bp243(void){
	if(g.flag.module.bp243 == 0){
		g.flag.module.bp243 = 1;
		g.timer.module.on.p243[0] = timer_restart_s(g.timer.module.work.p243[0]);
		g.timer.module.on.p243[1] = timer_start_ms();
	}
	return 0;
}
int bp3_individual_start(void){
	if(g.flag.module.bp3 == 0){
		g.flag.module.bp3 = 1;
		g.timer.module.on.p3[0] = timer_restart_s(g.timer.module.work.p3[0]);
		g.timer.module.on.p3[1] = timer_start_ms();
	}
	return 0;
}
int bp314(void){
	if(g.flag.module.bp314 == 0){
		g.flag.module.bp314 = 1;
		g.timer.module.on.p314[0] = timer_restart_s(g.timer.module.work.p314[0]);
		g.timer.module.on.p314[1] = timer_start_ms();
	}
	return 0;
}

int bp8(void){
	if(g.flag.module.bp8 == 0){
		g.flag.module.bp8 = 1;
		g.timer.module.on.p8[0] = timer_restart_s(g.timer.module.work.p8[0]);
		g.timer.module.on.p8[1] = timer_start_ms();
	}
	return 0;
}

int b_inital_acid_tank_drainage_start_process(void){

	return 0;
}

int bp112_p1_start_process(void){
	return 0;
}


int b_p1_start(void){
	if ( g.io.pump_1 == 0){
		PUMP_1_PIN = PUMP_ON;
		g.io.pump_1 = 1;
		g.timer.module.on.io.p1[0] = timer_restart_s(g.timer.module.work.io.p1[0]);
		g.timer.module.on.io.p1[1] = timer_start_ms();
		return 1;
	}
	return 0;
}
int b_p2_start(void){
	if( g.io.pump_2 == 0 ){
		PUMP_2_PIN = PUMP_ON;
		g.io.pump_2 = 1;
		g.timer.module.on.io.p2[0] = timer_restart_s(g.timer.module.work.io.p2[0]);
		g.timer.module.on.io.p2[1] = timer_start_ms();
	}
	return 0;
}
int b_sp_start(void){
	if( g.io.salt_pump == 0 ){
		PUMP_2_PIN = PUMP_ON;
		g.io.salt_pump = 1;
		g.timer.module.on.io.sp[0] = timer_restart_s(g.timer.module.work.io.sp[0]);
		g.timer.module.on.io.sp[1] = timer_start_ms();
	}
	return 0;
}
int b_sv1_start(void){
	if ( g.io.valve.sv1 == 0){
		SV1_PIN = VALVE_ON;
		g.io.valve.sv1 = 1;
		g.timer.module.on.io.sv1[0] = timer_restart_s(g.timer.module.work.io.sv1[0]);
		g.timer.module.on.io.sv1[1] = timer_start_ms();
		return 1;
	}
	return 0;
}
int b_sv2_start(void){
	if( g.io.valve.sv2 == 0){
		SV2_PIN = VALVE_ON;
		g.io.valve.sv2 = 1;
		g.timer.module.on.io.sv2[0] = timer_restart_s(g.timer.module.work.io.sv2[0]);
		g.timer.module.on.io.sv2[1] = timer_start_ms();
		return 1;
	}
	return 0;
}
int b_sv3_start(void){
	if(g.io.valve.sv3 == 0){
		SV3_PIN = VALVE_ON;
		g.io.valve.sv3 = 1;
		g.timer.module.on.io.sv3[0] = timer_restart_s(g.timer.module.work.io.sv3[0]);
		g.timer.module.on.io.sv3[1] = timer_start_ms();
		return 0;
	}
	return 0;
}
int b_sv4_start(void){
	if(g.io.valve.sv4 == 0){
		SV4_PIN = VALVE_ON;
		g.io.valve.sv4 = 1;
		g.timer.module.on.io.sv4[0] = timer_restart_s(g.timer.module.work.io.sv4[0]);
		g.timer.module.on.io.sv4[1] = timer_start_ms();
		return 0;
	}
	return 0;
}
int b_sv5_start(void){
	if ( g.io.valve.sv5 == 0){
		SV5_PIN = VALVE_ON;
		g.io.valve.sv5 = 1;
		g.timer.module.on.io.sv5[0] = timer_restart_s(g.timer.module.work.io.sv5[0]);
		g.timer.module.on.io.sv5[1] = timer_start_ms();
		return 1;
	}
	return 0;
}
int b_sv6_start(void){
	if( g.io.valve.sv6 == 0 ){
		SV6_PIN = VALVE_ON;
		g.io.valve.sv6 = 1;
		g.timer.module.on.io.sv6[0] = timer_restart_s(g.timer.module.work.io.sv6[0]);
		g.timer.module.on.io.sv6[1] = timer_start_ms();
	}
	return SV6_PIN;
}
int b_sv7_start(void){
	if( g.io.valve.sv7 == 0 ){
		SV7_PIN = VALVE_ON;
		g.io.valve.sv7 = 1;
		g.timer.module.on.io.sv7[0] = timer_restart_s(g.timer.module.work.io.sv7[0]);
		g.timer.module.on.io.sv7[1] = timer_start_ms();
	}
	return SV7_PIN;
}

int bc1(void){
	if(g.flag.module.bc1 == 0){
		g.timer.module.on.c1[0] = timer_restart_s(g.timer.module.work.c1[0]);
		g.timer.module.on.c1[1] = timer_start_ms();
		//TODO: CVCC error??

		g.flag.module.bc1 = 1;
	}
	return 0;
}
int bc2(void){
	if(g.flag.module.bc2 == 0){
		g.timer.module.on.c2[0] = timer_restart_s(g.timer.module.work.c2[0]);
		g.timer.module.on.c2[1] = timer_start_ms();
		g.flag.module.bc2 = 1;
	}
	return 0;
}
int bc3(void){
	if(g.flag.module.bc3 == 0){
		g.timer.module.on.c3[0] = timer_restart_s(g.timer.module.work.c3[0]);
		g.timer.module.on.c3[1] = timer_start_ms();
		g.flag.module.bc3 = 1;
	}
	return 0;
}
int bc4(void){
	if(g.flag.module.bc4 == 0){
		g.timer.module.on.c4[0] = timer_restart_s(g.timer.module.work.c4[0]);
		g.timer.module.on.c4[1] = timer_start_ms();
		g.flag.module.bc4 = 1;
	}
	return 0;
}
int bc5(void){
	if(g.flag.module.bc5 == 0){
		g.timer.module.on.c5[0] = timer_restart_s(g.timer.module.work.c5[0]);
		g.timer.module.on.c5[1] = timer_start_ms();
		g.flag.module.bc5 = 1;
	}
	return 0;
}
int bc51(void){
	if(g.flag.module.bc51 == 0){
		g.timer.module.on.c51[0] = timer_restart_s(g.timer.module.work.c51[0]);
		g.timer.module.on.c51[1] = timer_start_ms();
		g.flag.module.bc51 = 1;
	}
	return 0;
}
int bc52(void){
	if(g.flag.module.bc52 == 0){
		g.timer.module.on.c52[0] = timer_restart_s(g.timer.module.work.c52[0]);
		g.timer.module.on.c52[1] = timer_start_ms();
		g.flag.module.bc52 = 1;
	}
	return 0;
}
int bc53(void){
	if(g.flag.module.bc53 == 0){
		g.timer.module.on.c53[0] = timer_restart_s(g.timer.module.work.c53[0]);
		g.timer.module.on.c53[1] = timer_start_ms();
		g.flag.module.bc53 = 1;
	}
	return 0;
}
int bc531(void){
	if(g.flag.module.bc531 == 0){
		g.timer.module.on.c531[0] = timer_restart_s(g.timer.module.work.c531[0]);
		g.timer.module.on.c531[1] = timer_start_ms();
		g.flag.module.bc531 = 1;
	}
	return 0;
}
int bc54(void){
	if(g.flag.module.bc54 == 0){
		g.timer.module.on.c54[0] = timer_restart_s(g.timer.module.work.c54[0]);
		g.timer.module.on.c54[1] = timer_start_ms();
		g.flag.module.bc54 = 1;
	}
	return 0;
}
int bc55(void){
	if(g.flag.module.bc55 == 0){
		g.timer.module.on.c55[0] = timer_restart_s(g.timer.module.work.c55[0]);
		g.timer.module.on.c55[1] = timer_start_ms();
		g.flag.module.bc55 = 1;
	}
	return 0;
}
int bc56(void){
	if(g.flag.module.bc56 == 0){
		g.timer.module.on.c56[0] = timer_restart_s(g.timer.module.work.c56[0]);
		g.timer.module.on.c56[1] = timer_start_ms();
		g.flag.module.bc56 = 1;
	}
	return 0;
}
int bc6(void){
	if(g.flag.module.bc6 == 0){
		g.timer.module.on.c6[0] = timer_restart_s(g.timer.module.work.c6[0]);
		g.timer.module.on.c6[1] = timer_start_ms();
		g.flag.module.bc6 = 1;
	}
	return 0;
}
int bc7(void){
	if(g.flag.module.bc7 == 0){
		g.timer.module.on.c7[0] = timer_restart_s(g.timer.module.work.c7[0]);
		g.timer.module.on.c7[1] = timer_start_ms();
		g.flag.module.bc7 = 1;
	}
	return 0;
}
int bc8(void){
	if(g.flag.module.bc8 == 0){
		g.timer.module.on.c8[0] = timer_restart_s(g.timer.module.work.c8[0]);
		g.timer.module.on.c8[1] = timer_start_ms();
		g.flag.module.bc8 = 1;
	}
	return 0;
}
int bc_10(void){
	if(g.flag.module.bc10 == 0){
		g.timer.module.on.c10[0] = timer_restart_s(g.timer.module.work.c10[0]);
		g.timer.module.on.c10[1] = timer_start_ms();
		g.flag.module.bc10 = 1;
	}
	return 0;
}
int bc_11(void){
	if(g.flag.module.bc11 == 0){
		g.timer.module.on.c11[0] = timer_restart_s(g.timer.module.work.c11[0]);
		g.timer.module.on.c11[1] = timer_start_ms();
		g.flag.module.bc11 = 1;
	}
	return 0;
}
int bc_12(void){
	if(g.flag.module.bc12 == 0){
		g.timer.module.on.c12[0] = timer_restart_s(g.timer.module.work.c12[0]);
		g.timer.module.on.c12[1] = timer_start_ms();
		g.flag.module.bc12 = 1;
	}
	return 0;
}
int bc_13(void){
	if(g.flag.module.bc13 == 0){
		g.timer.module.on.c13[0] = timer_restart_s(g.timer.module.work.c13[0]);
		g.timer.module.on.c13[1] = timer_start_ms();
		g.flag.module.bc13 = 1;
	}
	return 0;
}
int bc_14(void){
	if(g.flag.module.bc14 == 0){
		g.timer.module.on.c14[0] = timer_restart_s(g.timer.module.work.c14[0]);
		g.timer.module.on.c14[1] = timer_start_ms();
		g.flag.module.bc14 = 1;
	}
	return 0;
}
int bc_15(void){
	if(g.flag.module.bc15 == 0){
		g.timer.module.on.c15[0] = timer_restart_s(g.timer.module.work.c15[0]);
		g.timer.module.on.c15[1] = timer_start_ms();
		g.flag.module.bc15 = 1;
	}
	return 0;
}
int bc_16(void){
	if(g.flag.module.bc16 == 0){
		g.timer.module.on.c16[0] = timer_restart_s(g.timer.module.work.c16[0]);
		g.timer.module.on.c16[1] = timer_start_ms();
		g.flag.module.bc16 = 1;
	}
	return 0;
}
int bc_17(void){
	if(g.flag.module.bc17 == 0){
		g.timer.module.on.c17[0] = timer_restart_s(g.timer.module.work.c17[0]);
		g.timer.module.on.c17[1] = timer_start_ms();
		g.flag.module.bc17 = 1;
	}
	return 0;
}
int bc_18(void){
	if(g.flag.module.bc18 == 0){
		g.timer.module.on.c18[0] = timer_restart_s(g.timer.module.work.c18[0]);
		g.timer.module.on.c18[1] = timer_start_ms();
		g.flag.module.bc18 = 1;
	}
	return 0;
}
int bc_19(void){
	if(g.flag.module.bc19 == 0){
		g.timer.module.on.c19[0] = timer_restart_s(g.timer.module.work.c19[0]);
		g.timer.module.on.c19[1] = timer_start_ms();
		g.flag.module.bc19 = 1;
	}
	return 0;
}
int be1(void){
	if(g.flag.module.be1 == 0){
		g.timer.module.on.e1[0] = timer_restart_s(g.timer.module.work.e1[0]);
		g.timer.module.on.e1[1] = timer_start_ms();
		g.flag.module.be1 = 1;
	}
	return 0;
}
