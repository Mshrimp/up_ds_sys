#include "llist.h"


void fri(char *s)
{
	printf("%s\n", s);
}
struct cls_t{
	char name[128];
	int id;//4
	int age;//4
	char sex;//4
	int c;//4
	int ds;//4
	int result;//4
	int flag;//4
	llist_love_t *love;//4
};

void ls(void *data, char **s)
{
	struct cls_t *sp = (struct cls_t *)data;

	printf("name : %s | id : %d | age : %d | sex : %c | c : %d | ds : %d | result : %d | love : ", sp->name, sp->id, sp->age, sp->sex, sp->c, sp->ds, sp->result);
	sp->love(s[sp->flag]);
}

int sort_name(void *d1, void *d2)
{
	return strcmp(((struct cls_t *)d1)->name, ((struct cls_t *)d2)->name);
}
int cmp_name(void *d1, void *d2)
{
	return strcmp((char *)d1, ((struct cls_t *)d2)->name);
}
int sort_id(void *d1, void *d2)
{
	return ((struct cls_t *)d1)->id - ((struct cls_t *)d2)->id;
}

int cmp_love(void *d1, void *d2)
{
	return *(int *)d1 - ((struct cls_t *)d2)->flag;
}
int cmp_stoi(char *s, char **name)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		if (strcmp(s, name[i]) == 0)
			return i;
	}
	return -1;
}

int cmp_age(void *d1, void *d2)
{
	return *(int *)d1 - ((struct cls_t *)d2)->age;
}
int cmp_sex(void *d1, void *d2)
{
	return *(int *)d1 - ((struct cls_t *)d2)->sex;
}
int sort_result(void *d1, void *d2)
{
	return ((struct cls_t *)d1)->result - ((struct cls_t *)d2)->result;
}
int sort_age(void *d1, void *d2)
{
	return ((struct cls_t *)d1)->age - ((struct cls_t *)d2)->age;
}
int main(int argc, char *argv[])
{
	int i, num;
	char tmp[128], ch;
	struct cls_t cls, *p = NULL, stu = {"tomtom", 1604100, 20, 'M', 99, 98, 99 + 98, 0, fri};
	char *name[MAX] = {"xiaocao", "xiaohua", "xiaohong", "xiaofang", "xiaoxuan", "xiaomeng", "xiaohei", "xiaobai", "xiaolv", "xiaoshe"};
	LLIST *handle = NULL, *find = NULL;

	if (argc >= 2)
	{
		printf("llist_load : \n");
		handle = llist_load("./stu.db");
		
	}
	else
	{
		handle = llist_create(sizeof(struct cls_t));
		ERRP(handle == NULL, llist_create, goto ERR1);

		for (i = 0; i < MAX; i++)
		{
			snprintf(cls.name, sizeof(cls.name), "cls_%c%c", rand() % 26 + 'A', rand() % 26 + 'a');
			cls.id = rand() % 100 + 1604000;
			cls.age = rand() % 3 + 18;
			cls.sex = "FM"[rand() % 2];
			cls.c = rand() % 30 + 70;
			cls.ds = rand() % 20 + 80;
			cls.result = cls.c + cls.ds;
			cls.flag = rand() % MAX;
			cls.love = fri;
			/*cls.love(name[rand() % 10]);*/
			//ls(&cls, name);

			/*llist_append(&cls, handle);*/
			
			/*llist_sort_insert(&cls, sort_id, handle);*/
			llist_prepend(&cls, handle);
		}
		
		llist_travel(handle, ls, name);
		printf("================\n");
		llist_sort(2, sort_result, handle);
		llist_store("./stu.db", handle);
		/*llist_sort(2, sort_age, handle);*/
		/*
		 *num = 18;
		 *find = llist_find(&num, cmp_age, handle);
		 *if (find == NULL)
		 *{
		 *    printf("no find!\n");
		 *    return -1;
		 *}
		 */

		/*llist_travel(find, ls, name);*/
		/*
		 *printf("please input find bit : ");
		 *scanf("%d", &num);
		 *p = llist_index_find(num, handle);
		 *if (p == NULL)
		 *{
		 *    printf("no find!\n");
		 *}
		 *else
		 *{
		 *    ls(p, name);
		 *}
		 */
		/*llist_alldel(&num, cmp_age, handle);*/
		ch = 'M';
		/*llist_alldel(&ch, cmp_sex, handle);*/
	/*
	 *    printf("please input key love : ");
	 *    fgets(tmp, sizeof(tmp), stdin);
	 *    if (tmp[strlen(tmp) - 1] == '\n')
	 *        tmp[strlen(tmp) - 1] = '\0';
	 *    
	 *    num = cmp_stoi(tmp, name);
	 *    [>llist_del(&num, cmp_love, handle);<]
	 *    llist_alldel(&num, cmp_love, handle);
	 *
	 *    llist_travel(handle, ls, name);
	 *
	 */
	/*
	 *    printf("==================\n");
	 *    int bit;
	 *    printf("please input insert index : ");
	 *    scanf("%d", &bit);
	 *
	 *    llist_index_insert(bit, &stu, handle);
	 */
 	}
	llist_travel(handle, ls, name);
	llist_destroy(handle, find);
	return 0;
ERR1:
	return -1;
}
