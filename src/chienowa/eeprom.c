/*
 * eeprom.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Renan
 *		Before use, please check
 *
 *		HOW IT WORK?
 *      First, send 1 byte 0x06 to write enable,
 *      Next, send
 *
 */

#include "eeprom.h"
#include "../r_cg_serial.h"
#include "circular_buffer.h"
#include "delay.h"

enum EEPROM_STATE {
	READY, TRANSMITING, BUSY
} state = READY;

eeprom_config *config;

struct Transmit_Package {
	uint8_t *pointer;
	uint16_t len;
	void (*callback)(void);
};
struct Data_Queue {
	struct Transmit_Package pakages[10];
	uint8_t head;
	uint8_t tail;
} data_queue = { .head = 0 };
struct Transmit_Package *current_pakage;

int push_queue(struct Transmit_Package *pakage) {
	uint8_t next = data_queue.head + 1;
	if(next >= 10){
		next = 0;
	}
	if(next == data_queue.tail){
		return -1;
	}
	data_queue.pakages[data_queue.head] = *pakage;
	data_queue.head = next;

	return 0;
}
int pop_queue(void) {
	uint8_t next = data_queue.tail + 1;
	if(next >= 10){
		next = 0;
	}
	if(data_queue.tail == data_queue.head){
		return -1;
	}
	current_pakage = &data_queue.pakages[data_queue.tail];
	data_queue.tail = next;
	return 0;
}

void get_status_callback(void);
int add_transmit_data_queue(uint8_t *const p_data, uint16_t tx_len,
		void (*callback)(void)) {
	struct Transmit_Package pakage = { .pointer = p_data, .len = tx_len,
			.callback = callback };
	if (push_queue(&pakage) == -1)
		return -1;
	return 0;
}
uint8_t busy_count;
int transmit_data(struct Transmit_Package *pakage) {
	state = TRANSMITING;
	CSI_CS_LOW();
	config->csi_pre_flag = *config->csi_flag;
	config->transmit_callback = pakage->callback;
	config->csi_send_receive(pakage->pointer, pakage->len, pakage->pointer);
	return pakage->len;
}
uint8_t runtime_state = 0;
uint32_t runtime_wait;
int eeprom_runtime(void) {
	//Check data queue
	if (data_queue.head != data_queue.tail || runtime_state != 0) {
		switch (runtime_state) {
		case 0:
			runtime_state++;
			break;
		case 1:
			//Check if busy or not
			if (state == READY) {
				get_status();
			} else {
				//Get result of status data
				if (config->csi_pre_flag != *config->csi_flag) {
					CSI_CS_HIGH();
					config->csi_pre_flag = *config->csi_flag;

					config->status.raw = config->status_data[1];
					if (config->status.refined.RB == 1) {
						state = READY;
						busy_count++;
					} else {
						state = READY;
						runtime_state++;
					}
				}
			}
			break;
		case 2:
			//Pop queue & send
			if (pop_queue() == -1) {
				CSI_CS_HIGH();
				runtime_state = 0;
				return 0;
			}
			if (transmit_data(current_pakage) == 1)
				runtime_state = 3;
			else
				runtime_state = 4;
			break;
		case 3:
			//After command transmit
			if (config->csi_pre_flag != *config->csi_flag) {
				CSI_CS_HIGH();
				if (current_pakage->callback)
					current_pakage->callback();
				runtime_state = 2;
			}
			break;
		case 4:
			//Wait to Callback
			if (config->csi_pre_flag != *config->csi_flag) {
				config->csi_pre_flag = *config->csi_flag;
				state = READY;
				runtime_state = 1;
				if (current_pakage->callback)
					current_pakage->callback();
			}
			break;
		default:
			break;
		}
		return 1;
	}
	return 0;
}
uint8_t write_cmd = EEPROM_WREN;
void write_enable(void) {
//	if (config->status.refined.WEN == 0U) {
//	}
	write_cmd = EEPROM_WREN;
	add_transmit_data_queue(&write_cmd, 1, 0);
}
void get_status(void) {
	state = TRANSMITING;
	config->status_data[0] = EEPROM_RDSR;
	CSI_CS_LOW();
	config->csi_pre_flag = *config->csi_flag;
	config->csi_send_receive(config->status_data, 2, config->status_data);
}

