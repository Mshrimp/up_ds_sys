#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//双向链表节点信息
struct node_t{
	char *name;//保存当前用户输入数据
	struct node_t *next;//指向下一个节点地址
	struct node_t *prev;//指向上一个节点地址
};
//实现有头 无序 循环 双向链表
int main(void)
{
	struct node_t head = {NULL, &head, &head};//定义头节点并且是一个循环链表
	int num;//临时变量
	char buf[128];
	struct node_t *new = NULL;//新节点信息
	struct node_t *tail = NULL;//循环变量

	while(1)
	{
		printf("please input name : ");
		fgets(buf, sizeof(buf), stdin);
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';
		if (!strcmp(buf, "exit"))
		{
			break;
		}
		
		new = (struct node_t *)malloc(sizeof(struct node_t));
		if (NULL == new)
		{
			printf("malloc failed!\n");
			return -1;
		}

		new->name = (char *)malloc(strlen(buf) + 1);
		if (new->name == NULL)
		{
			free(new);
			return -1;
		}

		/*new->name = buf;*/
		strcpy(new->name, buf);
		new->next = NULL;
		new->prev = NULL;
		//先写new的next和prev,其次谁长就先写谁 
		//插到链表开头
		new->next = head.next;
		new->prev = &head;
		head.next->prev = new;
		head.next = new;
	}

	printf("next : ");
	for (tail = head.next; tail != &head; tail = tail->next)
	{
		printf("%s ", tail->name);
	}
	printf("\n");
	printf("prev : ");
	for (tail = head.prev; tail != &head; tail = tail->prev)
	{
		printf("%s ", tail->name);
	}
	printf("\n");
	for (tail = head.next; tail != &head; tail = new)
	{
		new = tail->next;
		free(tail->name);
		free(tail);
	}
	return 0;
}
