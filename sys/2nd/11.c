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

	ret = stat(argv[1], &s);
	if (ret < 0)
	{
		printf("stat failed!\n");
		return -1;
	}

	printf("stat success!\n");
	
	PRI(s.st_dev);     /* ID of device containing file */
	PRI(s.st_ino);     /* inode number */
	PRI(s.st_mode);    /* protection */
	PRI_O(s.st_mode);    /* protection */
	PRI(s.st_nlink);   /* number of hard links */
	PRI(s.st_uid);     /* user ID of owner */
	PRI(s.st_gid);     /* group ID of owner */
	PRI(s.st_rdev);    /* device ID (if special file) */
	PRI(s.st_size);    /* total size, in bytes */
	PRI(s.st_blksize); /* blocksize for filesyPRI(s.stem I/O */
	PRI(s.st_blocks);  /* number of blocks allocated */
	PRI(s.st_atime);   /* time of laPRI(s.st access */
	PRI(s.st_mtime);   /* time of laPRI(s.st modification */
	PRI(s.st_ctime);   /* time of laPRI(s.st PRI(s.status change */
	return 0;
}
