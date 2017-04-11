#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

struct node_t{
	void *data;// size * count
	struct node_t *next;
};

void arr_rand(int *arr)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		arr[i] = rand() % 100;
	}
}

void arr_display(int *arr)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
//哈希算法
int hash(int num)
{
	return num % MAX;
}
int main(void)
{
	int arr[MAX];
	int count = 0;
	int i;
	int num, tmp;
	struct node_t head[MAX];//头
	struct node_t *new = NULL;
	struct node_t *tail = NULL;
	/*arr_rand(arr);*/

	srand(time(NULL));
	memset(head, 0, sizeof(head));
	//接受用户数据数据，存入哈西表中
	//创建哈西表
	for (i = 0; i < MAX; i++)
	{
		//数据
		num = rand() % 100;
		//数据存入数组中，方便遍历数据
		arr[i] = num;
		//哈西转换
		tmp = hash(num);

		//申请节点地址空间，存入接受用户的数据
		new = (struct node_t *)malloc(sizeof(struct node_t));
		if (new == NULL)
		{
			printf("new malloc failed!\n");
			return -1;
		}

		new->data = num;
		new->next = NULL;

		//存入节点到哈希表中
		for (tail = &head[tmp]; tail->next != NULL; tail = tail->next)
			;
		tail->next = new;

		count++;
	}
	//哈西遍历：
	for (i = 0; i < MAX; i++)
	{
		printf("%d : ", i);
		for (tail = head[i].next; tail != NULL; tail = tail->next)
		{
			printf("%d ", tail->data);
		}
		printf("\n");
	}
	//哈西查找
	int key;
	printf("please input key : ");	
	scanf("%d", &key);
	
	tmp = hash(key);
	for (tail = head[tmp].next; tail != NULL; tail = tail->next)
	{
		if (key == tail->data)
		{
			printf("find = %d\n", tail->data);
			goto loop;
		}
	}
	printf("no find!\n");
	loop:
	//哈西销毁
	for (i = 0; i < MAX; i++)
	{
		for (tail = head[i].next; tail != NULL; tail = new)
		{
			new = tail->next;
			free(tail);
		}
	}
	arr_display(arr);
	return 0;
}
