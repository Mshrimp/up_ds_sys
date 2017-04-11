#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <shadow.h>
#include <grp.h>
#include <time.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <glob.h>
#include <sys/wait.h>

#define MIN 3000
#define MAX 6000
#define NUM 10
#define STEP (MAX - MIN) / NUM

int prime(int min, int max)
{
	int i, j;
	int count = 0;

	printf("pid = %d min = %d\n", getpid(), min);
	for (i = min; i < max; i++)
	{
		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
			{
				break;
			}
		}
		if (i == j)
		{
			printf("%d ", i);
			count++;
		}
	}

	printf("count = %d\n", count);
	return count;
}
int main(int argc, char *argv[])
{
	/*printf("count = %d\n", prime(1, 100));*/
	int i;
	int status;
	int result = 0;

	for (i = 0; i < NUM; i++)
	{
		if (fork() == 0)
		{
			exit(prime(MIN + i * STEP, MIN + (i + 1) * STEP));
		}
	}


	for (i = 0; i < NUM; i++)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			result += WEXITSTATUS(status);
		}
	}
	printf("result = %d\n", result);
	return 0;
}







