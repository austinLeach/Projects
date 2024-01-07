// Name: Austin Leach

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
#include <string.h>

FILE *ifacesFile;
FILE *rtablesFile;
FILE *hostsFile;

int main(int argc, char * argv[])
{
	int sockfd, maxf, rv, flag;
	char buf[100];
	char bufCpy[100];
	char ifacesBuffer[100];
	char rtablesBuffer[100];
	char hostsBuffer[100];
	fd_set  rset, orig_set;
	struct addrinfo hints, *res, *ressave;
	struct sockaddr_in addr;
	char *ifacesData[4];
	char *menuData[100];
	char *ptr;

	// -no for station, route to ifaces file, route to rtable file, route to hosts file
	if (argc < 5) {
		fprintf(stderr, "%s -no/-route, ifaces file, rtable file, hosts file missing\n", argv[0]);
		exit(1);
	}

	// extract ifaces
	printf("\nreading ifaces...\n\n");
	ifacesFile=fopen(argv[2],"r");
	if (ifacesFile == NULL) {
		printf("Ifaces file not found");
		exit(1);
	} else {
		while(fgets(ifacesBuffer, 100, ifacesFile) != NULL) {
			printf("%s\n", ifacesBuffer);
		}
	}
	fclose(ifacesFile);

	char delim[] = " ";

	ptr = strtok(ifacesBuffer, delim);
	int counter = 0;
	while(ptr != NULL) {
		// printf("%s\n", ptr);
		ifacesData[counter++] = ptr;
		ptr = strtok(NULL, delim);
	}

	printf("stationName is: %s\n", ifacesData[0]);

	// extract rtables
	printf("\n\nreading rtables...\n\n");
	rtablesFile=fopen(argv[3],"r");
	if (rtablesFile == NULL) {
		printf("rtables file not found");
		exit(1);
	} else {
		while(fgets(rtablesBuffer, 100, rtablesFile) != NULL) {
			printf("%s", rtablesBuffer);
		}
	}
	fclose(rtablesFile);

	// extract hosts
	printf("\n\nreading hosts...\n\n");
	hostsFile=fopen(argv[4],"r");
	if (hostsFile == NULL) {
		printf("hosts file not found");
		exit(1);
	} else {
		while(fgets(hostsBuffer, 100, hostsFile) != NULL) {
			printf("%s", hostsBuffer);
		}
	}
	fclose(hostsFile);

	// below is chatclient.c

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[5], argv[6], &hints, &res)) != 0) {
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

	printf("connected to server on '%s' at '%s' thru '%hu'\n", argv[5], argv[6], ntohs(addr.sin_port));

	FD_ZERO(&orig_set);
	FD_SET(STDIN_FILENO, &orig_set);
	FD_SET(sockfd, &orig_set);    
	if (sockfd > STDIN_FILENO) maxf = sockfd+1;
	else maxf = STDIN_FILENO+ 1;
	
	while (1) {
		printf("STATION %s>", ifacesData[0]);
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
			strcpy(bufCpy, buf);
			ptr = strtok(bufCpy, delim);
			int counter = 0;
			while(ptr != NULL) {
				menuData[counter++] = ptr;
				ptr = strtok(NULL, delim);
			}
			if (strcmp(menuData[0],"send") == 0) {
				write(sockfd, buf, strlen(buf)+1);
			} else {
				//printf("NOT WRITING DATA TO SERVER DOING MENU STUFF\n");
				if (strcmp(menuData[0],"show") == 0 && strcmp(menuData[1],"arp\n") == 0) {
					printf("***************************************\n");
					printf("\tARP cache\n");
					printf("***************************************\n");
					//logic here
					printf("EMPTY(TEMP FOR NOW)\n");
					printf("***************************************\n");
				}
				if (strcmp(menuData[1],"pq\n") == 0) {
					printf("***************************************\n");
					printf("\tpending queue\n");
					printf("***************************************\n");
					//logic here
					printf("***************************************\n");
				}
				if (strcmp(menuData[1],"host\n") == 0) {
					printf("***************************************\n");
					printf("\thosts\n");
					printf("***************************************\n");
					hostsFile=fopen(argv[4],"r");
					if (hostsFile == NULL) {
						printf("hosts file not found");
						exit(1);
					} else {
						while(fgets(hostsBuffer, 100, hostsFile) != NULL) {
							printf("%s", hostsBuffer);
						}
					}
					fclose(hostsFile);
					printf("***************************************\n");
				}
				if (strcmp(menuData[1],"iface\n") == 0) {
					printf("***************************************\n");
					printf("\tiface\n");
					printf("***************************************\n");
					ifacesFile=fopen(argv[2],"r");
					if (ifacesFile == NULL) {
						printf("Ifaces file not found");
						exit(1);
					} else {
						while(fgets(ifacesBuffer, 100, ifacesFile) != NULL) {
							printf("%s\n", ifacesBuffer);
						}
					}
					fclose(ifacesFile);
					printf("***************************************\n");
				}
				if (strcmp(menuData[1],"rtable\n") == 0) {
					printf("***************************************\n");
					printf("\trtable\n");
					printf("***************************************\n");
					rtablesFile=fopen(argv[3],"r");
					if (rtablesFile == NULL) {
						printf("rtables file not found");
						exit(1);
					} else {
						while(fgets(rtablesBuffer, 100, rtablesFile) != NULL) {
							printf("%s", rtablesBuffer);
						}
					}
					fclose(rtablesFile);
					printf("\n***************************************\n");
				}
				if (strcmp(menuData[0],"quit\n") == 0) {
					exit(0);
				}
				menuData[0] = "";
				menuData[1] = "";
			}
		}
	}
	return 0;
}