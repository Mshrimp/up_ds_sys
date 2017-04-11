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

#define PRI(e) printf(#e" = %d\n", e)

int main(int argc, char *argv[])
{
	time_t t;
	time_t tmp;
	struct tm *m;
	char buf[128];

	//1970 1 1 => atime mtime ctime
	tmp = time(&t);
	printf("tmp = %ld\n", tmp);
	printf("t = %ld\n", t);
	printf("ctime = %s\n", ctime(&t));

	/*m = gmtime(&t);*/
	m = localtime(&t);

	//month-days hours:mintex
	strftime(buf, sizeof(buf), "%m-%d %H:%M", m);
	printf("buf = %s\n", buf);
	strftime(buf, sizeof(buf), "%D", m);
	printf("buf = %s\n", buf);
	strftime(buf, sizeof(buf), "%F", m);
	printf("buf = %s\n", buf);
	strftime(buf, sizeof(buf), "%T", m);
	printf("buf = %s\n", buf);

	PRI(m->tm_sec);         /* seconds */
	PRI(m->tm_min);         /* minutes */
	PRI(m->tm_hour);        /* hours */
	PRI(m->tm_mday);        /* day of the month */
	PRI(m->tm_mon + 1);         /* month */
	PRI(m->tm_year + 1900);        /* year */
	PRI(m->tm_wday);        /* day of the week */
	PRI(m->tm_yday);        /* day in the year */
	PRI(m->tm_isdst);       /* daylight saving time */

	printf("%d-%d %d:%d\n", m->tm_mon + 1, m->tm_mday, m->tm_hour + 8, m->tm_min);

	return 0;
}
