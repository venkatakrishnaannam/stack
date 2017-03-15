/* vim: set ts=8 sw=8 tw=0 noet : */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack_oop.h"

static void stack_init(Stack this, size_t elem_size, void (*print_elem)(void *))
{
	this->print_elem = print_elem;
	this->length = 0;
	this->size = 4;
	this->el_size = elem_size;
	this->head = malloc(this->el_size * 4);
	this->tail = this->head;
	this->top = NULL;
}

Stack stack_new(size_t elem_size, void (*print_elem)(void *))
{
	Stack new = malloc (sizeof *new);
	stack_init(new, elem_size, print_elem);
	return new;
}

void stack_push(Stack this, void *elem)
{
	if (this->size == this->length) {
		void *tmp = realloc(this->head, this->el_size * this->size<<1);
		if (tmp != NULL) {
			this->head = tmp;
			this->size <<= 1;
			this->tail = this->head + this->length * this->el_size;
		}
	}
	memcpy(this->tail, elem, this->el_size);
	this->top = this->tail;
	this->tail += this->el_size;
	this->length++;
}

void *stack_pop(Stack this)
{
	if (stack_is_empty(this))
		return NULL;
	void *top = this->top;
	this->tail = this->top;
	this->top = this->length > 1? this->top - this->el_size: NULL;
	this->length--;
	if (this->length * 4 <= this->size) {
		void *tmp = realloc(this->head, this->el_size * this->size >> 1);
		if (tmp != NULL)
			this->head = tmp;
	}
	return top;
}

bool stack_is_empty(Stack this)
{
	return this->length == 0;
}

void stack_print(Stack this)
{
	void *curr = this->head;
	for (size_t i = 0; i < this->length; i++, curr += this->el_size)
		this->print_elem(curr);
	putchar('\n');
}

void stack_delete(Stack this)
{
	free(this->head);
	free(this);
}
