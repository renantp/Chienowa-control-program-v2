/*
 * circular_buffer.h
 *
 *  Created on: Jul 25, 2022
 *      Author: Hung
 */

#ifndef CHIENOWA_CIRCULAR_BUFFER_H_
#define CHIENOWA_CIRCULAR_BUFFER_H_

#include "../r_cg_macrodriver.h"

typedef struct {
	uint8_t *buffer;
	int head;
	int tail;
	int max_len;
} circular_buffer;

typedef struct {
	uint8_t **buffer;
	int head;
	int tail;
	int max_len;
} circular_pointer_buffer;

int circular_buffer_push(circular_buffer *const c, uint8_t data);
int circular_buffer_pop(circular_buffer *const c, uint8_t *data);
int circular_buffer_get(circular_buffer *const c, uint8_t *data, uint8_t len);
int circular_buffer_set(circular_buffer *const c, uint8_t *data, uint8_t len);
uint8_t* circular_buffer_calloc(circular_buffer *const c, uint16_t len);

int circular_pointer_buffer_push(circular_pointer_buffer *const c,
		uint8_t *data);
int circular_pointer_buffer_pop(circular_pointer_buffer *const c,
		uint8_t **data);

#endif /* CHIENOWA_CIRCULAR_BUFFER_H_ */
