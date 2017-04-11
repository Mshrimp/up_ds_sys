/***********************************************
	lseek()函数测试
	lseek(fd, 0, SEEK_CUR);	//查看文件定位
	read()函数中第二个参数：权限
	O_RDONLY : 0	只读
	O_WRONLY : 1	只写
	O_RDWR	 : 2	读写
	第三个参数：新创建文件时指定文件权限
	mode = mode & ~umask
***********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int fd, ret;
	char buf[128];

	/*fd = creat(argv[1], 0666);*/
	fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);	//读写权限，可以读也可以写文件
	/*fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);	//只写权限，读取文件会失败 */
	/*fd = open(argv[1], O_CREAT | O_TRUNC, 0666);	//只创建权限，读取文件和写文件都失败 */
	if (fd == -1)
	{
		printf("Open failed!\n");
		return -1;
	}

	printf("O_RDONLY = %o\n", O_RDONLY);
	printf("O_WRONLY = %o\n", O_WRONLY);
	printf("O_RDWR = %o\n", O_RDWR);
	printf("O_CREAT = %o\n", O_CREAT);
	printf("O_TRUNC = %o\n", O_TRUNC);

	//写入文件后测试定位
	ret = write(fd, "hello", 5);
	if (-1 == ret)
	{
		printf("Write failed!\n");
		return -1;
	}

	printf("ret = %d\n", ret);

	//查看当前文件偏移量
	printf("lseek = %d\n", lseek(fd, 0, SEEK_CUR));	

	//将文件定位偏移设置到文件开头
	lseek(fd, 0, SEEK_SET);

	printf("lseek = %d\n", lseek(fd, 0, SEEK_CUR));

	ret = read(fd, buf, sizeof(buf));
	if (-1 == ret)
	{
		printf("read buf");
		return -1;
	}

	printf("ret = %d, buf = %s\n", ret, buf);

    /*
	 *while(1)
	 *{
	 *    sleep(1);
	 *}
     */
	
	return 0;
}
