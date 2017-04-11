/***************************************************
	test-DS-1th-1:
	动态分配内存存储不定个数结构体数组内容
***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct st_t
{
	char name[128];
	int id;
	int age;
	char sex;
};


int main(int argc, char *argv[])
{
	int i = 0;
	int count = 0;
	struct st_t stu;
	struct st_t *new = NULL;
	struct st_t *prev = NULL;

	srand(time(NULL));

	while (1)
	{
		//手动输入结构体信息
	#if 1
		printf("Please input %d name:", count + 1);
		fgets(stu.name, sizeof(stu.name), stdin);
		if (stu.name[strlen(stu.name) - 1] == '\n')
			stu.name[strlen(stu.name) - 1] = '\0';
		if (!strcmp(stu.name, "exit"))	//检测到输入exit退出循环
		{
			break;
		}
		//随即获取学生的id,age,sex
		stu.id = rand()%1000+1000;
		stu.age = rand()%4+17;
		stu.sex = "MF"[rand()%2];

	#elif
		printf("Please input %d name:", count + 1);
		scanf("%s", stu.name);
		if (!memcmp(stu.name, "exit", 4))
		{
			break;
		}
		printf("Please input %d id:", count + 1);
		scanf("%d", &stu.id);
		getchar();
		printf("Please input %d age:", count + 1);
		scanf("%d", &stu.age);
		getchar();
		printf("Please input %d sex:", count + 1);
		/*scanf("%c", &stu.sex);*/
		stu.sex = getchar();
	#endif

		new = (struct st_t *)malloc(sizeof(struct st_t) * (count + 1));	//分配结构体类型动态内存空间
		if (NULL == new)
		{
			perror("Malloc struct");
			return -1;
		}

		memcpy(new, prev, sizeof(struct st_t) * count);	//将动态分配的内存中旧地址的结构体数据拷贝到新地址中
		memcpy(new + count, &stu, sizeof(struct st_t));	//将当前输入的结构体数据内容存储在新结构体中

		free(prev);
		prev = new;
		count++;

	}

	for (i = 0; i < count; i++)	//以结构体数组形式逐个打印动态内存中的内容
	{
		printf("new[%d] : name = %-8s id = %-8d age = %-6d sex = %c\n", i+1, new[i].name, new[i].id, new[i].age, new[i].sex);
	}

	free(new);

	return 0;
}
