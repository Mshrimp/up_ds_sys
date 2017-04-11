#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <shadow.h>
#include <grp.h>

int main(int argc, char *argv[])
{
	int i = 0;
	struct group *grp = NULL;

	grp = getgrgid(atoi(argv[1]));
	if (grp == NULL)
	{
		return -1;
	}

	printf("name : %s gid : %d\n", grp->gr_name, grp->gr_gid);
	//char **gr_mem
	while(grp->gr_mem[i] != NULL)
	{
		printf("%s ", grp->gr_mem[i]);
		i++;
	}
	printf("\n");
    /*
	 *for (i = 0; i < 3; i++)
	 *{
	 *    printf("group : %s\n", *(grp->gr_mem + i));
	 *}
     */
	return 0;
}
