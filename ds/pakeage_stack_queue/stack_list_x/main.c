/**********************************************************
	用有头双向循环链表，实现栈的封装
	2016.05.15

**********************************************************/


#include "stack.h"


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
	STACK_LIST *handle = NULL;

	handle = stack_create(sizeof(struct data_t));
	ERRP(NULL == handle, main stack_create handle, goto ERR1);

	for (i = 0; i < MAX; i++)
	{
		num = rand() % 100;
		printf("i = %d, num = %d\n", i, num);
		stack_push(&num, handle);
	}


	stack_store("./stack_data.db", handle);

	stack_travel(handle, ls);

    /*
	 *handle = stack_load("./stack_data.db");
	 *stack_travel(handle, ls);
     */
	printf("pop: %d\n", *(int *)stack_pop(handle));
	printf("pop: %d\n", *(int *)stack_pop(handle));
	printf("pop: %d\n", *(int *)stack_pop(handle));

	for (i = 0; i < MAX; i++)
	{
		ret = stack_pop(handle);
		if (NULL == ret)
		{
			printf("NU ");
		}
		else
		{
			num = *(int *)ret;
			printf("pop: i = %d, num = %d\n", i, num);
		}
	}
	printf("\n");


	stack_destory(handle);


	return 0;
ERR1:
	return -1;
}


