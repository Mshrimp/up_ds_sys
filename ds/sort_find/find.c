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
int find(int key, int *arr)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		if (key == arr[i])
		{
			return arr[i];
		}
	}

	return -1;
}
int my_bsearch(int *arr, int key, int low, int high)
{
	int left = low;
	int right = high;

	int m;

	while(left <= right)
	{
		m = (left + right) / 2;
		if (key > arr[m])
		{
			left = m + 1;
		}
		else if (key < arr[m])
		{
			right = m - 1;
		}
		else
		{
			return arr[m];
		}
	}
	return -1;
}

int cmp(const void *d1, const void *d2)
{
	return *(int *)d1 - *(int *)d2;
}
int main(void)
{
	int arr[MAX];
	int key, ind;
	int *p = NULL;

	/*srand(time(NULL));*/
	arr_init(arr);
	arr_show(arr);
	/*arr_swap(arr);*/
	arr_show(arr);
	printf("please input find key : ");
	scanf("%d", &key);

	/*ind = my_bsearch(arr, key, 0, MAX - 1);*/
	p = (int *)bsearch(&key, arr, MAX, sizeof(int), cmp);
	/*ind = find(key, arr);*/
	if (p == NULL)
	{
		printf("no find !\n");
	}
	else
	{
		printf("find = %d\n", *p);
	}


	return 0;
}






