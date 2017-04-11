#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

//int
//判断是否为满栈
int is_full(int top)
{
	if (top == MAX)
		return 1;
	return 0;
}
//判断是否是空栈
int is_empty(int top)
{
	if (top == 0)
		return 1;
	return 0;
}
//入栈
void push(int data, int *stack, int *top)
{
	if (is_full(*top))
		return ;
	stack[*top] = data;
	(*top)++;
}
int pop(int *stack, int *top)
{
	if (is_empty(*top))
		return -1;
	(*top)--;
	return stack[*top];
}
void travel(int *stack, int top)
{
	int i;
	for (i = 0; i < top; i++)
	{
		printf("%d ", stack[i]);
	}
	printf("\n");
}
int main(void)
{
	int num, i;
	int stack[MAX];//定义栈空间大小
	int top = 0;
	int ret;

	/*printf("sizeof(0) = %d\n", sizeof(0));*/
	memset(stack, 0, sizeof(stack));//清空栈

	for (i = 0; i < MAX + 2; i++)
	{
		num = rand() % 100;
		printf("%d ", num);
		push(num, stack, &top);
	}
	printf("\n");

	//栈遍历
	travel(stack, top);
	printf("pop = %d\n", pop(stack, &top));
	printf("pop = %d\n", pop(stack, &top));
	printf("pop = %d\n", pop(stack, &top));
	push(100, stack, &top);
	for (i = 0; i < MAX; i++)
	{
		ret = pop(stack, &top);
		if (ret == -1)
		{
			printf("空 ");
		}
		else
		{
			printf("%d ", ret);
		}
		/*printf("%d ", pop(stack, &top));*/
	}
	printf("\n");
	return 0;
}
