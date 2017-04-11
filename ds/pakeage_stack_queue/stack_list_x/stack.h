#ifndef __STACK_LIST_H__
#define __STACK_LIST_H__

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


typedef void (stack_op_t)(void *);

struct node_t
{
	void *data;
	struct node_t *next;
	struct node_t *prev;
};

//抽象数据类型
typedef struct stack_t{
	struct node_t head;
	int size;
	int top;
	//stack_op_t *travel;
}STACK_LIST;


STACK_LIST *stack_create(int size);
int stack_num(STACK_LIST *handle);
int stack_is_empty(STACK_LIST *handle);
void stack_push(void *data, STACK_LIST *handle);
void *stack_pop(STACK_LIST *handle);
void stack_travel(STACK_LIST *handle, stack_op_t *op);
void stack_destory(STACK_LIST *handle);
void stack_store(const char *path, STACK_LIST *handle);
STACK_LIST *stack_load(const char *path);


#endif

