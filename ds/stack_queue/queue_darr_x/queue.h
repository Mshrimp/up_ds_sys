#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10


#define ERRP(con, func, ret)	do{									\
									if (con)						\
									{								\
										printf(#func" failed!\n");	\
										ret;						\
									}								\
								}while(0)

typedef void(queue_op_t)(void *);

typedef struct queue_t
{
	void *data;
	int size;
	int max;
	int front;
	int end;
	void *save;
}QUEUE;


//队列初始化
QUEUE *queue_create(int size, int max);
//队列数据清零
void queue_clean(QUEUE *handle);
//检查队列是否已满，满返回1，不满返回0
int queue_is_full(QUEUE *handle);
//检查队列是否为空，为空返回1，不为空返回0
int queue_is_empty(QUEUE *handle);
//计算队列中元素个数，返回个数
int queue_num(QUEUE *handle);
//遍历队列中各个数据元素
void queue_travel(QUEUE *handle, queue_op_t *op);
//队列数据入队
void queue_qe(void *data, QUEUE *handle);
//队列数据出队
void *queue_de(QUEUE *handle);
//队列数据空间释放
void queue_destory(QUEUE *handle);
//队列内存空间扩容
void queue_resize(int new_max, QUEUE *handle);


#endif

