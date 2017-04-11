#include <stdio.h>
#include <stdlib.h>

//双向链表节点信息
struct node_t{
	int data;//保存当前用户输入数据
	struct node_t *next;//指向下一个节点地址
	struct node_t *prev;//指向上一个节点地址
};
//实现有头 无序 不循环 双向链表
int main(void)
{
	struct node_t head = {0, NULL, NULL};//定义头节点并且是一个循环链表
	int num;//临时变量
	struct node_t *new = NULL;//新节点信息
	struct node_t *tail = NULL;//循环变量

	while(1)
	{
		printf("please input number : ");
		scanf("%d", &num);

		if (num == -1)
		{
			break;
		}

		new = (struct node_t *)malloc(sizeof(struct node_t));
		if (NULL == new)
		{
			printf("malloc failed!\n");
			return -1;
		}
		new->data = num;
		new->next = NULL;
		new->prev = NULL;

		for (tail = &head; tail->next != NULL; tail = tail->next)
			;
		new->prev = tail;
		tail->next = new;
	}

	printf("next : ");
	for (tail = head.next; tail != NULL; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("\n");
	printf("prev : ");
	for (tail = &head; tail->next != NULL; tail = tail->next)
			;
	struct node_t *tmp = NULL;
	for (tmp = tail; tmp != &head; tmp = tmp->prev)
	{
		printf("%d ", tmp->data);
	}
	printf("\n");
	for (tail = head.next; tail != NULL; tail = new)
	{
		new = tail->next;
		free(tail);
	}
	return 0;
}
