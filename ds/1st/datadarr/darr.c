#include "darr.h"


//初始化
DARR *darr_create(int size)
{
	DARR *handle = NULL;

	handle = (DARR *)malloc(sizeof(DARR));
	ERRP(handle == NULL, "malloc", goto ERR1);

	handle->data = NULL;
	handle->size = size;
	handle->num = 0;

	return handle;
ERR1:
	return NULL;
}

//尾插
int darr_append(void *data, DARR *handle)
{
	void *new = NULL;

	ERRP(data == NULL, "darr_append argument", goto ERR1);

	new = (void *)malloc(handle->size * (handle->num + 1));
	if (new == NULL)
	{
		return -1;
	}

	memcpy(new, handle->data, handle->size * handle->num);
	memcpy(new + handle->size * handle->num, data, handle->size);
	free(handle->data);
	handle->data = new;
	handle->num++;
	
	return 0;
ERR1:
	return -1;
}

//头插
int darr_prepend(void *data, DARR *handle)
{
	void *new = NULL;

	ERRP(data == NULL, "darr_prepend argument", goto ERR1);

	new = (void *)malloc(handle->size * (handle->num + 1));
	if (new == NULL)
	{
		return -1;
	}

	memcpy(new, data, handle->size);
	memmove(new + handle->size, handle->data, handle->size * handle->num);
	free(handle->data);
	handle->data = new;
	handle->num++;
	
	return 0;
ERR1:
	return -1;
}

int darr_index_insert(int index, void *data, DARR *handle)
{
	void *new = NULL;

	ERRP(data == NULL, "darr_index_insert argument", goto ERR1);

	new = (void *)malloc(handle->size * (handle->num + 1));
	if (new == NULL)
	{
		return -1;
	}

	memcpy(new, handle->data, handle->size * index);
	memcpy(new + handle->size * (index), data, handle->size);
	memcpy(new + handle->size * (index + 1), handle->data + handle->size * index, handle->size * (handle->num - index));

	free(handle->data);
	handle->data = new;
	handle->num++;
	
	return 0;
ERR1:
	return -1;
}

//指定位置插入
int my_darr_index_insert(int index, void *data, DARR *handle)
{
	void *new = NULL;

	ERRP(data == NULL, "darr_index_insert argument", goto ERR1);

	new = (void *)malloc(handle->size * (handle->num + 1));
	if (new == NULL)
	{
		return -1;
	}

	if (handle->num < index)
	{
		memcpy(new, handle->data, handle->size * handle->num);
		memcpy(new + handle->size * handle->num, data, handle->size);
	}
	else
	{
		memcpy(new, handle->data, handle->size * index);
		memcpy(new + handle->size * (index), data, handle->size);
		memcpy(new + handle->size * (index + 1), handle->data + handle->size * index, handle->size * (handle->num - index));
	}
	free(handle->data);
	handle->data = new;
	handle->num++;
	
	return 0;
ERR1:
	return -1;
}

//求数据个数
int darr_count(DARR *handle)
{
	return handle->num;
}

//左移
void darr_left(int bit, DARR *handle)
{
	void *new = NULL;
	
	if (bit < 0 || bit > handle->num)
	{
		printf("Error num (0 < bit < %d)\n", handle->num);
		return ;
	}

	new = (void *)malloc(handle->size * handle->num);
	ERRP(NULL == new, "Malloc new", goto ERR1);

	memcpy(new, handle->data + handle->size * bit, handle->size * (handle->num - bit));
	memcpy(new + handle->size * (handle->num - bit), handle->data, handle->size * bit);

	free(handle->data);
	handle->data = new;

ERR1:
	return ;
}

//右移
void darr_right(int bit, DARR *handle)
{
	void *new = NULL;
	
	if (bit < 0 || bit > handle->num)
	{
		printf("Error num (0 < bit < %d)\n", handle->num);
		return ;
	}

	new = (void *)malloc(handle->size * handle->num);
	ERRP(NULL == new, "Malloc new", goto ERR1);

	memcpy(new, handle->data + handle->size * (handle->num - bit), handle->size * bit);
	memcpy(new + handle->size * bit, handle->data, handle->size * (handle->num - bit));

	free(handle->data);
	handle->data = new;

ERR1:
	return ;
}

