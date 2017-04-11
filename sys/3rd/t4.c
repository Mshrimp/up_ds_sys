/***************************************************

***************************************************/
#define X_OPEN_SOURCE
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

#define GETLINES(string, buf)	do{										\
									printf(string);						\
									fgets(buf, sizeof(buf), stdin);		\
									if (buf[strlen(buf) - 1] == '\n')	\
										buf[strlen(buf) - 1] = '\0';	\
								}while(0)



int main(int argc, char *argv[])
{
	char buf[32] = {};
	char *tmp = NULL;
	char *pwd = NULL;
	struct spwd *spw = NULL;

	spw = getspname(argv[1]);
	if (NULL == spw)
	{
		printf("getspnam failed!\n");
		return -1;
	}

	tmp = spw->sp_pwdp;
	tmp = strrchr(tmp, '$');

	*(tmp + 1) = '\0';

	tmp = spw->sp_pwdp;

	GETLINES("Please input a string:", buf);

	printf("tmp = %s\n", tmp);
	printf("buf = %s\n", buf);

	pwd = crypt(buf, tmp);
	if (NULL == pwd)
	{
		printf("Crypt failed!\n");
		return -1;
	}

	printf("pwd = %s\n", pwd);

	return 0;
}
