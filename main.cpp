#include "unp.h"

int main(int argc, char * agrc[])
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockadddr_in servaddr;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");
