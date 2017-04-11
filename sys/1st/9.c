#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	fwrite("hello", 5, 1, stdout);//满缓冲函数
	fwrite("wrold\njim", 9, 1, stdout);
	/*fprintf(stdout, "hello\n");*/

	while(1)
	{
		sleep(1);
	}
	return 0;
}
