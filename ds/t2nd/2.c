/***************************************************
	有头 有序 不循环 链表 
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
	struct node_t *tail = NULL;
	struct node_t *new = NULL;

	int num = 0;
	int i = 0;

	while (1)
	{
		printf("Please input %d num:", ++i);
		scanf("%d", &num);

		if (-1 == num)
		{
			break;
		}

		new = (struct node_t *)malloc(sizeof(struct node_t));
		if (NULL == new)
		{
			printf("Malloc new failed!\n");
			return -1;
		}

		new->data = num;
		new->next = NULL;

	#if 1
		for (tail = &head; (tail->next != NULL); tail = tail->next)
		{
			if (tail->next->data > new->data)
			{
				break;
			}
		}
	#else
		for (tail = &head; (tail->next != NULL) && (tail->next->data < new->data); tail = tail->next)
			;
	#endif
		new->next = tail->next;
		tail->next = new;
	}

	for (tail = head.next; tail != NULL; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	putchar(10);

	for (tail = head.next; tail != NULL; tail = new)
	{
		new = tail->next;
		free(tail);
	}

	return 0;
}
