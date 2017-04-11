
//防止重文件重复包含
#ifndef __KEN_LLIST_H__
#define __KEN_LLIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX 10
//排序宏
//升序
#define LLIST_SORT_ASC 1
//降序
#define LLIST_SORT_DASC 2

//插入宏
#define LLIST_APPEND_INSERT -1
#define LLIST_PREPEND_INSERT -2
#define LLIST_INDEX_INSERT -3
#define LLIST_SORT_INSERT -4


#define ERRP(con, func, ret)  do{							\
						if (con)							\
						{									\
							fprintf(stderr, #func" failed!\n");\
							ret;							\
						}									\
					}while(0)

//函数指针
typedef void (llist_love_t)(char *);
//第一个参数表示接受数据信息
//第二个参数表示用户数据伴侣名
typedef void (llist_op_t)(void *, char **);
typedef int (llist_cmp_t)(void *, void *);

//char *name[MAX] = {"xiaocao", "xiaohua", "xiaohong", "xiaofang", "xiaoxuan", "xiaomeng", "xiaohei", "xiaobai", "xiaolv", "xiaoshe"};
//双向链表节点信息
struct node_t{
	void *data;//数据域
	struct node_t *next;//指针域 保存下一个节点地址
	struct node_t *prev;//指针域 保存上一个节点地址
};
//抽象数据类型
typedef struct llist_t{
	struct node_t head;//头节点
	int size;//数据类型
	int num;//数据大小
}LLIST;

//有头 无序 循环 双向链表

//函数声明
//初始化 需要数据类型
LLIST *llist_create(int size);
//尾插函数 就是把数据链接到链表结尾
void llist_append(void *data, LLIST *handle);
void llist_prepend(void *data, LLIST *handle);//前插
void llist_index_insert(int index, void *data, LLIST *handle);//指定位置插入
void llist_sort_insert(void *data, llist_cmp_t *cmp, LLIST *handle);//插入排序
//删除
void llist_del(void *key, llist_cmp_t *cmp, LLIST *handle);
void llist_alldel(void *key, llist_cmp_t *cmp, LLIST *handle);//删除所有
void llist_index_del(int index, LLIST *handle);//指定位置删除
//查找
void *llist_ind(void *key, llist_cmp_t *cmp, LLIST *handle);//查找匹配
LLIST *llist_find(void *key, llist_cmp_t *cmp, LLIST *handle);//查找所有
void *llist_index_find(int index, LLIST *handle);//位置查找
int llist_num(LLIST *handle);//求长度
void llist_sort(int flag, llist_cmp_t *cmp, LLIST *handle);//排序
int llist_store(const char *path, LLIST *handle);//存储
LLIST *llist_load(const char *path);//加载
//遍历。就是打印出所有数据信息
void llist_travel(LLIST *handle, llist_op_t *op, char **);
//销毁函数，就是释放空间地址
void llist_destroy(LLIST *handle, LLIST *find);
#endif /*KEN_LLIST_H*/










