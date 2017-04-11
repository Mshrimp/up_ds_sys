#include <stdio.h>
#include <stdlib.h>

//双向链表节点信息
struct node_t{
	int data;//保存当前用户输入数据
	struct node_t *next;//指向下一个节点地址
	struct node_t *prev;//指向上一个节点地址
};
//实现有头 无序 循环 双向链表
int main(void)
{
	struct node_t head = {0, &head, &head};//定义头节点并且是一个循环链表
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
		//先写new的next和prev,其次谁长就先写谁 
		//插到链表结尾
		new->next = &head;
		//new->prev = &head;
		new->prev = head.prev;
		//head.next = new;
		head.prev->next = new;
		head.prev = new;
	}

	printf("next : ");
	for (tail = head.next; tail != &head; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("\n");
	printf("prev : ");
	for (tail = head.prev; tail != &head; tail = tail->prev)
	{
		printf("%d ", tail->data);
	}
	printf("\n");
	for (tail = head.next; tail != &head; tail = new)
	{
		new = tail->next;
		free(tail);
	}
	return 0;
}
