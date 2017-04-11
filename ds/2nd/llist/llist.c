#include "llist.h"

LLIST *llist_create(int size)
{
	LLIST *handle = NULL;

	handle = (LLIST *)malloc(sizeof(LLIST));
	ERRP(handle == NULL, malloc, goto ERR1);

	handle->size = size;
	handle->num = 0;
	
	handle->head.data = NULL;
	//使链表循环
	handle->head.next = &handle->head;
	handle->head.prev = &handle->head;

	return handle;
ERR1:
	return NULL;
}

static void _insert(void *data, int index, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail = NULL;
	struct node_t *new = NULL;


	if (index == LLIST_APPEND_INSERT)
	{
		tail = handle->head.prev;
	}
	else if (index == LLIST_PREPEND_INSERT)
	{
		tail = &handle->head;
	}
	else if (index == LLIST_SORT_INSERT)
	{
		for (tail = &handle->head; tail->next != &handle->head && cmp(data, tail->data) > 0; tail = tail->next)
			;
	}
	else
	{
		for (tail = &handle->head; tail->next != &handle->head && index--; tail = tail->next)
			;
	}

	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(new == NULL, malloc_new, goto ERR1);
	
	new->data = (void *)malloc(handle->size);
	ERRP(new->data == NULL, malloc_data, goto ERR2);

	memcpy(new->data, data, handle->size);

	//tail

	new->next = tail->next;
	new->prev = tail;
	tail->next->prev = new;
	tail->next = new;
	handle->num++;
	return ;
ERR2:
	free(new);
ERR1:
	return ;
}
//插入数据的结尾
void llist_append(void *data, LLIST *handle)
{
	_insert(data, LLIST_APPEND_INSERT, NULL, handle);
	//定义一个节点信息
/*
 *    struct node_t *new = NULL;
 *
 *    ERRP(data == NULL, llist_append, goto ERR1);
 *
 *    new = (struct node_t *)malloc(sizeof(struct node_t));
 *    ERRP(new == NULL, malloc_new, goto ERR1);
 *
 *    new->data = (void *)malloc(handle->size);
 *    ERRP(NULL == new->data, malloc_data, goto ERR2);
 *
 *    //表示把用户接受数据保存到链表节点信息中。
 *    memcpy(new->data, data, handle->size);
 *    //节点插入到头中
 *    
 *    new->next = &handle->head;
 *    new->prev = handle->head.prev;
 *    handle->head.prev->next = new;
 *    handle->head.prev = new;
 *    handle->num++;
 *    
 *    return ;
 *ERR2:
 *    free(new);
 *ERR1:
 *    return ;
 */
}

//数据插入到头的后面
void llist_prepend(void *data, LLIST *handle)
{
	_insert(data, LLIST_PREPEND_INSERT, NULL, handle);
/*
 *    struct node_t *new = NULL;
 *
 *    new = (struct node_t *)malloc(sizeof(struct node_t));
 *    ERRP(new == NULL, malloc_new, goto ERR1);
 *
 *    new->data = (void *)malloc(handle->size);
 *    ERRP(new->data == NULL, malloc_data, goto ERR2);
 *
 *    memcpy(new->data, data, handle->size);
 *
 *    new->next = handle->head.next;
 *    new->prev = &handle->head;
 *    handle->head.next->prev = new;
 *    handle->head.next = new;
 *    handle->num++;
 *
 *    return ;
 *ERR2:
 *    free(new);
 *ERR1:
 *    return ;
 */
}
//指定位置插入
void llist_index_insert(int index, void *data, LLIST *handle)
{
	struct node_t *tail = NULL;
	struct node_t *new = NULL;
	
	ERRP(index < 0 || index > handle->num, llist_index_err, goto ERR1);


	for (tail = &handle->head; tail->next != &handle->head && index--; tail = tail->next)
		;

	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(new == NULL, malloc_new, goto ERR1);

	new->data = (void *)malloc(handle->size);
	ERRP(new->data == NULL, malloc_data, goto ERR2);

	memcpy(new->data, data, handle->size);

	new->next = tail->next;
	new->prev = tail;
	tail->next->prev = new;
	tail->next = new;
	handle->num++;

	return ;
ERR2:
	free(new);
ERR1:
	return ;
}
//插入排序
void llist_sort_insert(void *data, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail = NULL, *new = NULL;

	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(new == NULL, malloc_new, goto ERR1);

	new->data = (void *)malloc(handle->size);
	ERRP(new->data == NULL, malloc_data, goto ERR2);

	memcpy(new->data, data, handle->size);

	for (tail = &handle->head; tail->next != &handle->head; tail = tail->next)
	{
		if (cmp(new->data, tail->next->data) < 0)
		{
			break;
		}
	}

	new->next = tail->next;
	new->prev = tail;
	tail->next->prev = new;
	tail->next = new;
	handle->num++;

	return ;
ERR2:
	free(new);
ERR1:
	return ;
}
//删除匹配第一个信息
void llist_del(void *key, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(key, tail->data) == 0)
		{
			tail->next->prev = tail->prev;
			tail->prev->next = tail->next;
			free(tail->data);
			free(tail);
			handle->num--;
			return ;
		}
	}

	return ;
}
//删除所有
void llist_alldel(void *key, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail = NULL, *save = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = save)
	{
		save = tail->next;
		if (cmp(key, tail->data) == 0)
		{
			tail->next->prev = tail->prev;
			tail->prev->next = tail->next;
			free(tail->data);
			free(tail);
			handle->num--;
		}
	}

	return ;
}
//查找匹配第一个信息
void *llist_ind(void *key, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(key, tail->data) == 0)
		{
			return tail->data;
		}
	}
	return NULL;
}
//查找所有匹配信息
LLIST *llist_find(void *key, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail = NULL;
	LLIST *ind = NULL;

	ind = llist_create(handle->size);
	ERRP(ind == NULL, llist_create, goto ERR1);

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(key, tail->data) == 0)
		{
			llist_append(tail->data, ind);
		}
	}
	return ind;
