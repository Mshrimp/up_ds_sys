#include "tree.h"



TREE *tree_create(int size, int max)
{
	TREE *handle = NULL;

	handle = (TREE *)malloc(sizeof(TREE));
	ERRP(NULL == handle, tree_create handle malloc, goto ERR1);

	handle->root->data = (void *)malloc(size);
	ERRP(NULL == handle->root->data, tree_create handle->root malloc, goto ERR2);

	handle->size = size;
	handle->num = max;


ERR2:
	free(handle);
ERR1:
	return NULL;
}


