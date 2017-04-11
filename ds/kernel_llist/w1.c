#include "llist.h"

struct word_t{
	char *en;
	char *cn;
};

void ls(void *data, char **s)
{
	struct word_t *word = (struct word_t *)data;
	printf("en : %s\n", word->en);
	printf("cn : %s\n", word->cn);
}
LLIST *init_word(const char *path)
{
	LLIST *handle = NULL;
	struct word_t word;	
	FILE *fp = NULL;
	char buf[128] = {};
	char *tmp = NULL;
	int flag = 1;

	fp = fopen(path, "r");
	ERRP(fp == NULL, fopen, goto ERR1);

	handle = llist_create(sizeof(struct word_t));
	ERRP(handle == NULL, llist_create, goto ERR2);

	while(fgets(buf, sizeof(buf), fp) != NULL)
	{
		buf[strlen(buf) - 1] = '\0';
		/*printf("buf = %s\n", buf);*/
		tmp = (char *)malloc(strlen(buf) + 1);
		ERRP(tmp == NULL, malloc_tmp, goto ERR3);
		
		strcpy(tmp, buf);

		if (flag == 1)
		{
			word.en = tmp;
		}
		else
		{
			word.cn = tmp;
			llist_append(&word, handle);
		}
		flag = -flag;
		memset(buf, 0, sizeof(buf));
	}
	
	fclose(fp);
	return handle;
ERR3:
	/*free(handle);*/
	llist_destroy(handle, NULL);
ERR2:
	fclose(fp);
ERR1:
	return NULL;
}
int main(void)
{
	LLIST *handle = NULL;
	
	handle = init_word("./ciku.dict");
	ERRP(handle == NULL, init_word, goto ERR1);

	llist_travel(handle, ls, NULL);
	return 0;
ERR1:
	return -1;
}
