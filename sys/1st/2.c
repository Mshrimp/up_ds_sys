/************************************************************************
fread fwrite函数的使用
	size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
	size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

	size: 每次传输的字节数
	nmemb: 传输的数据个数

	read和write过程中，数据个数达到nmemb或者到文件结尾或者出错才停止。
	Return: 运行成功时返回值和nmemb相等。
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//cp->argv[0]->a.out src->argv[1]->r dest->argv[2]->w
int main(int argc, char *argv[])
{
	FILE *fpr = NULL, *fpw = NULL;
	char buf[1024] = {};
	//1. mode 1024 size 1
	//2. mode 1 size 1024
	int ret;

	fpr = fopen(argv[1], "r");
	if (fpr == NULL)
	{
		return -1;
	}

	fpw = fopen(argv[2], "w");
	if (fpw == NULL)
	{
		fclose(fpr);
		return -1;
	}

#if 1
	// 每次读取sizeof(buf)并发送，一次传输
	// fread 读取到字符串结尾时返回0
	// 每次发送sizeof(buf)字节，发送1次，fread返回1
	while((ret = fread(buf, sizeof(buf), 1, fpr)) > 0)
	{
		printf("fread: ret = %d\n", ret);
		ret = fwrite(buf, sizeof(buf), 1, fpw);
		//printf("fwrite: ret = %d\n", ret);
		memset(buf, 0, sizeof(buf));
	}

	// fread读取到的字节数小于size时，返回0，通过此处将数据fwrite
	fwrite(buf, strlen(buf), 1, fpw);
	/*printf("buf = %s\n", buf);*/
#else
	// 每次发送1字节，发送sizeof(buf)次，fread返回sizeof(buf)
	while((ret = fread(buf, 1, sizeof(buf), fpr)) > 0)
	{
		printf("fread: ret = %d\n", ret);
		ret = fwrite(buf, 1, ret, fpw);
		printf("fwrite: ret = %d\n", ret);
	}
#endif
	fclose(fpr);
	fclose(fpw);
	return 0;
}
