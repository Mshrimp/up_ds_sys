#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

STACK *stack_create(int size, int max)
{
    STACK *handle = NULL;

    handle = (STACK *)malloc(sizeof(STACK));
    ERR(NULL == handle, goto ERR1);

    handle->head.next = &handle->head;
    handle->head.prev = &handle->head;
    handle->size = size;
    handle->max = max;
    handle->num = 0;

    return handle;
ERR1:
    return NULL;
}

void stack_destroy(STACK *handle, stack_op_t *op)
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

void stack_clean(STACK *handle, stack_op_t *op)
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

int stack_isempty(STACK *handle)
{
    if (handle->num == 0)
        return 1;
    return 0;
}

int stack_isfull(STACK *handle)
{
    if (handle->num == handle->max)
        return 1;
    return 0;
}

int stack_push(void *data, STACK *handle)
{
    struct node_t *new = NULL;

    ERR(NULL == data, goto ERR1);
    ERR(stack_isfull(handle), goto ERR1);

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

void *stack_pop(STACK *handle, stack_op_t *op)
{
    void *data = NULL;
    struct node_t *save = NULL;

    ERR(stack_isempty(handle), goto ERR1);

    data = (void *)malloc(handle->size);
    ERR(NULL == data, goto ERR1);

    handle->num -= 1;
    memcpy(data, handle->head.prev->data, handle->size); 

    save = handle->head.prev;
    save->prev->next = &handle->head;
    handle->head.prev = save->prev;
    if (op == NULL)
        free(save->data);
    else
        op(save->data);
    free(save);

    return data;
ERR1:
    return NULL;
}

void stack_travel(stack_op_t *op, STACK *handle)
{
    struct node_t *tail = NULL;

    for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
    {
        op(tail->data);
    }
}

int stack_store(const char *path, STACK *handle)
{
    FILE *fp = NULL;
    struct node_t *tail = NULL;

    fp = fopen(path, "w");
    ERR(NULL == fp, goto ERR1);

    fwrite(MAGIC, sizeof(char), strlen(MAGIC), fp);
    fwrite(&handle->max, sizeof(int), 1, fp);
    fwrite(&handle->size, sizeof(int), 1, fp);
    fwrite(&handle->num, sizeof(int), 1, fp);

    for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
    {
        fwrite(tail->data, handle->size, 1, fp); 
    }

    fclose(fp);

    return 0;
ERR1:
    return -1;
}

STACK *stack_load(const char *path)
{
    STACK *handle = NULL;
    FILE *fp = NULL;
    int max, size, num, i;
    char buf[128];
    void *tmp = NULL;

    fp = fopen(path, "r");
    ERR(NULL == fp, goto ERR1);

    ERR(!fread(buf, sizeof(char), strlen(MAGIC), fp), goto ERR2);
    ERR(strncmp(MAGIC, buf, strlen(MAGIC)) , goto ERR2);
    ERR(!fread(&max, sizeof(int), 1, fp), goto ERR2);
    ERR(!fread(&size, sizeof(int), 1, fp), goto ERR2);
    ERR(!fread(&num, sizeof(int), 1, fp), goto ERR2);

    handle = stack_create(size, max);
    ERR(NULL == handle, goto ERR2);

    tmp = (void *)malloc(size);
    ERR(NULL == tmp, goto ERR3);

    for (i = 0; i < num; i++)
    {
        ERR(fread(tmp, size, 1, fp) != 1, goto ERR4);
        ERR(stack_push(tmp, handle) != 0, goto ERR4);
    }

    free(tmp);
    fclose(fp);
    
    return handle;
ERR4:
    free(tmp);
    stack_destroy(handle, NULL);
ERR3:
    free(handle);
ERR2:
    fclose(fp);
ERR1:
    return NULL;
}

int stack_resize(int _max, STACK *handle)
{
    ERR(_max <= handle->num, goto ERR1);

    handle->max = _max;

    return 0;
ERR1:
    return -1;
}
