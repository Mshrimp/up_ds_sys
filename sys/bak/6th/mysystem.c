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

void mysystem(char *cmd)
{
	int count = 0, i;
	char *ar[128];
	char buf[128];
	char *p= buf;

	strcpy(buf, cmd);
	printf("buf = %s\n", buf);
	while ((ar[count++] = strsep(&p, " ")) != NULL)
		;

	if (fork() == 0)
	{
		execvp(ar[0], ar);
		exit(0);
	}
	wait(NULL);

    /*
	 *for (i = 0; i < count - 1; i++)
	 *{
	 *    printf("ar[%d] = %s\n", i, ar[i]);
	 *}
     */
}
int main(int argc, char *argv[])
{
	
	printf("main stat!\n");
	mysystem("ls -l -h -i /ken/sys NULL");
	printf("main end!\n");
	return 0;
}
