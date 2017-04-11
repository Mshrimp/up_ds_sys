#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node_t{
	int data;
	struct node_t *next;
};

int main(void)
{
	struct node_t head = {0, NULL};
	struct node_t *new = NULL, *tail = NULL;
	int num;
	struct node_t *save = NULL;//保存下一个节点地址
	struct node_t *prev = NULL;//保存上一个节点地址

	while(1)
	{
		printf("please input number : ");
		scanf("%d", &num);

		if (num == -1)
		{
			break;
		}

		new = (struct node_t *)malloc(sizeof(struct node_t));
		if (new == NULL)
		{
			return -1;
		}

		new->data = num;
		new->next = NULL;
	
		for (tail = &head; tail->next != NULL; tail = tail->next)
			;
		tail->next = new;

	}

	printf("for : ");
	for (tail = head.next; tail != NULL; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("\n");

	printf("while : ");
	tail = head.next;
	while(tail != NULL)
	{
		save = tail->next;
		tail->next = prev;
		prev = tail;
		/*printf("%d ", tail->data);*/
		tail = save;
	}
	head.next = prev;
	for (tail = head.next; tail != NULL; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("\n");
	return 0;
}
