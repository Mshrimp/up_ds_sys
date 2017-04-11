/**********************************************************
	用有头双向循环链表，实现栈的封装
	2016.05.15
**********************************************************/

#include "stack.h"

STACK_LIST *stack_create(int size)
{
	STACK_LIST *handle = NULL;

	handle = (STACK_LIST *)malloc(sizeof(STACK_LIST));
	ERRP(NULL == handle, stack_create handle malloc, goto ERR1);


	handle->size = size;
	handle->top = 0;

	handle->head.data = NULL;

	handle->head.next = &handle->head;
	handle->head.prev = &handle->head;
	
	return handle;
ERR1:
	return NULL;
}


int stack_num(STACK_LIST *handle)
{
	return handle->top;
}



int stack_is_empty(STACK_LIST *handle)//判断是否是空栈
{
	if (handle->top == 0)
	{
		return 1;
	}

	return 0;
}



void stack_push(void *data, STACK_LIST *handle)
{
	struct node_t *new = NULL;

	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(NULL == new, stack_push new malloc, goto ERR1);

	new->data = (struct node_t *)malloc(handle->size);
	ERRP(NULL == new, stack_push new->data malloc, goto ERR2);

	memcpy(new->data, data, handle->size);

	new->next = handle->head.next;
	new->prev = &handle->head;
	handle->head.next->prev = new;
	handle->head.next = new;

	handle->top++;

	return ;
ERR2:
	free(new);
ERR1:
	return ;
}



void *stack_pop(STACK_LIST *handle)
{
	void *data = NULL;
	struct node_t *tail = NULL;

	if (stack_is_empty(handle))
	{
		return NULL;
	}

	data = (void *)malloc(handle->size);
	ERRP(NULL == data, stack_pop data malloc, goto ERR1);

	memcpy(data, handle->head.next->data, handle->size);

	tail = handle->head.next;
	tail->next->prev = &handle->head;
	handle->head.next = tail->next;
	handle->top--;
	free(tail->data);
	free(tail);

	return data;
ERR1:
	return NULL;
}


//从栈底到栈顶遍历打印
void stack_travel(STACK_LIST *handle, stack_op_t *op)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.prev; tail != &handle->head; tail = tail->prev)
	{
		op(tail->data);
	}
	printf("\n");
}


void stack_destory(STACK_LIST *handle)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.prev; tail != &handle->head; tail = tail->prev)
	{
		free(tail->data);
		free(tail);
	}	
	free(handle);

	return ;
}



void stack_store(const char *path, STACK_LIST *handle)
{
	FILE *fp = NULL;
	int i = 0;
	int ret = 0;
	struct node_t *tail = NULL;

	fp = fopen(path, "w");
	ERRP(NULL == fp, stack_store fopen, goto ERR1);
	
	ret = fwrite(&handle->size, sizeof(int), 1, fp);
	ERRP(1 != ret, stack_store fwrite handle->size, goto ERR2);

	ret = fwrite(&handle->top, sizeof(int), 1, fp);
	ERRP(1 != ret, stack_store fwrite handle->top, goto ERR2);

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		ret = fwrite(tail->data, handle->size, 1, fp);
		ERRP(1 != ret, stack_store fwrite handle->data, goto ERR2);
	}

	fclose(fp);

	return ;
ERR2:
	fclose(fp);
ERR1:
	return ;
}



STACK_LIST *stack_load(const char *path)
{
	FILE *fp = NULL;
	int ret = 0;
	int size = 0;
	int count = 0;
	int num = 0;
	int i = 0;
	STACK_LIST *handle = NULL;


	fp = fopen(path, "r");
	ERRP(NULL == fp, stcak_load fopen, goto ERR1);

	ret = fread(&size, sizeof(int), 1, fp);
	ERRP(1 != ret, stack_load fread size, goto ERR2);

	ret = fread(&count, sizeof(int), 1, fp);
	ERRP(1 != ret, stack_load fread count, goto ERR2);

	handle = (STACK_LIST *)stack_create(size);

	for (i = 0; i < count; i++)
	{
		ret = fread(&num, size, 1, fp);
		ERRP(1 != ret, stack_load fread num, goto ERR2);
		stack_push(&num, handle);
	}

	fclose(fp);
	
	return handle;
ERR2:
	fclose(fp);
ERR1:
	return NULL;
}













