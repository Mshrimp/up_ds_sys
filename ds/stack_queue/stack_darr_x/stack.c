#include "stack.h"


STACK *stack_create(int size, int max)//初始化
{
	STACK *handle = NULL;
	
	handle = (STACK *)malloc(sizeof(STACK));
	ERRP(NULL == handle, stack_create handle malloc, goto ERR1);

	handle->data = (void *)malloc(size * max);
	ERRP(NULL == handle->data, stack_create handle->data malloc, goto ERR2);

	handle->size = size;
	handle->max = max;
	handle->top = 0;
	handle->save = NULL;

	return handle;
ERR2:
	free(handle);
ERR1:
	return NULL;
}


int stack_is_full(STACK *handle)//判断是否满栈
{
	if (handle->top == handle->max)
	{
		return 1;
	}

	return 0;
}


int stack_is_empty(STACK *handle)//判断是否是空栈
{
	if (handle->top == 0)
	{
		return 1;
	}

	return 0;
}


int stack_num(STACK *handle)//求栈长度
{
	return handle->top;
}



int stack_clean(STACK *handle)//栈清空
{
	memset(handle->data, 0, handle->size * handle->max);

	return 0;
}



void stack_resize(int new_max, STACK *handle)//栈扩容
{
	void *new = NULL;

	new = (void *)malloc(handle->size * new_max);
	ERRP(NULL == new, stack_resize new malloc, goto ERR1);

	memcpy(new, handle->data, handle->size * handle->max);
	free(handle->data);
	handle->data = new;
	handle->max = new_max;

	return ;
ERR1:
	return ;
}


void stack_push(void *data, STACK *handle)//入栈
{
	if (stack_is_full(handle))
	{
		return ;
	}

	memcpy(handle->data + handle->size * handle->top, data, handle->size);
	handle->top++;

	return ;
}


void *stack_pop(STACK *handle)//出栈
{
	void *data = NULL;

	if (stack_is_empty(handle))
	{
		return NULL;
	}

	data = (void *)malloc(handle->size);
	ERRP(NULL == data, stack_pop data malloc, goto ERR1);

	handle->top--;

	memcpy(data, handle->data + handle->size * handle->top, handle->size);

	memset(handle->data + handle->size * handle->top, 0, handle->size);

    /*
	 *handle->top--;
	 *data = handle->data + handle->size * handle->top;
	 *handle->save = data;
     */

	return data;
ERR1:
	return NULL;
}


void stack_travel(STACK *handle, stack_op_t *op)//遍历
{
	int i = 0;

	for (i = 0; i < handle->top; i++)
	{
		op(handle->data + handle->size * i);
	}
	printf("\n");

	return ;
}


void stack_destory(STACK *handle)//销毁
{
	free(handle->data);
	free(handle);

	return ;
}


void stack_store(const char *path, STACK *handle);//存储
STACK *stack_load(const char *path);//加载


