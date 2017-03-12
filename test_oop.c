/* vim: set ts=8 sw=8 tw=0 noet : */
#include <stdio.h>
#include <stdlib.h>
#include "stack_oop.h"

struct delem {
	int idata;
	float data;
	struct delem *next;
};

struct delem *new_delem(float f)
{
	struct delem *elem = malloc(sizeof (struct delem));
	elem->idata = (int)f;
	elem->data = f;
	elem->next = NULL;
	return elem;
}

void print(void *delem)
{
	struct delem *elem = delem;
	printf("-> %d %.2f ", elem->idata, elem->data);
}

int main()
{
	struct stack *stack = stack_new(sizeof(struct delem *), print);
	for (float i = 5; i < 7; i += 0.25) {
		struct delem *elem = new_delem(i);
		stack->methods->push(stack, elem);
	}
	stack->methods->print(stack);
	print(stack->methods->pop(stack));
	print(stack->methods->pop(stack));
	stack->methods->print(stack);
	stack_delete(stack);
	return 0;
}
