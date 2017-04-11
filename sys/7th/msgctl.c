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

struct cls_t{
	int type;
	char name[128];
	int age;
	char sex;
};

struct tea_t{
	int type;
	int id;
	char name[128];
};

int main(int argc, char *argv[])
{
	key_t key;
	int ret;
	struct cls_t cls = {1, "tom", 18, 'M'};
	struct tea_t tea = {2, 10001, "张三"};
	
	key = ftok("/tmp", 11);
	if (key < 0)
	{
		printf("ftok failed!\n");
		return -1;
	}
	/*printf("key = %0x\n", key);*/

	ret = msgget(key, IPC_CREAT);
	if (ret < 0)
	{
		printf("msgget failed!\n");
		return -1;
	}


	msgctl(ret, IPC_RMID, NULL);

	return 0;
}
