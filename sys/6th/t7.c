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
	int ret1, ret2;
	struct itimerval it1;
	struct itimerval it2;
	sighandler_t head1 = NULL;

	/*head = signal(SIGALRM, func);*/
	/*head = signal(SIGVTALRM, func);*/
	head1 = signal(SIGPROF, func);
	if (head1 == SIG_ERR)
	{
		printf("signal failed!\n");
		return -1;
	}

	//循环时间
	it1.it_interval.tv_sec = 1;//表示秒
	it1.it_interval.tv_usec = 1000;//表示微妙
	//第一次执行时间
	it1.it_value.tv_sec = 0;
	it1.it_value.tv_usec = 1000;

	//循环时间
	it2.it_interval.tv_sec = 1;//表示秒
	it2.it_interval.tv_usec = 1000;//表示微妙
	//第一次执行时间
	it2.it_value.tv_sec = 0;
	it2.it_value.tv_usec = 1000;

	/*ret = setitimer(ITIMER_REAL, &it, NULL);*/
	/*ret = setitimer(ITIMER_VIRTUAL, &it, NULL);*/
	ret1 = setitimer(ITIMER_PROF, &it1, NULL);
	if (ret1 < 0)
	{
		printf("setitimer failed!\n");
		return -1;
	}

	ret2 = setitimer(ITIMER_PROF, &it, NULL);
	if (ret2 < 0)
	{
		printf("setitimer failed!\n");
		return -1;
	}

	printf("Hello!\n");

	while(1)
		;
		/*sleep(1);*/
	/*getchar();*/
	return 0;
}
