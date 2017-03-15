/* vim: set ts=8 sw=8 tw=0 noet : */
#include <stdio.h>
#include <stdlib.h>
#include "stack_oop.h"

struct delem {
	int idata;
	float data;
	long ldata;
};

struct delem new_delem(float f)
{
	struct delem elem = {
		.idata = (int)f,
		.data = f,
		.ldata = 2*f
	};
	return elem;
}

void print(void *delem)
{
	struct delem *elem = delem;
	printf("-> %d %.2f %ld ", elem->idata, elem->data, elem->ldata);
}

int main()
{
	Stack stack = stack_new(sizeof(struct delem), print);
	for (float i = 5; i < 7.25; i += 0.25) {
		struct delem elem = new_delem(i);
		stack_push(stack, &elem);
	}
	stack_print(stack);
	stack_pop(stack);
	stack_pop(stack);
	stack_pop(stack);
	stack_print(stack);
	stack_pop(stack);
	stack_pop(stack);
	stack_print(stack);
	stack_delete(stack);
	return 0;
}
