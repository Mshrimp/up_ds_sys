#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>

int main(int argc, char *argv[])
{
	struct passwd *pwd;

	pwd = getpwnam(argv[1]);
	if (pwd == NULL)
	{
		printf("getpwnam failed!\n");
		return -1;
	}

	printf("uid = %d\n", pwd->pw_uid);
	printf("passwd = %s\n", pwd->pw_passwd);
	getchar();

	printf("===============\n");
	while(1)
	{
		pwd = getpwent();
		if (pwd == NULL)
		{
			printf("getpwent failed!\n");
			break;
			/*return -1;*/
		}
		printf("name : %s | uid : %d\n", pwd->pw_name, pwd->pw_uid);
	}
	printf("===2nd======\n");

	setpwent();//-> lseek -> open -> close
	
	while(1)
	{
		pwd = getpwent();
		if (pwd == NULL)
		{
			printf("getpwent failed!\n");
			return -1;
		}
		printf("name : %s | uid : %d\n", pwd->pw_name, pwd->pw_uid);
	}
	endpwent();
	return 0;
}
