#include "stack.h"

void ls(void *data)
{
	printf("%c", *(char *)data);
}
int main(void)
{
	char buf[128];
	STACK *handle = NULL;
	int i;
	char ch = '\n';

	handle = stack_create(sizeof(char), 128);

	printf("please input string : ");
	fgets(buf, sizeof(buf), stdin);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';

	printf("buf = %s\n", buf);

	for (i = 0; i < strlen(buf); i++)
	{
		if (buf[i] == '#')
		{
			stack_pop(handle);
		}
		else if (buf[i] == '@')
		{
			stack_push(&ch, handle);
		}
		else
		{
			stack_push(&buf[i], handle);
		}
	}

	stack_travel(handle, ls);
	stack_destroy(handle);
	return 0;
}
