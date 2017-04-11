#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print(void *data)
{
    printf("print : pth = %u\n", pthread_self());
    printf("print : pid = %d\n", getpid());
    printf("Hello world!\n");
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


    sleep(1);

    return 0;
}


