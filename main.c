#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>//inet_pton
#include <unistd.h>

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>

#define MAXLINE 256

int main(int argc, char * argv[])
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2){
		printf("usage: a.out <IPaddress>\n");
		return -1;
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0){
		printf("socket error\n");
		return -1;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0){
		printf("inet_pton error for %s\n", argv[1]);
		return -1;
	}

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in)) < 0){
		printf("connect error\n");
		return -1;
	}


	while ( ( n = read(sockfd, recvline, MAXLINE) ) > 0){
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF){
			printf("fputs error\n");
			return -1;
		}
	}

	if (n < 0){
		printf("read error");
		return -1;
	}
	return 0;
}
	
