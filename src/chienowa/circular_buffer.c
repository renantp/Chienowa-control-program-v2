/*
 * circular_buffer.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Hung
 */

#include "circular_buffer.h"

int circular_pointer_buffer_push(circular_pointer_buffer *const c,
		uint8_t *data) {
	int next;

	next = c->head + 1;
	if (next >= c->max_len) {
		next = 0;
	}
	if (next == c->tail) {
		return -1;
	}

	c->buffer[c->head] = data;
	c->head = next;
	return 0;
}
int circular_pointer_buffer_pop(circular_pointer_buffer *const c,
		uint8_t **data) {
	int next;
	if (c->head == c->tail)
		return -1;

	next = c->tail + 1;
	if (next >= c->max_len)
		next = 0;
	*data = c->buffer[c->tail];
	c->tail = next;

	return 0;
}
int circular_buffer_push(circular_buffer *const c, uint8_t data) {
	int next;

	next = c->head + 1;
	if (next >= c->max_len) {
		next = 0;
	}
	if (next == c->tail) {
		return -1;
	}

	c->buffer[c->head] = data;
	c->head = next;

	return 0;
}

int circular_buffer_pop(circular_buffer *const c, uint8_t *data) {
	int next;
	if (c->head == c->tail)
		return -1;

	next = c->tail + 1;
	if (next >= c->max_len)
		next = 0;
	*data = c->buffer[c->tail];
	c->tail = next;

	return 0;
}

int circular_buffer_get(circular_buffer *const c, uint8_t *data, uint8_t len) {
	if (len > c->max_len)
		return -1;
	for (int i = 0; i < len; i++) {
		if (circular_buffer_pop(c, data))
			data++;
		else
			return -2;
	}
	return 0;
}

int circular_buffer_set(circular_buffer *const c, uint8_t *data, uint8_t len) {
	for (int i = 0; i < len; i++) {
		if (circular_buffer_push(c, data[i]) != 0)
			return -1;
	}
	return 0;
}

uint8_t* circular_buffer_calloc(circular_buffer *const c, uint16_t len) {
	uint8_t *const p = &c->buffer[c->head];
	int next;
	next = c->head + len;
	if (next >= c->max_len)
		next = next - c->max_len;
	c->head = next;
	return p;
}

