/***************************************************
	用顺序表封装队列函数
***************************************************/

#include "queue.h"

void ls(void *data)
{
	printf("%d ", *(int *)data);
}


int main(int argc, char *argv[])
{
	int num = 0, i = 0;
	int *ret = NULL;
	QUEUE *handle = NULL;


	handle = queue_create(sizeof(int), MAX);
	ERRP(NULL == handle, main queue_create handle, goto ERR1);

	queue_clean(handle);

	for (i = 0; i < MAX; i ++)
	{
		num = rand() % 100;
		printf("%d ", num);
		queue_qe(&num, handle);
	}
	printf("\n");

	queue_travel(handle, ls);

	printf("%d ", *(int *)(queue_de(handle)));
	printf("%d ", *(int *)(queue_de(handle)));
	printf("%d ", *(int *)(queue_de(handle)));
	printf("%d ", *(int *)(queue_de(handle)));
	printf("\n");

	for (i = 0; i < MAX; i++)
	{
		ret = (int *)queue_de(handle);
		
		if (NULL == ret)
		{
			printf("NU ");
		}
		else
		{
			printf("%d ", *ret);
		}
	}
	printf("\n");

	return 0;
ERR1:
	return -1;
}



