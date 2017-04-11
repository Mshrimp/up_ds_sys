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

//信号执行函数
typedef void (*sighandler_t)(int);

//自定义
void hello(int sig)
{
	printf("hello! : sig = %d\n", sig);
}
int main(int argc, char *argv[])
{
	sighandler_t p = NULL;

    /*
	 *p = signal(2, SIG_IGN);//忽略
	 *p = signal(2, SIG_DFL);//默认
     */
	p = signal(3, hello);
	p = signal(3, hello);
	if (p == SIG_ERR)
	{
		printf("signal failed!\n");
		return ;
	}
	/*sleep(5);*/

	printf("p = %p\n", p);
	printf("hello = %p\n", hello);
	while(1)
		sleep(1);
	return 0;
}
