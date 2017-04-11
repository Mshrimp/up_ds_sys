/*******************************************************
    主线程需要休眠，如果主线程不休眠，运行完会退出，
    新线程还没有机会运行，整个进程可能已经结束了。
    
    线程中创建进程，线程号不变

    程序编译时需要使用库文件：
    gcc *.c -lpthread

*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print(void *data)
{
    int i = 0;
    int count = 1000;

    printf("print : pth = %u\n", pthread_self());
    printf("print : pid = %d\n", getpid());
    printf("Hello world!\n");

    for (i = 0; i < 10; i++)
    {
        if (fork() == 0)
        {
            count++;
            printf("child : pid = %d  pth = %u  count = %d\n", getpid(), pthread_self(), count);
            exit(0);
        }
    }

    for (i = 0; i < 10; i++)
    {
        wait(NULL);
    }

    printf("parent : pid = %d  pth = %u  count = %d\n", getpid(), pthread_self(), count);
}


int main(void)
{
    pthread_t pth;
    int count = 0;
    int ret = 0;

    pthread_create(&pth, NULL, print, NULL);
    if (0 != ret)
    {
        perror("pthread_create");
        return -1;
    }

    printf("pth = %u\n", pth);
    printf("main : pth = %u\n", pthread_self());
    printf("main : pid = %d\n", getpid());


    sleep(1);       /* !!! */

    return 0;
}


