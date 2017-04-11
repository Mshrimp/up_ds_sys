/***************************************************
	获取所有用户组及组成员，并打印
	getgrent()	循环获取
	setgrent()	设置偏移量到文件开头
	endgrent()	设置偏移量到文件结尾
***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[])
{
	struct group *grp = NULL;
	char *name = NULL;
	int i = 0;
	
	while (1)
	{
		//循环获取/etc/group文件用户组名
		grp = getgrent();
		if (NULL == grp)
		{
			printf("getgrent failed!\n");
			break;
		}
		//打印用户组名
		printf("%s\t", grp->gr_name);

		//打印用户组成员
		i = 0;
		while (1)
		{
			//获取用户组成员
			name = grp->gr_mem[i++];
			if (NULL == name)
			{
				break;
			}

			printf("%s\t", name);
		}

		putchar('\n');
	}

	printf("==================================\n");

	setgrent();	//设置偏移量到文件开头，重新定位
	endgrent();

	while (1)
	{
		grp = getgrent();
		if (NULL == grp)
		{
			printf("getgrent failed!\n");
			return -1;
		}

		printf("%s\t", grp->gr_name);

		i = 0;
		while (1)
		{
			name = grp->gr_mem[i++];
			if (NULL == name)
			{
				break;
			}

			printf("%s\t", name);
		}

		putchar('\n');
	}



	return 0;
}
