/**********************************************************
	用有头双向循环链表，实现队列的封装
	2016.05.15
**********************************************************/

#include "queue.h"

QUEUE_LIST *queue_create(int size)
{
	QUEUE_LIST *handle = NULL;

	handle = (QUEUE_LIST *)malloc(sizeof(QUEUE_LIST));
	ERRP(NULL == handle, queue_create handle malloc, goto ERR1);


	handle->size = size;
	handle->count = 0;

	handle->head.data = NULL;

	handle->head.next = &handle->head;
	handle->head.prev = &handle->head;
	
	return handle;
ERR1:
	return NULL;
}


int queue_num(QUEUE_LIST *handle)
{
	return handle->count;
}



int queue_is_empty(QUEUE_LIST *handle)//判断是否是空队列
{
	if (handle->count == 0)
	{
		return 1;
	}

	return 0;
}


//入队在链表结尾添加节点
void queue_qe(void *data, QUEUE_LIST *handle)
{
	struct node_t *new = NULL;

	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(NULL == new, queue_qe new malloc, goto ERR1);

	new->data = (struct node_t *)malloc(handle->size);
	ERRP(NULL == new, queue_qe new->data malloc, goto ERR2);

	memcpy(new->data, data, handle->size);

	new->next = &handle->head;
	new->prev = handle->head.prev;
	handle->head.prev->next = new;
	handle->head.prev = new;

	handle->count++;

	return ;
ERR2:
	free(new);
ERR1:
	return ;
}


//出对删除链表开始头节点后的节点
void *queue_de(QUEUE_LIST *handle)
{
	void *data = NULL;
	struct node_t *tail = NULL;

	if (queue_is_empty(handle))
	{
		return NULL;
	}

	data = (void *)malloc(handle->size);
	ERRP(NULL == data, queue_de data malloc, goto ERR1);

	tail = handle->head.next;
	memcpy(data, tail->data, handle->size);

	tail->next->prev = &handle->head;
	handle->head.next = tail->next;
	handle->count--;
	free(tail->data);
	free(tail);

	return data;
ERR1:
	return NULL;
}


//从栈底到栈顶遍历打印
void queue_travel(QUEUE_LIST *handle, queue_op_t *op)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		op(tail->data);
	}
	printf("\n");
}


void queue_destory(QUEUE_LIST *handle)
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



void queue_store(const char *path, QUEUE_LIST *handle)
{
	FILE *fp = NULL;
	int ret = 0;
	struct node_t *tail = NULL;

	fp = fopen(path, "w");
	ERRP(NULL == fp, queue_store fopen, goto ERR1);
	
	ret = fwrite(&handle->size, sizeof(int), 1, fp);
	ERRP(1 != ret, queue_store fwrite handle->size, goto ERR2);

	ret = fwrite(&handle->count, sizeof(int), 1, fp);
	ERRP(1 != ret, queue_store fwrite handle->top, goto ERR2);

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		ret = fwrite(tail->data, handle->size, 1, fp);
		ERRP(1 != ret, queue_store fwrite handle->data, goto ERR2);
	}

	fclose(fp);

	return ;
ERR2:
	fclose(fp);
ERR1:
	return ;
}



QUEUE_LIST *queue_load(const char *path)
{
	FILE *fp = NULL;
	int ret = 0;
	int size = 0;
	int count = 0;
	int num = 0;
	int i = 0;
	QUEUE_LIST *handle = NULL;


	fp = fopen(path, "r");
	ERRP(NULL == fp, stcak_load fopen, goto ERR1);

	ret = fread(&size, sizeof(int), 1, fp);
	ERRP(1 != ret, queue_load fread size, goto ERR2);

	ret = fread(&count, sizeof(int), 1, fp);
	ERRP(1 != ret, queue_load fread count, goto ERR2);

	handle = (QUEUE_LIST *)queue_create(size);

	for (i = 0; i < count; i++)
	{
		ret = fread(&num, size, 1, fp);
		ERRP(1 != ret, queue_load fread num, goto ERR2);
		queue_qe(&num, handle);
	}

	fclose(fp);
	
	return handle;
ERR2:
	fclose(fp);
ERR1:
	return NULL;
}













