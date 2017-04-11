#ifndef __KEN_DARR_H__
#define __KEN_DARR_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//容错宏
#define ERRP(con, func, ret)	do{										\
									if (con)							\
									{									\
										printf("%s frailed!\n", func);	\
										ret;							\
									}									\
								}while(0)

//输入一个字符串
#define GETLINES(string, buf)	do{										\
									printf(string);						\
									fgets(buf, sizeof(buf), stdin);		\
									if (buf[strlen(buf) - 1] == '\n')	\
									{									\
										buf[strlen(buf) - 1] = '\0';	\
									}									\
								}while(0)

//函数指针
typedef void (darr_op_t)(void *);
typedef int (darr_cmp_t)(void *, void *);

//抽象数据类型
typedef struct darr_t{
	void *data;//数据
	int size;//类型
	int num;//长度
}DARR;


DARR *darr_create(int size);//初始化
int darr_append(void *data, DARR *handle);//尾插
int darr_prepend(void *data, DARR *handle);//头插
int darr_index_insert(int index, void *data, DARR *handle);//指定位置插入
int my_darr_index_insert(int index, void *data, DARR *handle);//指定位置插入
int darr_count(DARR *handle); //求数据个数
void darr_left(int bit, DARR *handle);	//左移
void darr_right(int bit, DARR *handle);//右移
void darr_del(void *key, DARR *handle, darr_cmp_t *cmp);	//按关键字查找，删除找到的第一组数据
void darr_alldel(void *key, DARR *handle, darr_cmp_t *cmp);	//按关键字查找，删除找到所有匹配数据
void darr_index_del(int index, DARR *handle);	//指定位置删除
void *darr_ind(void *key, DARR *handle, darr_cmp_t *cmp);	//按关键字查找第一组数据
DARR *darr_all_find(void *key, DARR *handle, darr_cmp_t *cmp);//查找所有
void *darr_index_find(int index, DARR *handle);//指定位置查找
void darr_sort(DARR *handle, darr_cmp_t *cmp);//排序
void darr_store(const char *path, DARR *handle);//存储
DARR *darr_load(const char *path);//加载
void darr_travel(DARR *handle, darr_op_t *op);//遍历
void darr_destroy(DARR *handle);//销毁


#endif /*__KEN_DARR_H__*/
