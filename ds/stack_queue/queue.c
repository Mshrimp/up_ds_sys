#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10//队列长度

int is_full(int front, int end)
{
	if ((end + 1) % MAX == front)
		return 1;
	return 0;
}
int is_empty(int front, int end)
{
	if (front == end)
		return 1;
	return 0;
}
void qe(int data, int *queue, int *end, int front)
{
	if (is_full(front, *end))
		return ;
	queue[*end] = data;
	(*end)++;
	if (*end == MAX)
		*end = 0;
}
int de(int *queue, int *front, int end)
{
	int data;
	
	if (is_empty(*front, end))
		return -1;

	data = queue[*front];
	(*front)++;
	if (*front == MAX)
		*front = 0;
	return data;

}
int len(int front, int end)
{
	if (end > front)
	{
		return end - front;
	}
	else
	{
		return MAX - (front - end);
	}
}


void travel(int *queue, int front, int end)
{
	int i, j;
	for (i = front, j = 0; j < len(front, end); j++, i++)
	{
		if (i == MAX)
			i = 0;
		printf("%d ", queue[i]);
		
	}
	printf("\n");
}
int main(void)
{
	int num;
	int queue[MAX];//队列空间大小
	int front = 0;//表示队头
	int end = 0;//表示队尾

	int i;
	for (i = 0; i < MAX; i++)
	{
		num = rand() % 100;
		printf("%d ", num);
		qe(num, queue, &end, front);
	}
	printf("\n");


	travel(queue, front, end);
	printf("de = %d\n", de(queue, &front, end));
	qe(100, queue, &end, front);
	printf("de = %d\n", de(queue, &front, end));
	printf("de = %d\n", de(queue, &front, end));
	printf("de = %d\n", de(queue, &front, end));
	
	
	for (i = 0; i < MAX; i++)
	{
		printf("%d ", de(queue, &front, end));
	}
	printf("\n");
	return 0;
}
