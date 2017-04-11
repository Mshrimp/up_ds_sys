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

int main(int argc, char *argv[])
{
	int shm;
	key_t key;
	key = ftok("./", 123);
	char *p = NULL;

	if (key < 0)
	{
		return -1;
	}
	shm = shmget(key, 1024, IPC_CREAT | 0600);
	if (shm < 0)
	{
		return -1;
	}

	printf("shm = %d\n", shm);

	p = shmat(shm, NULL, 0);
	if (p == NULL)
	{
		return -1;
	}
	printf("p = %p\n", p);

	if (fork() == 0)
	{
		strcpy(p, argv[1]);//写入内存中
		exit(0);
	}

	wait(NULL);
	/*shmdt(p);*/
	shmctl(shm, IPC_RMID, NULL);
	p = shmat(shm, NULL, 0);
	printf("p = %s\n", p);

	return 0;
}
