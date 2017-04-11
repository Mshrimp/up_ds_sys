#include <stdio.h>
#include <stdlib.h>

#include "proto.h"


int main(void)
{
	int sd;

	sd = socket(AF_INET, SOCK_DGRAM, 0);/*IPPROTO_UDP*/
	if (sd < 0)
	{
		perror("socket");
		exit(-1);
	}

	bind(sd, (void *)laddr, sizeof(laddr));

	recvfrom();

	close();

	exit(0);
}


