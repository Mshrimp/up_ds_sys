/**********************************************************


**********************************************************/
#include <stdio.h>
/*#include <string.h>*/
/*#include <stdlib.h>*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;

	fd = open("./test", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		perror("KEN");
		return -1;
	}

	printf("O_RDONLY = %#o\n", O_RDONLY);
	printf("O_RDONLY = %d\n", O_RDONLY);

	printf("O_WRONLY = %#o\n", O_WRONLY);
	printf("O_CREAT = %#o\n", O_CREAT);
	printf("O_TRUNC = %#o\n", O_TRUNC);

	return 0;
}
