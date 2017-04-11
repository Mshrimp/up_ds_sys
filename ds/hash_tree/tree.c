#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

struct tree_t{
	int data;//数据
	struct tree_t *left;//左孩子
	struct tree_t *right;//右孩子
};

//int **p
// p *p **p
void insert(int num, struct tree_t **root)
{
	struct tree_t *new = NULL;
	struct tree_t *tail = *root;

	new = (struct tree_t *)malloc(sizeof(struct tree_t));
	if (new == NULL)
	{
		return ;
	}

	new->data = num;
	new->left = NULL;
	new->right = NULL;

	if (*root == NULL)
	{
		*root = new;
	}
	else
	{
		while(1)
		{
			if (new->data >= tail->data)
			{
				if (tail->right == NULL)
				{
					tail->right = new;
					break;
				}
				tail = tail->right;
			}

			if (new->data < tail->data)
			{
				if (tail->left == NULL)
				{
					tail->left = new;
					break;
				}
				tail = tail->left;
			}
		}
	}
	return ;
}
//前序遍历
void fri(struct tree_t *root)
{
	if (root == NULL)
	{
		return ;
	}
	printf("%d ", root->data);
	fri(root->left);
	fri(root->right);
}
//中序遍历
void mid(struct tree_t *root)
{
	if (root == NULL)
	{
		return;
	}
	mid(root->left);
	printf("%d ", root->data);
	mid(root->right);
}
//后序遍历
void end(struct tree_t *root)
{
	if (root == NULL)
	{
		return;
	}
	end(root->left);
	end(root->right);
	printf("%d ", root->data);
}

void show(struct tree_t *root)
{
	static int lev = 0;
	int i;

	if (root == NULL)
	{
		return ;
	}

	lev++;
	show(root->right);
	lev--;
	for (i = 0; i < lev; i++)
	{
		printf("\t");
	}
	printf("%d\n", root->data);

	lev++;
	show(root->left);
	lev--;
}

//求最大值
struct tree_t *max(struct tree_t *root)
{
	if (root == NULL)
	{
		return NULL;
	}
	while(root-> right != NULL)
	{
		root = root->right;
	}

	return root;
}
//求最小值
struct tree_t *min(struct tree_t *root)
{
	if (root == NULL)
	{
		return NULL;
	}
	while(root-> left != NULL)
	{
		root = root->left;
	}

	return root;
}
//统计节点数
int count(struct tree_t *root)
{
	if (root == NULL)
	{
		return 0;
	}

	return 1 + count(root->left) + count(root->right);
}
//求树深度
int depth(struct tree_t *root)
{
	if (root == NULL)
	{
		return 0;
	}
	return 1 + (depth(root->left) > depth(root->right) ? depth(root->left) : depth(root->right));
}
//层次遍历
void lev(struct tree_t *root)
{
	struct tree_t *queue[MAX];
	int front = 0, end = 0;

	queue[end++] = root;

	while (front != end)
	{
		root = queue[front++];
		printf("%d ", root->data);
		if (root->left != NULL)
		{
			queue[end++] = root->left;
		}
		if (root->right != NULL)
		{
			queue[end++] = root->right;
		}
	}
	
}
//查找
struct tree_t *find(int key, struct tree_t *root)
{
	if (root == NULL)
	{
		return NULL;
	}

	while(1)
	{
		if (key > root->data)
		{
			if (root->right == NULL)
			{
				return NULL;
			}
			root = root->right;
		}
		else if (key < root->data)
		{
			if (root->left == NULL)
			{
				return NULL;
			}
			root = root->left;
		}
		else
		{
			return root;
		}
	}
}
//删除关键字
void del(int key, struct tree_t **root)
{
	struct tree_t *tail = *root;
	struct tree_t *parent = NULL;
	struct tree_t *l = NULL, *r = NULL, *new = NULL;
	if (*root == NULL)
	{
		return ;
	}

	while(1)
	{
		if (key > tail->data)
		{
			parent = tail;
			if (tail->right == NULL)
			{
				return ;
			}
			tail = tail->right;
		}
		else if (key < tail->data)
		{
			parent = tail;
			if (tail->left == NULL)
			{
				return;
			}
			tail = tail->left;
		}
		else
		{
			break;
		}
	}
	
	/*printf("parent = %d\n", parent->data);*/

	l = tail->left;
	r = tail->right;
	if (l == NULL && r != NULL)
	{
		new = r;
	}
	if (l != NULL && r == NULL)
	{
		new = l;
	}
	if (l != NULL && r != NULL)
	{
#if 0
	// l -> r
		min(r)->left = l;
		new = r;
#else

	// r -> l
		max(l)->right = r;
		new = l;
#endif
	}
	
	if (key == (*root)->data)
	{
		*root = new;
	}
	else
	{
		if (parent->data > key)
		{
			parent->left = new;
		}
		else
		{
			parent->right = new;
		}
	}

	free(tail);
}
//求最大值 最小值 节点数 深度  层次遍历 树打印 查找 删除
int main(void)
{
	int num;
	int i;
	struct tree_t *root = NULL;//定义空树
	struct tree_t *ind = NULL;
	srand(time(NULL));
	printf("old : ");

	for (i = 0; i < MAX; i++)
	{
		num = rand() % 100;
		printf("%d ", num);
		insert(num, &root);
	}
	printf("\n");

	printf("max = %d\n", max(root)->data);
	printf("min = %d\n", min(root)->data);
	printf("count = %d\n", count(root));
	printf("depth = %d\n", depth(root));
	printf("fri : ");
	fri(root);
	printf("\n");
	printf("mid : ");
	mid(root);
	printf("\n");
	printf("end : ");
	end(root);
	printf("\n");
	printf("lev : ");
	lev(root);
	printf("\n");
	printf("=========================\n");
	show(root);
	printf("=========================\n");
	int key;

	printf("please input del key : ");
	scanf("%d", &key);
	del(key, &root);
	printf("=========================\n");
	show(root);
	printf("=========================\n");
    /*
	 *ind = find(key, root);
	 *if (ind == NULL)
	 *{
	 *    printf("no find!\n");
	 *}
	 *else
	 *{
	 *    printf("ind = %d\n", ind->data);
	 *}
     */
	return 0;
}
