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
uint8_t runtime_state = 0;
uint32_t runtime_wait;
void write_enable(void);
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

int push_package_queue(struct Transmit_Package *pakage) {
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
int pop_package_queue(void) {
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
struct Runtime_Queue_Data{
	uint8_t *p_data;
	uint16_t len;
	uint16_t addr;
};
struct Runtime_Queue_Data *current_runtime_data;
struct Runtime_Queue{
	uint16_t queue;
	struct Runtime_Queue_Data data[16];
	uint8_t head;
	uint8_t tail;
} runtime_queue;

enum RUMTIME_QUEUE_E{
	READ = 0x0000, WRITE = 0x0001
}current_runtime_type;
int push_runtime_queue(enum RUMTIME_QUEUE_E input, uint8_t *const p_data, uint16_t addr, uint16_t len){
	uint8_t next = runtime_queue.head + 1;
	if(next >= 16){
		next = 0;
	}
	if(next == runtime_queue.tail){
		return -1;
	}
	uint16_t bit = 0x0001 << (15 - runtime_queue.head);
	if(input)
		runtime_queue.queue |= bit;
	else{
		runtime_queue.queue &= (~bit);
	}
	runtime_queue.data[runtime_queue.head].p_data = p_data;
	runtime_queue.data[runtime_queue.head].addr = addr;
	runtime_queue.data[runtime_queue.head].len = len;
	runtime_queue.head = next;
    return 0;
}
int pop_runtime_queue(void){
	uint8_t next = runtime_queue.tail + 1;
	if(next >= 16){
		next = 0;
	}
	if(runtime_queue.tail == runtime_queue.head){
		return -1;
	}
    uint16_t bit = 0x0001 << (15 - runtime_queue.tail);
    bit &= runtime_queue.queue;
    bit = bit >> (15 - runtime_queue.tail);
	current_runtime_type = bit ? WRITE : READ;
	current_runtime_data = &runtime_queue.data[runtime_queue.tail];
	runtime_queue.tail = next;
	return 0;
}

void get_status_callback(void);
int add_transmit_data_queue(uint8_t *const p_data, uint16_t tx_len,
		void (*callback)(void)) {
	struct Transmit_Package pakage = { .pointer = p_data, .len = tx_len,
			.callback = callback };
	if (push_package_queue(&pakage) == -1)
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
} eeprom_buffer;

void read_callback(void) {
	if (eeprom_buffer.current_page != 0) {
		for (int i = 0; i < 32; i++) {
			eeprom_buffer.p_data[i] = eeprom_buffer.page_data.refined.data[i];
		}
		eeprom_buffer.p_data += 32;
		eeprom_buffer.addr += (uint16_t) 32
							* (eeprom_buffer.max_page - eeprom_buffer.current_page + 1);
		eeprom_buffer.page_data.refined.cmd = EEPROM_READ;
		eeprom_buffer.page_data.refined.addr0 = eeprom_buffer.addr >> 8;
		eeprom_buffer.page_data.refined.addr1 = eeprom_buffer.addr;
		eeprom_buffer.current_page--;
		if (eeprom_buffer.current_page == 0 && eeprom_buffer.rsvd != 0) {
			add_transmit_data_queue(eeprom_buffer.page_data.refined.data, eeprom_buffer.rsvd,
					read_callback);
			runtime_state = 2;
			eeprom_runtime();
		}else if(eeprom_buffer.current_page != 0){
			add_transmit_data_queue(eeprom_buffer.page_data.refined.data, 32, read_callback);
			eeprom_runtime();
			runtime_state = 2;
		}else{
			CSI_CS_HIGH();
			eeprom_buffer.busy = 0;
		}
	}else{
		//Run callback last time
		CSI_CS_HIGH();
		for (int i = 0; i < eeprom_buffer.rsvd; i++) {
			eeprom_buffer.p_data[i] = eeprom_buffer.page_data.refined.data[i];
		}
		eeprom_buffer.busy = 0;
	}
}
int read(uint8_t *const pBuffer, uint16_t addr, uint32_t num) {
	if (!eeprom_buffer.busy) {
		eeprom_buffer.busy = 1;
		eeprom_buffer.current_page = eeprom_buffer.max_page = num / 32;
		eeprom_buffer.rsvd = num % 32;
		eeprom_buffer.p_data = pBuffer;
		eeprom_buffer.page_data.refined.cmd = EEPROM_READ;
		eeprom_buffer.addr = addr;
		eeprom_buffer.page_data.refined.addr0 = eeprom_buffer.addr >> 8;
		eeprom_buffer.page_data.refined.addr1 = eeprom_buffer.addr;
		if(eeprom_buffer.current_page > 0)
			add_transmit_data_queue(eeprom_buffer.page_data.transmit_buffer, 32 + 3, read_callback);
		else if(eeprom_buffer.rsvd != 0){
			add_transmit_data_queue(eeprom_buffer.page_data.transmit_buffer, eeprom_buffer.rsvd + 3, read_callback);
		}
	} else{
		push_runtime_queue(READ, pBuffer, addr, num);
		eeprom_runtime();
		return -1;
	}
	return 0;
}

void write_callback(void){
	CSI_CS_HIGH();
	if(eeprom_buffer.current_page != 0){
		eeprom_buffer.current_page--;
		eeprom_buffer.p_data += 32;
		eeprom_buffer.addr += (uint16_t) 32
				* (eeprom_buffer.max_page - eeprom_buffer.current_page);
		eeprom_buffer.page_data.refined.cmd = EEPROM_WRITE;
		eeprom_buffer.page_data.refined.addr0 = eeprom_buffer.addr >> 8;
		eeprom_buffer.page_data.refined.addr1 = eeprom_buffer.addr;
		if(eeprom_buffer.current_page == 0 && eeprom_buffer.rsvd != 0){
			for (int i = 0; i < eeprom_buffer.rsvd; i++) {
				 eeprom_buffer.page_data.refined.data[i] = eeprom_buffer.p_data[i];
			}
			write_enable();
			add_transmit_data_queue(eeprom_buffer.page_data.transmit_buffer, eeprom_buffer.rsvd + 3,
								write_callback);
			runtime_state = 1;
		}else if(eeprom_buffer.current_page != 0){
			for (int i = 0; i < 32; i++) {
				 eeprom_buffer.page_data.refined.data[i] = eeprom_buffer.p_data[i];
			}
			write_enable();
			add_transmit_data_queue(eeprom_buffer.page_data.transmit_buffer, 32 + 3,
											write_callback);
			runtime_state = 1;
		}else{
			eeprom_buffer.busy = 0;
			runtime_state = 0;
		}
	}else{
		eeprom_buffer.busy = 0;
		runtime_state = 0;
	}
}
int write(uint8_t *const pBuffer, uint16_t addr, uint32_t num){
	if (!eeprom_buffer.busy) {
		eeprom_buffer.busy = 1;
		eeprom_buffer.current_page = eeprom_buffer.max_page = num / 32;
		eeprom_buffer.rsvd = num % 32;
		eeprom_buffer.p_data = pBuffer;
		eeprom_buffer.page_data.refined.cmd = EEPROM_WRITE;
		eeprom_buffer.addr = addr;
		eeprom_buffer.page_data.refined.addr0 = eeprom_buffer.addr >> 8;
		eeprom_buffer.page_data.refined.addr1 = eeprom_buffer.addr;
		write_enable();
		if(eeprom_buffer.max_page != 0){
			for(int i=0; i<32; i++){
				eeprom_buffer.page_data.refined.data[i] = pBuffer[i];
			}
			add_transmit_data_queue(eeprom_buffer.page_data.transmit_buffer, 32 + 3, write_callback);
		}else if(eeprom_buffer.rsvd != 0){
			for(uint8_t i=0; i<eeprom_buffer.rsvd; i++){
				eeprom_buffer.page_data.refined.data[i] = pBuffer[i];
			}
			add_transmit_data_queue(eeprom_buffer.page_data.transmit_buffer, eeprom_buffer.rsvd + 3,
											write_callback);
		}
	} else{
		eeprom_runtime();
		return -1;
	}
	return 0;
}

int eeprom_runtime(void) {
	//Check runtime queue
	if((runtime_queue.head != runtime_queue.tail)
			&& (runtime_state == 0) && eeprom_buffer.busy == 0){
		pop_runtime_queue();
		switch (current_runtime_type) {
			case READ:
				read(current_runtime_data->p_data, current_runtime_data->addr, current_runtime_data->len);
				break;
			case WRITE:
				write(current_runtime_data->p_data, current_runtime_data->addr, current_runtime_data->len);
				break;
			default:
				break;
		}
	}
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
			if (pop_package_queue() == -1) {
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

void eeprom_read(uint8_t *const pBuffer, uint16_t addr, uint32_t num){
	push_runtime_queue(READ, pBuffer, addr, num);
}
void eeprom_write(uint8_t *const pBuffer, uint16_t addr, uint32_t num){
	push_runtime_queue(WRITE, pBuffer, addr, num);
}
