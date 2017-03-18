/* vim: set ts=8 sw=8 tw=0 noet : */
#include <stdbool.h>
#include <stdlib.h>

#ifndef STACK_OOP_H
#define STACK_OOP_H

struct Stack {
	void *head;
	void *tail;
	void *top;
	size_t length;
	size_t el_size;
	size_t size;
	void (*print_elem) (void *elem);
};
typedef struct Stack * Stack;

Stack stack_new (size_t elem_size, void (*print_elem)(void *));
void stack_push (Stack this, void *elem);
void *stack_pop (Stack this);
bool stack_is_empty (Stack this);
void stack_print(Stack this);
void stack_delete (Stack this);
#endif
