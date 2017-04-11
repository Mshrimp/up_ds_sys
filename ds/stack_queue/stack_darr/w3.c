#include "stack.h"

void ls(void *data)
{
	printf("%d", *(int *)data);
}
int main(void)
{
	char buf[128];
	STACK *handle = NULL;
	int i, num;
	int val1, val2;
	char ch = '\n';

	handle = stack_create(sizeof(int), 128);

	printf("please input string : ");
	fgets(buf, sizeof(buf), stdin);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';

	printf("buf = %s\n", buf);

	for (i = strlen(buf) - 1; i >= 0; i--)
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			num = buf[i] - 48;
			stack_push(&num, handle);
		}

	}

	for (i = 0; i < strlen(buf); i++)
	{
		if (buf[i] == '+' || buf[i] == '-' || 
			buf[i] == '*' || buf[i] == '/' ||
			buf[i] == '%')
		{
			val1 = *(int *)stack_pop(handle);
			val2 = *(int *)stack_pop(handle);
			/*printf("val1 = %d val2 = %d\n", val1, val2);*/
			switch (buf[i])
			{
				case '+':
					val1 += val2;
					break;
				case '-':
					val1 -= val2;
					break;
				case '*':
					val1 *= val2;
					break;
				case '/':
					val1 /= val2;
					break;
				case '%':
					val1 %= val2;
					break;
			}
			stack_push(&val1, handle);
		}
	}
	printf("result = %d\n", *(int *)stack_pop(handle));
	/*stack_travel(handle, ls);*/
	stack_destroy(handle);
	return 0;
}
