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

void lock(int sem, int num)
{
	struct sembuf op;
	op.sem_num = num;
	op.sem_op = -1;
	op.sem_flg = 0;
	semop(sem, &op, 1);
}

void unlock(int sem, int num)
{
	struct sembuf op;
	op.sem_num = num;
	op.sem_op = 1;
	op.sem_flg = 0;
	semop(sem, &op, 1);
}

int main(int argc, char *argv[])
{
	key_t key;
	int sem;

	key = ftok("./", 1122);
	if (key < 0)
	{
		return -1;
	}
	sem = semget(key, 1, IPC_CREAT | 0666);
	if (sem < 0)
	{
		return -1;
	}

	semctl(sem, 0, SETVAL, 1);

	int fd, i;
	char buf[1024];
	

	fd = open("./test", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		return -1;
	}

	if (fork() == 0)
	{
		lock(sem, 0);
		for (i = 0; i < 1000; i++)
		{
			if (i == 888)
			{
				goto loop;
			}
			snprintf(buf, sizeof(buf), "child : count = %d\n", i);
			write(fd, buf, strlen(buf));
		}
		unlock(sem, 0);
		loop:
		exit(0);
	}
	else
	{
		usleep(100);
		lock(sem, 0);
		for (i = 0; i < 1000; i++)
		{
			snprintf(buf, sizeof(buf), "parent : count = %d\n", i);
			write(fd, buf, strlen(buf));
		}
		unlock(sem, 0);	
	}

	wait(NULL);



	return 0;
}
