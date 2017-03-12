/* vim: set ts=8 sw=8 tw=0 noet : */
#include <stdbool.h>
#include <stdlib.h>

#ifndef STACK_OOP_H
#define STACK_OOP_H

struct stack {
	struct stack_methods *methods;
	void *head;
	void *tail;
	void *top;
	size_t length;
	size_t el_size;
	size_t size;
};

struct stack_methods {
	void (*init) (struct stack *this, size_t elem_size,
			void (*print_elem)(void *));
	struct stack * (*new) (size_t elem_size, void (*print_elem)(void *));
	void (*push) (struct stack *this, void *e);
	void * (*pop) (struct stack *this);
	bool (*is_empty) (struct stack *this);
	void (*print) (struct stack *this);
	void (*print_elem) (void *elem);
};

void stack_init (struct stack *this, size_t elem_size,
		void (*print_elem)(void *));
struct stack * stack_new (size_t elem_size, void (*print_elem)(void *));
void stack_push (struct stack *this, void *elem);
void *stack_pop (struct stack *this);
bool stack_is_empty (struct stack *this);
void stack_print(struct stack *this);
void stack_delete (struct stack *this);
#endif
