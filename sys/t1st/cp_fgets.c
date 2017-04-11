/***************************************************
	用fgets()和fputs()函数实现cp功能
	说明：./a.out src dest
***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fpr = NULL;
	FILE *fpw = NULL;
	char buf[128] = {};
	char *retp = NULL;
	int ret = 0;

	fpr = fopen(argv[1], "r");
	if (NULL == fpr)
	{
		printf("fopen file1 failed!\n");
		return 0;
	}
	fpw = fopen(argv[2], "w");
	if (NULL == fpw)
	{
		fclose(fpr);
		printf("fopen file2 failed!\n");
		return 0;
	}

	while (1)
	{
		retp = fgets(buf, sizeof(buf), fpr);
		if (NULL == retp)
		{
			/*printf("fgets failed!\n");*/
			break;
		}

		ret = fputs(buf, fpw);
		if (EOF == ret)
		{
			/*printf("fputs failed!\n");*/
			break;
		}
	}

	printf("File copy OK!\n");

	ret = fclose(fpr);
	if (0 != ret)
	{
		printf("fclose fpr failed!\n");
	}

	ret = fclose(fpw);
	if (0 != ret)
	{
		printf("fclose fpw failed!\n");
	}

	return 0;
}
