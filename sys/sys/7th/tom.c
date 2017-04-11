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

#define SHOW 3
#define INPUT 10

// tom -> jim -> tom_to_jim
int main(int argc, char *argv[])
{
	int fdr, fdw;
	char buf[128];

	mkfifo("tom_to_jim", 0666);
	mkfifo("jim_to_tom", 0666);

	
	fdr = open("jim_to_tom", O_RDWR);
	if (fdr < 0)
	{
		unlink("tom_to_jim");
		unlink("jim_to_tom");
		return -1;
	}

	fdw = open("tom_to_jim", O_RDWR);
	if (fdw < 0)
	{
		close(fdr);
		unlink("tom_to_jim");
		unlink("jim_to_tom");
		return -1;
	
	}
	system("clear");	
	if (fork() == 0)
	{
		//read
		while(1)
		{
			read(fdr, buf, sizeof(buf));
			printf("\033[%d;1HJIM : \033[K%s\033[u", SHOW, buf);
			fflush(NULL);
			if (strcmp(buf, "exit") == 0)
			{
				break;
			}
		}
		exit(0);
	}

	//write
	while(1)
	{
		printf("\033[%d;1HTOM : \033[K\033[s", INPUT);
		fgets(buf, sizeof(buf), stdin);
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';
		write(fdw, buf, strlen(buf) + 1);
		if (strcmp(buf, "exit") == 0)
		{
			break;
		}
	}

	wait(NULL);
	close(fdr);
	close(fdw);
	unlink("tom_to_jim");
	unlink("jim_to_tom");

	return 0;
}
