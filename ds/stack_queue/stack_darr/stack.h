#ifndef __KEN_STACK_H__
#define __KEN_STACK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERRP(con, err, ret) do{						\
					if (con)						\
					{								\
						fprintf(stderr, "%s", err);	\
						ret;						\
					}								\
				}while(0)

typedef void (stack_op_t)(void *);

//抽象数据类型
typedef struct stack_t{
	void *data;//栈整个空间大小
	int size;//数据类型
	int max;//栈长度
	int top;//栈顶元素
	//void *save;//出栈元素
	//stack_op_t *travel;
}STACK;

//顺序表封装栈 -> 数栈
STACK *stack_create(int size, int max);//初始化
int stack_is_full(STACK *handle);//判断是否满栈
int stack_is_empty(STACK *handle);//判断是否是空栈
int stack_num(STACK *handle);//求栈长度
int stack_clean(STACK *handle);//栈清空
void stack_resize(int new_max, STACK *handle);//栈空间不足后扩容
void stack_push(void *data, STACK *handle);//入栈
void *stack_pop(STACK *handle);//出栈
void stack_travel(STACK *handle, stack_op_t *);//遍历
void stack_destroy(STACK *handle);//销毁
void stack_store(const char *path, STACK *handle);//存储
STACK *stack_load(const char *path);//加载

#endif /*KEN_STACK_H*/






