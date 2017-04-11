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



struct cls_t *insert(int size, int *count, struct cls_t *prev, struct cls_t cls)
{
	struct cls_t *new = NULL;

	new = (struct cls_t *)malloc(sizeof(struct cls_t) * (*count + 1));
	if (new == NULL)
	{
		return NULL;
	}

	memcpy(new, prev, sizeof(struct cls_t) * (*count));
	memcpy(new + (*count), &cls, sizeof(struct cls_t));
	free(prev);
	(*count)++;
	
	return new;
}

int main(void)
{
	int count = 0, i;
	struct cls_t cls;//定义临时变量
	struct cls_t *new = NULL;//接受用户数据数据
	struct cls_t *prev = NULL;//保存上一次数据

	while(1)
	{
		printf("please input %d name : ", count + 1);
		fgets(cls.name, sizeof(cls.name), stdin);
		if (cls.name[strlen(cls.name) - 1] == '\n')
			cls.name[strlen(cls.name) - 1] = '\0';

		if (!strcmp(cls.name, "exit"))
			break;
		cls.id = rand() % 100 + 10000;
		cls.age = rand() % 3 + 18;
		cls.sex = "MF"[rand() % 2];
		cls.cn = rand() % 20 + 80;
		cls.en = rand() % 30 + 70;

		new = insert(sizeof(struct cls_t), &count, new, cls);


	}

	for (i = 0; i < count; i++)
	{
		printf("name : %s id : %d age : %d sex : %c cn : %.2f en : %.2f\n", new[i].name, new[i].id, new[i].age, new[i].sex, new[i].cn, new[i].en);
	}
	free(new);
	return 0;
}
