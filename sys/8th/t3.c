/*******************************************************
    主线程需要休眠，如果主线程不休眠，运行完会退出，
    新线程还没有机会运行，整个进程可能已经结束了。
    
    新线程和老线程共享数据空间，在新线程中修改指针指
    向的变量的值，会修改老线程中的变量的值。

    程序编译时需要使用库文件：
    gcc *.c -lpthread

*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10


void *func(void *data)
{
    printf("print : pth = %u\n", pthread_self());
    printf("print : pid = %d\n", getpid());
    printf("Hello world!\n");
    printf("data = %d\n", *(int *)data);
    *(int *)data = 1234;
    printf("data = %d\n", *(int *)data);

    if (fork() == 0)
    {
        printf("child : pid = %d  pth = %u *(int *)data = %d\n", getpid(), pthread_self(), *(int *)data);
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("parent : pid = %d  pth = %u  *(int *)data = %d\n", getpid(), pthread_self(), *(int *)data);
    }
}


int main(void)
{
    int count = 1111;
    int ret = 0;
    int i = 0;
    pthread_t pth[MAX] = {};
    
    for (i = 0; i < MAX; i++)
    {
        count++;
        printf("i = %d\n", i);
        pthread_create(pth + i, NULL, func, &count);
        if (0 != ret)
        {
            perror("pthread_create");
            return -1;
        }
    }

    printf("pth = %u\n", pth);
    printf("main : pth = %u\n", pthread_self());
    printf("main : pid = %d\n", getpid());


    sleep(1);       /* !!! */

    return 0;
}


