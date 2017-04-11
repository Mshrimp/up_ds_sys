#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int fd;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *write_data(void *data)
{
    char buf[128] = {};
    int count = 1;
    int ret = 0;

    pthread_mutex_lock(&mutex);

    while (1)
    {
        snprintf(buf, sizeof(buf), "%s : count = %d\n", (char *)data, count++);
        ret = write(fd, buf, strlen(buf));
        if (ret < 0)
        {
            perror("write data");
        }

        if (count > 1000)
        {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}


int main(void)
{
    pthread_t pth;
    int ret = 0;

    fd = open("./test", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd < 0)
    {
        perror("open file");
        exit(-1);
    }

    pthread_create(&pth, NULL, write_data, "child");

    write_data("parent");

    return 0;
}

