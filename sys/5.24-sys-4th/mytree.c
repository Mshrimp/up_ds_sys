/***************************************************
	递归实现tree功能：
	opendir()
	readdir()
	closedir()
	chdir()
***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <dirent.h>


void my_tree(char *p);	//tree实现，并按格式打印


int main(int argc, char *argv[])
{

	my_tree(argv[1]);

	return 0;
}


//tree实现，并按格式打印
void my_tree(char *p)
{
	DIR *dir = NULL;
	int ret = 0, i = 0;
	struct dirent *dren = NULL;
	static int count;
	static int dircount = 1;
	static int filecount = 0;

	//打印最外层目录文件夹名称
	if (0 == count)
	{
		printf("%s\n", p);
	}

	//打开文件夹
	dir = opendir(p);
	if (NULL == dir)
	{
		/*filecount++;	//打开文件夹失败，文件计数*/
		return ;
	}
    /*
	 *else
	 *{
	 *    dircount++;		//文件夹计数
	 *}
     */

	ret = chdir(p);		//改变目录，进入到已打开文件夹
	if (-1 == ret)
	{
		printf("chdir failed!\n");
	}
	while (1)
	{
		dren = readdir(dir);	//读取文件夹内的文件或文件夹名称
		if (NULL == dren)
		{
			break;
		}
		if (!strncmp(dren->d_name, ".", 1))	//不显示隐藏文件及文件夹
		{
			continue;
		}
		count++;

		if (dren->d_type == 4)
		{
			dircount++;
		}
		else if (dren->d_type != 0)
		{
			filecount++;
		}

		//输出打印格式，层次
		if (1 != count)
		{
			printf("%c", '|');
		}
		for (i = 1; i < count; i++)
		{
			printf("%s", "   ");
			if (count != 2)
			{
				printf("%s", " ");
			}
		}

		printf("|-- %s\n", dren->d_name);	//打印文件或者文件夹名称

		my_tree(dren->d_name);	//递归调用本函数，进入内层文件夹显示打印
		count--;
	}

	ret = chdir("../");		//切换到上级目录
	if (-1 == ret)
	{
		printf("chdir out failed!\n");
	}

	ret = closedir(dir);	//关闭目标文件夹
	if (-1 == ret)
	{
		printf("closedir failed!\n");
		return ;
	}

	//判断最后一层递归，打印文件及文件夹个数
	if (0 == count)
	{
		printf("%d directories, %d files!\n", dircount-1, filecount);
	}

	return ;
}