ERR1:	
	return NULL;
}
//指定位置查找
void *llist_index_find(int index, LLIST *handle)
{
	int i;
	struct node_t *tail = handle->head.next;

	for (i = 0; i < handle->num && tail != &handle->head; i++, tail = tail->next)
	{
		if (i == index)
		{
			return tail->data;
		}
	}

	return NULL;
}
//排序
void llist_sort(int flag, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail_i = NULL, *tail_j = NULL;
	void *tmp = NULL;

	for (tail_i = handle->head.next; tail_i->next != &handle->head; tail_i = tail_i->next)
	{
		for (tail_j = tail_i->next; tail_j != &handle->head; tail_j = tail_j->next)
		{
			if ((flag == LLIST_SORT_DASC && cmp(tail_i->data, tail_j->data) < 0) || (flag == LLIST_SORT_ASC && cmp(tail_i->data, tail_j->data) > 0))
			{
				tmp = tail_i->data;
				tail_i->data = tail_j->data;
				tail_j->data = tmp;
			}
		}
	}
}
//存储
int llist_store(const char *path, LLIST *handle)
{
	FILE *fp = NULL;
	struct node_t *tail = NULL;
	int ret;

	fp = fopen(path, "w");
	ERRP(fp == NULL, fopen, goto ERR1);

	//size -> file
	ret = fwrite(&handle->size, sizeof(handle->size), 1, fp);
	ERRP(ret != 1, fwrite_size, goto ERR2);

	//num -> file
	ret = fwrite(&handle->num, sizeof(handle->num), 1, fp);
	ERRP(ret != 1, fwrite_num, goto ERR2);

	//data ->file
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		ret = fwrite(tail->data, handle->size, 1, fp);
		ERRP(ret != 1, fwrite_data, goto ERR2);
	}
	
	fclose(fp);
	return 0;
ERR2:
	fclose(fp);
ERR1:
	return -1;
}
//加载
LLIST *llist_load(const char *path)
{
	LLIST *handle = NULL;
	FILE *fp = NULL;
	int i, ret, size, num;
	void *tmp = NULL;

	/*printf("hello!\n");*/
	fp = fopen(path, "r");
	ERRP(fp == NULL, fopen, goto ERR1);

	ret = fread(&size, sizeof(size), 1, fp);
	ERRP(ret != 1, fread_size, goto ERR2);

	ret = fread(&num, sizeof(num), 1, fp);
	ERRP(ret != 1, fread_num, goto ERR2);

	/*printf("size = %d num = %d\n", size, num);*/
	handle = llist_create(size);
	ERRP(handle == NULL, llist_create, goto ERR2);

	tmp = (void *)malloc(size);
	ERRP(tmp == NULL, malloc_tmp, goto ERR3);

	for (i = 0; i < num; i++)
	{
		ret = fread(tmp, size, 1, fp);
		ERRP(ret != 1, fread_data, goto ERR4);
		llist_append(tmp, handle);
	}
	fclose(fp);
	return handle;
ERR4:
	free(tmp);
ERR3:
	free(handle);
ERR2:
	fclose(fp);
ERR1:
	return NULL;
}
//遍历
void llist_travel(LLIST *handle, llist_op_t *op, char **name)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		op(tail->data, name);
	}
}

void llist_destroy(LLIST *handle, LLIST *op)
{
	struct node_t *tail = NULL;
	struct node_t *save = NULL;

	if (op != NULL)
	{
		for (tail = op->head.next; tail != &op->head; tail = save)
		{
			save = tail->next;
			free(tail->data);
			free(tail);
		}
		free(op);
	}
	for (tail = handle->head.next; tail != &handle->head; tail = save)
	{
		save = tail->next;
		free(tail->data);
		free(tail);
	}
	free(handle);
}
