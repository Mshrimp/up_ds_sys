#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int quit = 1;
	while(quit)
	{
		system("clear");
		printf("====> 清华学生管理系统(V1.0) <====\n");
		printf("====>     1 添加学生信息     <====\n");
		printf("====>     2 删除学生信息     <====\n");
		printf("====>     3 查找学生信息     <====\n");
		printf("====>     4 修改学生信息     <====\n");
		printf("====>     5 遍历学生信息     <====\n");
		printf("====>     6 存储学生信息     <====\n");
		printf("====>     8 退出学生系统     <====\n");
		printf("please input option : ");
		scanf("%d", &option);
		
		switch option
		{
			case 1:
				add_menu()
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				quit = 0;
				break;
		}
	}	
	return 0;
}
