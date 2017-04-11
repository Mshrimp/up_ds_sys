#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node_t{
	char *name;
	struct node_t *next;
	struct node_t *prev;
};

//无头 无序 循环 双向链表
int main(void)
{
	int m, n, i;
	char name[128];
	struct node_t *new = NULL, *tail = NULL;
	struct node_t *head = NULL;
	int count = 0;

	printf("please input m and n : ");
	scanf("%d%d", &m, &n);

	getchar();
	for (i = 0; i < m; i++)
	{
		printf("please input %d name : ", i + 1);
		fgets(name, sizeof(name), stdin);
		if (name[strlen(name) - 1] == '\n')
			name[strlen(name) - 1] = '\0';

		new = (struct node_t *)malloc(sizeof(struct node_t));
		if (NULL == new)
		{
			printf("malloc new failed!\n");
			return -1;
		}
		new->name = (char *)malloc(strlen(name) + 1);
		if (NULL == new->name)
		{
			printf("malloc new->name failed!\n");
			free(new);
			return -1;
		}

		strcpy(new->name, name);

		if (head == NULL)
		{
			new->next = new;
			new->prev = new;
			head = new;
		}
		else
		{
			new->next = head;
			new->prev = head->prev;
			head->prev->next = new;
			head->prev = new;
		}
	}

	for (tail = head; tail->next != head; tail = tail->next)
	{
		printf("%s ", tail->name);
	}
	printf("%s", tail->name);
	putchar(10);
	

	tail = head;
	while(tail->next != tail)
	{
		new = tail->next;
		count++;
		if (count == n)
		{
			printf("%s ", tail->name);
			tail->prev->next = tail->next;
			tail->next->prev = tail->prev;
			free(tail->name);
			free(tail);
			count = 0;
		}
		tail = new;
	}
	printf("%s\n", tail->name);
	
	free(tail->name);
	free(tail);
	return 0;
}









