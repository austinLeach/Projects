#define _POSIX_SOURCE
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

#define MAXCONN 3

// Austin Leach

int main(int argc, char * argv[])
{
	int sockfd, rec_sock, len, i;
	struct sockaddr_in addr, recaddr;
	int client[MAXCONN];
	char buf[100];
	fd_set allset, rset;
	int maxfd;
	

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror(": Can't get socket");
		exit(1);
	}

	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(0);
	
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror(": bind");
		exit(1);
	}

	if (listen(sockfd, 5) < 0) {
		perror(": bind");
		exit(1);
	}

	socklen_t lenthofaddr = sizeof(addr);

	if (getsockname(sockfd, (struct sockaddr *)&addr, &lenthofaddr) == -1) {
		perror(": getsockname");
		exit(1);
	}
	
	// gethostname for ip
	char hostname[100];
	gethostname(hostname, 100);
	
	printf("Started server on '%s' at '%d'\n", hostname, ntohs(addr.sin_port));
		

	for (i=0; i<MAXCONN; i++) client[i] = -1;

	FD_ZERO(&allset);
	FD_SET(sockfd, &allset);
	maxfd = sockfd;

	char clientAddresses[MAXCONN][100];
	int clientPorts[MAXCONN];

	while (1) {
		rset = allset;
		select(maxfd+1, &rset, NULL, NULL, NULL);
		if (FD_ISSET(sockfd, &rset)) {
			/* somebody tries to connect */
			if ((rec_sock = accept(sockfd, (struct sockaddr*)(&recaddr), (socklen_t *)&len)) < 0) {
				if (errno == EINTR)
					continue;
				else {
					perror(":accept error");
					exit(1);
				}
			}


			/* print the remote socket information */
			socklen_t lenthofrecaddr = sizeof(recaddr);
			if (getpeername(rec_sock, (struct sockaddr*)(&recaddr), &lenthofrecaddr) == -1) {
				perror(":peername error");
				exit(1);
			}
			printf("remote machine = %s, port = %d.\n", inet_ntoa(recaddr.sin_addr), ntohs(recaddr.sin_port)); 
			
			for (i=0; i<MAXCONN; i++) {
				if (client[i] < 0) {
					client[i] = rec_sock; 
					FD_SET(client[i], &allset);
					strcpy(clientAddresses[i], inet_ntoa(recaddr.sin_addr));
					clientPorts[i] =  ntohs(recaddr.sin_port);
					break;
				}
			}
			if (i== MAXCONN) {
				printf("too many connections.\n");
				close(rec_sock);
			}
			if (rec_sock > maxfd) maxfd = rec_sock;
		}

		for (i=0; i<MAXCONN; i++) {
			if (client[i] < 0) continue;
			if (FD_ISSET(client[i], &rset)) {
				int num;
				num = read(client[i], buf, 100);
				if (num == 0) {
					/* client exits */
					close(client[i]);
					FD_CLR(client[i], &allset);
					client[i] = -1;
					printf("disconnected from '%s(%i)'\n", clientAddresses[i], clientPorts[i]);
				} else {
					for (int j=0; j<MAXCONN; j++) {
						if (client[j] < 0) continue;
						if (j == i) {
							printf("%s(%i): %s", clientAddresses[i], clientPorts[i], buf);
						} else {
							write(client[j], buf, num);
						}
					}
				}
			}
		}
	}
}



