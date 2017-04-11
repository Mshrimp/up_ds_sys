#include <stdio.h>
#include <stdlib.h>


//节点信息 以整形数据为例
struct node_t{
	int data;
	struct node_t *next;
};

//有头 有序 循环 单向链表
int main(void)
{
	int num;//定义临时变量 用来接受用户数据
	struct node_t head = {0, &head};//定义头节点
	struct node_t *new = NULL;//新节点信息，用来接受用户输入数据
	struct node_t *tail = NULL;//循环变量

	while(1)
	{
		//接受用户输入数据
		printf("please input number : ");
		scanf("%d", &num);
		//退出条件
		if (num == -1)
		{
			break;
		}
		//接受数据放入节点信息，则需要申请空间
		new = (struct node_t *)malloc(sizeof(struct node_t));
		if (NULL == new)
		{
			printf("malloc faied!\n");
			return -1;
		}

		//接受数据则存放申请节点空间中
		new->data = num;
		new->next = NULL;
		//连结新的节点信息到头节点中
	//	head.next = new;
		//head.next->next = new;
		for (tail = &head; tail->next != &head && new->data > tail->next->data; tail = tail->next)
			;
		//插入新的节点到头节点中
		new->next = tail->next;
		tail->next = new;
	}

	//prinotf("head.next->data = %d\n", head.next->data);
	//遍历
	for(tail = head.next; tail != &head; tail = tail->next)
	{
		printf("%d ", tail->data, &tail->data, tail);
	}
	putchar(10);

	//释放
	for (tail = head.next; tail != &head; tail = new)
	{
		new = tail->next;
		free(tail);
	}
	return 0;
}
