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


struct stu_t
{
	char name[32];
	int age;
	char sex;
};


int main(int argc, char *argv[])
{
	key_t key;
	int ret;
	struct stu_t stu;
	int i = 0;
	srand(time(NULL));
	key = ftok("/tmp", 11);
	if (key < 0)
	{
		printf("ftok failed!\n");
		return -1;
	}
	printf("key = %0x\n", key);

	/*ret = msgget(1, IPC_CREAT | IPC_EXCL | 0666);*/
	ret = msgget(1, IPC_CREAT | 0666);
	if (ret < 0)
	{
		printf("msgget failed!\n");
		perror("msgget");
		return -1;
	}

	printf("msgget success!\n");
	printf("ret = %d\n", ret);

	int size;
	/*for (i = 0; i < 10; i++)*/
	{
		snprintf(stu.name, sizeof(stu.name), "stu_%c%c", rand() % 26 + 'a', rand() % 26 + 'a');
		stu.age = rand() % 5 + 15;
		stu.sex = "FM"[rand() % 2];

		size = msgsnd(ret, &stu, sizeof(struct stu_t), 0);
		if (size < 0)
		{
			return -1;
		}
		printf("stu.name = %s | stu.age = %d | stu.sex = %c\n", stu.name, stu.age, stu.sex);
		printf("size = %d\n", size);
	}
	return 0;
}
