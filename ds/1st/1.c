#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//为了解决空间不足或者空间浪费,所以提出动态数组
int main(void)
{
	int i;
	int num;
	int count = 0;
	int *new = NULL;
	int *prev = NULL;

	while(1)
	{
		printf("please input %d numbers : ", count + 1);
		scanf("%d", &num);

		if (num == -1)
		{
			break;
		}
		
		new = (int *)malloc(sizeof(int) * (count + 1));
		if (new == NULL)
		{
			printf("malloc new failed!\n");
			return -1;
		}
		
		memcpy(new, prev, sizeof(int) * count);
		memcpy(new + count, &num, sizeof(int));
		free(prev);
		prev = new;
		count++;
	}

	for (i = 0; i < count; i++)
	{
		printf("%d ", new[i]);
	}
	printf("\n");

	free(new);
	return 0;
}
