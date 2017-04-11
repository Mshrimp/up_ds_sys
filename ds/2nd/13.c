#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node_t{
	int data;
	struct node_t *next;
	struct node_t *prev;
};

//无头 有序 循环 双向链表
int main(void)
{
	struct node_t *head = NULL;//无头
	int num;
	struct node_t *new = NULL;
	struct node_t *tail = NULL;

	while(1)
	{
		printf("please input nunmber : ");
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

		if (head == NULL)
		{
			new->next = new;
			new->prev = new;
			head = new;
		}
		else
		{
			//尾插
		#if 1
			if (new->data < head->data)
			{
				new->next = head;
				new->prev = head->prev;
				head->prev->next = new;
				head->prev = new;
				head = new;
			}
			else
			{
				for (tail = head; tail->next != head; tail = tail->next)
				{
					if (new->data < tail->next->data)
					{
						break;
					}
				}
				new->next = tail->next;
				new->prev = tail;
				tail->next->prev = new;
				tail->next = new;
			}
		#else
			for (tail = head; tail->next != head; tail = tail->next)
			{
				if (new->data < head->data)
				{
				
				}
				if (new->data < tail->data)
				{
					break;
				}
			}
			new->next = tail;
			new->prev = tail->prev;
			tail->prev->next = new;
			tail->prev = new;
		#endif
		}
	}

	printf("next : ");
	for (tail = head; tail->next != head; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("%d\n", tail->data);

	printf("prev : ");
	for (tail = head->prev; tail != head; tail = tail->prev)
	{
		printf("%d ", tail->data); 
	}
	printf("%d\n", tail->data);

	for (tail = head->prev; tail != head; tail = new)
	{
		new = tail->prev;
		free(tail);
	}
	free(tail);

	
	return 0;
}





