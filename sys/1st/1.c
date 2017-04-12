/*****************************************************************
BUFSIZ作用:
	程序输出时，为减轻系统负担，可以先将需要输出的字符保存起来，
即放入内存缓冲。
	当达到输出条件时：行缓冲遇到换行符，块缓冲遇到写满缓存，或
用户强制fflush；才进行写文件动作。BUFSIZ为系统默认的缓冲区大小。

BUFSIZ使用:
	#include <stdio.h> (引入头文件即可)
	setbuf(stdout, buf); (修改默认缓冲大小)
	默认BUFSIZ = 8192字节
*****************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	//默认缓冲区大小
	printf("BUFSIZ = %d\n", BUFSIZ);
	return 0;
}
