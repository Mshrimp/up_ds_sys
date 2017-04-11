#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int main(void)
{
    pthread_t pth;      //unsigned long int 无符号长整形

    printf("pid = %d\n", getpid());
    printf("pthread_self = %d\n", pthread_self());
    printf("pthread_self = %u\n", pthread_self());
    printf("pthread_self = %lu\n", pthread_self());

    /*getchar();*/

    return 0;
}

