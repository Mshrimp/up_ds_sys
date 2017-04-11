#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>


int main(int argc, char *argv[])
{
	int ret;
	int fd;
	struct stat s;
	struct passwd *pw = NULL;

	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		perror("open");
		return -1;
	}
	ret = fstat(fd, &s);
	if (ret < 0)
	{
		perror("fstat");
		return -1;
	}

	printf("s.st_uid = %d\n", s.st_uid);
	/*printf("s.st_uid = %s\n", s.st_uid);*/
	pw = getpwuid(s.st_uid);
	if (pw == NULL)
	{
		return -1;
	}

	printf("name = %s\n", pw->pw_name);//       /* user name */
	printf("passwd = %s\n", pw->pw_passwd);//     /* user password */
	printf("uid = %u\n", pw->pw_uid);//        /* user ID */
	printf("gid = %u\n", pw->pw_gid);//        /* group ID */
	printf("real = %s\n", pw->pw_gecos);//      /* real name */
	printf("dir = %s\n", pw->pw_dir);//        /* home directory */
	printf("shell = %s\n", pw->pw_shell);//      /* shell program */

	/*free(pw);*/
	return 0;

}
