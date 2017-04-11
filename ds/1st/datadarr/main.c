#include "darr.h"

#define MAX 10

struct cls_t{
	char name[128];
	int id;
	int age;
	char sex;
	float cn;
	float en;
};

void ls(void *data)
{
	struct cls_t *stu = (struct cls_t *)data;

	printf("name : %s id : %d age : %d sex : %c cn : %.2f en : %.2f\n", stu->name, stu->id, stu->age, stu->sex, stu->cn, stu->en);
}

int cmp_name(void *str1, void *str2)
{
	return (strcmp((char *)str1, ((struct cls_t *)str2)->name));
}

int cmp_id(void *str1, void *str2)
{
	return *(int *)str1 - ((struct cls_t *)str2)->id;
}

int cmp_age(void *str1, void *str2)
{
	return (*(int *)str1 - ((struct cls_t *)str2)->age);
}

int cmp_sex(void *str1, void *str2)
{
	return (*(char *)str1 - ((struct cls_t *)str2)->sex);
}

int cmp_cn(void *str1, void *str2)
{
	return (*(float *)str1 - ((struct cls_t *)str2)->cn);
}

int cmp_en(void *str1, void *str2)
{
	return (*(float *)str1 - ((struct cls_t *)str2)->en);
}

int main(void)
{
	int count = 0, i, num = 0;
	char name[10] = {};
	int id = 0, age = 0;
	char sex = 0;
	float cn = 0, en = 0;
	char buf[128] = {}, key[128] = {};
	struct cls_t cls, stu = {"tomli", 10099, 20, 'M', 88.8, 99.9};
	DARR *handle = NULL;
	DARR *new = NULL;
	DARR *fnd = NULL;

	handle = darr_create(sizeof(struct cls_t));
	fnd = darr_create(sizeof(struct cls_t));
	ERRP(handle == NULL, "darr_create", goto ERR1);

	for (i = 0;  i < MAX; i++)
	{
		snprintf(cls.name, sizeof(cls.name), "stu_%c%c", rand() % 26 + 'a', rand() % 26 + 'a');
		cls.id = rand() % 100 + 10000;
		/*cls.age = i;*/
		cls.age = rand() % 3 + 18;
		cls.sex = "MF"[rand() % 2];
		cls.cn = rand() % 20 + 80;
		cls.en = rand() % 30 + 70;
 		
		darr_append(&cls, handle);
		/*darr_prepend(&cls, handle);*/
		/*my_darr_index_insert(4, &cls, handle);*/
	}
		darr_travel(handle, ls);
		printf("count = %d\n", darr_count(handle));

	//中间插入一个数据
/*
 *    darr_travel(handle, ls);
 *    printf("Please input bit:");
 *    scanf("%d", &num);
 *
 *    darr_index_insert(num, &stu, handle);
 */

	//左移和右移
    /*
	 *darr_travel(handle, ls);
	 *printf("Please input bit:");
     *scanf("%d", &num);
	 *[>darr_left(num, handle);<]
	 *darr_right(num, handle);
     */

	//查找关键字，并删除第一组找到的数据
    /*
	 *darr_travel(handle, ls);
	 *printf("count = %d\n", darr_count(handle));
	 *[>GETLINES("Please input a name to del:", key);<]
	 *[>darr_del(key, handle, cmp_name);<]
	 *
	 *printf("Please input an id:");
	 *scanf("%d", &id);
	 *darr_del(&id, handle, cmp_id);
     */

	//查找关键字，并删除所有匹配数据
/*
 *    [>printf("Please input an id:");<]
 *    [>scanf("%d", &id);<]
 *    [>darr_alldel(&id, handle, cmp_id);<]
 *
 *    printf("Please input a sex:");
 *    sex = getchar();
 *    darr_alldel(&sex, handle, cmp_sex);
 */

	//指定位置删除一组数据
    /*
	 *printf("Please input the num to del:");
	 *scanf("%d", &num);
	 *darr_index_del(num, handle);
     */

	//按关键字，查找第一组数据
	printf("Please input id to search:");
	scanf("%d", &id);
	new = darr_ind(&id, handle, cmp_id);
	darr_travel(new, ls);
	free(new);
	/*fnd = darr_all_find(&sex, handle, cmp_sex);*/

	//按关键字，查找所有数据
    /*
     *printf("Please input a sex:");
     *sex = getchar();
	 *
	 *darr_travel((DARR *)darr_all_find(&sex, handle, cmp_sex), ls);
	 *printf("count = %d\n", darr_count(fnd));
	 *free(fnd);
     */
    
	/*
	 *darr_travel(handle, ls);
	 *printf("count = %d\n", darr_count(handle));
     */
	darr_destroy(handle);

	return 0;
ERR1:
	return -1;
}

