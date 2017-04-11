#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//#include <errno.h>

//extern errno;//声明
int e;
char *err[] = {"errno", 
				"Operation not permitted",
				"No such file or directory",
				};
#define	EPERM		 1	/* Operation not permitted */
#define	ENOENT		 2	/* No such file or directory */
/*
 *
 *#define	ESRCH		 3	[> No such process <]
 *#define	EINTR		 4	[> Interrupted system call <]
 *#define	EIO		 5	[> I/O error <]
 *#define	ENXIO		 6	[> No such device or address <]
 *#define	E2BIG		 7	[> Argument list too long <]
 *#define	ENOEXEC		 8	[> Exec format error <]
 *#define	EBADF		 9	[> Bad file number <]
 *#define	ECHILD		10	[> No child processes <]
 *#define	EAGAIN		11	[> Try again <]
 *#define	ENOMEM		12	[> Out of memory <]
 *#define	EACCES		13	[> Permission denied <]
 *#define	EFAULT		14	[> Bad address <]
 *#define	ENOTBLK		15	[> Block device required <]
 *#define	EBUSY		16	[> Device or resource busy <]
 */

int main(void)
{
	int fd;

	fd = open("./test", O_RDONLY);
	if (fd == -1)
	{
		if(1)
		{
			e = EPERM;
		}
		printf("errno = %d\n", e);
		return -1;
	}
	return 0;
}
