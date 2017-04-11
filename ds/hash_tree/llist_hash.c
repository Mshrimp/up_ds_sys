#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20
//"tom" ->  (t + o + m) % MAX
//"jim" -> 
//"mary" -> 
struct cls_t{
	char name[128];
};
struct node_t{
	void *data;
	struct node_t *next;
	struct node_t *prev;
};

typedef struct llist_t{
	struct node_t *head;// size * count
	int size;
	int num;
}HASH;

void arr_rand(int *arr)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		arr[i] = rand() % 100;
	}
}

void arr_display(int *arr)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int hash(void *data)
{
	return (*(int *)data) % MAX;
}
void ls(void *data)
{
	printf("%d ", *(int *)data);
}
//初始化
HASH *hash_create(int size, int max)
{
	HASH *handle = NULL;
	int i;

	handle = (HASH *)malloc(sizeof(HASH));
	if (NULL == handle)
	{
		return NULL;
	}
	//顺序表
	handle->head = (struct node_t *)malloc(max * sizeof(struct node_t));
	if (handle->head == NULL)
	{
		free(handle);
		return NULL;
	}

	for (i = 0; i < max; i++)
	{
		/*memset(handle->head[i].data, 0, size);*/
		handle->head[i].data = NULL;
		handle->head[i].next = &handle->head[i];
		handle->head[i].prev = &handle->head[i];
	}

	handle->size = size;
	handle->num = max;
	return handle;
}

void hash_insert(void *data, HASH *handle)
{
	int tmp;
	struct node_t *new = NULL;

	tmp = hash(data);

    /*
	 *printf("handle->size = %d handle->num = %d\n", handle->size, handle->num);
	 *printf("hello!tmp = %d data = %d\n", tmp, *(int *)data);
     */
	new = (struct node_t *)malloc(sizeof(struct node_t));
	if (new == NULL)
	{
		return ;
	}
	new->data = (void *)malloc(handle->size);
	if (new->data == NULL)
	{
		return ;
	}

	memmove(new->data, data, handle->size);

	//尾插
	new->next = &handle->head[tmp];
	new->prev = handle->head[tmp].prev;
	handle->head[tmp].prev->next = new;
	handle->head[tmp].prev = new;

	return ;
}


void hash_travel(HASH*handle , void (*op)(void *))
{
	int i;
	struct node_t *tail = NULL;

	for (i = 0;i < handle->num; i++)
	{
		printf("%d : ", i);
		for (tail = handle->head[i].next; tail != &handle->head[i]; tail = tail->next)
		{
			op(tail->data);
		}
		printf("\n");
	}
}
int main(void)
{
	HASH *handle = NULL;
	int i, num;
	
	handle = hash_create(sizeof(int), MAX);
	if (handle == NULL)
	{
		return -1;
	}

	for (i = 0;i < MAX; i++)
	{
		num = rand() % 100;
		hash_insert(&num, handle);
	}

	hash_travel(handle, ls);
	return 0;
}
