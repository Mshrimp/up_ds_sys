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
#include <time.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <signal.h>


typedef void (*sighandler_t)(int);

void sig_func(int sig)
{
	struct time_t *tail = NULL;
	struct time_t *save = NULL;

	for (tail = head.next; tail != &head; tail = tail->next)
	{
		tail->count++;
		if (tail->count == tail->t)
		{
			tail->func(tail->data);
			if (tail->flag)
			{
				tail->count = 0;
			}
			else
			{
			
			}
		}
	}
}

void init_timer(void)
{
	int ret = 0;
	struct itimerval it;
	sighandler_t sig;

	head.next = &head;
	head.prev = &head;

	if (signal(SIGALRM, sig_func) == SIG_ERR)
	{
		printf("signal failed!\n");
		return ;
	}

	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 0;

	it.it_value.tv_sec = 0;
	it.it_value.tv_usec = 1000;



}


int main(int argc, char *argv[])
{
	

	return 0;
}
