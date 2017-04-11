#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct cls_t{
	char name[128];
	int id;
	int age;
	char sex;
	float cn;
	float en;
};


int a;
//抽象数据类型
struct darr_t{
	void *data;//数据
	int size;//类型
	int num;//长度
};

void *insert(int size, int *count, void *prev, void *cls)
{
	void *new = NULL;

	new = (void *)malloc(size * (*count + 1));
	if (new == NULL)
	{
		return NULL;
	}

	memcpy(new, prev, size * (*count));
	memcpy(new + size * (*count), cls, size);
	free(prev);
	(*count)++;
	
	return new;
}

int main(void)
{
	int count = 0, i;
	struct cls_t cls;//定义临时变量
	/*struct cls_t *new = NULL;//接受用户数据数据*/
	int *new = NULL;//接受用户数据数据
	struct cls_t *prev = NULL;//保存上一次数据
	int num;
	while(1)
	{
/*
 *        printf("please input %d name : ", count + 1);
 *        fgets(cls.name, sizeof(cls.name), stdin);
 *        if (cls.name[strlen(cls.name) - 1] == '\n')
 *            cls.name[strlen(cls.name) - 1] = '\0';
 *
 *        if (!strcmp(cls.name, "exit"))
 *            break;
 *        cls.id = rand() % 100 + 10000;
 *        cls.age = rand() % 3 + 18;
 *        cls.sex = "MF"[rand() % 2];
 *        cls.cn = rand() % 20 + 80;
 *        cls.en = rand() % 30 + 70;
 */
 		printf("please input number : ");
		scanf("%d", &num);

		if (num == -1)
			break;

		/*new = insert(sizeof(struct cls_t), &count, new, &cls);*/
		new = insert(sizeof(int), &count, new, &num);


	}

	for (i = 0; i < count; i++)
	{
		/*printf("name : %s id : %d age : %d sex : %c cn : %.2f en : %.2f\n", new[i].name, new[i].id, new[i].age, new[i].sex, new[i].cn, new[i].en);*/
		printf("%d ", new[i]);
	}
	printf("\n");
	free(new);
	return 0;
}
