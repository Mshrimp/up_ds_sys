/***************************************************
	unlink()	删除文件
	mkdir()		创建目录
	rmdir()		删除空目录
	remove()	删除文件或目录
	rename()	文件或文件夹重命名或者移动
	chdir()		更改目录
	getcwd()	获取当前目录路径
	get_current_dir_name()	获取当前目录路径
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
#include <sys/utsname.h>

int main(int argc, char *argv[])
{
	int ret = 0;
	char buf[32] = {};
	
	//删除文件
    /*
	 *ret = unlink(argv[1]);
	 *if (-1 == ret)
	 *{
	 *    printf("unlink failed!\n");
	 *    return -1;
	 *}
     */

	//创建目录
    /*
	 *ret = mkdir(argv[1], 0755);
	 *if (-1 == ret)
	 *{
	 *    printf("mkdir failed!\n");
	 *    return -1;
	 *}
     */

	//删除一个空目录
    /*
	 *ret = rmdir(argv[1]);
	 *if (-1 == ret)
	 *{
	 *    printf("rmdir failed!\n");
	 *    return -1;
	 *}
     */

	//删除文件或目录
    /*
	 *ret = remove(argv[1]);
	 *if (-1 == ret)
	 *{
	 *    printf("remove failed!\n");
	 *    return -1;
	 *}
     */

	//文件或者文件夹重命名或者移动
    /*
	 *ret = rename(argv[1], argv[2]);
	 *if (-1 == ret)
	 *{
	 *    printf("rename failed!\n");
	 *    return -1;
	 *}
     */

	//切换目录
    /*
	 *getcwd(buf, sizeof(buf));	//获取当前目录路径
	 *printf("%s\n", buf);
	 *ret = chdir(argv[1]);
	 *printf("ret = %d\n", ret);
	 *if (-1 == ret)
	 *{
	 *    printf("chdir failed!\n");
	 *    return -1;
	 *}
	 *printf("get = %s\n", get_current_dir_name());	//获取当前目录路径
	 *getcwd(buf, sizeof(buf));
	 *printf("%s\n", buf);
     */


	return 0;
}
