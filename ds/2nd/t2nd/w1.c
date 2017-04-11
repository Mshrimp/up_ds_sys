/***************************************************
	homework-ds-2nd-1:
	实现 有头 无序 不循环 单向链表 的逆序
***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node_t
{
	int data;
	struct node_t *next;
};

int main(int argc, char *argv[])
{
	struct node_t head = {0, NULL};
	struct node_t *new = NULL;
	struct node_t *tail = NULL;
	struct node_t *nextp = NULL;
	struct node_t *prevp = NULL;

	int num = 0;
	int count = 0;
	int i = 0;

	while (1)
	{
		printf("Please input %d number:", count + 1);
		scanf("%d", &num);

		if (-1 == num)
		{
			break;
		}

		new = (struct node_t *)malloc(sizeof(struct node_t));
		if (NULL == new)
		{
			printf("Malloc New failed!\n");
			return -1;
		}

		new->data = num;
		new->next = NULL;

		for (tail = &head; tail->next != NULL; tail = tail->next)
			;
		tail->next = new;
	
		count++;
	}

	for (tail = head.next; tail != NULL; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("\n");

	for (tail = head.next; tail != NULL; tail = nextp)
	{
		nextp = tail->next;
		tail->next = prevp;
		prevp = tail;
	}
	head.next = prevp;

	for (tail = head.next; tail != NULL; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("\n");

	return 0;
}
