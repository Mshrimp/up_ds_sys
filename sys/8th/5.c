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


void *func(void *data)
{
	int *p = NULL;
	// &p  => stack
	p = (int *)malloc(sizeof(int));
	if (p == NULL)
	{
		printf("malloc p failed!\n");
		pthread_exit(NULL);
	}
	/*printf("q = %p\n", q);*/
	printf("pthread_self = %u\n", pthread_self());
	/**p = 2147483647 + 1;*/
	*p = -2147483649;

	printf("&p = %p\n", &p);
	printf("p = %p\n", p);
	printf("*p = %d\n", *p);
	
	printf("==================\n");
	pthread_exit(p);
}
int main(int argc, char *argv[])
{
	int ret;
	pthread_t pth;
	int *q = NULL;

	ret = pthread_create(&pth, NULL, func, NULL);
	if (ret != 0)
	{
		printf("pthread_create failed!\n");
		return -1;
	}

	// **q
	//&q  q  *q  **q 
    /*
	 *q = (int **)malloc(sizeof(int *));
	 *if (q == NULL)
	 *{
	 *    printf("main failed!\n");
	 *    return -1;
	 *}
     */
	pthread_join(pth, (void **)&q);

    /*
	 *printf("&q = %p\n", &q);
	 *printf("q = %p\n", q);
	 *printf("*q = %p\n", *q);
	 *printf("**q = %d\n", **q);
     */
	printf("*q = %d\n", *q);
	printf("main : pthread_self = %u\n", pthread_self());

	free(q);
	return 0;
}








