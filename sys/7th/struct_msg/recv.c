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

/*
 *struct a_t{
 *    int type;
 *    struct cls_t cls;
 *};
 */

struct cls_t{
	int type;

	char name[128];
	int age;
	char sex;
};

struct tea_t{
	int type;

	int id;
	char *name[128];
};

int main(int argc, char *argv[])
{
	key_t key;
	int ret;
	struct cls_t stu;
	struct tea_t tea;


	key = ftok("/tmp", 11);
	if (key < 0)
	{
		printf("ftok failed!\n");
		return -1;
	}

	ret = msgget(key, IPC_CREAT);
	if (ret < 0)
	{
		printf("msgget failed!\n");
		return -1;
	}


	int size;
	if (atoi(argv[1]) == 1)
	{
		size = msgrcv(ret, &stu, sizeof(stu), atoi(argv[1]), 0);
		if (size < 0)
		{
			printf("msgrcv failed!\n");
			return -1;
		}
		printf("name : %s age : %d  sex : %c\n", stu.name, stu.age, stu.sex);
	}
	else
	{
		size = msgrcv(ret, &tea, sizeof(tea), atoi(argv[1]), 0);
		printf("id : %d name : %s\n", tea.id, tea.name);
	}
	return 0;
}
