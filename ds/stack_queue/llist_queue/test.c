#include <stdio.h>
#include <queue.h>

#define MAX         10

void ls(const void *data)
{
    printf("%d ", *(int *)data);
}

int main(void)
{
    int i, n, *val = NULL;
    QUEUE *handle = NULL;

    handle = queue_create(sizeof(int), MAX);

    for (i = 0; i < MAX; i++)
    {
        n = rand() % MAX;
        queue_en(&n, handle);
        /*queue_travel(ls, handle);*/
        /*printf("\n");*/
    }

    for (i = 0; i < MAX; i++)
    {
        val = queue_de(handle, NULL); 
        if (val != NULL)
            printf("%d ", *val);
        free(val);
    }
    printf("\n");

    queue_destroy(handle, NULL);

    return 0;
}
