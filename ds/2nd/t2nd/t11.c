/***************************************************
	有头 无序 循环 双向链表
	实现在头节点后插入新节点数据，数据为字符串,
	结构体中使用数组
***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//双向链表节点信息
struct node_t
{
	/*int data;				//保存当前用户输入的数据*/
	char name[128];
	struct node_t *next;	//指向下一个节点地址
	struct node_t *prev;	//指向上一个节点地址
};


int main(int argc, char *argv[])
{
	struct node_t head = {{}, &head, &head};		//定义头节点为一个循环链表
	struct node_t *new = NULL;					//新节点指针
	struct node_t *tail = NULL;					//循环变量指针

	int num = 0;		//输入数据变量
	int count = 0;		//输入数据计数
	char name[128] = {};

	while (1)
	{
		//手动输入数据
		printf("Please input %d name:", count + 1);
		fgets(name, sizeof(name), stdin);
		if (name[strlen(name) - 1] == '\n')
			name[strlen(name) - 1] = '\0';
		/*scanf("%d", &num);*/
		//退出循环的条件，输入数据为-1退出循环
        /*
		 *if (-1 == num)
		 *{
		 *    break;
		 *}
         */
		if (!strcmp(name, "q"))
		{
			break;
		}
		//给新节点指针分配内存空间
		new = (struct node_t *)malloc(sizeof(struct node_t));
		if (NULL == new)
		{
			printf("Malloc new failed!\n");
			return -1;
		}
		//新节点指针内容初始化
		strcpy(new->name ,name);
		new->next = NULL;
		new->prev = NULL;

		//先设置新节点指针的next和prev指针
		new->next = head.next;
		new->prev = &head;
		//再设置循环尾部头节点指针的next和prev指针
		head.next->prev = new;
		head.next = new;

		count++;
	}

	//从头到尾遍历链表各节点的next指针，并打印数据
	printf("next : ");
	for (tail = head.next; tail != &head; tail = tail->next)
	{
		printf("%s ", tail->name);
	}
	printf("\n");

	//从尾到头遍历链表各节点的prev指针，并打印数据
	printf("prev : ");
	for (tail = head.prev; tail != &head; tail = tail->prev)
	{
		printf("%s ", tail->name);
	}
	printf("\n");

	//从头到尾遍历链表各节点的next指针，备份next指针，并释放节点指针内存空间
	for (tail = head.next; tail != &head; tail = new)
	{
		new = tail->next;
		free(tail);
	}

	return 0;
}
