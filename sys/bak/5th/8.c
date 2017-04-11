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
#include <time.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <glob.h>
#include <sys/wait.h>


void A(void)
{
	printf("AAAAA!\n");
}
void B(void)
{
	printf("BBBBB!\n");
}
void C(void)
{
	printf("CCCCC!\n");
}

int main(int argc, char *argv[])
{
	atexit(A);
	atexit(B);
	atexit(C);

	printf("main stat!\n");
    /*
	 *A();
	 *B();
	 *C();
     */
	printf("main end!\n");
	printf("hello!\n");
	return 0;
}
