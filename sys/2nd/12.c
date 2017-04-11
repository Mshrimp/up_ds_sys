#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define PRI(e) printf(#e" = %d\n", e)
#define PRI_O(e) printf(#e" = %o\n", e)

int main(int argc, char *argv[])
{
	/*system("ls -l");*/
	int ret;
	struct stat s;

	ret = lstat(argv[1], &s);
	if (ret < 0)
	{
		printf("stat failed!\n");
		return -1;
	}

	printf("stat success!\n");
	
	//mode 表示文件类型和权限
	// - d b c l s p 
	//属主 属组 其他用户
	PRI_O(s.st_mode);    /* protection */

	mode_t m = s.st_mode;

	if (S_ISREG(m))//  is it a regular file?
		putchar('-');
	else if (S_ISDIR(m))//  directory?
		putchar('d');
	else if (S_ISCHR(m))//  character device?
		putchar('c');
	else if (S_ISBLK(m))//  block device?
		putchar('b');
	else if (S_ISFIFO(m))// FIFO (named pipe)?
		putchar('p');
	else if (S_ISLNK(m))//  symbolic link? (Not in POSIX.1-1996.)
		putchar('l');
	else if (S_ISSOCK(m))// socket? (Not in POSIX.1-1996.)
		putchar('s');

    /*
	 *S_IRWXU    00700     mask for file owner permissions
	 *S_IRUSR    00400     owner has read permission
	 *S_IWUSR    00200     owner has write permission
	 *S_IXUSR    00100     owner has execute permission
     */

	if ((m & S_IRUSR) == S_IRUSR)
	{
		putchar('r');
	}
	else
	{
		putchar('-');
	}
	if ((m & S_IWUSR) == S_IWUSR)
	{
		putchar('w');
	}
	else
	{
		putchar('-');
	}
	if ((m & S_IXUSR) == S_IXUSR)
	{
		putchar('x');
	}
	else
	{
		putchar('-');
	}
	printf("\n");

	return 0;
}
