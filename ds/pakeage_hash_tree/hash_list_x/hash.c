/*************************************************
	用链表封装哈希表
	表头采用顺序表，哈希表采用有头双向循环链表

*************************************************/

#include "hash.h"

//哈希表数据取模
int hash_mod(void *data)
{
	return (*(int *)data) % MAX;
}

//哈希表初始化
HASH *hash_create(int size, int max)
{
	HASH *handle = NULL;
	int i = 0;

	handle = (HASH *)malloc(sizeof(HASH));
	ERRP(NULL == handle, hash_create handle malloc, goto ERR1);

	handle->head = (struct node_t *)malloc(sizeof(struct node_t) * max);
	ERRP(NULL == handle->head, hash_create handle->head malloc, goto ERR2);

	for (i = 0; i < max; i++)
	{
		handle->head[i].data = NULL;
		handle->head[i].next = &handle->head[i];
		handle->head[i].prev = &handle->head[i];
	}

	handle->size = size;
	handle->count = max;

	return handle;
ERR2:
	free(handle);
ERR1:
	return NULL;
}

//在哈希表中插入数据
void hash_insert(void *data, HASH *handle)
{
	int i = 0;
	struct node_t *new = NULL;

	i = hash_mod(data);

	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(NULL == new, hash_insert new malloc, goto ERR1);

	new->data = (void *)malloc(handle->size);
	ERRP(NULL == new->data, hash_insert new->data malloc, goto ERR2);

	memcpy(new->data, data, handle->size);

	//尾插
	new->prev = handle->head[i].prev;
	new->next = &handle->head[i];
	handle->head[i].prev->next = new;
	handle->head[i].prev = new;

	return ;
ERR2:
	free(new);
ERR1:
	return ;
}

//按索引进行查找
void *hash_find(void *key, HASH *handle, hash_cmp_t *cmp)
{
	int tmp = 0;
	struct node_t *tail = NULL;

	tmp = hash_mod(key);

	for (tail = handle->head[tmp].next; tail != &handle->head[tmp]; tail = tail->next)
	{
		if (!cmp(key, tail->data))
		{
			return tail;
		}
	}

	printf("Data no found!\n");

	return NULL;
}

//遍历各个节点并打印节点数据
void hash_travel(HASH *handle, hash_op_t *op)
{
	int i = 0;
	struct node_t *tail = NULL;

	for (i = 0; i < handle->count; i++)
	{
		printf("%d : ", i);

		for (tail = handle->head[i].next; tail != &handle->head[i]; tail = tail->next)
		{
			op(tail->data);
		}
		printf("\n");
	}

	return ;
}

//释放各节点内存空间
void hash_destory(HASH *handle)
{
	int i = 0;
	struct node_t *tail = NULL;
	struct node_t *save = NULL;

	for (i = 0; i < handle->count; i++)
	{
		for (tail = handle->head[i].next; tail != &handle->head[i]; tail = save)
		{
			save = tail->next;

			free(tail->data);
			free(tail);
		}
	}

	free(handle->head);
	free(handle);
	
	return ;
}


