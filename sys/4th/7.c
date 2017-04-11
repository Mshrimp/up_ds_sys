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

int main(int argc, char *argv[])
{
	//运行状态
	printf("hello!\n");
	getchar();
    /*
	 *while(1)
	 *    ;
     */
	//不可中断睡眠状态
    /*
	 *if (!vfork())
	 *{
	 *    sleep(100);
	 *}
     */
	return 0;
}
