#ifndef __QUEUE_LIST_H__
#define __QUEUE_LIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 10


#define ERRP(con, func, ret)	do{										\
									if (con)							\
									{									\
										printf(#func" failed!\n");		\
										ret;							\
									}									\
								}while(0)


typedef void (queue_op_t)(void *);

struct node_t
{
	void *data;
	struct node_t *next;
	struct node_t *prev;
};

//抽象数据类型
typedef struct queue_t{
	struct node_t head;
	int size;
	int count;
}QUEUE_LIST;


QUEUE_LIST *queue_create(int size);
int queue_num(QUEUE_LIST *handle);
int queue_is_empty(QUEUE_LIST *handle);
void queue_push(void *data, QUEUE_LIST *handle);
void *queue_pop(QUEUE_LIST *handle);
void queue_travel(QUEUE_LIST *handle, queue_op_t *op);
void queue_destory(QUEUE_LIST *handle);
void queue_store(const char *path, QUEUE_LIST *handle);
QUEUE_LIST *queue_load(const char *path);


#endif

