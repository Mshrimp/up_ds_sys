#ifndef __HASH_H__
#define __HASH_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct node_t
{
	void *data;
	struct node_t *next;
	struct node_t *prev;
};


typedef struct llist_t
{
	struct node_t *head;
	int size;
	int count;
}HASH;


#define ERRP(con, func, ret)	do{									\
									if (con)						\
									{								\
										printf(#func" failed!\n");	\
										ret;						\
									}								\
								}while(0)

#define MAX 20

typedef void (hash_op_t)(void *);
typedef int (hash_cmp_t)(void *, void *);

int hash_mod(void *data);
HASH *hash_create(int size, int max);
void hash_insert(void *data, HASH *handle);
void hash_travel(HASH *handle, hash_op_t *op);
void hash_destory(HASH *handle);
void *hash_find(void *key, HASH *handle, hash_cmp_t *cmp);




#endif/*__HASH+H__*/

