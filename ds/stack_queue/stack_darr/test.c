#include "stack.h"

#define MAX 10


void ls(void *data)
{
	printf("%d ", *(int *)data);
}
int main(void)
{
	int i, num;
	STACK *handle = NULL;
	int *p = NULL;

	handle = stack_create(sizeof(int), MAX);
	ERRP(handle == NULL, "stack_create", goto ERR1);
	
	for (i = 0; i < MAX; i++)
	{
		num = rand() % 1000;
		stack_push(&num, handle);
	}
	stack_travel(handle, ls);

	printf("pop = %d\n", *(int *)stack_pop(handle));
	p = (int *)stack_pop(handle);
	if (p == NULL)
	{
		printf("stack is empty!\n");
		return -1;
	}
	printf("*p = %d\n", *p);
	stack_destroy(handle);
	return 0;
ERR1:
	return -1;
}
