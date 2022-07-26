/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G14 V2.05.06.02 [08 Nov 2021]
* Device(s)    : R5F104ML
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 9/13/2022
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_serial.h"
#include "r_cg_adc.h"
#include "r_cg_dac.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
#include "chienowa/delay.h"
#include "chienowa/water_flow_calculation.h"
#include "chienowa/runtime.h"
#include "chienowa/raspberry_pi_communication.h"
#include "chienowa/module/p_module.h"
#include "r_cg_dac.h"
#include "chienowa/module/b_module.h"
#include "chienowa/hand_sensor.h"
#include "chienowa/module/t_module.h"
#include "chienowa/c_main.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
uint32_t g_count;
struct Number_Setting_s g_V_S, g_V_S_buffer;
struct Timer_Setting_s g_T_S, g_T_S_buffer;
struct {
	uint32_t task1;
	uint32_t task2;
}stamp;
eeprom_config e_config = {
		.csi_flag = &g_csi01_flag,
		.csi_send_receive =	R_CSI01_Send_Receive };
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
    set_timer_setting_default(&g_T_S);
	if (eeprom_init(&e_config) == 0) {
		eeprom_set_block(NONE_BLOCK);
	}
	R_UART2_Receive(get_pointer_uart_queue(), 6);
	while (1U) {
		runtime();
		loop();
//		p_0();
	}
	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
	EI();

	R_SAU0_Create();
	R_CSI01_Create();

	R_SAU1_Create();
	R_UART2_Create();
	R_UART2_Start();

	R_TAU0_Create();
	R_TAU0_Channel0_Start();
	R_TAU1_Create();
	R_TAU1_Channel0_Start();
//	R_RTC_Create();
//	R_RTC_Start();

	R_DAC_Create();
	R_DAC0_Start();
	R_DAC1_Start();

	R_ADC_Create();
	R_ADC_Set_OperationOn();
	R_ADC_Start();

	R_INTC_Create();
	R_INTC8_Start();
	R_INTC9_Start();
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
