#ifndef __MYSYS_H__
#define __MYSYS_H__


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


#define ERRP(con, func, ret)	do{										\
									if (con)							\
									{									\
										printf(#func" failed!\n");		\
										ret;							\
									}									\
								}while(0)


#define GETLINES(string, buf)	do{										\
									printf(string);						\
									fgets(buf, sizeof(buf), stdin);		\
									if (buf[strlen(buf) - 1] == '\n')	\
									{									\
										buf[strlen(buf) - 1] = '\0';	\
									}									\
								}while(0)




#endif/*__MYSYS_H__*/



