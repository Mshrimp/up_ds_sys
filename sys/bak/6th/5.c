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
	printf("hello!\n");
	/*alarm(2);*/
}
int main(int argc, char *argv[])
{
	int count = 5;

	signal(9, func);
	kill(getpid(), 9);
	/*alarm(1);*/

	while(count--)
		pause();
	
    /*
	 *while(count--)
	 *    sleep(1);
     */

	return 0;
}
