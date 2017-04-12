/************************************************************************
fread fwrite函数的使用
	size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
	size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

	size: 每次传输的字节数
	nmemb: 传输的数据个数
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//cp->argv[0]->a.out src->argv[1]->r dest->argv[2]->w
int main(int argc, char *argv[])
{
	FILE *fpr = NULL, *fpw = NULL;
	char buf[1024] = {};
	//mode 1024 size 1
	//mode 1 size 1024
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

#if 0
	// 每次读取sizeof(buf)并发送，一次传输
	// fread 读取到字符串结尾时返回0
	while((ret = fread(buf, sizeof(buf), 1, fpr)) == 1)
	{
		printf("ret = %d\n", ret);
		fwrite(buf, sizeof(buf), 1, fpw);
		memset(buf, 0, sizeof(buf));
	}

	fwrite(buf, strlen(buf), 1, fpw);
	/*printf("buf = %s\n", buf);*/
#else
	// 每次发送1字节，发送sizeof(buf)次
	while((ret = fread(buf, 1, sizeof(buf), fpr)) > 0)
	{
		fwrite(buf, 1, ret, fpw);
	}
#endif
	fclose(fpr);
	fclose(fpw);
	return 0;
}
