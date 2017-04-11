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

typedef void (*sighandler_t)(int);

void func(int sig)
{
	printf("sig = %d\n", sig);
}
int main(int argc, char *argv[])
{
	int ret;
	struct itimerval it;
	sighandler_t head = NULL;

	/*head = signal(SIGALRM, func);*/
	head = signal(SIGVTALRM, func);
	if (head == SIG_ERR)
	{
		printf("signal failed!\n");
		return -1;
	}
	//循环时间
	it.it_interval.tv_sec = 1;//表示秒
	it.it_interval.tv_usec = 1000;//表示微妙
	//第一次执行时间
	it.it_value.tv_sec = 0;
	it.it_value.tv_usec = 1000;

	/*ret = setitimer(ITIMER_REAL, &it, NULL);*/
	ret = setitimer(ITIMER_VIRTUAL, &it, NULL);
	if (ret < 0)
	{
		printf("setitimer failed!\n");
		return -1;
	}

	while(1)
		;
	/*getchar();*/
	return 0;
}
