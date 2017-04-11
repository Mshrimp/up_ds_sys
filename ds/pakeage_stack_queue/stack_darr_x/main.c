/***************************************************
	用顺序表封装栈函数
***************************************************/

#include "stack.h"


void ls(void *data)
{
	printf("%d ", *(int *)data);
}


int main(int argc, char *argv[])
{
	int num = 0, i = 0;
	STACK *handle = NULL;
	int *ret = NULL;

	handle = stack_create(sizeof(int), MAX);
	ERRP(NULL == handle, main handle stack_create, goto ERR1);

	stack_clean(handle);

/*
 *    for (i = 0; i < MAX; i++)
 *    {
 *        num = rand() % 100;
 *        printf("%d ", num);
 *        stack_push(&num, handle);
 *    }
 *    printf("\n");
 *
 *    stack_travel(handle, ls);
 *    [>stack_store("./data.db", handle);<]
 *    stack_clean(handle);
 *    [>stack_travel(handle, ls);<]
 */
	handle = stack_load("./data.db");
	stack_travel(handle, ls);

	printf("%d\n", *(int *)stack_pop(handle));
	printf("%d\n", *(int *)stack_pop(handle));
	printf("%d\n", *(int *)stack_pop(handle));

	for (i = 0; i < MAX; i++)
	{
		ret = (int *)stack_pop(handle);
		
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

	free(ret);
	stack_destory(handle);

	return 0;
ERR1:
	return -1;
}
