#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
/*
 *    int *p = NULL;
 *
 *    if (p == NULL)
 *    {
 *        perror("malloc");
 *        return -1;
 *    }
 */
	int fd;

	/*close(2);*/
	fprintf(stderr, "hello!\n");
	fd = open("./test", O_RDONLY);
	/*fd = open("./test", O_WRONLY);*/
	if (fd == -1)
	{
		perror("open");
		return -1;
	}

	printf("fd = %d\n", fd);

/*
 *    fd = open("./test", O_RDONLY);
 *    if (fd == -1)
 *    {
 *        perror("open");
 *        return -1;
 *    }
 *
 *    printf("fd = %d\n", fd);
 *    getchar();
 */
	close(fd);
	return 0;
}
