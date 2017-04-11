#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//cp->argv[0]->a.out src->argv[1]->r dest->argv[2]->w
int main(int argc, char *argv[])
{
	FILE *fpr = NULL, *fpw = NULL;
	char buf[1024] = {};
	//mode 1024 size 1
	//mode 1 size 1024
	int ret;

	fpr = fopen(argv[1], "r");
	if (fpr == NULL)
	{
		return -1;
	}

	fpw = fopen(argv[2], "w");
	if (fpw == NULL)
	{
		fclose(fpr);
		return -1;
	}

#if 0
	while((ret = fread(buf, sizeof(buf), 1, fpr)) == 1)
	{
		printf("ret = %d\n", ret);
		fwrite(buf, sizeof(buf), 1, fpw);
		memset(buf, 0, sizeof(buf));
	}

	fwrite(buf, strlen(buf), 1, fpw);
	/*printf("buf = %s\n", buf);*/
#else
	while((ret = fread(buf, 1, sizeof(buf), fpr)) > 0)
	{
		fwrite(buf, 1, ret, fpw);
	}
#endif
	fclose(fpr);
	fclose(fpw);
	return 0;
}
