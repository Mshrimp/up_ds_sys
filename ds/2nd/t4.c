#include <stdio.h>
#include <stdlib.h>


struct node_t{
	int data;
	struct node_t *next;
};

//无头 有序 不循环 单向链表
int main(void)
{
	int num, count = 0;
	struct node_t *head = NULL;//无头
	struct node_t *new = NULL, *tail = NULL;

	while(1)
	{
		printf("please input %d numbers : ", count + 1);
		scanf("%d", &num);

		if (num == -1)
		{
			break;
		}

		new = (struct node_t *)malloc(sizeof(struct node_t));
		if (NULL == new)
		{
			return -1;
		}

		new->data = num;
		new->next = NULL;//表示这个节点跟任何节点没有任何关系

		if (head == NULL)
		{
			head = new;
		}
		else
		{
			if (new->data < head->data)
			{
				new->next = head;
				head = new;
			}
			else
			{
				for (tail = head; tail->next != NULL && tail->next->data < new->data; tail = tail->next)
					;
				new->next = tail->next;
				tail->next = new;
			}
		}
		count++;

	}


	for (tail = head; tail != NULL; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("\n");

	for (tail = head; tail != NULL; tail = new)
	{
		new = tail->next;
		free(tail);
	}
	return 0;
}
