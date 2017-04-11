#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 3000000

void arr_init(int *arr)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		arr[i] = rand() % MAX;
	}
}

void arr_show(int *arr)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		printf("%d ", arr[i]);
	}
	putchar(10);
}
//交换排序：就是取出一个数据，然后跟后面所有数据进行比较，如果满足条件则交换，则一边循环结束，则第一个数据存储就是最大或者最小数，依次类推。
void arr_swap(int *arr)
{
	int i, j;
	int tmp;

	for (i = 0; i < MAX; i++)
	{
		for (j = i + 1; j < MAX; j++)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}
//选择排序 :取出第一个数据跟后面所有的数据比较，如果满足条件，则保存这个最小值下标。循环结束，则跟第一个数据交换，依次类推。
void arr_select(int *a)
{
	int i, j;
	int tmp, t;

	for (i = 0; i < MAX; i++)
	{
		tmp = i;
		for (j = i + 1; j < MAX; j++)
		{
			if (a[tmp] > a[j])
			{
				tmp = j;
			}
		}
		t = a[i];
		a[i] = a[tmp];
		a[tmp] = t;
	}
}
//冒泡排序：相邻的两个数比较，满足条件，则小数上浮，大数下沉，一轮结束后则最大数沉到底部，依次类推。
void arr_bubble(int *a)
{
	int i, j;
	
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				a[j] ^= a[j + 1];
				a[j + 1] ^= a[j];
				a[j] ^= a[j + 1];
			}
		}
	}
}

//插入排序：取出第二个数，跟前面数比较，如果满足条件，则把前一个数赋给后一个数，则需要定义一个临时变量。来保存我当前数据，如果不满足条件，则退出。退出后，则把保存数据赋值给退出位置。

void arr_insert(int *a)
{
	int i, j, tmp;

	for (i = 1; i < MAX; i++)
	{
		tmp = a[i];
		for (j = i; j > 0; j--)
		{
			if (tmp < a[j - 1])
			{
				a[j] = a[j - 1];
			}
			else
			{
				break;
			}
		}
		a[j] = tmp;
	}
}

int cmp(const void *d1, const void *d2)
{
	return *(int *)d1 - *(int *)d2;
}

int main(int argc, char *argv[])
{
	int arr[MAX];

	arr_init(arr);
	/*arr_show(arr);*/
	/*srand(time(NULL));*/
	

	switch(atoi(argv[1]))
	{
		case 1:
			/*pinsertf("swap : \n");*/
			arr_swap(arr);
			break;
		case 2:
			/*printf("select : \n");*/
			arr_select(arr);
			break;
		case 3:
			/*printf("bubble : \n");*/
			arr_bubble(arr);
			break;
		case 4:
			/*printf("insert : \n");*/
			arr_insert(arr);
			break;
		case 5:
			qsort(arr, MAX, sizeof(int), cmp);
			break;
		default :
			printf("option err!\n");
			break;
	}
	/*arr_show(arr);*/


	return 0;
}






