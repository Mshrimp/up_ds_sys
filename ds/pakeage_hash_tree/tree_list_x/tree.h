#ifndef __TREE_H__
#define __TREE_H__

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



struct node_t
{
	void *data;
	struct node_t *left;
	struct node_t *right;
};


typedef struct tree_t
{
	struct node_t *root;
	int size;
	int num;
}TREE;


TREE *tree_create(int size, int max);









#endif/*__TREE_H__*/

