#include "queue.h"



//队列初始化
QUEUE *queue_create(int size, int max)
{
	QUEUE *handle = NULL;

	handle = (QUEUE *)malloc(sizeof(QUEUE));
	ERRP(NULL == handle, queue_create handle malloc, goto ERR1);

	handle->data = (void *)malloc(size * max);
	ERRP(NULL == handle->data, queue_create handle->data malloc, goto ERR2);

	handle->size = size;
	handle->max = max;
	handle->front = 0;
	handle->end = 0;
	handle->save = NULL;

	return handle;
ERR2:
	free(handle);
ERR1:
	return NULL;
}

//队列数据清零
void queue_clean(QUEUE *handle)
{
	memset(handle->data, 0, handle->size * handle->max);

	return ;
}

//检查队列是否已满，满返回1，不满返回0
int queue_is_full(QUEUE *handle)
{
	if ((handle->end + 1) % handle->max == handle->front)
	{
		return 1;
	}

	return 0;
}

//检查队列是否为空，为空返回1，不为空返回0
int queue_is_empty(QUEUE *handle)
{
	if (handle->front == handle->end)
	{
		return 1;
	}

	return 0;
}

//计算队列中元素个数，返回个数
int queue_num(QUEUE *handle)
{
	if (handle->end > handle->front)
	{
		return handle->end - handle->front;
	}
	else
	{
		return (handle->max - (handle->front - handle->end));
	}
}

//遍历队列中各个数据元素
void queue_travel(QUEUE *handle, queue_op_t *op)
{
	int i = 0, j = 0;

	for (i = handle->front, j = 0; j < queue_num(handle); i++, j++)
	{
		if (i == handle->max)
		{
			i = 0;
		}

		op(handle->data + handle->size * i);
	}
	printf("\n");

	return ;
}


//队列数据入队
void queue_qe(void *data, QUEUE *handle)
{
	if (queue_is_full(handle))
	{
		return ;
	}

	memcpy(handle->data + handle->size * handle->end, data, handle->size);
	handle->end++;

	if (handle->end == handle->max)
	{
		handle->end = 0;
	}

	return ;
}

//队列数据出队
void *queue_de(QUEUE *handle)
{
	void *data;

	if (queue_is_empty(handle))
	{
		return NULL;
	}

	data = (int *)(handle->data + handle->size * handle->front);
	handle->front++;

	if (handle->front == handle->max)
	{
		handle->front = 0;
	}

	return data;
}

//队列数据空间释放
void queue_destory(QUEUE *handle)
{
	free(handle->data);
	free(handle);

	return ;
}

//队列内存空间扩容
void queue_resize(int new_max, QUEUE *handle)
{
	void *new = NULL;

	new = (void *)malloc(handle->size * new_max);
	ERRP(NULL == new, queue_resize new malloc, goto ERR1);

	if (handle->end > handle->front)
	{
		memcpy(new + handle->size * handle->front, handle->data + handle->size * handle->front, handle->size * (handle->end - handle->front));
	}
	else
	{
		memcpy(new, handle->data, handle->size * handle->end);
		memcpy(new + handle->size * (new_max - queue_num(handle) + handle->end), handle->data + handle->size * handle->front, handle->size * (handle->max - handle->front));
	}

	free(handle->data);
	handle->data = new;
	handle->max = new_max;

	return ;
ERR1:
	return ;
}


void queue_store(const char *path, QUEUE *handle)
{
	int i = 0;
	int ret  = 0;
	int count = 0;
	FILE *fp = NULL;

	count = queue_num(handle);

	fp = fopen(path, "w");
	ERRP(NULL == fp, queue_store fopen, goto ERR1);

	ret = fwrite(&handle->size, sizeof(handle->size), 1, fp);
	ERRP(1 != ret, queue_store fwrite handle->size, goto ERR2);

	ret = fwrite(&count, sizeof(count), 1, fp);
	ERRP(1 != ret, queue_store fwrite count, goto ERR2);

	for (i = 0; i < count; i++)
	{
		ret = fwrite(handle->data + handle->size * i, handle->size, 1, fp);
		ERRP(1 != ret, queue_store fwrite handle->data, goto ERR2);
	}

	return ;
ERR2:
	fclose(fp);
ERR1:
	return ;
}




QUEUE *queue_load(const char *path)
{
	FILE *fp = NULL;
	int i = 0;
	int ret = 0;
	int num = 0;
	int size = 0;
	int count = 0;
	QUEUE *handle= NULL;

	fp = fopen(path, "r");
	ERRP(NULL == fp, queue_load fopen, goto ERR1);
	
	ret = fread(&size, sizeof(int), 1, fp);
	ERRP(1 != ret, queue_load fwrite size, goto ERR2);

	ret = fread(&count, sizeof(int), 1, fp);
	ERRP(1 != ret, queue_load fwrite count, goto ERR2);

	handle = (QUEUE *)queue_create(size, count);
	handle->size = size;
	queue_clean(handle);

	for (i = 0; i < count; i++)
	{
		ret = fread(&num, handle->size, 1, fp);
		ERRP(1 != ret, queue_load fwrite handle->data, goto ERR2);
		queue_qe(&num, handle);
	}

	return handle;
ERR2:
	fclose(fp);
ERR1:
	return NULL;
}



