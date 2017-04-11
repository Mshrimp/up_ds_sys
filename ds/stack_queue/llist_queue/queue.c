#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>

QUEUE *queue_create(int size, int max)
{
    QUEUE *handle = NULL;

    handle = (QUEUE *)malloc(sizeof(QUEUE));
    ERR(NULL == handle, goto ERR1);

    handle->head.next = &handle->head;
    handle->head.prev = &handle->head;
    handle->size = size;
    handle->max = max;
    handle->num = 0;

    return handle;
ERR2:
    free(handle);
ERR1:
    return NULL;
}

void queue_destroy(QUEUE *handle, queue_op_t *op)
{
    struct node_t *tail = handle->head.next, *save = NULL; 

    while (tail != &handle->head)
    {
        save = tail->next;
        if (op == NULL)
            free(tail->data);
        else
            op(tail->data);
        free(tail);
        tail = save;
    } 
    free(handle);
}

void queue_clean(QUEUE *handle, queue_op_t *op)
{
    struct node_t *tail = handle->head.next, *save = NULL; 

    while (tail != &handle->head)
    {
        save = tail->next;
        if (op == NULL)
            free(tail->data);
        else
            op(tail->data);
        free(tail);
        tail = save;
    } 
    handle->head.next = &handle->head;
    handle->head.prev = &handle->head;
    handle->num = 0;
}

int queue_isempty(QUEUE *handle)
{
    if (handle->num == 0)
        return 1;
    return 0;
}

int queue_isfull(QUEUE *handle)
{
    if (handle->num == handle->max)
        return 1;
    return 0;
}

int queue_en(void *data, QUEUE *handle)
{
    struct node_t *new = NULL;

    ERR(NULL == data, goto ERR1);
    ERR(queue_isfull(handle), goto ERR1);

    new = (struct node_t *)malloc(sizeof(struct node_t));
    ERR(NULL == new, goto ERR1);

    new->data = (void *)malloc(handle->size);
    ERR(NULL == new->data, goto ERR2);

    memcpy(new->data, data, handle->size);
    new->next = &handle->head;
    new->prev = handle->head.prev;
    handle->head.prev->next = new;
    handle->head.prev = new;

    handle->num += 1;

    return 0;
ERR2:
    free(new);
ERR1:
    return -1;
}

void *queue_de(QUEUE *handle, queue_op_t *op)
{
    void *data = NULL;
    struct node_t *save = NULL;

    ERR(queue_isempty(handle), goto ERR1);
    data = (void *)malloc(handle->size);
    ERR(NULL == data, goto ERR1);

    memcpy(data, handle->head.next->data, handle->size);

    handle->num -= 1;
    save = handle->head.next;
    handle->head.next = save->next;
    save->next->prev = &handle->head;
    if (op == NULL)
        free(save->data);
    else
        op(save->data);
    free(save);

    return data;
ERR1:
    return NULL;
}

int queue_len(QUEUE *handle)
{
    return handle->num;
}

void queue_travel(queue_op_t *op, QUEUE *handle)
{
    struct node_t *tail = NULL;

    for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
    {
        op(tail->data);
    }
}
