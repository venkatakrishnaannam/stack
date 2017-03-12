/* vim: set ts=8 sw=8 tw=0 noet : */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack_oop.h"

struct stack_methods Stack = {
	.init = stack_init,
	.new = stack_new,
	.push = stack_push,
	.pop = stack_pop,
	.is_empty = stack_is_empty,
	.print = stack_print
};

void stack_init (struct stack *this, size_t elem_size,
		void (*print_elem)(void *))
{
	this->methods = &Stack;
	this->methods->print_elem = print_elem;
	this->length = 0;
	this->size = 4;
	this->el_size = elem_size;
	this->head = malloc(this->el_size * 4);
	this->tail = this->head;
	this->top = NULL;
}

struct stack * stack_new (size_t elem_size, void (*print_elem)(void *))
{
	struct stack *new = (struct stack *) malloc (sizeof (struct stack));
	stack_init(new, elem_size, print_elem);
	return new;
}

void stack_push (struct stack *this, void *elem)
{
	if (this->size == this->length) {
		this->size *= 2;
		this->head = realloc(this->head, this->size * this->el_size);
		this->tail = this->head + this->length * this->el_size;
	}
	memcpy(this->tail, elem, this->el_size);
	this->top = this->tail;
	this->tail += this->el_size;
	this->length++;
}

void *stack_pop (struct stack *this)
{
	if (this->methods->is_empty(this))
		return NULL;
	void *top = this->top;
	this->tail = this->top;
	this->top = this->length > 1? this->top - this->el_size: NULL;
	this->length--;
	return top;
}

bool stack_is_empty (struct stack *this)
{
	return this->length == 0;
}

void stack_print (struct stack *this)
{
	void *curr = this->head;
	for (size_t i = 0; i < this->length; i++, curr += this->el_size)
		this->methods->print_elem(curr);
	putchar('\n');
}

void stack_delete (struct stack *this)
{
	free(this->head);
	free(this);
}
