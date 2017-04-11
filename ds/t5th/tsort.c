#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

void arr_init(int *arr)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		arr[i] = rand() % 100;
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
	int count = 0;

	for (i = 0; i < MAX; i++)
	{
		printf("%d : ", i + 1);
		for (j = i + 1; j < MAX; j++)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				count++;
			}
		}
		arr_show(arr);
	}
	printf("count = %d\n", count);
}
//选择排序 :取出第一个数据跟后面所有的数据比较，如果满足条件，则保存这个最小值下标。循环结束，则跟第一个数据交换，依次类推。
void arr_select(int *a)
{
	int i, j;
	int tmp, t;
	int count = 0;

	for (i = 0; i < MAX; i++)
	{
		tmp = i;
		printf("%d : ", i + 1);
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
		count++;
        /*
		 *a[i] ^= a[tmp];
		 *a[tmp] ^= a[i];
		 *a[i] ^= a[tmp];
         */
		arr_show(a);
		getchar();
	}
	printf("count = %d\n", count);
}


void arr_bubble(int *a)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	int count = 0;

	for (i = 0; i < MAX; i++)
	{
		printf("%2d:", i + 1);
		for (j = 0; j < MAX-i-1; j++)
		{
			if (a[j] > a[j+1])
			{
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
				count++;
			}
		}
		arr_show(a);
		getchar();
	}
	printf("count = %d\n", count);
}


void arr_insert(int *a)
{
	int i = 0, j = 0;
	int tmp = 0;
	int count = 0;

	for (i = 1; i < MAX; i++)
	{
		printf("%2d: ", i + 1);
		tmp = a[i];

		for (j = i; j > 0; j--)
		{
			if (tmp < a[j-1])
			{
				a[j] = a[j-1];
			}
			else
			{
				break;
			}
		}
		a[j] = tmp;

        /*
		 *for (j = 0; j <= i; j++)
		 *{
		 *    tmp = a[i];
		 *    if (tmp < a[j])
		 *    {
		 *        a[i] = a[j];
		 *        a[j] = tmp;
		 *        count++;
		 *    }
		 *}
         */
		arr_show(a);
	}
	printf("count = %d\n", count);

}


int main(void)
{
	int arr[MAX];

	arr_init(arr);
	arr_show(arr);
	/*arr_swap(arr);*/
	/*arr_select(arr);*/
	/*arr_bubble(arr);*/
	arr_insert(arr);
	arr_show(arr);


	return 0;
}






