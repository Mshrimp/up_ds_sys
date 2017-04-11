#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
	//stat
	int ret;
	struct stat s;
	char *mode[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
	char type[] = " pc d b - l s";
	
    /*
	 *S_IFMT     0170000   bitmask for the file type bitfields
	 *S_IFSOCK   0140000   12 s socket
	 *S_IFLNK    0120000   10 l symbolic link
	 *S_IFREG    0100000   8  - regular file
	 *S_IFBLK    0060000   6  b block device
	 *S_IFDIR    0040000   4  d directory
	 *S_IFCHR    0020000   2  c character device
	 *S_IFIFO    0010000   1  p FIFO
     */

	ret = lstat(argv[1], &s);
	if (ret < 0)
	{
		return -1;
	}
	printf("%c%s%s%s", type[(s.st_mode & S_IFMT) >> 12], mode[(s.st_mode & S_IRWXU) >> 6], mode[(s.st_mode & S_IRWXG) >> 3], mode[s.st_mode & S_IRWXO]);

	return 0;
}
