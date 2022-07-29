/*
 * eeprom.h
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 *
 *     	Please check define Pin define and function define
 */

#ifndef CHIENOWA_EEPROM_H_
#define CHIENOWA_EEPROM_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "../r_cg_macrodriver.h"

/* Pin define */
#define CSI_CS_LOW() 			P14_bit.no1=0
#define CSI_CS_HIGH()			P14_bit.no1=1
#define EEPROM_HOLD_EN()		P12_bit.no0=0 //HOLD
#define EEPROM_HOLD_DIS()		P12_bit.no0=1 //HOLD
#define EEPROM_WRITE_PROTECT_EN()		P14_bit.no0=0 //WPB: Write prohibited
#define EEPROM_WRITE_PROTECT_DIS()	P14_bit.no0=1 //WPB

/* Function define */
#define CSI_Create()	R_CSI01_Create();
#define CSI_Start()		R_CSI01_Start()

/*BR25G320 Command*/
#define EEPROM_WREN  (0x06)  /*!< Write Enable >*/
#define EEPROM_WRDI  (0x04)  /*!< Write Disable >*/
#define EEPROM_RDSR  (0x05)  /*!< Read Status Register >*/
#define EEPROM_WRSR  (0x01)  /*!< Write Status Register >*/
#define EEPROM_READ  (0x03)  /*!< Read from Memory Array >*/
#define EEPROM_WRITE (0x02)  /*!< Write to Memory Array >*/

typedef enum {
	NONE_BLOCK, BLOCK_C00, BLOCK_800, BLOCK_ALL
} EEPROM_BLOCK_t;

union EEPROM_status_u {
	struct {
		uint8_t RB :1;
		uint8_t WEN :1;
		uint8_t BP :2;
		uint8_t RSVD :3;
		uint8_t WPEN :1;
	} refined;
	uint8_t raw;
};
/*!
 * Should initialize csi_flag and csi_send_receive. If not eeprom_init will return -1
 */
typedef struct {
	volatile int8_t *const csi_flag;
	int8_t csi_pre_flag;
	uint8_t data[2], status_data[2];
	MD_STATUS (*const csi_send_receive)(uint8_t *const tx_buf, uint16_t tx_num,
			uint8_t *const rx_buf);
	void (*transmit_callback)(void);
	union EEPROM_status_u status;
	uint8_t *state;
} eeprom_config;

int eeprom_init(eeprom_config *const e_config);
void eeprom_read(uint8_t *const pBuffer, uint16_t addr, uint32_t num);
void eeprom_write(uint8_t *const pBuffer, uint16_t addr, uint32_t num);
void get_status(void);
void eeprom_set_block(EEPROM_BLOCK_t block);
int eeprom_runtime(void);

#ifdef __cplusplus
}
#endif
#endif /* CHIENOWA_EEPROM_H_ */
