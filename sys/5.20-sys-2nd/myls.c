/***************************************************
	自己封装实现ls功能
	lstat();
	getpwuid();
	getgrgid();
	格式：
		./a.out filename [-h]
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

#define MODECHK(chr, s, mode)		do{										\
										if ((s->st_mode & mode) == mode)	\
										{									\
											putchar(chr);					\
										}									\
										else								\
										{									\
											putchar('-');					\
										}									\
									}while(0)



int year_leap(int year);	//判断是闰年还是平年

int year_chk(int (*year), int day);	//判断当前年份，返回最后一年中已过的天数

int month_day_chk(int *year, int *moth, int day);	//判断月份和日期

void print_month_day(int moth, int day);	//按month-day格式打印月份和日期

int print_time(int curhour, int curminu);	//按hour:minute格式打印时间

void file_size(int argc, char *argv[], int size);	//文件大小转换及打印

void file_chk(struct stat *s);	//文件类型检测及打印

void mode_chk(struct stat *s);	//文件权限检测及打印

void file_name_chk(char *argv[]);	//从第二个参数中提取出文件名，并打印

void mode_arr_chk(struct stat *s);

void file_str_chk(struct stat *s);

int main (int argc, char *argv[])
{
	struct stat s;
	struct passwd *pw = NULL;
	struct group *grp = NULL;
	int size = 0;
	int ret = 0;
	int time = 0; 
	int year = 1970;
	int moth = 1;
	int days = 0;
	int day = 0;
	int curhour = 0;
	int curminu = 0;
	int cursecd = 0;
	int hour = 0;
	int minu = 0;

	ret = lstat(argv[1], &s);
	if (-1 == ret)
	{
		printf("lstat failed!\n");
		return -1;
	}

	file_arr_chk(&s);	//检测文件类型，并打印
	mode_arr_chk(&s);	//检测权限，并打印

	printf("%d ", s.st_nlink);	//打印硬链接数

	pw = getpwuid(s.st_uid);	//由uid匹配到文件所属用户名，并打印
	printf("%s ", pw->pw_name);

	grp = getgrgid(s.st_gid);	//由gid匹配到文件所属用户组名，并打印
	printf("%s ", grp->gr_name);

	size = s.st_size;
	file_size(argc, argv, size);	//文件大小转换及打印

	time = s.st_mtime;	//文件修改时间，及时间格式转换
	cursecd = time % 60;
	minu = time / 60;
	curminu = minu % 60;
	hour = minu / 60;
	curhour = hour % 24;
	day = hour / 24;

	days = year_chk(&year, day);	//年检测
	day = month_day_chk(&year, &moth, days);	//计算月份和日期
	print_time(curhour, curminu);	//打印时间
	file_name_chk(argv);	//文件名查找，并打印

	putchar('\n');

	return 0;
}


void file_arr_chk(struct stat *s)
{
	char type[] = " pc d b - l s";

	printf("%c", type[(s->st_mode & S_IFMT) >> 12]);

	return ;
}

void mode_arr_chk(struct stat *s)
{
	char *mode[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

	printf("%s", mode[(s->st_mode & S_IRWXU) >> 6]);
	printf("%s", mode[(s->st_mode & S_IRWXG) >> 3]);
	printf("%s", mode[(s->st_mode & S_IRWXO)]);

	putchar(' ');

	return ;
}

//判断是闰年还是平年
int year_leap(int year)
{
	if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
	{
		return 1;
	}

	return 0;
}

//判断当前年份，返回最后一年中已过的天数
int year_chk(int (*year), int day)
{
	int days = 0;
	int year_days = 0;
	int i = 0;

	while (1)
	{
		year_days = 365;

		if (year_leap((*year)))
		{
			year_days++;
		}

		if (days + year_days < day)
		{
			days += year_days;
			(*year)++;
			i++;
		}
		else
		{	
			break;
		}
	}
	day -= days;

	return day;
}

//判断月份和日期
int month_day_chk(int *year, int *moth, int day)
{
	int days = 0;
	int month_days = 0;

	while (1)
	{
		if (*moth < 1 || *moth > 12)
		{
			break;
		}

		if ((*moth == 1) || (*moth == 3) || (*moth == 5) || (*moth == 7) || (*moth == 8) || (*moth == 10) || (*moth == 12))
		{
			month_days = 31;
		}
		else if ((*moth == 4) || (*moth == 6) || (*moth == 9) || (*moth == 11))
		{
			month_days = 30;
		}
		else if (*moth == 2)
		{
			month_days = 28;

			if (year_leap(*year))
			{
				month_days++;
			}
		}

		if (days + month_days < day)
		{
			days += month_days;
			(*moth)++;
		}
		else
		{
			break;
		}

	}
	day -= days;
	day++;

	print_month_day(*moth, day);

	return day;
}

//按month-day格式打印月份和日期
void print_month_day(int moth, int day)
{
	if (moth < 10)
	{
		printf("0%d-%d ", moth, day);
	}
	if (day < 10)
	{
		printf("%d-0%d ", moth, day);
	}
	if (moth < 10 && day < 10)
	{
		printf("0%d-0%d ", moth, day);
	}
	if (moth >= 10 && day >= 10)
	{
		printf("%d-%d ", moth, day);
	}
}

//按hour:minute格式打印时间
int print_time(int curhour, int curminu)
{
	curhour += 8;

	if (curhour < 10)
	{
		printf("0%d:%d ", curhour, curminu);
	}

	if (curminu < 10)
	{
		printf("%d:0%d ", curhour, curminu);
	}

	if (curhour < 10 && curminu < 10)
	{
		printf("0%d:0%d ", curhour, curminu);
	}

	if (curhour > 10 && curminu > 10)
	{
		printf("%d:%d ", curhour, curminu);
	}

	return 0;
}

//文件大小转换及打印
void file_size(int argc, char *argv[], int size)
{
	float sizef = 0;

	if (3 == argc)
	{
		if (!strcmp(argv[2], "-h"))
		{
			sizef = (float)size / 1024.0;
			if (sizef < 1.0)
			{
				printf("%d ", size);
			}
			else if ((sizef >= 1.0) && (sizef < 1024.0))
			{
				printf("%.1fK ", sizef);
			}
			else if (sizef >= 1024)
			{
				sizef /= 1024;
				if (sizef < 1024)
				{
					printf("%.1fM ", sizef);
				}
				else
				{
					sizef /= 1024;
					printf("%.1fG ", sizef);
				}
			}

		}
	}
	else if (argc < 3)
	{
		printf("%d ", size);
	}

	return ;
}

//文件类型检测及打印
void file_chk(struct stat *s)
{
	if (S_ISREG(s->st_mode))
		putchar('-');
	else if (S_ISDIR(s->st_mode))
		putchar('d');
	else if (S_ISCHR(s->st_mode))
		putchar('c');
	else if (S_ISBLK(s->st_mode))
		putchar('b');
	else if (S_ISFIFO(s->st_mode))
		putchar('p');
	else if (S_ISLNK(s->st_mode))
		putchar('l');
	else if (S_ISSOCK(s->st_mode))
		putchar('s');
	
	return ;
}

//文件权限检测及打印
void mode_chk(struct stat *s)
{
	MODECHK('r', s, S_IRUSR);
	MODECHK('w', s, S_IWUSR);
	MODECHK('x', s, S_IXUSR);
	MODECHK('r', s, S_IRGRP);
	MODECHK('w', s, S_IWGRP);
	MODECHK('x', s, S_IXGRP);
	MODECHK('r', s, S_IROTH);
	MODECHK('w', s, S_IWOTH);
	MODECHK('x', s, S_IXOTH);
	putchar(' ');

	return ;
}

//从第二个参数中提取出文件名，并打印
void file_name_chk(char *argv[])
{
	char *filename = NULL;

	filename = strrchr(argv[1], '/');	//文件名中含有路径，查找出文件名
	if (NULL == filename)
	{
		printf("%s", argv[1]);
	}
	else	//文件名中不含有路径
	{
		printf("%s", filename + 1);
	}
}