//按关键字查找，并删除找到的第一组数据
void darr_del(void *key, DARR *handle, darr_cmp_t *cmp)
{
	void *new = NULL;
	int i = 0;

	for (i = 0; i < handle->num; i++)
	{
		if (0 == cmp(key, handle->data + handle->size * i))
		{
			new = (void *)malloc(handle->size * (handle->num - 1));
			ERRP(NULL == new, "Malloc new", goto ERR1);
			
			memcpy(new, handle->data, handle->size * i);
			memcpy(new + handle->size * i, handle->data + handle->size * (i + 1), handle->size * (handle->num - i - 1));

			free(handle->data);
			handle->data = new;
			handle->num--;
			
			return ;	
		}
	}

ERR1:
	return ;
}

//按关键字查找，并删除找到的所有匹配数据
void darr_alldel(void *key, DARR *handle, darr_cmp_t *cmp)
{
	void *new = NULL;
	int i = 0;

	for (i = 0; i < handle->num; i++)
	{
		while (0 == cmp(key, handle->data + handle->size * i))
		{
			new = (void *)malloc(handle->size * (handle->num - 1));
			ERRP(NULL == new, "Malloc new", goto ERR1);
			
			memcpy(new, handle->data, handle->size * i);
			memcpy(new + handle->size * i, handle->data + handle->size * (i + 1), handle->size * (handle->num - i - 1));

			free(handle->data);
			handle->data = new;
			handle->num--;
		}
	}

ERR1:
	return ;
}

//指定位置删除
void darr_index_del(int index, DARR *handle)
{
	void *new = NULL;
	int i = 0;

	if (index < 0 || index > handle->num)
	{
		printf("Index num error!\n");
		return ;
	}

	for (i = 0; i < handle->num; i++)
	{
		if (index == i)
		{
			new = (void *)malloc(handle->size * (handle->num - 1));
			ERRP(NULL == new, "Malloc new", goto ERR1);
			
			memcpy(new, handle->data, handle->size * i);
			memcpy(new + handle->size * i, handle->data + handle->size * (i + 1), handle->size * (handle->num - i - 1));

			free(handle->data);
			handle->data = new;
			handle->num--;
		}
	}

ERR1:
	return ;
}

//按关键字查找第一个
void *darr_ind(void *key, DARR *handle, darr_cmp_t *cmp)
{
	void *new = NULL;
	int i = 0;

	for (i = 0; i < handle->num; i++)
	{
		if (0 == cmp(key, handle->data + handle->size * i))
		{
			new = (void *)malloc(handle->size);
			ERRP(NULL == new, "Malloc new", goto ERR1);
			
			memcpy(new, handle->data + handle->size * i, handle->size);

			free(handle->data);
			handle->data = new;

			return new;
		}
	}

ERR1:
	return NULL;
}


//按关键字查找所有数据
/*
 *DARR *darr_all_find(void *key, DARR *handle, darr_cmp_t *cmp)
 *{
 *    DARR *new = NULL;
 *    int i = 0, j = 0;
 *    new = darr_create(handle->size);
 *
 *    for (i = 0; i < handle->num; i++)
 *    {
 *        if (0 == cmp(key, handle->data + handle->size * i))
 *        {
 *            
 *            new = (void *)malloc(handle->size * (j + 1));
 *            ERRP(NULL == new, "Malloc new", goto ERR1);
 *
 *            memcpy(new + handle->size * j, handle->data + handle->size * i, handle->size);
 *
 *            j++;
 *
 *        }
 *    }
 *    return new;
 *
 *ERR1:
 *    return NULL;
 *}
 */

//遍历函数
void darr_travel(DARR *handle, darr_op_t *op)
{
	int i;
	for (i = 0; i < handle->num; i++)
	{
		op(handle->data + i * handle->size);
	}
}
//销毁函数
void darr_destroy(DARR *handle)
{
	free(handle->data);
	free(handle);
}