void eeprom_set_block(EEPROM_BLOCK_t block) {
	write_enable();
	config->status.refined.BP = block;
	config->data[0] = EEPROM_WRSR;
	config->data[1] = config->status.raw;
	add_transmit_data_queue(config->data, 2, 0);
}

int eeprom_init(eeprom_config *const e_config) {
	CSI_Create();
	CSI_Start();
	EEPROM_HOLD_DIS();
	EEPROM_WRITE_PROTECT_DIS();
	CSI_CS_HIGH();

	config = e_config;
	config->state = (uint8_t*) &state;
	if (!config->csi_flag || !config->csi_send_receive)
		return -1;
	return 0;
}
union Page_Data {
	struct {
		uint8_t cmd;
		uint8_t addr0;
		uint8_t addr1;
		uint8_t data[32];
	} refined;
	uint8_t transmit_buffer[32 + 3];
};
struct {
	uint8_t *p_data;
	uint8_t current_page;
	uint8_t max_page;
	uint16_t addr;
	uint8_t rsvd;
	uint8_t busy;
	union Page_Data page_data;
} read_buffer, write_buffer;

void read_callback(void) {
//	if (read_buffer.current_page != 0) {
//		CSI_CS_HIGH();
//		for (int i = 0; i < 32; i++) {
//			read_buffer.p_data[i] = read_buffer.page_data.refined.data[i];
//		}
//		read_buffer.p_data += 32;
//		read_buffer.addr += (uint16_t) 32
//							* (read_buffer.max_page - read_buffer.current_page + 1);
//		read_buffer.page_data.refined.cmd = EEPROM_READ;
//		read_buffer.page_data.refined.addr0 = read_buffer.addr >> 8;
//		read_buffer.page_data.refined.addr1 = read_buffer.addr;
//		read_buffer.current_page--;
//		if (read_buffer.current_page == 0 && read_buffer.rsvd != 0) {
//			add_transmit_data_queue(read_buffer.page_data.transmit_buffer, read_buffer.rsvd + 3,
//					read_callback);
//		}else if(read_buffer.current_page != 0){
//			add_transmit_data_queue(read_buffer.page_data.transmit_buffer, 32 + 3, read_callback);
//		}else{
//			read_buffer.busy = 0;
//		}
//	}else{
//		//Run callback last time
//		CSI_CS_HIGH();
//		for (int i = 0; i < read_buffer.rsvd; i++) {
//			read_buffer.p_data[i] = read_buffer.page_data.refined.data[i];
//		}
//		read_buffer.busy = 0;
//	}
	if (read_buffer.current_page != 0) {
		for (int i = 0; i < 32; i++) {
			read_buffer.p_data[i] = read_buffer.page_data.refined.data[i];
		}
		read_buffer.p_data += 32;
		read_buffer.addr += (uint16_t) 32
							* (read_buffer.max_page - read_buffer.current_page + 1);
		read_buffer.page_data.refined.cmd = EEPROM_READ;
		read_buffer.page_data.refined.addr0 = read_buffer.addr >> 8;
		read_buffer.page_data.refined.addr1 = read_buffer.addr;
		read_buffer.current_page--;
		if (read_buffer.current_page == 0 && read_buffer.rsvd != 0) {
			add_transmit_data_queue(read_buffer.page_data.refined.data, read_buffer.rsvd + 3,
					read_callback);
			runtime_state = 2;
		}else if(read_buffer.current_page != 0){
			add_transmit_data_queue(read_buffer.page_data.refined.data, 32 + 3, read_callback);
			runtime_state = 2;
		}else{
			read_buffer.busy = 0;
		}
	}else{
		//Run callback last time
		CSI_CS_HIGH();
		for (int i = 0; i < read_buffer.rsvd; i++) {
			read_buffer.p_data[i] = read_buffer.page_data.refined.data[i];
		}
		read_buffer.busy = 0;
	}
}
int eeprom_read(uint8_t *const pBuffer, uint16_t addr, uint32_t num) {
	if (!write_buffer.busy && !read_buffer.busy) {
		read_buffer.busy = 1;
		read_buffer.current_page = read_buffer.max_page = num / 32;
		read_buffer.rsvd = num % 32;
		read_buffer.p_data = pBuffer;
		read_buffer.page_data.refined.cmd = EEPROM_READ;
		read_buffer.addr = addr;
		read_buffer.page_data.refined.addr0 = read_buffer.addr >> 8;
		read_buffer.page_data.refined.addr1 = read_buffer.addr;
		if(read_buffer.current_page > 0)
			add_transmit_data_queue(read_buffer.page_data.transmit_buffer, 32 + 3, read_callback);
		else if(read_buffer.rsvd != 0){
			add_transmit_data_queue(read_buffer.page_data.transmit_buffer, read_buffer.rsvd + 3, read_callback);
		}
	} else
		return -1;
	return 0;
}

