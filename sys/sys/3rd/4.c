#define _XOPEN_SOURCE
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


int main(int argc, char *argv[])
{
	char buf[128];
	char *p = NULL;
	char *tmp;
	struct spwd *spw = NULL;

	
	spw = getspnam(argv[1]);
	if (spw == NULL)
	{
		printf("getspnam failed!\n");
		return -1;
	}

	/*strcpy(tmp, spw->sp_pwdp);*/
	tmp = spw->sp_pwdp;

	tmp = strrchr(tmp, '$');
	*(tmp + 1) = '\0';
	tmp = spw->sp_pwdp;

	printf("tmp= %s\n", tmp);
	
	printf("please input passwd : ");
	fgets(buf, sizeof(buf), stdin);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';

	p = crypt(buf, tmp);
	if (p == NULL)
	{
		printf("crypt failed!\n");
		return -1;
	}
	
	printf("p = %s\n", p);
	/*spw->sp_pwdp;*/
/*
 *    printf("please input passwd : ");
 *    fgets(buf, sizeof(buf), stdin);
 *    if (buf[strlen(buf) - 1] == '\n')
 *        buf[strlen(buf) - 1] = '\0';
 *    
 *    p = crypt(buf, "$1$yJs5o$");
 *    if (p == NULL)
 *    {
 *        printf("crypt failed!\n");
 *        return -1;
 *    }
 *
 *    printf("p = %s\n", p);
 */
	return 0;
}
