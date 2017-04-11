/***************************************************************************
    大小端问题：
        大端模式：网络一般大端
            高地址存储低位字节数据
            低地址存储高位字节数据
        小端模式：主机一般小端
            高地址存储高位字节数据
            低地址存储低位字节数据
            
***************************************************************************/

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
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main(int argc, char *argv[])
{
	int i;
	int a = 0x11223344;		//整型数据占4个字节

	if (*((char *)&a) == 0x11)	//将int型地址强制转换为char型地址，并取间接引用
	{
		printf("big!\n");
	}
	else
	{
		printf("little!\n");
	}

	for (i = 0; i < 4; i++)		//按地址打印数据
	{
		printf("%p : %0x\n", (char *)&a + i, *((char *)&a + i));
	}
	return 0;
}
