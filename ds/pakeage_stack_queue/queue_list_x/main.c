/**********************************************************
	用有头双向循环链表，实现队列的封装
	2016.05.15

**********************************************************/


#include "queue.h"


struct data_t
{
	int num;
};

void ls(void *data)
{
	printf("%d ", *(int *)data);
}


int main(void)
{
	int i = 0;
	int num = 0;
	void *ret = NULL;
	QUEUE_LIST *handle = NULL;

	handle = queue_create(sizeof(struct data_t));
	ERRP(NULL == handle, main queue_create handle, goto ERR1);

	for (i = 0; i < MAX; i++)
	{
		num = rand() % 100;
		printf("i = %d, num = %d\n", i, num);
		queue_qe(&num, handle);
	}


	queue_store("./queue_data.db", handle);

	queue_travel(handle, ls);

    /*
	 *handle = queue_load("./queue_data.db");
	 *queue_travel(handle, ls);
     */
	printf("queue_de: %d\n", *(int *)queue_de(handle));
	printf("queue_de: %d\n", *(int *)queue_de(handle));
	printf("queue_de: %d\n", *(int *)queue_de(handle));

	for (i = 0; i < MAX; i++)
	{
		ret = queue_de(handle);
		if (NULL == ret)
		{
			printf("NU ");
		}
		else
		{
			num = *(int *)ret;
			printf("de: i = %d, num = %d\n", i, num);
		}
	}
	printf("\n");


	queue_destory(handle);


	return 0;
ERR1:
	return -1;
}


