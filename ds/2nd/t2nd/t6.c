/***************************************************
	无头 无序 不循环 双向链表
***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//双向链表节点信息
struct node_t
{
	int data;				//保存当前用户输入的数据
	struct node_t *next;	//指向下一个节点地址
	struct node_t *prev;	//指向上一个节点地址
};


int main(int argc, char *argv[])
{
	struct node_t *head = NULL;		//无头节点，定义头指针保存位置
	struct node_t *new = NULL;		//新节点指针
	struct node_t *tail = NULL;		//循环变量指针

	int num = 0;		//输入数据变量
	int count = 0;		//输入数据计数

	while (1)
	{
		//手动输入数据
		printf("Please input %d number:", count + 1);
		scanf("%d", &num);
		//退出循环的条件，输入数据为-1退出循环
		if (-1 == num)
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
		new->data = num;
		new->next = NULL;
		new->prev = NULL;

		//判断头指针是否为空，为空将头指针指向新节点
		if (head == NULL)
		{
			head = new;
		}
		else	
		{
			//从头到尾遍历链表各节点，找到链表最后一个节点
			for (tail = head; tail->next != NULL; tail = tail->next)
				;
			//头指针不为空，先设置新节点指针的next和prev指针
			new->prev = tail;
			new->next = NULL;
			//再设置循环尾部头指针的next指针
			tail->next = new;
		}
		count++;
	}


	//从头到尾遍历链表各节点的next指针，并打印数据
	printf("next : ");
	for (tail = head; tail->next != NULL; tail = tail->next)
	{
		printf("%d ", tail->data);
	}
	printf("%d ", tail->data);
	printf("\n");


	printf("prev : ");
	//从头到尾遍历链表各节点，找到链表最后一个节点
	for (tail = head; tail->next != NULL; tail = tail->next)
		;
	//从尾到头遍历链表各节点的prev指针，并打印数据
	for (; tail != head; tail = tail->prev)
	{
		printf("%d ", tail->data);
	}
	printf("%d ", tail->data);
	printf("\n");


	//从头到尾遍历链表各节点的next指针，备份next指针，并释放节点指针内存空间
	for (tail = head->next; tail != NULL; tail = new)
	{
		new = tail->next;
		free(tail);
	}
	free(tail);

	return 0;
}
