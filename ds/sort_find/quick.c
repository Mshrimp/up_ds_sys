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
int quickpass(int *a, int left, int right);

void quicksort(int *a, int l, int h)
{
	int m;

	if (l < h)
	{
		m = quickpass(a, l, h);
		quicksort(a, l, m - 1);
		quicksort(a, m + 1, h);
	}
}
int quickpass(int *a, int left, int right)
{
	int key;
	int low, high;

	key = a[left];
	low = left;
	high = right;

	while(low < high)
	{
		while (key <= a[high] && low < high)
		{
			high--;
		}
		if (low < high)
			a[low++] = a[high];
		while (key >= a[low] && low < high)
		{
			low++;
		}
		if (low < high)
			a[high--] = a[low];
	}
	a[low] = key;
	return low;
}


int main(void)
{
	int arr[MAX];

	/*srand(time(NULL));*/
	arr_init(arr);
	/*arr_show(arr);*/
	quicksort(arr, 0, MAX - 1);
	/*arr_show(arr);*/


	return 0;
}






