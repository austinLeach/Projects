#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <strings.h>

// Austin Leach

int main(int argc, char * argv[])
{
	int sockfd, maxf, rv, flag;
	char buf[100];
	fd_set  rset, orig_set;
	struct addrinfo hints, *res, *ressave;
	struct sockaddr_in addr;

	if (argc != 3) {
		fprintf(stderr, "%s server_name_or_ip port\n", argv[0]);
		exit(1);
	}

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo wrong: %s\n", gai_strerror(rv));
		exit(1);
	}

	ressave = res;
	flag = 0;
	do {
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
			continue;
		if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0) {
			flag = 1;
			break;
		}
		close(sockfd);
	} while ((res = res->ai_next) != NULL);
	freeaddrinfo(ressave);

	if (flag == 0) {
		fprintf(stderr, "cannot connect\n");
		exit(1);
	}

	// get port number
	socklen_t len = sizeof(addr);
	if (getsockname(sockfd, (struct sockaddr *)&addr, &len) == -1) {
		perror(": getsockname");
		exit(1);
	}

	printf("connected to server on '%s' at '%s' thru '%hu'\n", argv[1], argv[2], ntohs(addr.sin_port));

	FD_ZERO(&orig_set);
	FD_SET(STDIN_FILENO, &orig_set);
	FD_SET(sockfd, &orig_set);    
	if (sockfd > STDIN_FILENO) maxf = sockfd+1;
	else maxf = STDIN_FILENO+ 1;

	while (1) {
		rset = orig_set;
		select(maxf, &rset, NULL, NULL, NULL);
		if (FD_ISSET(sockfd, &rset)) {
			if (read(sockfd, buf, 100) == 0) {
				printf("server crashed.\n");
				exit(0);
			}
			printf(">>> %s", buf);
		}
		if (FD_ISSET(STDIN_FILENO, &rset)) {
			if (fgets(buf, 100, stdin) == NULL) exit(0);
			write(sockfd, buf, strlen(buf)+1);
		}
	}
}