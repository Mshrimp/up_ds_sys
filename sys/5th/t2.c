/***************************************************

***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <dirent.h>
#include <sys/wait.h>
#include <math.h>


#define BASESTA 3000
#define BASEEND 6000
#define STEP ((BASEEND - BASESTA) / 10)

int prime(int start, int end);	//求素数


int main(int argc, char *argv[])
{
	int i = 0, j = 0;
	int step = 0;
	int start, end;
	int status = 0;
	int ret = 0;

	for (i = 0; i < 10; i++)
	{

		/*if (0 == fork())*/
		if (1)
		{
			printf("===========================\n");
			start = STEP * i + BASESTA;
			end = STEP * (i + 1) + BASESTA;
			printf("start = %d end = %d\n", start, end);
			printf("pid = %d\n", getpid());
			ret = prime(start, end);
			exit(ret);
		}
		else
		{
			wait(NULL);
		}

	}

	printf("\n");

	return 0;
}



//求素数
int prime(int start, int end)
{
	int i = 0; 
	int j = 0;
	int count = 0;

	for (i = start; i < end; i++)
	{
		for (j = 2; j < (i / 2); j++)
		{
			if (i % j == 0)	
			break;
		}
		if (j == i)
		{
			printf("%d  ", i);
			count++;
		}
	}
	printf("\ncount = %d\n", count);

	return count;
}

