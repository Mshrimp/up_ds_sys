#include "hash.h"


void ls(void *data)
{
	printf("%d ", *(int *)data);
}

int cmp_int(void *key, void *data)
{
	return ((*(int *)key) - (*(int *)data));
}

void hash_init(int *arr)
{
	int i = 0;

	for (i = 0; i < MAX; i++)
	{
		arr[i] = rand() % 100;
	}

	return ;
}


void hash_show_arr(int *arr)
{
	int i = 0;

	for (i = 0; i < MAX; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	return ;
}


int main(void)
{
	int arr[MAX] = {};
	int i = 0;
	int key = 0;
	HASH *handle = NULL;
	struct node_t *find = NULL;

	handle = hash_create(sizeof(int), MAX);
	

	hash_init(arr);
	hash_show_arr(arr);
	
	for (i = 0; i < MAX; i++)
	{
		hash_insert(&arr[i], handle);
	}
	
	hash_travel(handle, ls);

	printf("Please input a key to find:");
	scanf("%d", &key);

	find = (struct node_t *)hash_find(&key, handle, cmp_int);
	ERRP(NULL == find, main hash_find, goto ERR1);
	printf("(*((int *)find->data)) = %d\n", (*((int *)find->data)));

	hash_destory(handle);

	return 0;
ERR1:
	return -1;
}


