#include <stdio.h>
#include <stdlib.h>


struct node_t{
	int data;
	struct node_t *next;
};

//无头 有序 循环 单向链表
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
			new->next = new;
			head = new;
		}
		else
		{
			if (new->data < head->data)
			{
				new->next = head;
				for (tail = head; tail->next != head; tail = tail->next)
					;
				tail->next = new;
				head = new;
			}
			else
			{
				for (tail = head; tail->next != head && tail->next->data < new->data; tail = tail->next)
					;
				new->next = tail->next;
				tail->next = new;
			}
		}
		count++;

	}


	for (tail = head; tail->next != head; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("%d\n", tail->data);

	for (tail = head; tail->next != head; tail = new)
	{
		new = tail->next;
		free(tail);
	}
	free(tail);
	return 0;
}