void write_callback(void){
	CSI_CS_HIGH();
	if(write_buffer.current_page != 0){
		write_buffer.current_page--;
		write_buffer.p_data += 32;
		write_buffer.addr += (uint16_t) 32
				* (write_buffer.max_page - write_buffer.current_page);
		write_buffer.page_data.refined.cmd = EEPROM_WRITE;
		write_buffer.page_data.refined.addr0 = write_buffer.addr >> 8;
		write_buffer.page_data.refined.addr1 = write_buffer.addr;
		if(write_buffer.current_page == 0 && write_buffer.rsvd != 0){
			for (int i = 0; i < write_buffer.rsvd; i++) {
				 write_buffer.page_data.refined.data[i] = write_buffer.p_data[i];
			}
			write_enable();
			add_transmit_data_queue(write_buffer.page_data.transmit_buffer, write_buffer.rsvd + 3,
								write_callback);
			runtime_state = 1;
		}else if(write_buffer.current_page != 0){
			for (int i = 0; i < 32; i++) {
				 write_buffer.page_data.refined.data[i] = write_buffer.p_data[i];
			}
			write_enable();
			add_transmit_data_queue(write_buffer.page_data.transmit_buffer, 32 + 3,
											write_callback);
			runtime_state = 1;
		}else{
			write_buffer.busy = 0;
			runtime_state = 0;
		}
	}else{
		write_buffer.busy = 0;
		runtime_state = 0;
	}
}
int eeprom_write(uint8_t *const pBuffer, uint16_t addr, uint32_t num){
	if (!write_buffer.busy && !read_buffer.busy) {
		write_buffer.busy = 1;
		write_buffer.current_page = write_buffer.max_page = num / 32;
		write_buffer.rsvd = num % 32;
		write_buffer.p_data = pBuffer;
		write_buffer.page_data.refined.cmd = EEPROM_WRITE;
		write_buffer.addr = addr;
		write_buffer.page_data.refined.addr0 = write_buffer.addr >> 8;
		write_buffer.page_data.refined.addr1 = write_buffer.addr;
		write_enable();
		if(write_buffer.max_page != 0){
			for(int i=0; i<32; i++){
				write_buffer.page_data.refined.data[i] = pBuffer[i];
			}
			add_transmit_data_queue(write_buffer.page_data.transmit_buffer, 32 + 3, write_callback);
		}else if(write_buffer.rsvd != 0){
			for(uint8_t i=0; i<write_buffer.rsvd; i++){
				write_buffer.page_data.refined.data[i] = pBuffer[i];
			}
			add_transmit_data_queue(write_buffer.page_data.transmit_buffer, write_buffer.rsvd + 3,
											write_callback);
		}
	} else
		return -1;
	return 0;
}
