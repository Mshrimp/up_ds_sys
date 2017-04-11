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
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <pthread.h>

#define MIN 3000
#define MAX 6000
#define NUM 10
#define STEP (MAX - MIN) / NUM

struct op_t{
	int min;
	int max;
};
int sum = 0;


void *count_prime(void *data)
{
	int *tmp = NULL;
	int i, j, count = 0; 
	int min = (int)data;
	int max = min + STEP;
	
	/*printf("pthread_self = %u min = %d\n", pthread_self(), min);*/
	tmp = (int *)malloc(sizeof(int));
	if (tmp == NULL)
	{
		pthread_exit(NULL);
	}

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
			count++;
		}
	}
	*tmp = count;
	sum += count;
	pthread_exit(tmp);
}
int main(int argc, char *argv[])
{
	int i;
	pthread_t pth[NUM];
	int *p = NULL;
	int result = 0;

	for (i = 0; i < NUM; i++)
	{
		pthread_create(pth + i, NULL, count_prime, (void *)(MIN + i * STEP));

	}


	for (i = 0; i < NUM; i++)
	{
		pthread_join(pth[i], (void **)&p);
		result += *p;
		free(p);
	}

	printf("result = %d\n", result);
	printf("sum = %d\n", sum);
	return 0;
}













