#include "stack.h"

STACK *stack_create(int size, int max)
{
	STACK *handle = NULL;

	handle = (STACK *)malloc(sizeof(STACK));
	ERRP(NULL == handle, "malloc", goto ERR1);

	handle->data = (void *)malloc(size * max);
	ERRP(NULL == handle->data, "malloc data", goto ERR2);

	memset(handle->data, 0, size * max);

	handle->size = size;
	handle->max = max;
	handle->top = 0;

	return handle;
ERR2:
	free(handle);
ERR1:	
	return NULL;
}
int stack_is_full(STACK *handle)
{
	if (handle->top == handle->max)
		return 1;
	return 0;
}
int stack_is_empty(STACK *handle)
{
	if (handle->top == 0)
		return 1;
	return 0;
}
void stack_push(void *data, STACK *handle)
{
	if (stack_is_full(handle))
		return ;
	memcpy(handle->data + handle->size * handle->top, data, handle->size);
	handle->top++;
	
	return ;
}

void *stack_pop(STACK *handle)
{
	void *data = NULL;

	if (stack_is_empty(handle))
		return NULL;

	data = (void *)malloc(handle->size);
	ERRP(data == NULL, "malloc_pop", goto ERR1);

	handle->top--;

	memcpy(data, handle->data + handle->size * handle->top, handle->size);

	return data;
ERR1:
	return NULL;
}
void stack_travel(STACK *handle, stack_op_t *op)
{
	int i;

	for (i = 0; i < handle->top; i++)
	{
		op(handle->data + handle->size * i);
	}
	printf("\n");
}
void stack_destroy(STACK *handle)
{
	free(handle->data);
	free(handle);
}
