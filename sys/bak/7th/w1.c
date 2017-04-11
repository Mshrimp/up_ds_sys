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

//封装定时器：
//ITIMER_REAL => SIGALRM

typedef void (FUNC)(void *);//函数指针
typedef void (*sighandler_t)(int);


//定时器结构体信息
struct time_t{
	int t;//表示循环时间
	int count;//表示累加时间，时间到则指向打印函数
	void *data;//表示执行打印函数的数据
	FUNC *func;//执行打印函数
	int flag;//是否循环打印
	struct time_t *next;//指向下一个节点
	struct time_t *prev;//指向上一个节点
};

//全局链表头
struct time_t head;

//打印函数
void hello(void *data)
{
	printf("%s\n", (char *)data);
}
//定时器插入链表中
void add(int t, FUNC *func, void *data, int flag)
{
	struct time_t *new = NULL;

	new = (struct time_t *)malloc(sizeof(struct time_t));
	if (new == NULL)
	{
		printf("new failed!\n");
		return ;
	}
	new->t = t;
	new->count = 0;
	new->data = data;
	new->func = func;
	new->flag = flag;

	//节点插入链表中
	new->next = &head;
	new->prev = head.prev;
	head.prev->next = new;
	head.prev = new;

}
//执行信号函数, 就是遍历链表
void sig_func(int sig)
{
	struct time_t *tail = NULL, *save = NULL;

	for (tail = head.next; tail != &head; tail = save)
	{
		save = tail->next;
		tail->count++;
		if (tail->count == tail->t)
		{
			tail->func(tail->data);
			if (tail->flag)
			{
				tail->count = 0;
			}
			else
			{
				tail->next->prev = tail->prev;
				tail->prev->next = tail->next;
				free(tail);
			}
		}
	}
}
//退出函数
void sig_exit(void)
{
	struct time_t *tail = NULL, *save = NULL;

	printf("exit!\n");
	for (tail = head.next; tail != &head; tail = save)
	{
		save = tail->next;
		free(tail);
	}
	head.next = &head;
	head.prev = &head;
}
//实现定时器
void init_timer(void)
{
	int ret;
	struct itimerval it;
	sighandler_t sig;

	//循环双向链表
	head.next = &head;
	head.prev = &head;

	if (signal(SIGALRM, sig_func) == SIG_ERR)
	{
		printf("signal failed!\n");
		return ;
	}

	//循环时间
	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 0;

	//开始时间
	it.it_value.tv_sec = 0;
	it.it_value.tv_usec = 1000;

	ret = setitimer(ITIMER_REAL, &it, NULL);
	if (ret < 0)
	{
		printf("setitimer failed!\n");
		return ;
	}
	atexit(sig_exit);
}
int main(int argc, char *argv[])
{
	init_timer();

	add(1, hello, "1111", 1);
	add(3, hello, "3333", 0);
	add(7, hello, "7777", 1);
	add(9, hello, "9999", 0);

	getchar();
	return 0;
}





