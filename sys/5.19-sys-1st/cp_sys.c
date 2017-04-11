/***************************************************
	使用系统IO实现cp拷贝功能
	说明：./a.out src dest
***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fdr = 0;
	int fdw = 0;
	int ret = 0;
	int len = 0;
	int i = 1;
	char buf[128] = {};

	if (3 != argc)		//检查程序运行命令格式是否正确
	{
		printf("Cmd error!\n");
		return -1;
	}

	fdr = open(argv[1], O_RDONLY);		//以只读方式打开源文件
	if (-1 == fdr)
	{
		perror("open src");
		return -1;
	}

	//以读写方式打开目标文件，不存在则创建，存在则清空文件内容
	fdw = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);	
	if (-1 == fdw)
	{
		perror("open dest");
		close(fdr);
		return -1;
	}

	while (1)
	{
		memset(buf, '\0', sizeof(buf));		//清空缓存，可以不用写

		len = read(fdr, buf, sizeof(buf));
		if (0 == len)		//读取文件结束
		{
			printf("Read over!\n");
			break;
		}
		if (len < 0)		//读取文件出错
		{
			printf("Read error!\n");
			break;
		}

		while (len > 0)		//判断是否有读到的数据未写入到文件中
		{
			ret = write(fdw, buf, len);
			if (ret < 0)	//写入文件出错
			{
				printf("write error!\n");
				return -1;
			}
			len -= ret;		//求未写入到文件中的字符数
		}
	}
	
	//关闭已经打开的读取文件和写入文件
	ret = close(fdw);
	if (-1 == ret)
	{
		perror("fdw close");
	}

	ret = close(fdr);
	if (-1 == ret)
	{
		perror("fdr close");
	}

	return 0;
}

